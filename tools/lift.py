#!/usr/bin/env python3
"""Lift a function of efz.exe back to C++ that Visual C++ .NET 2003 /Od compiles to the
same bytes.

Unoptimised MSVC code is a statement-by-statement translation: every statement loads
what it needs into registers, computes, and stores, and control flow is laid out in
source order. This tool runs that code symbolically to recover the statements, then
rebuilds the if/else, loops and switches from where the jumps go.

Memory is accessed through offset casts, `*(short*)((char*)this + 0x14a)`, which compile
exactly like the field access they stand for, so a function can be matched before its
types are known; `--types` uses the field names from src/.

Usage: tools/lift.py 0xADDR [--name Class::Method] [--sig 'BOOL CFile::Open(...)']
"""
import collections
import json
import os
import re
import struct
import subprocess
import sys

import capstone
from capstone import x86 as X
import pefile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, 'tools'))
import funcdiff  # noqa: E402


class LiftError(Exception):
    pass


# --- the original image --------------------------------------------------------------

class Image:
    def __init__(self, path):
        self.path = path
        self.pe = pefile.PE(path)
        self.data = self.pe.get_memory_mapped_image()
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.iat = {i.address: (i.name.decode() if i.name else f'#{i.ordinal}')
                    for d in self.pe.DIRECTORY_ENTRY_IMPORT for i in d.imports}
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.md.detail = True

    def read(self, addr, n):
        return self.data[addr - self.base:addr - self.base + n]

    def u8(self, addr):
        return self.read(addr, 1)[0]

    def u32(self, addr):
        return struct.unpack('<I', self.read(addr, 4))[0]

    def f64(self, addr):
        return struct.unpack('<d', self.read(addr, 8))[0]

    def f32(self, addr):
        return struct.unpack('<f', self.read(addr, 4))[0]

    def cstring(self, addr, limit=4096):
        b = self.read(addr, limit)
        end = b.find(b'\0')
        return b[:end] if end >= 0 else None

    def section_of(self, addr):
        for s in self.pe.sections:
            lo = self.base + s.VirtualAddress
            if lo <= addr < lo + s.Misc_VirtualSize:
                return s.Name.rstrip(b'\0').decode()
        return None


# --- operands ----------------------------------------------------------------------

REG32 = {'eax', 'ecx', 'edx', 'ebx', 'esi', 'edi'}
SUBREG = {'al': ('eax', 1, 0), 'ah': ('eax', 1, 8), 'ax': ('eax', 2, 0),
          'cl': ('ecx', 1, 0), 'ch': ('ecx', 1, 8), 'cx': ('ecx', 2, 0),
          'dl': ('edx', 1, 0), 'dh': ('edx', 1, 8), 'dx': ('edx', 2, 0),
          'bl': ('ebx', 1, 0), 'bh': ('ebx', 1, 8), 'bx': ('ebx', 2, 0),
          'si': ('esi', 2, 0), 'di': ('edi', 2, 0)}


class Op:
    """A decoded operand: ('reg', name, size) / ('imm', value, size) / ('mem', base, index,
    scale, disp, size)."""

    def __init__(self, ins, o):
        self.size = o.size
        if o.type == X.X86_OP_REG:
            self.kind = 'reg'
            self.reg = ins.reg_name(o.reg)
        elif o.type == X.X86_OP_IMM:
            self.kind = 'imm'
            self.imm = o.imm & 0xFFFFFFFF
        else:
            self.kind = 'mem'
            self.base = ins.reg_name(o.mem.base) if o.mem.base else None
            self.index = ins.reg_name(o.mem.index) if o.mem.index else None
            self.scale = o.mem.scale
            self.disp = o.mem.disp
            self.seg = ins.reg_name(o.mem.segment) if o.mem.segment else None

    def __repr__(self):
        if self.kind == 'reg':
            return self.reg
        if self.kind == 'imm':
            return hex(self.imm)
        return f'[{self.base}+{self.index}*{self.scale}+{self.disp:#x}]:{self.size}'


class Ins:
    def __init__(self, ci):
        self.addr = ci.address
        self.size = ci.size
        self.end = ci.address + ci.size
        self.m = ci.mnemonic
        self.text = f'{ci.mnemonic} {ci.op_str}'
        self.ops = [Op(ci, o) for o in ci.operands]

    def __repr__(self):
        return f'{self.addr:#x}: {self.text}'


def decode(img, start, end):
    """Instructions of the function at [start, end), skipping switch tables."""
    data_ranges = []
    out = []
    pc = start
    while pc < end:
        if any(lo <= pc < hi for lo, hi in data_ranges):
            pc = next(hi for lo, hi in data_ranges if lo <= pc < hi)
            continue
        ci = next(img.md.disasm(img.read(pc, 16), pc), None)
        if ci is None:
            raise LiftError(f'cannot decode at {pc:#x}')
        ins = Ins(ci)
        if ins.m == 'int3' and all(img.u8(a) == 0xcc for a in range(pc, end)):
            break
        out.append(ins)
        pc = ins.end
        # jmp dword ptr [reg*4 + table]: the address table, and the byte index table
        # loaded just before it, are data.
        if ins.m == 'jmp' and ins.ops[0].kind == 'mem' and ins.ops[0].index:
            table = ins.ops[0].disp & 0xFFFFFFFF
            prev = out[-2] if len(out) > 1 else None
            ntargets = None
            if prev and prev.m == 'movzx' and prev.ops[1].kind == 'mem' and prev.ops[1].size == 1:
                idx_table = prev.ops[1].disp & 0xFFFFFFFF
                count = switch_bound(out) + 1
                idx = [img.u8(idx_table + k) for k in range(count)]
                ntargets = max(idx) + 1
                data_ranges.append((idx_table, idx_table + count))
            else:
                ntargets = switch_bound(out) + 1
            data_ranges.append((table, table + 4 * ntargets))
    return out, data_ranges


def switch_bound(ins_list):
    """The `cmp x, N; ja default` bound before a switch jump."""
    for ins in reversed(ins_list[-8:]):
        if ins.m == 'cmp' and ins.ops[1].kind == 'imm':
            return ins.ops[1].imm
    raise LiftError(f'no switch bound before {ins_list[-1]}')


# --- C expressions -----------------------------------------------------------------

# Integer types by (size, signed).
ITYPE = {(1, True): 'char', (1, False): 'BYTE', (2, True): 'short', (2, False): 'WORD',
         (4, True): 'int', (4, False): 'DWORD'}
TSIZE = {'char': 1, 'BYTE': 1, 'short': 2, 'WORD': 2, 'int': 4, 'DWORD': 4, 'char*': 4,
         'float': 4, 'double': 8, 'void': 0}
SIGNED = {'char', 'short', 'int'}

PREC = {'call': 16, 'post': 16, 'unary': 15, 'cast': 15, '*': 13, '/': 13, '%': 13, '+': 12,
        '-': 12, '<<': 11, '>>': 11, '<': 10, '<=': 10, '>': 10, '>=': 10, '==': 9, '!=': 9,
        '&': 8, '^': 7, '|': 6, '&&': 5, '||': 4, '?': 3, '=': 2, 'atom': 17}


_CLOCK = [0]


class E:
    """An expression. `ty` is its C type: an integer type from ITYPE, 'char*' for
    pointers (byte arithmetic), 'float', 'double' or 'void'. `t` is the instruction
    index at which it was formed."""
    prec = 17
    ty = 'int'

    def __new__(cls, *args, **kwargs):
        o = object.__new__(cls)
        o.t = _CLOCK[0]
        return o

    def first_time(self):
        """When evaluation of this expression started: its earliest part."""
        return min([self.t] + [u.first_time() for u in self.uses()])

    def text(self, ctx=0):
        s = self.render()
        return f'({s})' if self.prec < ctx else s

    def uses(self):
        return []

    def has_side_effects(self):
        return any(u.has_side_effects() for u in self.uses())

    def weight(self):
        return 1 + sum(u.weight() for u in self.uses())


class Const(E):
    def __init__(self, v, ty='int'):
        self.v, self.ty = v, ty

    def render(self):
        if self.ty == 'float':
            # the shortest decimal that rounds to the same single-precision value
            f32 = struct.unpack('<f', struct.pack('<f', float(self.v)))[0]
            for p in range(1, 18):
                r = f'{f32:.{p}g}'
                if struct.unpack('<f', struct.pack('<f', float(r)))[0] == f32:
                    break
            if 'e' not in r and '.' not in r and 'inf' not in r and 'nan' not in r:
                r += '.0'
            return r + 'f'
        if self.ty in ('double', 'float'):
            r = repr(float(self.v))
            if 'e' not in r and '.' not in r and 'inf' not in r and 'nan' not in r:
                r += '.0'
            return r + ('f' if self.ty == 'float' else '')
        v = self.v
        if self.ty in SIGNED and v >= 0x80000000 and v - (1 << 32) >= -0x10000:
            v -= 1 << 32
        if v < 0:
            return f'-{fmt_int(-v)}'
        return fmt_int(v)


def fmt_int(v):
    return str(v) if v < 10 else hex(v)


class Str(E):
    ty = 'char*'

    def __init__(self, data, addr):
        self.data, self.addr = data, addr

    def render(self):
        return c_string(self.data)


def c_string(b):
    out = []
    try:
        s = b.decode('cp932')
    except UnicodeDecodeError:
        s = None
    if s is not None and all(ch.isprintable() or ch in '\n\r\t' for ch in s):
        for ch in s:
            out.append({'\\': '\\\\', '"': '\\"', '\n': '\\n', '\r': '\\r', '\t': '\\t'}.get(ch, ch))
        return '"' + ''.join(out) + '"'
    return '"' + ''.join(f'\\x{c:02x}' if not (0x20 <= c < 0x7f) or c in b'\\"' else chr(c)
                         for c in b) + '"'


class Var(E):
    """A named variable: local, parameter, `this` or global."""

    def __init__(self, name, ty, kind='local', key=None):
        self.name, self.ty, self.kind, self.key = name, ty, kind, key

    def render(self):
        return self.name


class Deref(E):
    """*(ty*)(addr)"""
    prec = PREC['unary']

    def __init__(self, addr, ty):
        self.addr, self.ty = addr, ty

    def uses(self):
        return [self.addr]

    def render(self):
        a = self.addr
        r = row_access(self)
        if r is not None:
            e = elem_of(r[0])
            if e is not None and e[1] == 0 and isinstance(e[2], tuple):
                return f'{e[0]}[{r[1].text()}]'
        b = a.e if isinstance(a, Cast) else a
        if isinstance(b, AddrOfVar):
            e = elem_of(b.v)
            if e is not None and e[1] == 0 and e[2] == self.ty:
                return e[0]
        if a.ty == f'{self.ty}*':
            return f'*{a.text(PREC["unary"])}'
        return f'*({self.ty}*){a.text(PREC["cast"])}'


class AddrOf(E):
    prec = PREC['unary']
    ty = 'char*'

    def __init__(self, lv):
        self.lv = lv

    def uses(self):
        return [self.lv]

    def render(self):
        return f'(char*)&{self.lv.text(PREC["unary"])}'


class Cast(E):
    prec = PREC['cast']

    def __init__(self, ty, e):
        self.ty, self.e = ty, e

    def uses(self):
        return [self.e]

    def render(self):
        return f'({self.ty}){self.e.text(PREC["cast"])}'


class Bin(E):
    def __init__(self, op, a, b, ty):
        if op in ('+', '-') and (isinstance(a, ThisVar) or
                                 (a.ty != 'char*' and is_pointer_type(a.ty))):
            # byte offsets from a typed pointer
            a, ty = Cast('char*', a), 'char*'
        elif op == '+' and isinstance(b, ThisVar):
            b, ty = Cast('char*', b), 'char*'
        elif op == '+' and b.ty == 'char*' and a.ty != 'char*':
            ty = 'char*'          # int + pointer
        self.op, self.a, self.b, self.ty = op, a, b, ty
        self.prec = PREC[op]

    def uses(self):
        return [self.a, self.b]

    def render(self):
        # Left-associative: the right operand needs parentheses at equal precedence.
        return f'{self.a.text(self.prec)} {self.op} {self.b.text(self.prec + 1)}'


class Un(E):
    prec = PREC['unary']

    def __init__(self, op, a, ty):
        self.op, self.a, self.ty = op, a, ty

    def uses(self):
        return [self.a]

    def render(self):
        return f'{self.op}{self.a.text(PREC["unary"])}'


class Call(E):
    prec = PREC['call']

    def __init__(self, fn, args, this=None, ty='int', virtual=False):
        self.fn, self.args, self.this, self.ty, self.virtual = fn, args, this, ty, virtual

    def uses(self):
        return ([self.this] if self.this is not None else []) + list(self.args)

    def has_side_effects(self):
        return True

    def render(self):
        ptypes = getattr(self, 'ptypes', None) or []
        parts = []
        for n, a in enumerate(self.args):
            t = ptypes[n] if n < len(ptypes) else None
            parts.append(arg_text(a, t))
        args = ', '.join(parts)
        if self.this is not None:
            cls = getattr(self, 'cls', None)
            obj = self.this
            if isinstance(obj, AddrOfVar) and isinstance(obj.v, SlotVar) \
                    and getattr(obj.v.slot, 'cls', None):
                whole = SlotVar(obj.v.slot)
                whole.whole = True
                return f'{whole.text(PREC["post"])}.{self.fn}({args})'
            if cls and not isinstance(obj, ThisVar) and obj.ty != cls + '*':
                return f'(({cls}*){obj.text(PREC["cast"])})->{self.fn}({args})'
            return f'{obj.text(PREC["post"])}->{self.fn}({args})'
        return f'{self.fn}({args})'


def arg_text(a, t):
    """An argument converted to parameter type t where C++ needs a cast."""
    if t is None or t == '...':
        return a.text(PREC['='] + 1)
    if is_pointer_type(t):
        if isinstance(a, Str) and t in ('LPCSTR', 'const char*', 'LPSTR', 'char*'):
            return a.text(PREC['='] + 1)
        if isinstance(a, Const) and a.v == 0:
            return '0'
        if a.ty == t:
            return a.text(PREC['='] + 1)
        return f'({t}){a.text(PREC["cast"])}'
    if a.ty in ('char*',) or is_pointer_type(a.ty) or is_pointer_type(late_type(a)):
        return f'({t}){a.text(PREC["cast"])}'
    return a.text(PREC['='] + 1)


def late_type(a):
    """The type of an expression as rendered: locals' types are only settled after
    lifting (a pointer local plus an offset is a pointer)."""
    if isinstance(a, SlotVar):
        return a.ty
    if isinstance(a, Bin) and a.op in ('+', '-'):
        if is_pointer_type(late_type(a.a)):
            return late_type(a.a)
        if a.op == '+' and is_pointer_type(late_type(a.b)):
            return late_type(a.b)
    return a.ty


class Cond(E):
    """A relational or logical expression with an int value."""

    def __init__(self, op, a, b=None):
        self.op, self.a, self.b = op, a, b
        self.ty = 'int'
        self.prec = PREC['unary'] if op == '!' else PREC[op]

    def uses(self):
        return [self.a] + ([self.b] if self.b is not None else [])

    def render(self):
        if self.op == '!':
            return f'!{self.a.text(PREC["unary"])}'
        if isinstance(self.a, Const) and isinstance(self.b, Const) and self.op in NEGATE:
            # a constant condition: `if (0)` around code left in
            v = {'==': self.a.v == self.b.v, '!=': self.a.v != self.b.v}.get(self.op)
            if v is not None:
                return '1' if v else '0'
        return f'{self.a.text(self.prec)} {self.op} {self.b.text(self.prec + 1)}'


class AssignExpr(E):
    """An assignment used as a value: (x = e)."""
    prec = PREC['=']

    def __init__(self, lhs, rhs):
        self.lhs, self.rhs = lhs, rhs
        self.ty = rhs.ty

    def uses(self):
        return [self.lhs, self.rhs]

    def has_side_effects(self):
        return True

    def render(self):
        return f'{self.lhs.text(PREC["="] + 1)} = {self.rhs.text(PREC["="])}'


class Ternary(E):
    prec = PREC['?']

    def __init__(self, c, a, b):
        self.c, self.a, self.b = c, a, b
        self.ty = 'int'

    def uses(self):
        return [self.c, self.a, self.b]

    def render(self):
        return f'{self.c.text(PREC["?"] + 1)} ? {self.a.text(PREC["?"])} : {self.b.text(PREC["?"])}'


NEGATE = {'==': '!=', '!=': '==', '<': '>=', '>=': '<', '>': '<=', '<=': '>'}


def negate(c):
    if isinstance(c, Cond):
        if c.op in NEGATE:
            return Cond(NEGATE[c.op], c.a, c.b)
        if c.op == '!':
            return c.a
        if c.op == '&&':
            return Cond('||', negate(c.a), negate(c.b))
        if c.op == '||':
            return Cond('&&', negate(c.a), negate(c.b))
    return Cond('!', c)


def truth(e):
    """e as a condition: `x != 0` reads better as `x`."""
    return e


# --- statements --------------------------------------------------------------------

class S:
    addr = None


class Assign(S):
    def __init__(self, lhs, rhs, op=''):
        self.lhs, self.rhs, self.op = lhs, rhs, op

    def lines(self):
        if self.op == '+' and isinstance(self.rhs, Const) and self.rhs.v == 1:
            return [f'{self.lhs.text(PREC["post"])}++;']
        if self.op == '-' and isinstance(self.rhs, Const) and self.rhs.v == 1:
            return [f'{self.lhs.text(PREC["post"])}--;']
        rhs = self.rhs
        lt, rt = self.lhs.ty, rhs.ty
        if lt != rt and (is_pointer_type(lt) != is_pointer_type(rt)) and lt != 'this' \
                and not (isinstance(rhs, Const) and rhs.v == 0) and lt not in ('double', 'float') \
                and rt not in ('double', 'float'):
            rhs = Cast(lt, rhs)
        elif lt == 'char*' and is_pointer_type(rt) and rt != 'char*' and not self.op:
            rhs = Cast(lt, rhs)       # a typed pointer into a byte pointer
        return [f'{self.lhs.text(PREC["="])} {self.op}= {rhs.text(PREC["="])};']


class ExprStmt(S):
    def __init__(self, e):
        self.e = e

    def lines(self):
        return [f'{self.e.text()};']


class Return(S):
    def __init__(self, e=None):
        self.e = e

    def lines(self):
        return ['return;' if self.e is None else f'return {self.e.text()};']


class Asm(S):
    def __init__(self, text):
        self.text = text

    def lines(self):
        return [self.text]


# --- symbols -----------------------------------------------------------------------

class Symbols:
    """What the lifter knows about addresses: annotated functions and globals in src/,
    imports, and the stdcall argument sizes of imported functions."""

    def __init__(self, img):
        self.img = img
        known = funcdiff.read_annotations(os.path.join(REPO, 'src'))
        self.funcs = {addr: name for name, (kind, addr) in known.items() if kind == 'FUNCTION'}
        self.globals = {addr: name for name, (kind, addr) in known.items() if kind == 'GLOBAL'}
        self.crt = {}
        self.protos = Protos()
        self.vtables = set()
        import progress
        self.inventory = progress.inventory(img.path)
        if self.inventory:
            self.vtables = {v['addr'] for v in self.inventory['vtables']}
        # virtual calls through a CPlayer: argument bytes per slot, from the
        # implementations' `ret N`
        self.vclass = 'CPlayer'
        self.char_vtable = 0x787df8
        self.vtables |= {0x787bcc}

    def func_name(self, addr):
        return self.funcs.get(addr)

    def infer_proto(self, img, addr, name):
        """Signature of a function nobody has declared yet, from lifting it."""
        cache = self.__dict__.setdefault('_inferred', {})
        if addr in cache or not 0x401000 <= addr < 0x77697e:
            return
        cache[addr] = None          # guards recursion
        clock = _CLOCK[0]
        try:
            lf = Lifter2(img, self, addr, function_end(self, addr))
            lf.execute(None)
            this, ret, params = infer_signature(lf)
        except Exception:
            return
        finally:
            _CLOCK[0] = clock
        cache[addr] = (ret, params)
        self.protos.methods[name] = [ret, params]


CC_SIGNED = {'jl': '<', 'jle': '<=', 'jg': '>', 'jge': '>=', 'je': '==', 'jne': '!=',
             'jb': '<', 'jbe': '<=', 'ja': '>', 'jae': '>=', 'jz': '==', 'jnz': '!=',
             'js': '<', 'jns': '>='}
UNSIGNED_CC = {'jb', 'jbe', 'ja', 'jae'}
SETCC = {'sete': 'je', 'setne': 'jne', 'setl': 'jl', 'setle': 'jle', 'setg': 'jg',
         'setge': 'jge', 'setb': 'jb', 'setbe': 'jbe', 'seta': 'ja', 'setae': 'jae'}


class Slot:
    """A stack slot ([ebp+off]): a local, a parameter or `this`."""

    def __init__(self, off):
        self.off = off
        self.sizes = collections.Counter()
        self.signed = collections.Counter()
        self.pointer = False
        self.float = None
        self.array = None       # element size when indexed
        self.unsigned_cmp = 0
        self.signed_cmp = 0
        self.name = None
        self.kind = 'param' if off > 0 else 'local'

    def ctype(self):
        if self.name == 'this':
            return None
        if getattr(self, 'declared', None):
            return self.declared
        if self.float:
            return self.float
        if self.pointer:
            return 'char*'
        size = self.sizes.most_common(1)[0][0] if self.sizes else 4
        if size == 8:
            return 'double'
        signed = True
        if self.signed:
            signed = self.signed.most_common(1)[0][0]
        if size == 4 and self.unsigned_cmp > self.signed_cmp:
            signed = False
        return ITYPE[(size if size in (1, 2, 4) else 4, signed)]


class Lifter:
    def __init__(self, img, syms, start, end, this_type=None):
        self.img, self.syms = img, syms
        self.start, self.end = start, end
        self.ins, self.data_ranges = decode(img, start, end)
        self.slots = {}
        self.items = []
        self.this_slot = None
        self.cookie_slot = None
        self.saved = []
        self.this_type = this_type
        self.frame_size = 0
        self.ret_pop = 0
        self.notes = []

    # frame -----------------------------------------------------------------------

    def slot(self, off):
        s = self.slots.get(off)
        if s is None:
            s = self.slots[off] = Slot(off)
            # inside a struct local of a declared type: one of its fields
            for t in self.slots.values():
                if getattr(t, 'struct_type', None) in layouts().structs \
                        and t.off < off < t.off + t.struct_size:
                    s.parent = t
                    break
        return s

    def analyze_frame(self):
        ins = self.ins
        if not (ins[0].m == 'push' and ins[0].ops[0].reg == 'ebp' and ins[1].m == 'mov'):
            raise LiftError('no ebp frame')
        k = 2
        if ins[k].m == 'sub' and ins[k].ops[0].kind == 'reg' and ins[k].ops[0].reg == 'esp':
            self.frame_size = ins[k].ops[1].imm
            k += 1
        elif ins[k].m == 'push' and ins[k].ops[0].kind == 'reg' and ins[k].ops[0].reg == 'ecx':
            self.frame_size = 4       # `push ecx` reserves one slot
            k += 1
        elif ins[k].m == 'mov' and ins[k].ops[0].kind == 'reg' and ins[k].ops[0].reg == 'eax' \
                and ins[k + 1].m == 'call':
            self.frame_size = ins[k].ops[1].imm   # _chkstk for big frames
            k += 2
        body = k
        # /GS: mov eax, [___security_cookie]; mov [ebp-4], eax  (may come before or after
        # the register saves)
        for j in range(k, min(k + 6, len(ins))):
            a, b = ins[j], ins[j + 1] if j + 1 < len(ins) else None
            if a.m == 'mov' and a.ops[1].kind == 'mem' and a.ops[1].base is None \
                    and (a.ops[1].disp & 0xFFFFFFFF) == 0x78f050 and b and b.m == 'mov' \
                    and b.ops[0].kind == 'mem' and b.ops[0].base == 'ebp':
                self.cookie_slot = b.ops[0].disp
                self.cookie_range = (a.addr, b.end)
        if self.cookie_slot is not None and ins[body].addr == self.cookie_range[0]:
            body += 2          # the cookie is stored before the registers are saved
        while ins[body].m == 'push' and ins[body].ops[0].kind == 'reg' \
                and ins[body].ops[0].reg in ('ebx', 'esi', 'edi'):
            self.saved.append(ins[body].ops[0].reg)
            body += 1
        self.body_start = body
        # `this`: mov [ebp-x], ecx in the first instructions, before anything else writes
        # ecx or jumps
        for j in range(k, min(k + 8, len(ins))):
            a = ins[j]
            if a.m == 'mov' and a.ops[0].kind == 'mem' and a.ops[0].base == 'ebp' \
                    and a.ops[1].kind == 'reg' and a.ops[1].reg == 'ecx':
                self.this_slot = a.ops[0].disp
                self.this_store = a.addr
                break
            if a.m.startswith('j') or (a.ops and a.ops[0].kind == 'reg'
                                       and SUBREG.get(a.ops[0].reg, (a.ops[0].reg,))[0] == 'ecx'):
                break
        # epilogue: the last `mov esp, ebp; pop ebp; ret`
        for j in range(len(ins) - 1, 0, -1):
            if ins[j].m == 'ret':
                self.ret_pop = ins[j].ops[0].imm if ins[j].ops else 0
                e = j - 1
                if ins[e].m == 'pop' and ins[e].ops[0].reg == 'ebp':
                    e -= 1
                if ins[e].m == 'mov' and ins[e].ops[0].kind == 'reg' and ins[e].ops[0].reg == 'esp':
                    e -= 1
                while ins[e].m == 'pop' and ins[e].ops[0].reg in ('ebx', 'esi', 'edi'):
                    e -= 1
                if ins[e].m == 'call' and self.cookie_slot is not None:
                    e -= 2                          # mov ecx, [ebp-4]; call check_cookie
                self.epilogue = ins[e + 1].addr
                self.ret_index = j
                break
        else:
            raise LiftError('no ret')

    # values ----------------------------------------------------------------------

    def var(self, off):
        if off == self.this_slot:
            return ThisVar()
        return SlotVar(self.slot(off))

    def lvalue(self, op, ty=None, record=True):
        """The C lvalue for a memory operand, typed by its size (ty overrides)."""
        size = op.size if record else 0
        if ty is None:
            ty = ITYPE.get((size, True), 'int') if size in (1, 2, 4) else 'double'
        if op.base == 'ebp' and op.index is None:
            v = self.var(op.disp)
            if isinstance(v, SlotVar) and size:
                v.slot.sizes[size] += 1
            return v
        if op.base == 'ebp':
            s = self.slot(op.disp)
            s.array = op.scale
            if size:
                s.sizes[size] += 1
            idx = self.reg_value(op.index)
            return Index(SlotVar(s), idx, ty)
        if op.base is None and op.index is None:
            addr = op.disp & 0xFFFFFFFF
            return self.global_var(addr, ty)
        base = self.reg_value(op.base) if op.base else None
        if isinstance(base, StructResult):
            return StructField(base, op.disp, ty)
        row = getattr(base, 'row', None)
        if row is not None and op.index and size:
            r = Row2D.make(row, self.reg_value(op.index), op.scale, ty, size, op.disp)
            if r is not None:
                return r
        index = self.reg_value(op.index) if op.index else None
        if base is not None and index is not None and op.scale == 1 \
                and is_offset(base) and not is_offset(index):
            # [ecx+eax]: the compiler put the offset in the base register
            base, index = index, base
        addr = None
        if base is not None:
            addr = as_pointer(base)
        if op.index:
            term = index
            if op.scale != 1:
                term = Bin('*', term, Const(op.scale), 'int')
            if addr is not None and op.disp and not isinstance(base, ThisVar) \
                    and base.t < term.first_time():
                # p->array[i]: the compiler adds the member offset to p, which makes
                # p the heavier operand and so evaluated first
                addr = Bin('+', Bin('+', addr, Const(op.disp), 'char*'), term, 'char*')
                return Deref(addr, ty)
            addr = term if addr is None else Bin('+', addr, term, 'char*')
        if op.disp:
            d = Const(op.disp & 0xFFFFFFFF if addr is None else op.disp)
            addr = d if addr is None else Bin('+', addr, d, 'char*')
        if addr.ty != 'char*':
            addr = Cast('char*', addr)
        return Deref(addr, ty)

    def global_var(self, addr, ty):
        name = self.syms.globals.get(addr)
        if name:
            return Var(name.split('::')[-1], ty, 'global', addr)
        return Deref(Cast('char*', Const(addr)), ty)

    def reg_value(self, r):
        if r in REG32:
            v = self.regs.get(r)
            if v is None:
                raise LiftError(f'{r} undefined at {self.pc:#x}')
            return v
        parent, size, shift = SUBREG[r]
        v = self.regs.get(parent)
        if v is None:
            raise LiftError(f'{r} undefined at {self.pc:#x}')
        if shift:
            raise LiftError(f'high byte {r} at {self.pc:#x}')
        return v

    def value(self, op, signed=None):
        if op.kind == 'imm':
            return self.imm_value(op.imm, op.size)
        if op.kind == 'reg':
            return self.reg_value(op.reg)
        lv = self.lvalue(op)
        return lv

    def imm_value(self, v, size=4):
        if 0x787000 <= v < 0x7b4000:
            first = self.img.u32(v) if self.img.section_of(v) == '.rdata' else 0
            if v in self.syms.vtables or (0x401000 <= first < 0x786500 and (
                    first in self.syms.funcs
                    or self.img.data[first - 0x400000:first - 0x400000 + 3] == b'\x55\x8b\xec')):
                self.syms.vtables.add(v)       # a table of code pointers: a vtable
                return Cast('char*', Const(v))
            if v in self.syms.globals:
                return AddrOf(self.global_var(v, 'int'))
            s = self.img.cstring(v, 2048)
            if self.img.section_of(v) == '.rdata' and s is not None and looks_like_text(s):
                return Str(s, v)
            return Cast('char*', Const(v))
        if size == 1 and v >= 0x80:
            v -= 0x100
        if size == 2 and v >= 0x8000:
            v -= 0x10000
        return Const(v)

    def set_reg(self, r, e):
        self.dirty.add(SUBREG.get(r, (r,))[0])
        if SUBREG.get(r, (r,))[0] == 'eax':
            self.last = 'eax'
            self.eax_size = SUBREG[r][1] if r in SUBREG else 4
        if r in REG32:
            old = self.regs.get(r)
            if old is not None and old is not e:
                self.flush_if_pending(old, e)
            self.regs[r] = e
        else:
            parent, size, shift = SUBREG[r]
            self.regs[parent] = e

    def flush_if_pending(self, old, new):
        """A call result about to be overwritten without being used: emit the call."""
        for c in list(self.pending):
            if c is old and not contains(new, c):
                # still held elsewhere (copied to another register, or an argument)?
                held = [v for v in self.regs.values() if v is not old] + list(self.fpu) \
                    + list(self.args) + list(self.forward.values())
                if any(contains(v, c) for v in held if isinstance(v, E)):
                    continue
                self.incoming = new     # (other calls inside the new value stay pending)
                try:
                    self.emit(ExprStmt(c))
                finally:
                    self.incoming = None

    def emit(self, stmt):
        stmt.addr = self.cur_stmt_addr
        for c in list(self.pending):
            if contains_stmt(stmt, c):
                self.pending.remove(c)
        # calls not consumed by this statement happened before it, unless their value
        # is still on its way into a later one
        rest = list(self.pending)
        self.pending = []
        held = list(self.regs.values()) + list(self.fpu) + list(self.args) \
            + list(self.forward.values()) + [getattr(self, 'incoming', None)]
        for c in rest:
            # (a register holding just the call's return value is the normal pending
            # state; an expression built on it is still being evaluated)
            if any(isinstance(v, E) and v is not c and not (isinstance(v, Cast) and v.e is c)
                   and contains(v, c) for v in held):
                self.pending.append(c)
                continue
            self.items.append(('stmt', ExprStmt(c), stmt.addr))
        self.items.append(('stmt', stmt, stmt.addr))
        self.cur_stmt_addr = None

    def consume(self, e):
        for c in list(self.pending):
            if contains(e, c):
                self.pending.remove(c)

    def flush_pending(self):
        for c in self.pending:
            self.items.append(('stmt', ExprStmt(c), self.pc))
        self.pending = []


class ThisVar(E):
    ty = 'this'

    def render(self):
        return 'this'


class SlotVar(E):
    def __init__(self, slot):
        self.slot = slot

    @property
    def ty(self):
        return self.slot.ctype() or 'int'

    def render(self):
        parent = getattr(self.slot, 'parent', None)
        if parent is not None:
            off = self.slot.off - parent.off
            return field_ref(parent, off, self.slot)
        if getattr(self.slot, 'struct_size', None) and not getattr(self, 'whole', False):
            return field_ref(self.slot, 0, self.slot)
        ct = getattr(self, 'copy_type', None)
        if ct and getattr(self.slot, 'struct_type', None) not in (None, ct):
            # a struct copied into a struct local's first member
            f = layouts().field(self.slot.struct_type, 0)
            if f:
                return f'{self.slot.name or f"l_{-self.slot.off:x}"}.{f}'
        if self.slot.name:
            return self.slot.name
        if self.slot.off > 0:
            return f'p{(self.slot.off - 8) // 4 + 1}'
        return f'l_{-self.slot.off:x}'


RECT_FIELDS = {0: 'left', 4: 'top', 8: 'right', 12: 'bottom'}


def field_ref(st, off, member):
    name = st.name or f'l_{-st.off:x}'
    S = getattr(st, 'elem_stride', None)
    if S:
        t = member_text(f'{name}[{off // S}]', off % S, st.elem)
        if t:
            return t
    if st.array and getattr(st, 'fixed_len', None) and off % st.array == 0:
        return f'{name}[{off // st.array}]'
    fields = STRUCT_FIELDS.get(getattr(st, 'struct_type', None), {})
    if off in fields:
        return f'{name}.{fields[off]}'
    f = layouts().field(getattr(st, 'struct_type', None) or getattr(st, 'cls', None), off)
    if f:
        return f'{name}.{f}'
    ty = member.ctype() if member is not st else 'int'
    return f'*({ty}*)((char*)&{name} + {off})'


class Row2D(E):
    """((T(*)[n])(p + K))[i][j]: a two-dimensional array member, its row's address
    worked out first (lea r, [p + i*R + K]) and then indexed."""
    prec = PREC['post']

    @staticmethod
    def make(row, j, scale, ty, size, extra=0):
        base, term, disp = row
        if not (isinstance(term, Bin) and term.op == '*' and isinstance(term.b, Const)):
            return None
        rbytes = term.b.v
        if rbytes % size or scale % size or extra % size:
            return None
        r = Row2D()
        r.base, r.i, r.j, r.ty = base, term.a, j, ty
        r.n, r.k, r.mul, r.add = rbytes // size, disp, scale // size, extra // size
        return r

    def uses(self):
        return [self.base, self.i, self.j]

    def render(self):
        b = self.base
        bt = b.text(PREC['cast']) if b.ty == 'char*' else f'(char*){b.text(PREC["cast"])}'
        j = self.j.text(PREC['+']) if self.mul == 1 else f'{self.j.text(PREC["*"])} * {self.mul}'
        if self.add:
            j = f'{j} + {self.add}'
        return f'(({self.ty}(*)[{fmt_int(self.n)}])({bt} + {fmt_int(self.k)}))[{self.i.text()}][{j}]'


class Index(E):
    prec = PREC['post']

    def __init__(self, arr, idx, ty):
        self.arr, self.idx, self.ty = arr, idx, ty

    def uses(self):
        return [self.arr, self.idx]

    def render(self):
        e = elem_of(self)
        if e is not None:
            t = member_text(e[0], e[1], e[2])
            if t:
                return t
        return f'{self.arr.text(PREC["post"])}[{self.idx.text()}]'


def base_call(obj, name):
    """Whether `obj` is this + the offset of the base class that `name` belongs to,
    which a call from a derived class's method adjusts to without writing it."""
    import objdefs
    if not (isinstance(obj, Bin) and obj.op == '+' and isinstance(obj.b, Const)
            and isinstance(obj.a, Cast) and isinstance(obj.a.e, ThisVar)) or '::' not in name:
        return False
    base = name.rsplit('::', 1)[0]
    return any(off == obj.b.v and b == base for (_c, off), b in objdefs.BASES.items())


# structs whose locals are recognized by their address being passed for a parameter
# of that type (their fields are other locals until then)
LOCAL_STRUCTS = {'CollisionInfo'}

# COM methods that fill a caller's buffer: (buffer argument, size argument)
BUFFER_ARGS = {'GetDeviceState': (1, 0)}
BUFFER_CALLS = {'CFile::Read': (0, 1)}


def load_cost(e):
    """Memory loads in an expression (a rough measure of how heavy it is to evaluate)."""
    n = 0
    for x in walk_expr(e):
        if isinstance(x, (Deref, SlotVar, Var, ThisVar, Index)):
            n += 1
    return n


def static_type(e, own):
    """The declared type of an expression built from `this` by field loads, as far as
    the layouts in efz.h tell (or None)."""
    if isinstance(e, ThisVar):
        return own + '*' if own else None
    if isinstance(e, Cast):
        if e.ty not in ('char*', 'int', 'DWORD'):
            return e.ty
        return static_type(e.e, own)
    if isinstance(e, Deref):
        a, off = e.addr, 0
        if isinstance(a, Bin) and a.op == '+' and isinstance(a.b, Const):
            a, off = a.a, a.b.v
        base = static_type(a, own)
        if base and base.endswith('*'):
            return layouts().field_type(base[:-1], off)
    return None


def is_offset(v):
    """An index computation rather than a pointer: i * size, or a constant."""
    if isinstance(v, Const):
        return True
    return isinstance(v, Bin) and v.op in ('*', '<<') and v.ty != 'char*'


def is_this_field(lv, off):
    a = lv.addr
    if isinstance(a, Cast) and isinstance(a.e, ThisVar):
        return off == 0
    return isinstance(a, Bin) and a.op == '+' and isinstance(a.a, Cast) and isinstance(a.a.e, ThisVar) \
        and isinstance(a.b, Const) and a.b.v == off


def as_pointer(e):
    if isinstance(e, SlotVar):
        if e.slot.off > 0:
            return Cast('char*', e)
        e.slot.pointer = True
        return e
    if isinstance(e, ThisVar):
        return Cast('char*', e)
    if isinstance(e, Deref) and e.ty in ('int', 'DWORD'):
        e.ty = 'char*'
        return e
    if e.ty == 'char*':
        return e
    return Cast('char*', e)


def looks_like_text(b):
    if not b:
        return False
    try:
        s = b.decode('cp932')
    except UnicodeDecodeError:
        return False
    return all(ch.isprintable() or ch in '\n\r\t' for ch in s)


def contains(e, target):
    if e is target:
        return True
    return any(contains(u, target) for u in e.uses())


def contains_stmt(s, target):
    for attr in ('lhs', 'rhs', 'e'):
        v = getattr(s, attr, None)
        if isinstance(v, E) and contains(v, target):
            return True
    return False


ARITH = {'add': '+', 'sub': '-', 'imul': '*', 'and': '&', 'or': '|', 'xor': '^',
         'shl': '<<', 'sar': '>>', 'shr': '>>'}
FARITH = {'fadd': '+', 'fsub': '-', 'fmul': '*', 'fdiv': '/', 'faddp': '+', 'fsubp': '-',
          'fmulp': '*', 'fdivp': '/', 'fiadd': '+', 'fisub': '-', 'fimul': '*', 'fidiv': '/'}
FARITH_R = {'fsubr': '-', 'fdivr': '/', 'fsubrp': '-', 'fdivrp': '/', 'fisubr': '-',
            'fidivr': '/'}
# FPU instructions that read an integer from memory
FINT_OPS = ('fild', 'fiadd', 'fisub', 'fimul', 'fidiv', 'fisubr', 'fidivr', 'ficomp', 'ficom')
# fnstsw ax; test ah, mask; jcc  ->  relation of st(0) to the fcomp operand
FTEST = {(0x01, 'jne'): '<', (0x01, 'je'): '>=', (0x05, 'jp'): '>=', (0x05, 'jnp'): '<',
         (0x41, 'jne'): '<=', (0x41, 'je'): '>', (0x41, 'jp'): '>', (0x41, 'jnp'): '<=',
         (0x44, 'jp'): '!=', (0x44, 'jnp'): '=='}


def same(a, b):
    """Structural equality of two expressions."""
    if a is b:
        return True
    if type(a) is not type(b):
        return False
    if isinstance(a, ThisVar):
        return True
    if isinstance(a, SlotVar):
        return a.slot is b.slot
    if isinstance(a, Var):
        return a.name == b.name
    if isinstance(a, Const):
        return a.v == b.v
    if isinstance(a, Str):
        return a.addr == b.addr
    if isinstance(a, Deref):
        # pointer and integer loads of the same 4 bytes read the same thing
        wide = ('int', 'DWORD', 'char*', 'this')
        return (a.ty == b.ty or (a.ty in wide and b.ty in wide)) and same(a.addr, b.addr)
    if isinstance(a, Cast):
        return a.ty == b.ty and same(a.e, b.e)
    if isinstance(a, Bin):
        return a.op == b.op and same(a.a, b.a) and same(a.b, b.b)
    if isinstance(a, Index):
        return same(a.arr, b.arr) and same(a.idx, b.idx)
    return False


class Lifter2(Lifter):
    def jump_targets(self):
        t = set()
        for k, ins in enumerate(self.ins):
            if ins.m.startswith('j') and ins.ops and ins.ops[0].kind == 'imm':
                prev = self.ins[k - 1]
                if ins.m == 'jns' and prev.m == 'and' and prev.ops[1].kind == 'imm' \
                        and prev.ops[1].imm & 0x80000000:
                    continue
                t.add(ins.ops[0].imm)
        for lo, hi in self.data_ranges:
            pass
        for tbl in self.switch_tables():
            t.update(tbl['targets'].values())
            t.add(tbl['default'])
        return t

    def switch_tables(self):
        if hasattr(self, '_tables'):
            return self._tables
        self._tables = []
        for k, ins in enumerate(self.ins):
            if ins.m == 'jmp' and ins.ops[0].kind == 'mem' and ins.ops[0].index:
                table = ins.ops[0].disp & 0xFFFFFFFF
                prev = self.ins[k - 1]
                j = k - 1
                idx_table = None
                if prev.m == 'movzx':
                    idx_table = prev.ops[1].disp & 0xFFFFFFFF
                    j -= 1
                # back to `cmp [tmp], N; ja default`
                while not (self.ins[j].m == 'ja'):
                    j -= 1
                default = self.ins[j].ops[0].imm
                bound = self.ins[j - 1].ops[1].imm
                targets = {}
                for v in range(bound + 1):
                    e = self.img.u8(idx_table + v) if idx_table is not None else v
                    targets[v] = self.img.u32(table + 4 * e)
                self._tables.append({'jmp': ins.addr, 'ja': self.ins[j].addr, 'targets': targets,
                                     'default': default, 'cmp': self.ins[j - 1]})
        return self._tables

    def callee_info(self, addr):
        """(stack bytes popped by `ret`, thiscall?) for a function in the image."""
        cache = self.syms.__dict__.setdefault('callee_cache', {})
        if addr in cache:
            return cache[addr]
        thiscall = False
        pop = 0
        pc = addr
        ecx_written = False
        for ci in self.img.md.disasm(self.img.read(addr, 0x40000), addr):
            if ci.address < addr + 40 and not ecx_written:
                if ci.mnemonic == 'mov' and ci.op_str.endswith(', ecx') and 'ebp' in ci.op_str:
                    thiscall = True
                elif re.match(r'(mov|lea|xor|movzx|movsx|add|sub|pop) (ecx|cx|cl),', ci.mnemonic + ' ' + ci.op_str):
                    ecx_written = True
            if ci.mnemonic == 'ret':
                pop = int(ci.op_str, 16) if ci.op_str else 0
                break
            if ci.mnemonic == 'int3':
                break
        cache[addr] = (pop, thiscall)
        return pop, thiscall

    # execution --------------------------------------------------------------------

    def execute(self, ret_type=None):
        self.analyze_frame()
        self.targets = self.jump_targets()
        self.regs, self.fpu, self.flags, self.args, self.pending = {}, [], None, [], []
        self.cur_stmt_addr = None
        self.copy = None
        self.arg_block = None
        self.ret_types = []
        self.forward = {}
        self.pads = self.__dict__.get('pads', {})
        self.ret_type = ret_type
        self.dirty = set()
        skip = {self.this_store} if self.this_slot is not None else set()
        if self.cookie_slot is not None:
            skip.update(i.addr for i in self.ins if self.cookie_range[0] <= i.addr < self.cookie_range[1])
        tables = {t['jmp']: t for t in self.switch_tables()}
        k = self.body_start
        while k < len(self.ins):
            ins = self.ins[k]
            self.pc = ins.addr
            if ins.addr >= self.epilogue:
                break
            if ins.addr in self.targets:
                self.flush_pending()
                self.items.append(('label', ins.addr))
                self.regs, self.fpu, self.flags = {}, [], None
            if ins.addr in skip:
                k += 1
                continue
            pad = self.pads.get(ins.addr)
            if pad and not self.fpu and not self.args and not self.forward:
                # a statement starts here (a finished call still pending is a
                # statement of its own)
                self.flush_pending()
                self.items.append(('stmt', PadStmt(pad), ins.addr))
                self.cur_stmt_addr = None
            if self.cur_stmt_addr is None:
                self.cur_stmt_addr = ins.addr
            k = self.step(k, tables)
        self.finish_return(self.epilogue)
        if self.epilogue in self.targets:
            self.items.append(('label', self.epilogue))
        for sl in list(self.slots.values()):
            src = getattr(sl, 'provisional_src', None)
            if src is not None and not getattr(src, 'consumed', False):
                sl.temp = False     # r = f(); r used as itself
        return self.items

    def finish_return(self, at):
        """Leaving for the epilogue: a value computed and not stored is returned."""
        val = None
        if getattr(self, 'last', None) == 'st0' and self.fpu and 'st0' in self.dirty:
            val = self.fpu[-1]
        elif 'eax' in self.dirty and self.regs.get('eax') is not None:
            val = self.regs['eax']
        elif self.fpu and 'st0' in self.dirty:
            val = self.fpu[-1]
        if val is not None and (self.ret_type != 'void'):
            if any(val is c for c in self.pending) and self.ret_type is None:
                self.flush_pending()
            else:
                self.emit(Return(val))
                ty = val.ty if not isinstance(val, Cond) else 'int'
                size = getattr(self, 'eax_size', 4) if val is self.regs.get('eax') else 4
                if size < 4 and ty not in ('char', 'BYTE', 'short', 'WORD'):
                    ty = {1: 'char', 2: 'short'}[size]
                self.ret_types.append(ty)
                self.dirty = set()
                return True
        self.flush_pending()
        return False

    def slot_read(self, off):
        """Whether any instruction other than a store reads [ebp+off]."""
        cache = self.__dict__.setdefault('_slot_reads', None)
        if cache is None:
            cache = self._slot_reads = set()
            for ins in self.ins:
                for n, o in enumerate(ins.ops):
                    if o.kind == 'mem' and o.base == 'ebp':
                        store = n == 0 and ins.m in ('mov', 'fstp', 'fst', 'fistp', 'fist')
                        if not store:
                            cache.add(o.disp)
        return off in cache

    def mem_copy(self, k):
        """mov r,[s]; mov [d],r; mov r,[s+4]; mov [d+4],r; ...: an inline struct copy
        from an address in a register to another one, or to stack slots. Returns the
        number of bytes, or 0."""
        n = 0
        d0 = None
        while k + 1 < len(self.ins):
            a, b = self.ins[k], self.ins[k + 1]
            if not (a.m == 'mov' and b.m == 'mov' and a.ops[0].kind == 'reg' and a.ops[1].kind == 'mem'
                    and b.ops[0].kind == 'mem' and b.ops[1].kind == 'reg'
                    and a.ops[0].reg == b.ops[1].reg and a.ops[0].size == 4
                    and a.ops[1].index is None and b.ops[0].index is None
                    and a.ops[1].base not in (None, 'esp') and b.ops[0].base not in (None, 'esp')
                    and not (a.ops[1].base == 'ebp' and b.ops[0].base == 'ebp')):
                break
            if d0 is None:
                d0, s0 = b.ops[0].disp, a.ops[1].disp
                if a.ops[1].base != 'ebp' and s0 != 0:
                    break
            if a.ops[1].disp != s0 + n:
                break
            if b.ops[0].disp != d0 + n or (b.ops[0].base != 'ebp' and d0 != 0):
                break
            if n and (a.ops[1].base != self.ins[k - 2].ops[1].base
                      or b.ops[0].base != self.ins[k - 1].ops[0].base):
                break
            n += 4
            k += 2
            if a.ops[0].reg in (a.ops[1].base, b.ops[0].base):
                break     # the address register was reused: this was the last pair
        return n

    def compare_chain(self, k):
        """mov [tmp], r; cmp [tmp], v1; je c1; cmp [tmp], v2; je c2; ...; jmp d: a switch
        compiled as compares. Returns (cases, default, next k) or None."""
        ins = self.ins[k]
        tmp = ins.ops[0]
        if not (ins.m == 'cmp' and tmp.kind == 'mem' and tmp.base == 'ebp' and tmp.index is None
                and ins.ops[1].kind == 'imm' and k > 0):
            return None
        prev = self.ins[k - 1]
        if not (prev.m == 'mov' and prev.ops[0].kind == 'mem' and prev.ops[0].base == 'ebp'
                and prev.ops[0].disp == tmp.disp and prev.ops[1].kind == 'reg'):
            return None
        def is_cmp(j):
            x = self.ins[j] if j < len(self.ins) else None
            return x is not None and x.m == 'cmp' and x.ops[0].kind == 'mem' \
                and x.ops[0].base == 'ebp' and x.ops[0].disp == tmp.disp and x.ops[1].kind == 'imm'

        def val(j):
            v = self.ins[j].ops[1].imm & ((1 << (8 * tmp.size)) - 1)
            return v - (1 << (8 * tmp.size)) if v >= 1 << (8 * tmp.size - 1) else v

        cases, j, outs = [], k, []
        while j + 1 < len(self.ins) and is_cmp(j):
            if self.ins[j + 1].m == 'je':
                cases.append((val(j), self.ins[j + 1].ops[0].imm))
                j += 2
            elif self.ins[j + 1].m == 'jl' and is_cmp(j + 2) and self.ins[j + 3].m == 'jle':
                # case lo: ... case hi: (one body): a range check
                lo, hi = val(j), val(j + 2)
                outs.append(self.ins[j + 1].ops[0].imm)
                cases += [(v, self.ins[j + 3].ops[0].imm) for v in range(lo, hi + 1)]
                j += 4
            else:
                break
        if not cases or j >= len(self.ins) or self.ins[j].m != 'jmp' \
                or self.ins[j].ops[0].kind != 'imm' \
                or any(o != self.ins[j].ops[0].imm for o in outs):
            return None
        # the temporary is read by these compares only
        for x in self.ins:
            if x.addr in (self.ins[i].addr for i in range(k - 1, j)):
                continue
            if any(o.kind == 'mem' and o.base == 'ebp' and o.disp == tmp.disp for o in x.ops):
                return None
        return cases, self.ins[j].ops[0].imm, j + 1

    def chain_switch(self, k, chain):
        cases_list, default, nk = chain
        slot = self.slot(self.ins[k].ops[0].disp)
        slot.temp = True
        expr = None
        while self.items and self.items[-1][0] == 'stmt' and isinstance(self.items[-1][1], Assign) \
                and isinstance(self.items[-1][1].lhs, SlotVar) and self.items[-1][1].lhs.slot is slot:
            st = self.items.pop()[1]
            if st.op == '':
                expr = st.rhs
        if expr is None:
            raise LiftError(f'switch value not found at {self.pc:#x}')
        cases = collections.defaultdict(list)
        for v, target in cases_list:
            cases[target].append(v)
        self.items.append(('switch', expr, dict(cases), default, self.pc))
        self.cur_stmt_addr = None
        self.dirty = set()
        return nk

    def step(self, k, tables):
        _CLOCK[0] = k
        self.k = k
        ins = self.ins[k]
        m, ops = ins.m, ins.ops
        if m == 'cmp':
            chain = self.compare_chain(k)
            if chain is not None:
                return self.chain_switch(k, chain)
        if m == 'rep movsd' and isinstance(self.regs.get('ecx'), Const):
            # a struct copy of ecx dwords from [esi] to [edi]
            n = self.regs['ecx'].v * 4
            ty = STRUCT_BY_SIZE.get(n)
            if ty is None:
                raise LiftError(f'struct copy of {n:#x} bytes at {self.pc:#x}')
            src = as_pointer(self.reg_value('esi'))
            dst = self.reg_value('edi')
            if isinstance(dst, AddrOfVar) and isinstance(dst.v, SlotVar):
                st = self.struct_slot(dst.v.slot.off, n, ty)
                lhs = SlotVar(st)
                lhs.whole = True
                lhs.copy_type = ty
            else:
                lhs = Deref(as_pointer(dst), ty)
            self.emit(Assign(lhs, Deref(src, ty)))
            self.dirty = set()
            return k + 1
        nxt = self.ins[k + 1] if k + 1 < len(self.ins) else None
        if m == 'mov' and ops[0].kind == 'reg' and ops[1].kind == 'mem' and ops[1].disp == 0 \
                and isinstance(self.regs.get(ops[1].base), StructResult) \
                and nxt is not None and nxt.ops and nxt.ops[0].kind == 'mem' \
                and nxt.ops[0].base not in ('ebp', 'esp', None) \
                and not isinstance(self.regs.get(nxt.ops[0].base), ArgBlock):
            # a struct-returning call's result copied straight into memory: p[i] = f()
            res = self.regs[ops[1].base]
            n = self.mem_copy(k)
            if n == res.size and n in STRUCT_BY_SIZE:
                res.copied = res.consumed = True
                lhs = Deref(as_pointer(self.reg_value(nxt.ops[0].base)), STRUCT_BY_SIZE[n])
                self.emit(Assign(lhs, res.call))
                self.dirty = set()
                return k + 2 * (n // 4)
        if m == 'mov' and ops[0].kind == 'reg' and ops[1].kind == 'mem' \
                and (ops[1].disp == 0 or ops[1].base == 'ebp') \
                and not isinstance(self.regs.get(ops[1].base), StructResult) \
                and nxt is not None and nxt.ops and nxt.ops[0].kind == 'mem' \
                and not isinstance(self.regs.get(nxt.ops[0].base), ArgBlock):
            n = self.mem_copy(k)
            if n in STRUCT_BY_SIZE:
                ty = STRUCT_BY_SIZE[n]
                if ops[1].base == 'ebp':
                    sst = self.struct_slot(ops[1].disp, n, ty)      # a struct local
                    src = None
                    whole = SlotVar(sst)
                    whole.whole = True
                    res = getattr(self.slot(ops[1].disp), 'copy_of', None)
                    if isinstance(res, StructResult) and getattr(sst, 'temp', False):
                        # the temporary a struct-returning call's result went to
                        whole = self.take_temp(res)
                else:
                    src = as_pointer(self.reg_value(ops[1].base))
                if nxt.ops[0].base == 'ebp':
                    st = self.struct_slot(nxt.ops[0].disp, n, ty)
                    lhs = SlotVar(st)
                    lhs.whole = True
                    lhs.copy_type = ty
                else:
                    lhs = Deref(as_pointer(self.reg_value(nxt.ops[0].base)), ty)
                self.emit(Assign(lhs, Deref(src, ty) if src is not None else whole))
                self.dirty = set()
                return k + 2 * (n // 4)
        if m == 'sub' and ops[0].kind == 'reg' and ops[0].reg == 'esp':
            # room for a by-value argument: a double (fstp [esp]) or a struct (copied
            # through `mov reg, esp`)
            self.arg_block = {'size': ops[1].imm, 'fields': {}}
            return k + 1
        if m == 'mov' and ops[0].kind == 'reg' and ops[1].kind == 'reg' and ops[1].reg == 'esp':
            self.regs[ops[0].reg] = ArgBlock()
            return k + 1
        if m == 'mov' and ops[0].kind == 'mem' and ops[0].base in REG32 \
                and isinstance(self.regs.get(ops[0].base), ArgBlock):
            blk = self.arg_block
            blk['fields'][ops[0].disp] = self.value(ops[1])
            if sum(4 for _ in blk['fields']) >= blk['size']:
                self.args.append(self.struct_arg(blk))
                self.arg_block = None
            return k + 1
        if m == 'mov' or m == 'movsx' or m == 'movzx':
            dst, src = ops
            if dst.kind == 'mem':
                lhs = self.lvalue(dst)
                rhs = self.value(src)
                self.store(lhs, rhs, dst.size)
            else:
                v = self.value(src)
                if m in ('movsx', 'movzx') and src.kind == 'mem':
                    self.note_sign(v, m == 'movsx', src.size)
                elif m == 'movzx' or m == 'movsx':
                    v = narrow(v, src.size, m == 'movsx')
                self.set_reg(dst.reg, v)
                self.dirty.add(SUBREG.get(dst.reg, (dst.reg,))[0])
            return k + 1
        if m == 'lea':
            dst, src = ops
            if src.base == 'ebp' and src.index is None:
                v = self.var(src.disp)
                self.set_reg(dst.reg, AddrOfVar(v))
            elif src.base == 'ebp':
                lv = self.lvalue(src, record=False)
                self.set_reg(dst.reg, AddrOfVar(lv))
            else:
                v = self.reg_value(src.base) if src.base else None
                if src.index and src.index == src.base and v.ty != 'char*':
                    # lea r, [x + x*s]: x * (s + 1)
                    v = Bin('*', v, Const(src.scale + 1), 'int')
                elif src.index:
                    term = self.reg_value(src.index)
                    if src.scale != 1:
                        term = Bin('*', term, Const(src.scale), 'int')
                    if v is not None and v.ty != 'char*' and src.scale != 1 \
                            and isinstance(v, Bin) and v.op in ('*', '<<'):
                        # lea r, [x*t + y*s (+ K)] with x already shifted: of two scaled
                        # terms the compiler folds the *left* one's scaling into the lea
                        # and shifts the right one itself, so this is y*s + x*t (+ K)
                        v = Bin('+', term, v, 'int')
                        if src.disp:
                            v = Bin('+', v, Const(src.disp), 'int')
                        self.set_reg(dst.reg, v)
                        return k + 1
                    if v is not None and v.ty != 'char*' and src.disp:
                        # lea r, [x + y + K]: the compiler folds a constant into the
                        # addition after it, so this is x + K + y, unless y was computed
                        # first, which (x + K) + y would not do: then x + y + K.
                        # (a load whose address was worked out first but which was only
                        # loaded after y is x + y too: x + K would have needed it at once)
                        base0 = v
                        if term.first_time() < v.first_time() or \
                                (isinstance(v, Deref) and term.first_time() < v.t):
                            v = Bin('+', Bin('+', v, term, 'int'), Const(src.disp), 'int')
                        else:
                            v = Bin('+', Bin('+', v, Const(src.disp), 'int'), term, 'int')
                        v.row = (base0, term, src.disp)     # maybe &rows[i] of a 2D array
                        self.set_reg(dst.reg, v)
                        return k + 1
                    v = term if v is None else Bin('+', v, term, v.ty if v.ty == 'char*' else 'int')
                if src.disp:
                    d = Const(src.disp & 0xFFFFFFFF if v is None else src.disp)
                    v = d if v is None else Bin('+', v, d, v.ty if v.ty == 'char*' else 'int')
                self.set_reg(dst.reg, v)
            return k + 1
        if m in ('xor', 'sub') and ops[0].kind == 'reg' and ops[1].kind == 'reg' \
                and ops[0].reg == ops[1].reg:
            self.set_reg(ops[0].reg, Const(0))
            self.flags = ('res', Const(0))      # `xor edx,edx; je`: if (0) { ... }
            return k + 1
        if m == 'or' and ops[0].kind == 'reg' and ops[1].kind == 'imm' \
                and ops[1].imm & ((1 << 8 * ops[0].size) - 1) == (1 << 8 * ops[0].size) - 1:
            self.set_reg(ops[0].reg, Const(-1))      # `or al,0xff`: a load of -1
            return k + 1
        if m == 'and' and ops[1].kind == 'imm' and ops[1].imm & 0x80000000 and nxt is not None \
                and nxt.m == 'jns' and self.ins[k + 2].m == 'dec':
            mask = (ops[1].imm & 0x7FFFFFFF) + 1
            r = ops[0].reg
            self.set_reg(r, Bin('%', self.reg_value(r), Const(mask), 'int'))
            self.mod_skip = nxt.ops[0].imm
            return k + 5
        if m in ARITH:
            if m == 'imul' and len(ops) == 3:
                v = Bin('*', self.value(ops[1]), self.value(ops[2]), 'int')
                self.set_reg(ops[0].reg, v)
                self.flags = ('res', v)
                return k + 1
            dst, src = ops
            a = self.value(dst)
            b = self.value(src)
            if m == 'shr':
                a = unsigned(a)
            # A load folded into the instruction was the left operand if its address
            # was computed before the register's value.
            if m in ('add', 'imul', 'and', 'or', 'xor') and src.kind == 'mem' and dst.kind == 'reg' \
                    and (src.base in REG32 or src.index in REG32):
                regs_t = [self.regs[r].first_time() for r in (src.base, src.index) if r in REG32]
                prev = self.ins[k - 1]
                copied = prev.m == 'mov' and prev.ops[0].kind == 'reg' and prev.ops[1].kind == 'reg' \
                    and prev.ops[0].reg == dst.reg
                # ... or the product is moved to eax for a division afterwards
                after = self.ins[k + 1] if k + 1 < len(self.ins) else None
                if m == 'imul' and dst.reg != 'eax' and after is not None and after.m == 'mov' \
                        and after.ops[0].kind == 'reg' and after.ops[0].reg == 'eax' \
                        and after.ops[1].kind == 'reg' and after.ops[1].reg == dst.reg \
                        and self.ins[k + 2].m == 'cdq' \
                        and isinstance(a, (SlotVar, Var, ThisVar, Deref, Index)):
                    copied = True       # (an expression in the register was the left one)
                # (unless the register holds a plain load: for M + a the compiler would
                # have loaded M and folded a, so M here is the heavier right operand,
                # evaluated first)
                heavier = isinstance(a, (SlotVar, Var, ThisVar, Deref, Index))
                # ... except in M op= a, where M's address is worked out first as the
                # left operand and the result is stored back to M
                for x in self.ins[k + 1:k + 6]:
                    if x.m == 'mov' and x.ops[0].kind == 'mem' and x.ops[1].kind == 'reg' \
                            and x.ops[1].reg == dst.reg:
                        if x.ops[0].disp == src.disp and x.ops[0].index == src.index \
                                and src.index is None:
                            heavier = False
                        break
                    if x.ops and x.ops[0].kind == 'reg' and x.ops[0].reg == dst.reg:
                        break
                if (min(regs_t) < a.first_time() and not heavier) or copied:
                    # (or the register operand was copied first: `mem * x` loads x and
                    # copies it into the result register)
                    a, b = b, a
            v = Bin(ARITH[m], a, b, 'int')
            if dst.size < 4:
                v.narrow = dst.size
            if dst.kind == 'mem':
                self.store(self.lvalue(dst), v, dst.size, compound=True)
            else:
                self.set_reg(dst.reg, v)
                self.dirty.add(SUBREG.get(dst.reg, (dst.reg,))[0])
            self.flags = ('res', v)
            return k + 1
        if m == 'neg':
            # sub eax, C; neg eax; sbb eax, eax  ->  (x == C) - 1, then
            # inc eax  ->  x == C;   add eax, K  ->  (x == C) + (K - 1)
            r = ops[0].reg
            same_reg = lambda o: o.kind == 'reg' and SUBREG.get(o.reg, (o.reg,))[0] == SUBREG.get(r, (r,))[0]
            if nxt and nxt.m == 'sbb' and same_reg(nxt.ops[0]) and same_reg(nxt.ops[1]):
                r8 = nxt.ops[0].reg       # sbb al,al: the 0/1 is worked out as a char
                v = self.reg_value(r)
                if isinstance(v, Bin) and v.op == '-':
                    c = Cond('==', v.a, v.b)
                else:
                    c = Cond('==', v, Const(0))
                if r8 in REG32:
                    c.wide = True
                after = self.ins[k + 2] if k + 2 < len(self.ins) else None
                if after is not None and after.ops and same_reg(after.ops[0]):
                    if after.m == 'inc':
                        self.set_reg(r, c)
                        return k + 3
                    if after.m == 'add' and after.ops[1].kind == 'imm':
                        kk = after.ops[1].imm - (1 << 32 if after.ops[1].imm & 0x80000000 else 0)
                        self.set_reg(r, c if kk == 1 else Bin('+', c, Const(kk - 1), 'int'))
                        return k + 3
                self.set_reg(r, Bin('-', c, Const(1), 'int'))
                return k + 2
            self.set_reg(ops[0].reg, Un('-', self.reg_value(ops[0].reg), 'int'))
            return k + 1
        if m == 'not':
            self.set_reg(ops[0].reg, Un('~', self.reg_value(ops[0].reg), 'int'))
            return k + 1
        if m == 'cdq':
            # cdq; sub eax, edx; sar eax, 1  ->  eax / 2
            if nxt.m == 'sub' and nxt.ops[1].kind == 'reg' and nxt.ops[1].reg == 'edx' \
                    and self.ins[k + 2].m == 'sar':
                sh = self.ins[k + 2].ops[1].imm
                self.set_reg('eax', Bin('/', self.reg_value('eax'), Const(1 << sh), 'int'))
                return k + 3
            # cdq; sub eax, edx; mov r, eax; sar r, 1  ->  r = eax / 2
            t = self.ins[k + 2] if k + 2 < len(self.ins) else None
            u = self.ins[k + 3] if k + 3 < len(self.ins) else None
            if nxt.m == 'sub' and nxt.ops[1].kind == 'reg' and nxt.ops[1].reg == 'edx' \
                    and t is not None and t.m == 'mov' and t.ops[1].kind == 'reg' \
                    and t.ops[1].reg == 'eax' and u is not None and u.m == 'sar' \
                    and u.ops[0].kind == 'reg' and u.ops[0].reg == t.ops[0].reg:
                v = Bin('/', self.reg_value('eax'), Const(1 << u.ops[1].imm), 'int')
                self.set_reg(t.ops[0].reg, v)
                return k + 4
            # cdq; and edx, 2^n - 1; add eax, edx; sar eax, n  ->  eax / 2^n
            if nxt.m == 'and' and self.ins[k + 2].m == 'add' and self.ins[k + 3].m == 'sar':
                sh = self.ins[k + 3].ops[1].imm
                self.set_reg('eax', Bin('/', self.reg_value('eax'), Const(1 << sh), 'int'))
                return k + 4
            # ... with the sum moved to another register before the shift
            if nxt.m == 'and' and self.ins[k + 2].m == 'add' and self.ins[k + 3].m == 'mov' \
                    and self.ins[k + 4].m == 'sar' and self.ins[k + 3].ops[1].kind == 'reg' \
                    and self.ins[k + 3].ops[1].reg == 'eax' \
                    and self.ins[k + 4].ops[0].reg == self.ins[k + 3].ops[0].reg:
                sh = self.ins[k + 4].ops[1].imm
                v = Bin('/', self.reg_value('eax'), Const(1 << sh), 'int')
                self.set_reg(self.ins[k + 3].ops[0].reg, v)
                return k + 5
            self.set_reg('edx', SignOf(self.reg_value('eax')))
            return k + 1
        if m in ('idiv', 'div'):
            a = self.reg_value('eax')
            b = self.value(ops[0])
            if m == 'div':
                a, b = unsigned(a), unsigned(b)
            self.set_reg('eax', Bin('/', a, b, 'int'))
            self.regs['edx'] = Bin('%', a, b, 'int')
            self.dirty.update(('eax', 'edx'))
            return k + 1
        if m == 'and' and False:
            pass
        if m == 'cmp':
            self.flags = ('cmp', self.value(ops[0]), self.value(ops[1]))
            return k + 1
        if m == 'test':
            self.flags = ('test', self.value(ops[0]), self.value(ops[1]))
            return k + 1
        if m.startswith('set') and m in SETCC:
            c = self.condition(SETCC[m])
            # `xor r32, r32` first: the 0 or 1 is an int (stored to a char only through
            # `c ? 1 : 0`)
            parent = SUBREG.get(ops[0].reg, (ops[0].reg,))[0]
            for back in (1, 2, 3):
                p = self.ins[k - back] if k >= back else None
                if p is not None and p.m == 'xor' and p.ops[0].kind == 'reg' and p.ops[0].reg == parent \
                        and p.ops[1].kind == 'reg' and p.ops[1].reg == parent:
                    c.wide = True
                    break
            self.set_reg(ops[0].reg, c)
            self.dirty.add(SUBREG[ops[0].reg][0])
            return k + 1
        if m == 'jmp':
            if ins.addr in tables:
                return k + 1        # handled at the bound check
            target = ops[0].imm
            if target == self.epilogue:
                if not self.finish_return(target):
                    pass
                self.flush_pending()
                self.items.append(('jump', target, ins.addr))
            else:
                self.flush_pending()
                self.items.append(('jump', target, ins.addr))
            self.cur_stmt_addr = None
            self.dirty = set()
            return k + 1
        if m.startswith('j'):
            # a switch's range check: cmp [tmp], N; ja default; ... jmp [table]
            tbl = next((t for t in tables.values() if t['ja'] == ins.addr), None)
            if tbl is not None:
                return self.switch_jump(k, tbl)
            f = self.flags
            if f is not None and f[0] == 'res' and self.items and self.items[-1][0] == 'stmt' \
                    and isinstance(self.items[-1][1], Assign) and not self.items[-1][1].op \
                    and self.items[-1][1].rhs is f[1]:
                # if ((x = e) < 0): the flags of e's arithmetic, with the store in between
                st = self.items.pop()[1]
                self.flags = ('res', AssignExpr(st.lhs, st.rhs))
            c = self.condition(m)
            self.consume(c)
            self.flush_pending()
            self.items.append(('cjump', c, ops[0].imm, ins.addr))
            self.cur_stmt_addr = None
            self.dirty = set()
            return k + 1
        if m == 'push':
            self.args.append(self.value(ops[0]))
            return k + 1
        if m == 'call':
            return self.call(k)
        if m == 'add' and False:
            pass
        if m.startswith('f') or m == 'wait':
            return self.fpu_step(k)
        raise LiftError(f'unhandled {ins}')

    def note_sign(self, v, signed, size):
        if isinstance(v, SlotVar):
            v.slot.signed[signed] += 1
            v.slot.sizes[size] += 1
        elif isinstance(v, (Deref, Index)):
            v.ty = ITYPE[(size, signed)]
            if isinstance(v, Index):
                v.arr.slot.signed[signed] += 1

    def take_temp(self, src):
        """A struct-returning call's first copy was to a compiler temporary after all:
        its value goes on to where the caller uses it."""
        call = src.call
        src.consumed = True
        if call in self.pending:
            self.pending.remove(call)
        prov = getattr(src, 'provisional', None)
        self.items[:] = [it for it in self.items if not (
            it[0] == 'stmt' and (it[1] is prov or isinstance(it[1], ExprStmt) and it[1].e is call))]
        return call

    def mem_struct_copy(self, lhs, rhs):
        """A struct-returning call's temporary copied field by field into memory:
        *(RECT*)p = MakeRect(...)."""
        if not (isinstance(lhs, Deref) and isinstance(rhs, SlotVar)):
            return False
        src = getattr(rhs.slot, 'copy_of', None)
        if not isinstance(src, StructResult):
            return False
        off = rhs.slot.off - rhs.slot.copy_base
        a, d = lhs.addr, 0
        while isinstance(a, Bin) and a.op == '+' and isinstance(a.b, Const):
            a, d = a.a, d + a.b.v
        cp = self.__dict__.get('mcopy')
        if off == 0:
            cp = self.mcopy = {'src': src, 'base': a, 'disp': d, 'next': 4}
        elif cp is None or cp['src'] is not src or off != cp['next'] or not same(cp['base'], a) \
                or d != cp['disp'] + off:
            return False
        else:
            cp['next'] = off + 4
        if cp['next'] >= src.size:
            self.mcopy = None
            base = cp['base'] if not cp['disp'] else Bin('+', cp['base'], Const(cp['disp']), 'char*')
            ty = STRUCT_BY_SIZE.get(src.size, 'RECT')
            self.emit(Assign(Deref(base, ty), self.take_temp(src)))
            self.dirty = set()
        return True

    def struct_copy(self, lhs, rhs):
        """Field-by-field copies of a struct into consecutive slots. Returns True if the
        store was taken."""
        if self.mem_struct_copy(lhs, rhs):
            return True
        if not isinstance(lhs, SlotVar):
            return False
        src = None
        if isinstance(rhs, StructField):
            src, off = rhs.src, rhs.off
        elif isinstance(rhs, SlotVar) and getattr(rhs.slot, 'copy_of', None) is not None:
            src, off = rhs.slot.copy_of, rhs.slot.off - rhs.slot.copy_base
        if src is None:
            return False
        cp = self.copy
        if cp is None or cp['src'] is not src or off != cp['next']:
            if off != 0:
                return False
            cp = self.copy = {'src': src, 'base': lhs.slot.off, 'next': 0}
        if lhs.slot.off != cp['base'] + off:
            return False
        cp['next'] = off + 4
        size = src.size
        if cp['next'] >= size:
            self.copy = None
            dst = self.struct_slot(cp['base'], size, src.call.rtype)
            for o in range(cp['base'], cp['base'] + size, 4):
                self.slot(o).copy_of = src
                self.slot(o).copy_base = cp['base']
            if isinstance(src, StructResult) and not getattr(src, 'copied', False):
                # the first copy: into a local (r = f()), or into a compiler temporary
                # that a later copy or argument takes (decided there, by take_temp)
                src.copied = True
                dst.temp = True
                dst.copy_of = src
                dst.provisional_src = src
                for o in range(cp['base'], cp['base'] + size, 4):
                    self.slot(o).copy_of = src
                whole = SlotVar(dst)
                whole.whole = True
                src.provisional = Assign(whole, src.call)
                self.emit(src.provisional)
                self.dirty = set()
                return True
            if isinstance(src, StructResult):
                self.take_temp(src)
            whole = SlotVar(dst)
            whole.whole = True
            self.emit(Assign(whole, src.call if isinstance(src, StructResult) else src))
            self.dirty = set()
        return True

    def store(self, lhs, rhs, size, compound=False):
        if self.struct_copy(lhs, rhs):
            return
        if size == 1 and isinstance(rhs, Cond) and getattr(rhs, 'wide', False):
            rhs = Ternary(rhs, Const(1), Const(0))     # worked out as an int
        if isinstance(lhs, Deref) and isinstance(rhs, Cast) and isinstance(rhs.e, Const) \
                and rhs.e.v in self.syms.vtables and is_this_field(lhs, 0):
            self.vtable = rhs.e.v          # set by the compiler in ctors and dtors
            self.dirty = set()
            return
        if isinstance(lhs, SlotVar) and self.this_slot is not None and lhs.slot.off < self.this_slot \
                and size == 4 and not compound and self.k + 1 < len(self.ins):
            # an int stored to a temporary only to be loaded by fild: part of the
            # expression, so keep it out of the statement list
            nxt = self.ins[self.k + 1]
            if nxt.m in FINT_OPS and nxt.addr not in self.targets \
                    and nxt.ops[0].kind == 'mem' and nxt.ops[0].base == 'ebp' \
                    and nxt.ops[0].disp == lhs.slot.off and nxt.ops[0].index is None:
                self.forward[lhs.slot.off] = rhs
                return
        if isinstance(lhs, SlotVar):
            lhs.slot.sizes[size] += 1
        elif isinstance(lhs, (Deref, Index)) and lhs.ty not in ('char*', 'double', 'float'):
            lhs.ty = ITYPE.get((size, lhs.ty in SIGNED), lhs.ty)
        op = ''
        if isinstance(rhs, Bin) and rhs.op in '+-*&|^<<>>' and same(rhs.a, lhs):
            if lhs.ty in ('double', 'float'):
                # x += e works out x's address first and loads x last; x = x + e loads
                # x first. With a constant both compile the same.
                ok = getattr(rhs, 'mem_left', False) or isinstance(rhs.b, Const)
            elif size < 4:
                # a short or char done at its own width is x += k; promoted to int
                # first (movsx/movzx) it is x = x + k
                ok = getattr(rhs, 'narrow', None) or compound
                # x += y evaluates y before loading x; x = x + y loads x first
                if not isinstance(rhs.b, Const) and rhs.b.first_time() < rhs.a.t:
                    ok = True
            else:
                ok = True
            if ok:
                op, rhs = rhs.op, rhs.b
        self.emit(Assign(lhs, rhs, op))
        self.dirty = set()

    def condition(self, cc):
        f = self.flags
        if f is None:
            raise LiftError(f'no flags at {self.pc:#x}')
        kind = f[0]
        op = CC_SIGNED.get(cc)
        if kind == 'cmp':
            a, b = f[1], f[2]
            if cc in UNSIGNED_CC:
                a = unsigned(a)
            return Cond(op, a, b)
        if kind == 'test':
            a, b = f[1], f[2]
            v = a if same(a, b) else Bin('&', a, b, 'int')
            return Cond(op, v, Const(0))
        if kind == 'res':
            return Cond(op, f[1], Const(0))
        if kind == 'ftest':
            rel = FTEST.get((f[3], cc))
            if rel is None:
                raise LiftError(f'float test {f[3]:#x} {cc} at {self.pc:#x}')
            if f[4]:
                rel = {'<': '>', '>': '<', '<=': '>=', '>=': '<='}.get(rel, rel)
            return Cond(rel, f[1], f[2])
        raise LiftError(f'flags {kind} at {self.pc:#x}')

    # calls ------------------------------------------------------------------------

    def pop_args(self, nbytes):
        out = []
        while nbytes > 0 and self.args:
            e = self.args.pop()
            out.append(e)
            nbytes -= getattr(e, 'arg_bytes', 4)
        return out

    def call(self, k):
        ins = self.ins[k]
        op = ins.ops[0]
        nxt = self.ins[k + 1] if k + 1 < len(self.ins) else None
        cleanup = 0
        consumed = k + 1
        if nxt is not None and nxt.m == 'add' and nxt.ops[0].kind == 'reg' and nxt.ops[0].reg == 'esp':
            cleanup = nxt.ops[1].imm
            consumed = k + 2
        this = None
        virtual = False
        ret = 'int'
        if op.kind == 'imm':
            target = op.imm
            crt = CRT.get(target)
            if crt is not None:
                name, kind = crt[:2]
                fixed = crt[2] if len(crt) > 2 else None
                if kind == 'ftol':
                    self.set_reg('eax', Cast('int', self.fpu.pop()))
                    self.dirty.add('eax')
                    return consumed
                if kind == 'cookie':
                    return consumed
                args = self.pop_args(cleanup)
                c = Call(name, args)
                if kind in ('call', 'void'):
                    c = self.typed_call(c, name)
                    if c is not None:
                        self.after_call(c)
                    return consumed
                proto = self.syms.protos.lookup(name)
                if proto:
                    c.ptypes = proto[1]
                if fixed:
                    c.ptypes = fixed
                if kind == 'fpu':
                    c.ty = 'double'
                    self.fpu.append(c)
                    self.pending.append(c)
                    self.dirty.add('st0')
                    return consumed
                if kind == 'void':
                    c.ty = 'void'
                self.after_call(c)
                return consumed
            pop, thiscall = self.callee_info(target)
            name = self.syms.func_name(target)
            if name is None:
                import objdefs
                name = objdefs.SHARED.get(target) or f'Unk{target:x}'
            if target not in self.syms.funcs and self.syms.protos.lookup(name) is None:
                # not declared anywhere yet (a function of an object still to come)
                self.syms.infer_proto(self.img, target, name)
            args = self.pop_args(pop or cleanup)
            if thiscall:
                this = self.reg_value('ecx')
            c = Call(name.split('::')[-1], args, this)
            c.target = target
            if '::' in name:
                c.cls = name.rsplit('::', 1)[0]
            c = self.typed_call(c, name)
            if c is None:
                return consumed
            if thiscall and base_call(this, name):
                c.this = None          # a method of a base class at a nonzero offset
                this = ThisVar()
            if thiscall and isinstance(this, ThisVar):
                c.this = None          # a call to another method of this class
                own = getattr(self, 'cls', None)
                if own and '::' in name and name.rsplit('::', 1)[0] != own:
                    c.fn = name        # a base class's version: no virtual dispatch
            self.after_call(c)
            return consumed
        if op.kind == 'mem' and op.base is None and op.index is None:
            name = self.img.iat.get(op.disp & 0xFFFFFFFF)
            if name is None:
                raise LiftError(f'indirect call {ins}')
            nbytes = stdcall_bytes(name)
            args = self.pop_args(nbytes if nbytes is not None else 4 * len(self.args))
            c = self.typed_call(Call(name, args), name)
            if c is not None:
                self.after_call(c)
            return consumed
        if op.kind == 'mem' and op.base:
            # call [vtable + off]: COM methods push `this` last; C++ ones pass it in ecx.
            vt = self.reg_value(op.base)
            obj = vt.addr if isinstance(vt, Deref) else None
            args = list(reversed(self.args))
            self.args = []
            if args and obj is not None and same(args[0], obj):
                slot = op.disp // 4
                name = {0: 'QueryInterface', 1: 'AddRef', 2: 'Release'}.get(slot, f'vtbl[{slot}]')
                iface = (static_type(obj, self.own_class()) or '').rstrip('*')
                methods = interfaces().get(iface)
                c = Call(name, args[1:], args[0], virtual=True)
                c.com = True
                c.cls = 'IUnknown' if slot <= 2 else None
                if methods and slot < len(methods):
                    c.fn, c.cls = methods[slot], iface
                    if c.fn in BUFFER_ARGS:
                        bi, si = BUFFER_ARGS[c.fn]
                        self.fixed_buffer(c.args[bi] if bi < len(c.args) else None,
                                          c.args[si] if si < len(c.args) else None)
            else:
                slot = op.disp // 4
                obj = self.reg_value('ecx')
                if isinstance(obj, ThisVar):
                    fam = getattr(self, 'vfamily', (self.syms.vclass, None, None))
                else:
                    # another object: its declared class's family, or most often a player
                    t = (static_type(obj, self.own_class()) or '').rstrip('*')
                    fam = vfamily(f'{t}::x') if t else vfamily(None)
                    if fam[0] == 'CPlayer':
                        fam = vfamily(None)
                nbytes = self.vslot_bytes(slot, fam)
                if nbytes is not None:
                    self.args = list(reversed(args))
                    args = self.pop_args(nbytes)
                else:
                    self.args = []
                vclass, vnames, _vt = fam
                c = Call(vnames[slot] if vnames and slot < len(vnames) else f'Vf{slot}', args, obj,
                         virtual=True)
                c.cls = vclass
                c.vslot = slot
                if isinstance(obj, ThisVar):
                    c.this = None
            c.slot_index = op.disp // 4
            self.after_call(c)
            return consumed
        raise LiftError(f'call form {ins}')

    def fixed_buffer(self, buf, n):
        """A local buffer of n bytes filled by a call: a char array, or above the /GS
        cookie (which only char arrays sit below) an int array."""
        if not (isinstance(buf, AddrOfVar) and isinstance(buf.v, SlotVar) and isinstance(n, Const)):
            return
        sl = buf.v.slot
        if sl.array or getattr(sl, 'struct_size', None) or getattr(sl, 'cls', None):
            return
        above = self.cookie_slot is not None and sl.off > self.cookie_slot
        sl.array = 4 if above and n.v % 4 == 0 else 1
        sl.signed[True] += 1
        sl.fixed_len = n.v

    def own_class(self):
        """The class whose layout describes `this` (a base class's for derived ones whose
        fields are raw offsets)."""
        cls = getattr(self, 'cls', None)
        if cls and cls not in layouts().structs:
            cls = base_of(f'{cls}::x')
        return cls

    def type_args(self, c, params):
        """Locals whose address is passed for a string or buffer are char arrays; for a
        struct declared in efz.h, locals of that struct."""
        for n, a in enumerate(c.args):
            t = params[n] if n < len(params) else None
            if t is None or not isinstance(a, AddrOfVar) or not isinstance(a.v, SlotVar):
                continue
            sl = a.v.slot
            base = t.replace('const ', '')
            st = base[:-1] if base.endswith('*') else None
            info = layouts().structs.get(st) if st in LOCAL_STRUCTS else None
            if info and not getattr(sl, 'cls', None) and sl.off < 0:
                self.struct_slot(sl.off, info[0], st)
                continue
            if base in ('char*', 'LPSTR', 'LPCSTR', 'HPSTR') and not sl.array:
                sl.array = 1
                sl.signed[True] += 1
            elif base in ('BYTE*', 'LPBYTE', 'unsigned char*') and not sl.array:
                sl.array = 1
                sl.signed[False] += 1

    def typed_call(self, c, qual):
        """Apply the callee's prototype; a floating-point result goes on the FPU stack
        (and None is returned)."""
        proto = self.syms.protos.lookup(qual)
        if proto is None:
            return c
        ret, params = proto
        self.type_args(c, params)
        if qual in BUFFER_CALLS:
            bi, si = BUFFER_CALLS[qual]
            self.fixed_buffer(c.args[bi] if bi < len(c.args) else None,
                              c.args[si] if si < len(c.args) else None)
        c.ptypes = params
        c.rtype = ret
        size = STRUCT_SIZES.get(ret)
        if size:
            # hidden pointer to the result: the first argument; eax returns it
            hidden = c.args.pop(0)
            if isinstance(hidden, AddrOfVar) and isinstance(hidden.v, SlotVar):
                st = self.struct_slot(hidden.v.slot.off, size, ret)
                st.temp = True
            c.ty = ret
            self.pending.append(c)
            self.regs['eax'] = StructResult(c, size)
            self.dirty = {'eax'}
            return None
        if c.args and getattr(c, 'cls', None) is None and False:
            pass
        if ret in ('double', 'float'):
            c.ty = ret
            self.fpu.append(c)
            self.pending.append(c)
            self.dirty.add('st0')
            self.last = 'st0'
            return None
        if ret == 'void':
            c.ty = 'void'
            return c
        if is_pointer_type(ret):
            c.ty = 'char*' if ret.endswith('*') else ret
            w = Cast('int', c)
            w.call = c
            return w
        return c

    def vslot_bytes(self, slot, fam):
        """Argument bytes of a virtual slot of a class family, from an implementation (a
        character's for CPlayer)."""
        vclass, vnames, table = fam
        if table is None:
            table = self.syms.char_vtable
        if slot >= (len(vnames) if vnames else 13):
            return None
        return self.callee_info(self.img.u32(table + 4 * slot))[0]

    def after_call(self, c):
        call = getattr(c, 'call', c)
        # calls whose results are this call's arguments are part of it
        for p in list(self.pending):
            if p is not call and contains(call, p):
                self.pending.remove(p)
        self.pending.append(call)
        self.regs['eax'] = c
        self.dirty = {'eax'}
        self.last = 'eax'

    def flush_args_check(self):
        pass

    def struct_arg(self, blk):
        """A struct copied field by field into argument space: the local it came from."""
        fields = blk['fields']
        first = fields.get(0)
        if isinstance(first, SlotVar):
            base = first.slot.off
            ok = all(isinstance(fields.get(d), SlotVar) and fields[d].slot.off == base + d
                     for d in range(0, blk['size'], 4))
            if ok:
                st = self.struct_slot(base, blk['size'],
                                      {16: 'RECT'}.get(blk['size']))
                src = getattr(st, 'copy_of', None)
                if getattr(st, 'temp', False) and isinstance(src, StructResult) \
                        and not getattr(src, 'consumed', False):
                    # a struct-returning call passed straight on as an argument
                    call = self.take_temp(src)
                    v = StructRef(SlotVar(st), blk['size'])
                    v.call = call
                    return v
                return StructRef(SlotVar(st), blk['size'])
        raise LiftError(f'struct argument from {fields} at {self.pc:#x}')

    def struct_slot(self, base, size, ctype=None):
        """Merge the slots at [base, base+size) into one struct local."""
        st = self.slot(base)
        st.struct_size = max(getattr(st, 'struct_size', 0), size)
        if ctype:
            st.struct_type = ctype
        for off in range(base + 1, base + size):
            if off in self.slots and self.slots[off] is not st:
                self.slots[off].parent = st
        return st

    # switches ---------------------------------------------------------------------

    def switch_jump(self, k, tbl):
        cmpop = tbl['cmp']
        tmp = cmpop.ops[0]
        if tmp.kind != 'mem' or tmp.base != 'ebp':
            raise LiftError(f'switch on {tmp} at {self.pc:#x}')
        slot = self.slot(tmp.disp)
        slot.temp = True
        # retract `tmp = x;` and `tmp -= min;`
        low = 0
        expr = None
        while self.items and self.items[-1][0] == 'stmt' and isinstance(self.items[-1][1], Assign) \
                and isinstance(self.items[-1][1].lhs, SlotVar) and self.items[-1][1].lhs.slot is slot:
            st = self.items.pop()[1]
            if st.op == '-':
                low = st.rhs.v
            elif st.op == '':
                expr = st.rhs
        if expr is None:
            raise LiftError(f'switch value not found at {self.pc:#x}')
        cases = collections.defaultdict(list)
        for v, target in tbl['targets'].items():
            if target != tbl['default']:
                cases[target].append(v + low)
        self.items.append(('switch', expr, dict(cases), tbl['default'], self.pc))
        self.cur_stmt_addr = None
        self.dirty = set()
        # skip to after the jmp [table]
        while self.ins[k].addr != tbl['jmp']:
            k += 1
        return k + 1

    # floating point ---------------------------------------------------------------

    def unsigned_pair(self, o):
        """mov [t], x; mov [t+4], 0; fild qword [t]: an unsigned int converted to double
        (zero-extended to 64 bits). Returns x as unsigned, or None."""
        if not (o.kind == 'mem' and o.size == 8 and o.base == 'ebp' and o.index is None):
            return None
        if len(self.items) < 2 or self.items[-1][0] != 'stmt' or self.items[-2][0] != 'stmt':
            return None
        hi, lo = self.items[-1][1], self.items[-2][1]
        if not (isinstance(hi, Assign) and isinstance(lo, Assign) and not hi.op and not lo.op
                and isinstance(hi.lhs, SlotVar) and hi.lhs.slot.off == o.disp + 4
                and isinstance(hi.rhs, Const) and hi.rhs.v == 0
                and isinstance(lo.lhs, SlotVar) and lo.lhs.slot.off == o.disp):
            return None
        del self.items[-2:]
        hi.lhs.slot.temp = lo.lhs.slot.temp = True
        x = lo.rhs
        if isinstance(x, (Deref, Index)):
            x.ty = 'DWORD'
        elif isinstance(x, SlotVar):
            x.slot.unsigned_cmp += 1
        else:
            x = Cast('DWORD', x)
        return x

    def fload(self, op):
        if op.kind == 'mem' and op.base is None and op.index is None:
            addr = op.disp & 0xFFFFFFFF
            if self.img.section_of(addr) == '.rdata' and addr not in self.syms.globals:
                if op.size == 8:
                    return Const(self.img.f64(addr), 'double')
                return Const(self.img.f32(addr), 'float')
        ty = 'double' if op.size == 8 else 'float'
        lv = self.lvalue(op, ty)
        if isinstance(lv, SlotVar):
            lv.slot.float = ty
        return lv

    def fpu_step(self, k):
        ins = self.ins[k]
        m, ops = ins.m, ins.ops
        st = self.fpu
        if m == 'fld':
            if ops[0].kind == 'reg':
                st.append(st[-1 - int(ops[0].reg[3])])
            else:
                st.append(self.fload(ops[0]))
            self.dirty.add('st0')
            self.last = 'st0'
            return k + 1
        if m == 'fild':
            o = ops[0]
            u = self.unsigned_pair(o)
            if u is not None:
                v = u
            elif o.kind == 'mem' and o.base == 'ebp' and o.index is None and o.disp in self.forward:
                v = self.forward.pop(o.disp)
            else:
                v = self.value(ops[0])
            if isinstance(v, SlotVar):
                v.slot.sizes[ops[0].size] += 1
            c = Cast('double', v)
            c.fild = True
            st.append(c)
            self.dirty.add('st0')
            self.last = 'st0'
            return k + 1
        if m == 'fldz':
            st.append(Const(0.0, 'double'))
            self.last = 'st0'
            return k + 1
        if m == 'fld1':
            st.append(Const(1.0, 'double'))
            self.last = 'st0'
            return k + 1
        if m == 'fst' and ops[0].kind == 'mem' and ops[0].base == 'ebp' and ops[0].index is None \
                and ops[0].disp < 0 and not self.slot_read(ops[0].disp):
            # a store to a temporary nobody reads: the compiler's (float) or (double) cast
            st[-1] = Cast('float' if ops[0].size == 4 else 'double', st[-1])
            return k + 1
        if m in ('fstp', 'fst'):
            v = st[-1]
            if m == 'fstp':
                st.pop()
            dst = ops[0]
            if dst.kind == 'reg':
                return k + 1
            if dst.base == 'esp':
                v.arg_bytes = 8 if dst.size == 8 else 4
                self.args.append(v)
                self.arg_block = None
                return k + 1
            ty = 'double' if dst.size == 8 else 'float'
            lhs = self.lvalue(dst, ty)
            if isinstance(lhs, SlotVar):
                lhs.slot.float = ty
            if isinstance(v, Cast) and getattr(v, 'fild', False) and not isinstance(lhs, SlotVar):
                v = v.e     # an int stored as floating point: converted implicitly
            self.store(lhs, v, dst.size)
            return k + 1
        if m in FARITH or m in FARITH_R:
            if ops and ops[0].kind == 'mem':
                o = ops[0]
                if m.startswith('fi') and o.base == 'ebp' and o.index is None and o.disp in self.forward:
                    b = self.forward.pop(o.disp)
                else:
                    b = self.fload(ops[0]) if not m.startswith('fi') else self.value(ops[0])
                a = st.pop()
                if m in FARITH_R:
                    st.append(fbin(FARITH_R[m], b, a))
                elif FARITH[m] in ('+', '*') and b.first_time() < a.first_time() \
                        and (isinstance(a, Bin) or getattr(a, 'fild', False)):
                    # (against a plain load, the memory operand's address can come
                    # first just because it is heavier)
                    # the memory operand's address was worked out first: it is the left
                    # operand, kept in memory while the right one was loaded
                    v = fbin(FARITH[m], b, a)
                    v.mem_left = True
                    st.append(v)
                else:
                    st.append(fbin(FARITH[m], a, b))
            elif m.endswith('p') and m not in ('fsubr', 'fdivr'):
                # fXXXp st(i), st(0): st(i) = st(i) op st(0), then pop
                i = int(ops[0].reg[3]) if ops else 1
                b = st.pop()
                a = st[-i]
                st[-i] = fbin(FARITH_R[m], b, a, reg_form=True) if m in FARITH_R \
                    else fbin(FARITH[m], a, b, reg_form=True)
            else:
                # fXXX st(i), st(j): st(i) = st(i) op st(j), one of them st(0)
                i, j = int(ops[0].reg[3]), int(ops[1].reg[3])
                a, b = st[-1 - i], st[-1 - j]
                if i == j and m == 'fadd':
                    # x * 2 (an int constant keeps a float x float)
                    v = fbin('*', a, Const(2))
                elif m in FARITH_R:
                    v = fbin(FARITH_R[m], b, a, reg_form=True)
                else:
                    v = fbin(FARITH[m], a, b, reg_form=True)
                st[-1 - i] = v
            self.dirty.add('st0')
            return k + 1
        if m == 'fchs':
            st.append(Un('-', st.pop(), 'double'))
            return k + 1
        unordered = m in ('fucomp', 'fucom', 'fucompp')
        if unordered:
            m = m.replace('fu', 'f', 1)
        if m in ('fcomp', 'fcom', 'fcompp', 'ficomp'):
            a = st[-1]
            if m == 'fcompp':
                b = st[-2]
                st.pop()
                st.pop()
                if not unordered:
                    # st(1) holds the left operand and st(0) the right: compare them
                    # the other way round so the source keeps its evaluation order.
                    # (== and != come out as fucompp with the right operand loaded
                    # first.)
                    a, b = b, a
                    self.fswap = True
            else:
                o = ops[0]
                if m == 'ficomp' and o.base == 'ebp' and o.index is None and o.disp in self.forward:
                    b = self.forward.pop(o.disp)
                else:
                    b = self.fload(ops[0]) if m != 'ficomp' else self.value(ops[0])
                if m != 'fcom':
                    st.pop()
                fild = isinstance(a, Cast) and getattr(a, 'fild', False)
                inner = a.e if fild else a
                # (an int has to go through fild whichever side it is on, so then the
                # order of evaluation is the source order too)
                if b.first_time() < a.first_time() and (isinstance(inner, Bin) or fild):
                    # The memory operand's address came first. Against an arithmetic
                    # expression that means it was the left operand; against a plain
                    # load it can just be the heavier right operand.
                    a, b = b, a
                    self.fswap = True
            # an int loaded with fild is compared with an implicit conversion
            if fprec(a) == 'int' and isinstance(a, Cast) and fprec(b) in ('float', 'double'):
                a = a.e
            elif fprec(b) == 'int' and isinstance(b, Cast) and fprec(a) in ('float', 'double'):
                b = b.e
            swap = getattr(self, 'fswap', False)
            self.fswap = False
            self.flags = ('fcmp', a, b)
            nxt = self.ins[k + 1]
            if nxt.m == 'fnstsw':
                t = self.ins[k + 2]
                if t.m == 'test' and t.ops[0].kind == 'reg' and t.ops[0].reg == 'ah':
                    self.flags = ('ftest', a, b, t.ops[1].imm, swap)
                    return k + 3
                if t.m == 'sahf':
                    self.flags = ('fsahf', a, b)
                    return k + 3
            return k + 1
        if m == 'fxch':
            st[-1], st[-2] = st[-2], st[-1]
            return k + 1
        raise LiftError(f'unhandled fpu {ins}')


def fprec(e):
    """'int' for an integer (or an int converted by fild), else 'float' or 'double'."""
    if isinstance(e, Cast) and getattr(e, 'fild', False):
        return 'int'
    if e.ty in ('float', 'double'):
        return e.ty
    if e.ty in ITYPE.values() or e.ty in ('int', 'DWORD'):
        return 'int'
    return 'double'


def fbin(op, a, b, reg_form=False):
    """A floating-point operation. Converting an int next to a floating operand is left
    implicit, as the source most likely had it: (double)i * f is double but i * f is
    float, which decides how later operations compile (float + int is fiadd, double +
    int is fild and faddp). The exception is the register form with a float left
    operand, which needs the explicit cast."""
    pa, pb = fprec(a), fprec(b)
    if pa == 'int' and pb in ('float', 'double') and isinstance(a, Cast):
        a = a.e
    if pb == 'int' and pa in ('float', 'double') and isinstance(b, Cast) \
            and not (reg_form and pa == 'float'):
        b = b.e
    kinds = []
    for e in (a, b):
        if isinstance(e, Cast) and e.ty == 'double':
            kinds.append('double')
        elif e.ty in ('float', 'double'):
            kinds.append(e.ty)
    ty = 'double' if 'double' in kinds or not kinds else 'float'
    return Bin(op, a, b, ty)


class ArgBlock(E):
    """The pointer to stack space reserved for a by-value argument."""

    def render(self):
        raise LiftError('argument block used as a value')


STRUCT_SIZES = {'RECT': 16}
# the struct type used for a copy of n bytes whose type is unknown
STRUCT_BY_SIZE = {16: 'RECT', 12: 'EffectFrame', 0xc8: 'PatternFrame'}
STRUCT_FIELDS = {
    'RECT': {0: 'left', 4: 'top', 8: 'right', 12: 'bottom'},
    'EffectFrame': {0: 'duration', 2: 'surface', 4: 'x', 6: 'y', 8: 'width', 10: 'height'},
}


class StructResult(E):
    """eax after a call returning a struct: a pointer to the result."""

    def __init__(self, call, size):
        self.call, self.size = call, size

    def uses(self):
        return [self.call]

    def render(self):
        return self.call.text()


class StructField(E):
    """A field of a struct value (read during a struct copy)."""

    def __init__(self, src, off, ty):
        self.src, self.off, self.ty = src, off, ty

    def uses(self):
        return [self.src]

    def render(self):
        raise LiftError('struct field read outside a copy')


class StructRef(E):
    """A whole struct local, used by value."""

    def __init__(self, var, size):
        self.var, self.size = var, size
        self.arg_bytes = size

    @property
    def ty(self):
        return self.var.ty

    def uses(self):
        call = getattr(self, 'call', None)
        return [call] if call is not None else [self.var]

    def render(self):
        call = getattr(self, 'call', None)
        if call is not None:
            return call.render()
        v = SlotVar(self.var.slot)
        v.whole = True
        return v.render()


class SignOf(E):
    def __init__(self, e):
        self.e = e

    def render(self):
        raise LiftError('unconsumed cdq')


class AddrOfVar(E):
    prec = PREC['unary']
    ty = 'char*'

    def __init__(self, v):
        self.v = v
        if isinstance(v, SlotVar):
            v.slot.address_taken = True

    def uses(self):
        return [self.v]

    def render(self):
        e = elem_of(self.v)
        if e is not None and e[1] == 0:
            # &rects[i]; a row decays to a pointer
            return e[0] if isinstance(e[2], tuple) else f'&{e[0]}'
        if isinstance(self.v, SlotVar) and getattr(self.v.slot, 'struct_size', None) \
                and getattr(self.v.slot, 'parent', None) is None:
            whole = SlotVar(self.v.slot)
            whole.whole = True
            return f'&{whole.text(PREC["unary"])}'
        if isinstance(self.v, SlotVar) and self.v.slot.array:
            return self.v.text()
        return f'&{self.v.text(PREC["unary"])}'


def unsigned(e):
    if isinstance(e, SlotVar):
        e.slot.unsigned_cmp += 1
        return e
    if e.ty in ('DWORD', 'WORD', 'BYTE', 'char*'):
        return e
    if isinstance(e, Const):
        return e
    if isinstance(e, Deref) and e.ty == 'int':
        e.ty = 'DWORD'
        return e
    return Cast('DWORD', e)


def narrow(v, size, signed):
    ty = ITYPE[(size, signed)]
    if v.ty == ty:
        return v
    return Cast(ty, v)


# CRT functions in the image: address -> (name, kind)
CRT = {
    0x777d46: ('operator new', 'call'),
    0x777d54: ('srand', 'void'),
    0x777d61: ('rand', 'call'),
    0x777d83: ('time', 'call'),
    0x777dc0: ('memset', 'call'),
    0x777e20: ('operator delete', 'void'),
    0x777f05: ('atexit', 'call'),
    0x777f55: ('_itoa', 'call'),
    0x778080: ('strcpy', 'call'),
    0x778090: ('strcat', 'call'),
    0x778180: ('_strnset', 'call'),
    0x7781dc: ('__security_check_cookie', 'cookie'),
    0x778204: ('sin', 'fpu'),
    0x7782b4: ('cos', 'fpu'),
    0x7783b8: ('__ftol2', 'ftol'),
    0x77842d: ('fabs', 'fpu'),
    0x7784e0: ('strlen', 'call'),
    0x77856b: ('vsprintf', 'call'),
    0x778600: ('memcpy', 'call'),
    0x778970: ('atan2', 'fpu'),
    0x778984: ('abs', 'call'),
    0x775810: ('pow', 'fpu', ['int', 'int']),   # <math.h>'s inline pow(int, int)
}


_STDCALL = None


def stdcall_bytes(name):
    """Argument bytes of an imported __stdcall function, from the SDK import libraries."""
    global _STDCALL
    if _STDCALL is None:
        cache = os.path.join(REPO, 'build', 'stdcall.json')
        if os.path.exists(cache):
            _STDCALL = json.load(open(cache))
        else:
            _STDCALL = {}
            tc = os.environ.get('EFZ_TOOLCHAIN', os.path.expanduser('~/tools/efz-toolchain'))
            for root, _, files in os.walk(tc):
                for fn in files:
                    if fn.lower().endswith('.lib'):
                        data = open(os.path.join(root, fn), 'rb').read()
                        for m in re.finditer(rb'__imp__([A-Za-z0-9_]+)@(\d+)\0', data):
                            _STDCALL.setdefault(m.group(1).decode(), int(m.group(2)))
            os.makedirs(os.path.dirname(cache), exist_ok=True)
            json.dump(_STDCALL, open(cache, 'w'))
    return _STDCALL.get(name)


def function_end(syms, start):
    inv = syms.inventory
    starts = sorted(f['addr'] for f in inv['functions'])
    import bisect
    i = bisect.bisect_right(starts, start)
    return starts[i] if i < len(starts) else start + 0x10000


def dump_items(items):
    for it in items:
        if it[0] == 'label':
            print(f'L{it[1]:x}:')
        elif it[0] == 'stmt':
            for l in it[1].lines():
                print('   ', l)
        elif it[0] == 'cjump':
            print(f'    if ({it[1].text()}) goto L{it[2]:x};')
        elif it[0] == 'jump':
            print(f'    goto L{it[1]:x};')
        elif it[0] == 'switch':
            print(f'    switch ({it[1].text()}) {{ {it[2]} default {it[3]:x} }}')




# --- control flow ------------------------------------------------------------------

class Node:
    pass


class If(Node):
    def __init__(self, cond, then, els=None):
        self.cond, self.then, self.els = cond, then, els


class While(Node):
    def __init__(self, cond, body):
        self.cond, self.body = cond, body


class DoWhile(Node):
    def __init__(self, body, cond):
        self.body, self.cond = body, cond


class For(Node):
    def __init__(self, init, cond, inc, body):
        self.init, self.cond, self.inc, self.body = init, cond, inc, body


class Switch(Node):
    def __init__(self, expr, cases, default):
        self.expr, self.cases, self.default = expr, cases, default


class Jmp(Node):
    def __init__(self, kind, target=None):
        self.kind, self.target = kind, target       # break / continue / return / goto


class Lbl(Node):
    def __init__(self, addr):
        self.addr = addr


class StmtNode(Node):
    def __init__(self, s):
        self.s = s


class Structurer:
    def __init__(self, items, epilogue):
        self.items = items
        self.epilogue = epilogue
        self.at = {}
        for k, it in enumerate(items):
            if it[0] == 'label':
                self.at[it[1]] = k
        self.gotos = set()

    def refs_within(self, addr, lo, hi):
        """Whether every jump to addr comes from items lo..hi-1."""
        for j, it in enumerate(self.items):
            if it[0] == 'cjump' and it[2] == addr or it[0] == 'jump' and it[1] == addr:
                if not lo <= j < hi:
                    return False
            if it[0] == 'switch' and (addr in it[2] or addr == it[3]):
                return False
        return True

    def idx(self, addr):
        if addr == self.epilogue and addr not in self.at:
            return len(self.items)
        return self.at[addr]

    def back_edges(self, k, hi):
        """Indices in (k, hi) of jumps back to the label at k."""
        addr = self.items[k][1]
        return [j for j in range(k + 1, hi) if self.items[j][0] in ('jump', 'cjump')
                and self.items[j][2 if self.items[j][0] == 'cjump' else 1] == addr]

    def parse(self, lo, hi, ctx):
        out = []
        k = lo
        while k < hi:
            it = self.items[k]
            kind = it[0]
            if kind == 'label':
                backs = self.back_edges(k, hi)
                if backs:
                    node, k = self.loop(k, backs, hi, ctx)
                    out.append(node)
                    continue
                out.append(Lbl(it[1]))
                k += 1
            elif kind == 'stmt':
                out.append(StmtNode(it[1]))
                k += 1
            elif kind == 'jump':
                node, k = self.jump(k, hi, ctx, out)
                if node is not None:
                    out.append(node)
            elif kind == 'cjump':
                node, k = self.conditional(k, hi, ctx)
                out.append(node)
            elif kind == 'switch':
                node, k = self.switch(k, hi, ctx)
                out.append(node)
            else:
                raise LiftError(f'item {it}')
        return out

    def jump(self, k, hi, ctx, out):
        t = self.items[k][1]
        # for (init; cond; inc): jmp cond; inc: ...; cond: test; body; jmp inc
        if k + 1 < hi and self.items[k + 1][0] == 'label' and t in self.at:
            tk = self.at[t]
            if k + 1 < tk < hi:
                backs = self.back_edges(k + 1, hi)
                if backs and max(backs) > tk:
                    return self.for_loop(k, tk, max(backs), hi, ctx)
        return self.exit_jump(t, ctx, out), k + 1

    def exit_jump(self, t, ctx, out):
        if t == ctx.get('brk'):
            return Jmp('break')
        if t == ctx.get('cont'):
            return Jmp('continue')
        if t == self.epilogue:
            if out and isinstance(out[-1], StmtNode) and isinstance(out[-1].s, Return):
                return None
            return Jmp('return')
        self.gotos.add(t)
        return Jmp('goto', t)

    # conditions -------------------------------------------------------------------

    def cond_group(self, k, hi):
        """The tests of one condition starting at k: [(index, cond, target)], the index
        after them, and the false target."""
        tests = []
        j = k
        while j < hi and self.items[j][0] in ('cjump', 'label'):
            if self.items[j][0] == 'cjump':
                tests.append(j)
            j += 1
        # the longest prefix whose jumps stay inside the condition
        for n in range(len(tests), 0, -1):
            group = tests[:n]
            end = group[-1] + 1
            false_t = self.items[group[-1]][2]
            inside = {self.items[y][1] for y in range(group[0], end) if self.items[y][0] == 'label'}
            if any(not self.refs_within(a, group[0], end) for a in inside):
                continue
            then_addrs = {self.items[y][1] for y in range(end, min(hi, end + 3))
                          if self.items[y][0] == 'label'}
            ok = True
            for x in group[:-1]:
                t = self.items[x][2]
                if t != false_t and t not in inside and t not in then_addrs:
                    ok = False
                    break
            if ok:
                expr = self.reduce(group, end, false_t)
                if expr is not None:
                    return expr, end, false_t
        raise LiftError(f'condition at item {k}')

    def reduce(self, group, end, false_t):
        """Combine the tests into one expression that is true when control reaches the
        code after them (the `then` side)."""
        THEN, FALSE = 'THEN', 'FALSE'

        def dest(t):
            if t == false_t:
                return FALSE
            for x in group:
                if self.items[x - 1][0] == 'label' and self.items[x - 1][1] == t:
                    return x
            return THEN

        nodes = {}
        for n, x in enumerate(group):
            nxt = group[n + 1] if n + 1 < len(group) else THEN
            nodes[x] = [self.items[x][1], dest(self.items[x][2]), nxt]
        changed = True
        while len(nodes) > 1 and changed:
            changed = False
            order = sorted(nodes)
            for a, b in zip(order, order[1:]):
                ca, ta, fa = nodes[a]
                cb, tb, fb = nodes[b]
                if fa != b:
                    continue
                preds = [x for x in nodes if x != a and (nodes[x][1] == b or nodes[x][2] == b)]
                if preds:
                    continue
                if ta == tb:
                    nodes[a] = [Cond('||', ca, cb), tb, fb]
                elif ta == fb:
                    nodes[a] = [Cond('&&', negate(ca), cb), tb, fb]
                else:
                    continue
                del nodes[b]
                for x in nodes:
                    if nodes[x][1] == b:
                        nodes[x][1] = a
                    if nodes[x][2] == b:
                        nodes[x][2] = a
                changed = True
                break
        if len(nodes) != 1:
            return None
        c, t, f = next(iter(nodes.values()))
        if t == FALSE and f == THEN:
            return negate(c)
        if t == THEN and f == FALSE:
            return c
        return None

    def conditional(self, k, hi, ctx):
        cond, end, false_t = self.cond_group(k, hi)
        fk = self.idx(false_t) if false_t in self.at or false_t == self.epilogue else None
        if fk is None or fk < end or fk > hi:
            # the false side leaves this range: if (cond) { rest } with an exit jump
            raise LiftError(f'if at item {k} jumps outside its range')
        then_end = fk
        els = None
        nxt = fk
        last = then_end - 1
        while last >= end and self.items[last][0] == 'label':
            last -= 1
        if last >= end and self.items[last][0] == 'jump':
            e = self.items[last][1]
            if e > false_t and e not in (ctx.get('brk'), ctx.get('cont'), self.epilogue) \
                    and e in self.at and self.at[e] <= hi:
                ek = self.at[e]
                then_body = self.parse(end, last, ctx)
                els = self.parse(fk + 1 if self.items[fk][0] == 'label' else fk, ek, ctx)
                return If(cond, then_body, els), ek
        then_body = self.parse(end, then_end, ctx)
        return If(cond, then_body), fk

    # loops ------------------------------------------------------------------------

    def loop(self, k, backs, hi, ctx):
        j = max(backs)
        head = self.items[k][1]
        exit_k = j + 1
        exit_addr = self.items[exit_k][1] if exit_k < len(self.items) and self.items[exit_k][0] == 'label' \
            else self.epilogue
        if self.items[j][0] == 'cjump':
            # do { body } while (cond)
            c0 = j
            while c0 - 1 > k and self.items[c0 - 1][0] in ('cjump', 'label'):
                c0 -= 1
            # the loop condition can be several tests: the longest run of them ending
            # at j that jumps only back to the head, out of the loop or within itself
            tests = [x for x in range(c0, j + 1) if self.items[x][0] == 'cjump']
            cond, start = self.items[j][1], j
            for n in range(len(tests)):
                group = tests[n:]
                inside = {self.items[y][1] for y in range(group[0], j + 1)
                          if self.items[y][0] == 'label'}
                if any(self.items[x][2] not in (head, exit_addr) and self.items[x][2] not in inside
                       for x in group):
                    continue
                if any(not self.refs_within(a, group[0], j + 1) for a in inside):
                    continue
                e = self.reduce(group, j + 1, head)
                if e is not None:
                    cond, start = negate(e), group[0]
                    break
            c0 = start
            while c0 - 1 > k and self.items[c0 - 1][0] == 'label':
                c0 -= 1
            cont = self.items[c0][1] if self.items[c0][0] == 'label' else None
            body = self.parse(k + 1, c0, dict(ctx, brk=exit_addr, cont=cont))
            return DoWhile(body, cond), exit_k
        # while (cond) { body }  or  for (;;)
        inner = dict(ctx, brk=exit_addr, cont=head)
        if k + 1 < j and self.items[k + 1][0] == 'cjump':
            try:
                cond, end, false_t = self.cond_group(k + 1, j)
            except LiftError:
                cond = None
            if cond is not None and false_t == exit_addr:
                body = self.parse(end, j, inner)
                return While(cond, body), exit_k
        body = self.parse(k + 1, j, inner)
        return While(None, body), exit_k

    def for_loop(self, k, tk, j, hi, ctx):
        inc_addr = self.items[k + 1][1]
        exit_k = j + 1
        exit_addr = self.items[exit_k][1] if exit_k < len(self.items) and self.items[exit_k][0] == 'label' \
            else self.epilogue
        inc = [self.items[x][1] for x in range(k + 2, tk) if self.items[x][0] == 'stmt']
        inner = dict(ctx, brk=exit_addr, cont=inc_addr)
        cond = None
        body_start = tk + 1
        if tk + 1 < j and self.items[tk + 1][0] == 'cjump':
            cond, end, false_t = self.cond_group(tk + 1, j)
            if false_t != exit_addr:
                raise LiftError(f'for condition at item {tk}')
            body_start = end
        body = self.parse(body_start, j, inner)
        return For(None, cond, inc, body), exit_k

    # switch -----------------------------------------------------------------------

    def switch(self, k, hi, ctx):
        _, expr, cases, default, addr = self.items[k]
        starts = sorted(set(cases) | {default})
        last_case = max(cases) if cases else default
        excluded = (ctx.get('brk'), ctx.get('cont'), self.epilogue)
        if default > last_case:
            end = default          # no default case: `ja` goes to the end of the switch
        else:
            # the default case is a body among the others; the end is where the breaks
            # go, or, if every case returns, the end of the range
            end = None
        # breaks: jumps out of the earlier cases to past the last one (jumps inside the
        # last case's own body can't be told apart from breaks, so they don't count)
        last_k = self.at.get(last_case, hi)
        targets = collections.Counter(self.items[x][1] for x in range(k + 1, min(last_k, hi))
                                      if self.items[x][0] == 'jump' and self.items[x][1] > last_case
                                      and self.items[x][1] not in excluded)
        if targets:
            t = targets.most_common(1)[0][0]
            end = t if end is None else max(end, t)
        if end is None:
            end = self.items[hi][1] if hi < len(self.items) and self.items[hi][0] == 'label' \
                else self.epilogue
            ek = hi
        else:
            ek = self.idx(end)
        inner = dict(ctx, brk=end)
        body_starts = sorted(set(cases) | ({default} if default != end else set()))
        out = []
        for n, st in enumerate(body_starts):
            sk = self.at[st]
            nk = self.at[body_starts[n + 1]] if n + 1 < len(body_starts) else ek
            values = sorted(cases.get(st, []))
            body = self.parse(sk + 1, nk, inner)
            out.append((values, st == default, body))
        return Switch(expr, out, default != end), ek


# --- output ------------------------------------------------------------------------

def render(nodes, indent=1, gotos=()):
    pad = '    ' * indent
    lines = []
    for n in nodes:
        if isinstance(n, StmtNode):
            lines += [pad + l for l in n.s.lines()]
        elif isinstance(n, If):
            lines.append(f'{pad}if ({n.cond.text()}) {{')
            lines += render(n.then, indent + 1, gotos)
            if n.els:
                if len(n.els) == 1 and isinstance(n.els[0], If):
                    sub = render(n.els, indent, gotos)
                    lines.append(f'{pad}}} else {sub[0].strip()}')
                    lines += sub[1:]
                    continue
                lines.append(f'{pad}}} else {{')
                lines += render(n.els, indent + 1, gotos)
            lines.append(f'{pad}}}')
        elif isinstance(n, While):
            c = n.cond.text() if n.cond is not None else '1'
            if n.cond is None:
                lines.append(f'{pad}for (;;) {{')
            else:
                lines.append(f'{pad}while ({c}) {{')
            lines += render(n.body, indent + 1, gotos)
            lines.append(f'{pad}}}')
        elif isinstance(n, DoWhile):
            lines.append(f'{pad}do {{')
            lines += render(n.body, indent + 1, gotos)
            lines.append(f'{pad}}} while ({n.cond.text()});')
        elif isinstance(n, For):
            inc = ', '.join(l.rstrip(';') for s in n.inc for l in s.lines())
            c = n.cond.text() if n.cond is not None else ''
            lines.append(f'{pad}for (; {c}; {inc}) {{')
            lines += render(n.body, indent + 1, gotos)
            lines.append(f'{pad}}}')
        elif isinstance(n, Switch):
            lines.append(f'{pad}switch ({n.expr.text()}) {{')
            for values, is_default, body in n.cases:
                for v in values:
                    lines.append(f'{pad}case {fmt_int(v) if v >= 0 else v}:')
                if is_default:
                    lines.append(f'{pad}default:')
                sub = render(body, indent + 1, gotos)
                lines += sub if sub else [f'{pad}    break;']
            lines.append(f'{pad}}}')
        elif isinstance(n, Jmp):
            lines.append(f'{pad}{n.kind}{f" L{n.target:x}" if n.kind == "goto" else ""};')
        elif isinstance(n, Lbl):
            if n.addr in gotos:
                last = all(isinstance(x, Lbl) for x in nodes[nodes.index(n) + 1:])
                lines.append(f'L{n.addr:x}:' + (';' if last else ''))
    return lines


def declare(slot, name):
    if getattr(slot, 'elem_stride', None):
        if slot.elem == 'RECT':
            return f'RECT {name}[{slot.array_len}];'
        return f'int {name}[{slot.array_len}][{slot.elem[1]}];'
    if getattr(slot, 'struct_size', None):
        return f'{getattr(slot, "struct_type", None) or "RECT"} {name};'
    if slot.array:
        esize = slot.array
        signed = slot.signed.most_common(1)[0][0] if slot.signed else True
        return f'{ITYPE[(esize, signed)]} {name}[{slot.array_len}];'
    return f'{slot.ctype()} {name};'


def array_bytes(space):
    """The array size that fills `space` bytes of frame: large arrays are rounded up
    to 8 bytes by the compiler."""
    return space // 8 * 8 if space >= 64 else space


def register_pads():
    path = os.path.join(REPO, 'tools', 'regpads.json')
    if not os.path.exists(path):
        return {}
    return {int(f, 16): {int(a, 16): n for a, n in v.items()}
            for f, v in json.load(open(path)).items()}


def base_of(qual):
    import objdefs
    cls = qual.rsplit('::', 1)[0] if qual and '::' in qual else None
    for c in objdefs.CLASSES:
        if c[1] == cls:
            return c[2]
    return 'CPlayer'


def vfamily(qual):
    """(base class, slot names, a vtable) for virtual calls made in qual's class."""
    import objdefs
    cls = qual.rsplit('::', 1)[0] if qual and '::' in qual else None
    for c in objdefs.CLASSES:
        if cls in (c[1], c[2]):
            first = next(x for x in objdefs.CLASSES if x[2] == c[2])
            return c[2], c[6], first[5]
    return 'CPlayer', objdefs.PLAYER_SLOTS, None


def lift(img, syms, start, ret_type=None, this_type=None, qual=None):
    lf = Lifter2(img, syms, start, function_end(syms, start), this_type)
    lf.pads = register_pads().get(start, {})
    lf.vfamily = vfamily(qual or syms.func_name(start))
    qual = qual or syms.func_name(start)
    lf.cls = qual.rsplit('::', 1)[0] if qual and '::' in qual else None
    if qual:
        proto = syms.protos.lookup(qual)
        if proto:
            if ret_type is None:
                ret_type = proto[0]
            off = 8 + (4 if STRUCT_SIZES.get(proto[0]) else 0)
            for n, t in enumerate(proto[1]):
                sl = lf.slot(off)
                sl.declared = t
                sl.name = f'p{n + 1}'
                off += STRUCT_SIZES.get(t, 8 if t == 'double' else 4)
    items = lf.execute(ret_type)
    st = Structurer(items, lf.epilogue)
    body = st.parse(0, len(items), {})
    ctx = {'ctor': bool(qual) and qual.split('::')[-1] == qual.split('::')[0].split('::')[-1]
                   if qual and '::' in qual else False,
           'dtor': bool(qual) and '::~' in qual}
    # *(RECT*)p1 = r; return p1;  ->  return r;  (p1 being the hidden result pointer)
    lf.struct_ret = None
    tail = [n for n in body if not (isinstance(n, Lbl))]
    if len(tail) >= 2 and isinstance(stmt_of(tail[-1]), Return) and isinstance(stmt_of(tail[-2]), Assign):
        r, a = stmt_of(tail[-1]), stmt_of(tail[-2])
        hidden = lambda e: isinstance(e, SlotVar) and e.slot.off == 8
        lhs_addr = a.lhs.addr.e if isinstance(a.lhs, Deref) and isinstance(a.lhs.addr, Cast) else \
            getattr(a.lhs, 'addr', None)
        if isinstance(a.lhs, Deref) and a.lhs.ty in STRUCT_SIZES and hidden(lhs_addr) \
                and (hidden(r.e) or (isinstance(r.e, Cast) and hidden(r.e.e))):
            lf.struct_ret = a.lhs.ty
            body.remove(tail[-2])
            r.e = a.rhs
    ctx['gotos'] = st.gotos
    ctx['top'] = body
    ctx['lf'] = lf
    body = rewrite_patterns(body, syms, ctx)
    lf.initializers = ctx.get('initializers', [])
    lf.base_init = ctx.get('base_init')
    if lf.this_slot is not None:
        temps = {sl for sl in lf.slots.values() if sl.off < lf.this_slot}
        body = fold_temps(body, temps, qual.rsplit('::', 1)[0] if qual and '::' in qual else None)
    lf.members = ctx.get('members', [])
    lf.inline_decls = ctx.get('inline_decls', [])
    return lf, body, st


NAME_PREFIXES = ['v', 'l', 'x', 'n', 'k', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'm',
                 'p', 'q', 'r', 's', 't', 'u', 'w', 'y', 'z', 'lv', 'tmp', 'var', 'loc', 'val',
                 'v_', 'l_', 'x_', 'n_', 'k_', 'a_', 'b_', 'c_', 'd_', 'e_', 'f_', 'g_', 'h_',
                 'i_', 'j_', 'm_', 'p_', 'q_', 'r_', 's_', 't_', 'u_', 'w_', 'y_', 'z_']


def name_locals(locals_, ranks=None):
    """Name the locals so that the compiler's hash order puts them at their offsets.
    Returns them in declaration order. `ranks` gives locals declared later in the body
    (1, 2, ... in code order)."""
    import stackorder
    ranks = ranks or {}
    top_down = sorted(locals_, key=lambda s: -s.off)
    if len(top_down) <= 1:
        for s in top_down:
            s.name = f'v{-s.off:x}'
        return top_down
    variables = [(s, [f'{p}{-s.off:x}' for p in NAME_PREFIXES]) for s in top_down]
    choice, _groups = stackorder.solve(variables, [ranks.get(id(s), 0) for s in top_down])
    if choice is None:
        raise LiftError('no names reproduce the stack layout')
    for (s, _), name in zip(variables, choice):
        s.name = name
    return list(reversed(top_down))


def node_values(n):
    exprs = [getattr(n, 'cond', None), getattr(n, 'expr', None)]
    st = getattr(n, 's', None)
    if isinstance(st, Assign):
        exprs += [st.lhs, st.rhs]
    elif isinstance(st, (ExprStmt, Return, DeleteStmt)):
        exprs.append(st.e)
    elif isinstance(st, DeclStmt):
        exprs += list(st.call.args)
    for inc in getattr(n, 'inc', None) or []:
        if isinstance(inc, Assign):
            exprs += [inc.lhs, inc.rhs]
    return [e for e in exprs if isinstance(e, E)]


def stride_of(idx):
    """A byte offset i << k or i * c as (i, stride); (idx, 1) otherwise."""
    if isinstance(idx, Bin) and isinstance(idx.b, Const):
        if idx.op == '<<':
            return idx.a, 1 << idx.b.v
        if idx.op == '*':
            return idx.a, idx.b.v
    return idx, 1


def shape_arrays(lf, nodes):
    """Local arrays of structs or rows, from byte-offset indexing with a stride: the
    slots inside one element become its fields (rects[i].top, hits[i][j])."""
    found = collections.defaultdict(set)      # stride -> slot offsets
    rows = set()
    for n in all_nodes(nodes):
        for e in node_values(n):
            for x in walk_expr(e):
                if isinstance(x, Index) and isinstance(x.arr, SlotVar) and x.arr.slot.array == 1:
                    sl = x.arr.slot
                    if getattr(sl, 'parent', None) is not None and \
                            getattr(sl.parent, 'struct_type', None):
                        continue
                    if getattr(sl, 'struct_type', None):
                        continue
                    i, S = stride_of(x.idx)
                    if S >= 8:
                        found[S].add(sl.off)
                elif isinstance(x, Deref) and row_access(x) is not None:
                    rows.add(row_access(x)[0].arr.slot.off)
    offs = sorted(o for o in lf.slots if o < 0)
    for S, members in found.items():
        members = sorted(members)
        while members:
            base = members[0]
            group = [o for o in members if o < base + S]
            members = [o for o in members if o >= base + S]
            A = lf.slot(base)
            A.elem_stride = S
            A.elem = 'RECT' if S == 16 and base not in rows else ('int', S // 4)
            for o in offs:
                if base < o < base + S and lf.slots[o] is not A:
                    lf.slots[o].parent = A
            above = [o for o in offs if o > base and getattr(lf.slots[o], 'parent', None) is not A
                     and lf.slots[o] is not A] + [lf.cookie_slot or 0]
            top = min(above) if above else 0
            A.array_len = (top - base) // S
            # slots further on in the array: elements (ignored as locals)
            for o in offs:
                if base + S <= o < base + A.array_len * S and lf.slots[o] is not A \
                        and getattr(lf.slots[o], 'parent', None) is None:
                    lf.slots[o].parent = A


def row_access(d):
    """*(int*)(&rows[i * S] + j * 4): (Index, j) or None."""
    a = d.addr
    if isinstance(a, Cast):
        a = a.e
    if isinstance(a, Bin) and a.op == '+' and isinstance(a.a, AddrOfVar) \
            and isinstance(a.a.v, Index) and isinstance(a.b, Bin) and a.b.op == '*' \
            and isinstance(a.b.b, Const) and a.b.b.v == 4 and d.ty in ('int', 'DWORD') \
            and isinstance(a.a.v.arr, SlotVar):
        return a.a.v, a.b.a
    return None


def slot_name(s):
    return s.name or f'l_{-s.off:x}'


def elem_of(ix):
    """For an Index into a local array of structs or rows, or into an array member of
    a struct local: (element text, offset within the element, element type) or None."""
    if not isinstance(ix, Index) or not isinstance(ix.arr, SlotVar):
        return None
    s = ix.arr.slot
    i, S = stride_of(ix.idx)
    if S < 2:
        return None
    A = s if getattr(s, 'elem_stride', None) else getattr(s, 'parent', None)
    if A is not None and getattr(A, 'elem_stride', None) == S:
        return f'{slot_name(A)}[{i.text()}]', s.off - A.off, A.elem
    P = s if getattr(s, 'struct_type', None) else getattr(s, 'parent', None)
    if P is not None and getattr(P, 'struct_type', None):
        af = layouts().array_field(P.struct_type, s.off - P.off)
        if af and af[2] == S:
            name, ety, esize, sub = af
            return f'{slot_name(P)}.{name}[{i.text()}]', sub, ety
    return None


def member_text(base, f, ety):
    """A field at offset f of an element."""
    if ety == 'RECT' and f in RECT_FIELDS:
        return f'{base}.{RECT_FIELDS[f]}'
    if isinstance(ety, tuple):
        return f'{base}[{f // 4}]'
    fname = layouts().field(ety, f)
    if fname:
        return f'{base}.{fname}'
    return None


def used_slots(nodes):
    """Slots referenced anywhere in a node tree."""
    used = set()
    for n in all_nodes(nodes):
        st = getattr(n, 's', None)
        if isinstance(st, DeclStmt):
            used.add(st.slot)
        exprs = node_values(n)
        for e in exprs:
            if isinstance(e, E):
                for x in walk_expr(e):
                    if isinstance(x, SlotVar):
                        used.add(x.slot)
                        p = getattr(x.slot, 'parent', None)
                        if p is not None:
                            used.add(p)
    return used


def body_text(lf, body, st, names=True):
    shape_arrays(lf, body)
    # arrays of known length (a buffer filled by a call): slots inside are elements
    for s in list(lf.slots.values()):
        n = getattr(s, 'fixed_len', None)
        if n:
            s.array_len = n // s.array
            for o in range(s.off + 1, s.off + n):
                if o in lf.slots and lf.slots[o] is not s:
                    lf.slots[o].parent = s
    used = used_slots(body)
    locals_ = [s for s in lf.slots.values()
               if s.off < 0 and s.off != lf.this_slot and s.off != lf.cookie_slot
               and not getattr(s, 'temp', False) and getattr(s, 'parent', None) is None
               and s in used]
    for s in lf.slots.values():
        if getattr(s, 'parent', None) is not None and getattr(s.parent, 'temp', False):
            s.temp = True
    # array lengths: up to the next slot above
    offs = sorted(s.off for s in lf.slots.values() if s.off < 0)
    for s in locals_:
        if s.array and not getattr(s, 'fixed_len', None) and not getattr(s, 'elem_stride', None):
            above = [o for o in offs if o > s.off] + [lf.cookie_slot or 0]
            top = min(o for o in above if o > s.off) if any(o > s.off for o in above) else 0
            s.array_len = array_bytes(top - s.off) // s.array
    late = getattr(lf, 'inline_decls', [])
    ranks = {id(s): n + 1 for n, s in enumerate(late)}
    ordered = name_locals(locals_, ranks) if names else sorted(locals_, key=lambda s: s.off)
    lines = ['{']
    shown = [s for s in ordered if id(s) not in ranks]
    for s in shown:
        lines.append('    ' + declare(s, s.name or SlotVar(s).render()))
    if shown:
        lines.append('')
    lines += render(body, 1, st.gotos)
    lines.append('}')
    return '\n'.join(lines)




# --- prototypes --------------------------------------------------------------------

TYPE_WORDS = {'int', 'char', 'short', 'long', 'void', 'float', 'double', 'unsigned', 'signed',
              'const', 'volatile', 'size_t', 'struct', 'class', 'enum', '__int64'}


def param_type(p):
    p = p.strip()
    p = re.sub(r'=.*$', '', p).strip()
    toks = re.findall(r'\w+|\*|&|\[\]', p)
    if not toks or toks == ['void']:
        return None
    if len(toks) >= 2 and re.match(r'\w+$', toks[-1]) and toks[-1] not in TYPE_WORDS \
            and toks[-2] not in ('struct', 'class', 'enum'):
        toks = toks[:-1]
    t = ' '.join(toks).replace(' *', '*').replace('* ', '*')
    return t.replace('[]', '*')


def split_top(s, sep=','):
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch == sep and depth == 0:
            out.append(cur)
            cur = ''
            continue
        depth += {'(': 1, ')': -1, '<': 1, '>': -1}.get(ch, 0)
        cur += ch
    if cur.strip():
        out.append(cur)
    return out


def parse_decl(chunk):
    chunk = re.sub(r'\)\s*=\s*0\s*$', ')', chunk.strip())     # pure virtual
    chunk = re.sub(r'__declspec\s*\([^)]*\)', '', chunk)
    chunk = re.sub(r'extern\s+"C"', '', chunk)
    m = re.match(r'^(.*?)\b(~?\w+)\s*\((.*)\)\s*(const)?\s*$', chunk.strip())
    if not m:
        return None
    prefix, name, params = m.groups()[:3]
    ret = re.sub(r'\b(extern|static|inline|__inline|__forceinline|virtual|__stdcall|__cdecl|'
                 r'WINAPI|__fastcall|__thiscall)\b', '', prefix).strip()
    ret = re.sub(r'\s+', ' ', ret).replace(' *', '*')
    if re.search(r'[(){}=]', ret):
        return None
    ptypes = [param_type(p) for p in split_top(params)]
    ptypes = [t for t in ptypes if t is not None]
    return name, ret or 'int', ptypes


PROTO_HEADERS = '''#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <windows.h>
#include <ddraw.h>
#define DIRECTINPUT_VERSION 0x0700
#include <dinput.h>
#include <mmsystem.h>
#include <dsound.h>
'''


def preprocess_headers(pre):
    """The CRT and SDK headers the game uses, run through the preprocessor."""
    os.makedirs(os.path.dirname(pre), exist_ok=True)
    src = os.path.join(os.path.dirname(pre), 'all.cpp')
    with open(src, 'w') as f:
        f.write(PROTO_HEADERS)
    rel = os.path.relpath(src, REPO)
    with open(pre, 'w') as out:
        subprocess.run([os.path.join(REPO, 'tools', 'msvc'), 'cl', '/nologo', '/E', '/D', 'WIN32',
                        '/D', 'NDEBUG', '/D', '_WINDOWS', '/D', '_MBCS', rel], cwd=REPO,
                       stdout=out, stderr=subprocess.DEVNULL, check=True)


# --- struct layouts ------------------------------------------------------------------

BASIC_SIZES = {'char': 1, 'BYTE': 1, 'bool': 1, 'short': 2, 'WORD': 2, 'int': 4, 'DWORD': 4,
               'BOOL': 4, 'long': 4, 'float': 4, 'double': 8, 'HWND': 4, 'HANDLE': 4,
               'RECT': 16, 'POINT': 8, 'GUID': 16, 'UINT': 4, 'DIJOYSTATE': 0x50,
               'PALETTEENTRY': 4, 'DDSURFACEDESC': 0x6c, 'DSBUFFERDESC': 0x24}
ALIGN4 = ('RECT', 'POINT', 'GUID', 'DIJOYSTATE', 'DDSURFACEDESC', 'DSBUFFERDESC')
ALIGN1 = ('PALETTEENTRY',)      # four BYTEs


class Layouts:
    """Field offsets of the POD structs declared in src/*.h, computed with natural
    alignment: {struct: (size, align, {offset: (name, type, count)})}."""

    def __init__(self):
        self.structs = {}
        for fn in sorted(os.listdir(os.path.join(REPO, 'src'))):
            if fn.endswith('.h'):
                self.parse(open(os.path.join(REPO, 'src', fn), encoding='utf-8').read())

    def type_info(self, t):
        t = t.strip()
        if t.endswith('*'):
            return 4, 4
        if t in BASIC_SIZES:
            n = BASIC_SIZES[t]
            return n, 4 if t in ALIGN4 else 1 if t in ALIGN1 else n
        if t in self.structs:
            size, align, _ = self.structs[t]
            return size, align
        return None

    def parse(self, text):
        text = re.sub(r'//[^\n]*', '', text)
        for m in re.finditer(r'^(?:struct|class) (\w+)(?: : public (\w+))? \{\n(.*?)^\};', text,
                             re.S | re.M):
            name, base, body = m.group(1), m.group(2), m.group(3)
            if base:
                continue        # derived classes: their fields are raw offsets anyway
            virtual = 'virtual' in body
            body = re.sub(r'\b(public|private|protected)\s*:', '', body)
            # drop inline method bodies
            while True:
                b = re.sub(r'\{[^{}]*\}', ';', body)
                if b == body:
                    break
                body = b
            fields, off, align, ok = {}, (4 if virtual else 0), (4 if virtual else 1), True
            for decl in body.split(';'):
                decl = ' '.join(decl.split())
                if not decl or '(' in decl or decl.startswith(('virtual', 'typedef', 'enum')):
                    continue
                fm = re.match(r'^(.*?)\s*\b(\w+)((?:\[[\w +\-*]+\])*)$', decl)
                if not fm:
                    ok = False
                    break
                ty, fname, dims = fm.group(1).replace(' *', '*'), fm.group(2), fm.group(3)
                info = self.type_info(ty)
                if info is None:
                    ok = False
                    break
                fsize, falign = info
                n = 1
                for d in re.findall(r'\[([\w +\-*]+)\]', dims):
                    n *= int(eval(d, {'__builtins__': {}}))     # (only numbers and + - *)
                count = dims or None
                off = (off + falign - 1) // falign * falign
                fields[off] = (fname, ty, n)
                off += fsize * n
                align = max(align, falign)
            if ok and fields:
                size = (off + align - 1) // align * align
                self.structs[name] = (size, align, fields)

    def field_type(self, struct, off):
        """The declared type of the field at `off` (an array's element type), or None."""
        info = self.structs.get(struct)
        if not info:
            return None
        for foff, (name, fty, n) in info[2].items():
            size = (self.type_info(fty) or (0, 0))[0]
            if foff <= off < foff + size * n and (off - foff) % max(size, 1) == 0:
                return fty
        return None

    def array_field(self, struct, off):
        """(name, element type, element size, offset within the element) of the array
        field containing `off`, or None."""
        info = self.structs.get(struct)
        if not info:
            return None
        for foff, (name, fty, n) in info[2].items():
            size = (self.type_info(fty) or (0, 0))[0]
            if n > 1 and size and foff <= off < foff + size * n:
                return name, fty, size, (off - foff) % size
        return None

    def field(self, struct, off, ty=None):
        """The name of the field at `off`, or None."""
        info = self.structs.get(struct)
        if not info:
            return None
        f = info[2].get(off)
        if f is None:
            return None
        name, fty, n = f
        if n != 1:
            return None
        return name



_INTERFACES = None


def interfaces():
    """{interface: [method names in vtable order]} from the DirectX SDK headers."""
    global _INTERFACES
    if _INTERFACES is not None:
        return _INTERFACES
    cache = os.path.join(REPO, 'build', 'interfaces.json')
    if os.path.exists(cache):
        _INTERFACES = json.load(open(cache))
        return _INTERFACES
    toolchain = os.environ.get('EFZ_TOOLCHAIN', os.path.expanduser('~/tools/efz-toolchain'))
    decls = {}
    for h in ('dinput.h', 'ddraw.h', 'dsound.h'):
        path = os.path.join(toolchain, 'dxsdk', 'Include', h)
        if not os.path.exists(path):
            continue
        text = open(path, encoding='latin-1').read()
        for m in re.finditer(r'DECLARE_INTERFACE_\(\s*(\w+)\s*,\s*(\w+)\s*\)\s*\{(.*?)\};',
                             text, re.S):
            name, base, body = m.groups()
            methods = re.findall(r'STDMETHOD_?\(\s*(?:\w+\s*,\s*)?(\w+)\s*\)', body)
            decls[name] = (base, methods)
    out = {}
    for name in decls:
        chain, n = [], name
        while n in decls:
            chain.insert(0, decls[n][1])
            n = decls[n][0]
        # IUnknown's own methods are in each derived body as STDMETHOD lines too
        flat = []
        for methods in chain:
            for x in methods:
                if x not in flat:
                    flat.append(x)
        out[name] = flat
        if name.endswith('A'):
            out.setdefault(name[:-1], flat)       # the ANSI build's typedef
    _INTERFACES = out
    json.dump(out, open(cache, 'w'))
    return out

_LAYOUTS = None


def layouts():
    global _LAYOUTS
    if _LAYOUTS is None:
        _LAYOUTS = Layouts()
    return _LAYOUTS


class Protos:
    def __init__(self):
        cache = os.path.join(REPO, 'build', 'protos.json')
        pre = os.path.join(REPO, 'build', 'protos', 'all.i')
        if not os.path.exists(pre):
            preprocess_headers(pre)
        if os.path.exists(cache) and os.path.getmtime(cache) >= os.path.getmtime(pre):
            self.free = json.load(open(cache))
        else:
            self.free = {}
            text = open(pre, encoding='latin-1').read()
            text = re.sub(r'#line \d+ "[^"]*"', '', text)
            text = re.sub(r'\s+', ' ', text)
            for chunk in re.split(r'[;{}]', text):
                if '(' not in chunk:
                    continue
                d = parse_decl(chunk)
                if d and d[0] not in self.free:
                    self.free[d[0]] = [d[1], d[2]]
            json.dump(self.free, open(cache, 'w'))
        self.free['operator new'] = ['void*', ['size_t']]
        self.free['operator delete'] = ['void', ['void*']]
        self.methods = {}
        for fn in os.listdir(os.path.join(REPO, 'src')):
            if fn.endswith('.h'):
                self.parse_header(open(os.path.join(REPO, 'src', fn), encoding='utf-8').read())

    def parse_header(self, text):
        text = re.sub(r'//[^\n]*', '', text)
        text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
        text = re.sub(r'#[^\n]*', '', text)
        # class bodies: track scope by braces
        stack = []
        pending = None
        cur = ''
        depth = 0
        for tok in re.split(r'([;{}])', text):
            if tok == '{':
                m = re.search(r'\b(class|struct)\s+(\w+)[^;]*$', cur)
                if m and '(' not in cur.split(m.group(2))[-1]:
                    stack.append((m.group(2), depth))
                elif stack and stack[-1][1] == depth - 1:
                    self.method(stack[-1][0], cur)      # an inline method's header
                depth += 1
                cur = ''
            elif tok == '}':
                depth -= 1
                if stack and stack[-1][1] == depth:
                    stack.pop()
                cur = ''
            elif tok == ';':
                if stack and stack[-1][1] == depth - 1:
                    self.method(stack[-1][0], cur)
                elif not stack and '(' in cur:
                    d = parse_decl(cur.replace('\n', ' '))
                    if d:
                        self.free[d[0]] = [d[1], d[2]]
                cur = ''
            else:
                cur += tok

    def method(self, cls, decl):
        decl = re.sub(r'\b(public|private|protected)\s*:', '', decl).replace('\n', ' ')
        if '(' not in decl:
            return
        d = parse_decl(decl)
        if d:
            name, ret, params = d
            if name == cls or name == '~' + cls:
                ret = 'void'
            self.methods[f'{cls}::{name}'] = [ret, params]

    def lookup(self, qual):
        if qual in self.methods:
            return self.methods[qual]
        return self.free.get(qual.split('::')[-1] if '::' not in qual else qual)


POINTERISH = re.compile(r'(\*|^LP|^P[A-Z]|^H[A-Z]|^HANDLE$|^HWND$|^HINSTANCE$|^HMODULE$|'
                        r'^REFGUID$|^REFIID$|^LPC?STR$|^HMMIO$|^HPSTR$)')


def is_pointer_type(t):
    return bool(POINTERISH.search(t.replace('const ', '')))




# --- source-level patterns -----------------------------------------------------------

VEC_CTOR = 0x408380      # `vector constructor iterator'
VEC_DTOR = 0x4082a0      # `vector destructor iterator'


class NewArray(E):
    def __init__(self, cls, count):
        self.cls, self.count = cls, count
        self.ty = 'char*'

    def render(self):
        n = fmt_int(self.count) if isinstance(self.count, int) else self.count.text(PREC['='] + 1)
        return f'(char*)new {self.cls}[{n}]'


class NewObject(E):
    prec = PREC['unary']

    def __init__(self, cls, call):
        self.cls, self.call = cls, call
        self.ty = cls + '*'

    def uses(self):
        return list(self.call.args)

    def has_side_effects(self):
        return True

    def render(self):
        args = Call('', self.call.args)
        args.ptypes = getattr(self.call, 'ptypes', None)
        return f'new {self.cls}{args.render()}'


class DeleteStmt(S):
    def __init__(self, e, cls, array):
        self.e, self.cls, self.array = e, cls, array

    def lines(self):
        return [f'delete{"[]" if self.array else ""} ({self.cls}*){self.e.text(PREC["cast"])};']


class PadStmt(S):
    """`if (0) {}`: no code, but each one advances the compiler's register rotation
    (eax, ecx, edx) by one step. The original has dead code here that did the same;
    tools/regfix.py finds where."""

    def __init__(self, n):
        self.n = n

    def lines(self):
        return ['if (0) {}'] * self.n


class DeclStmt(S):
    """A class-typed local constructed where it is declared."""

    def __init__(self, slot, cls, call):
        self.slot, self.cls, self.call = slot, cls, call

    def lines(self):
        args = Call('', self.call.args)
        args.ptypes = getattr(self.call, 'ptypes', None)
        v = SlotVar(self.slot)
        v.whole = True
        name = v.render()
        a = args.render()[1:-1]
        return [f'{self.cls} {name}({a});' if a else f'{self.cls} {name};']


def call_of(e):
    """The Call inside `e` (through an int cast), or None."""
    if isinstance(e, Cast):
        e = e.e
    return e if isinstance(e, Call) else None


def stmt_of(n):
    return n.s if isinstance(n, StmtNode) else None


def slot_of(e):
    return e.slot if isinstance(e, SlotVar) else None


def rewrite_patterns(nodes, syms, ctx):
    """Turn compiler-expanded forms back into new[], delete[] and implicit member
    construction."""
    gotos = ctx.get('gotos', ())
    top = ctx.get('top') is nodes
    nodes = [n for n in nodes if not (isinstance(n, Lbl) and n.addr not in gotos)]
    if top:
        ctx['top'] = nodes
    out = []
    k = 0
    while k < len(nodes):
        n = nodes[k]
        for attr in ('then', 'els', 'body'):
            sub = getattr(n, attr, None)
            if isinstance(sub, list):
                setattr(n, attr, rewrite_patterns(sub, syms, ctx))
        if isinstance(n, Switch):
            n.cases = [(v, d, rewrite_patterns(b, syms, ctx)) for v, d, b in n.cases]
        st = stmt_of(n)
        # t = operator new(n * size + 4); if (t) { *t = n; vector ctor(t+4, size, n, ctor);
        # r = t + 4; } else r = 0; dest = r;
        if isinstance(st, Assign) and not st.op and slot_of(st.lhs) and k + 2 < len(nodes):
            c = call_of(st.rhs)
            nx = nodes[k + 1]
            if c is not None and c.fn == 'operator new' and isinstance(nx, If) and nx.els \
                    and len(nx.then) == 3:
                vc = stmt_of(nx.then[1])
                vcall = call_of(vc.e) if isinstance(vc, ExprStmt) else None
                fin = stmt_of(nodes[k + 2])
                if vcall is not None and getattr(vcall, 'target', None) == VEC_CTOR \
                        and isinstance(fin, Assign) and slot_of(fin.rhs):
                    count = vcall.args[2]
                    ctor = vcall.args[3]
                    caddr = ctor.e.v if isinstance(ctor, Cast) else ctor.v
                    cls = syms.funcs.get(caddr, f'C{caddr:x}::').split('::')[0]
                    st.lhs.slot.temp = True
                    fin.rhs.slot.temp = True
                    # the count copied into a temporary just before: new X[n]
                    prev = stmt_of(out[-1]) if out else None
                    if isinstance(count, SlotVar) and isinstance(prev, Assign) and not prev.op \
                            and slot_of(prev.lhs) is count.slot and ctx.get('top') is not None:
                        if '_counts' not in ctx:
                            ctx['_counts'] = slot_counts(ctx['top'])
                        w_all, r_all = ctx['_counts']
                        w_in, r_in = slot_counts(nodes[k:k + 3])
                        if w_all[count.slot] == 1 and r_all[count.slot] == r_in[count.slot]:
                            out.pop()
                            count.slot.temp = True
                            count = prev.rhs
                    out.append(StmtNode(Assign(fin.lhs, NewArray(cls, count))))
                    k += 3
                    continue
        # t = operator new(n); if (t) r = t->X(args); else r = 0; dest = r;  ->  new X(args)
        if isinstance(st, Assign) and not st.op and slot_of(st.lhs) and k + 2 < len(nodes):
            c = call_of(st.rhs)
            nx = nodes[k + 1]
            pads = []
            if c is not None and c.fn == 'operator new' and isinstance(nx, If) and nx.els:
                pads = [x for x in nx.then if isinstance(stmt_of(x), PadStmt)]
                if pads and len(nx.then) - len(pads) == 1:
                    nx.then = [x for x in nx.then if x not in pads]
                    out += pads         # (register rotation: before the statement)
            if c is not None and c.fn == 'operator new' and isinstance(nx, If) and nx.els \
                    and len(nx.then) == 1 and len(nx.els) == 1:
                cs = stmt_of(nx.then[0])
                ctor = call_of(cs.rhs) if isinstance(cs, Assign) else None
                fin = stmt_of(nodes[k + 2])
                name = syms.funcs.get(getattr(ctor, 'target', None)) if ctor is not None else None
                if name and name.rpartition('::')[2] == name.rpartition('::')[0].split('::')[-1] \
                        and isinstance(fin, Assign) and slot_of(fin.rhs) \
                        and slot_of(cs.lhs) is fin.rhs.slot:
                    st.lhs.slot.temp = True
                    fin.rhs.slot.temp = True
                    out.append(StmtNode(Assign(fin.lhs, NewObject(name.rpartition('::')[0], ctor))))
                    k += 3
                    continue
        # t1 = p; t2 = t1; if (t2) r = t2->??_E(3); else r = 0;   ->   delete[] p;
        if isinstance(st, Assign) and not st.op and slot_of(st.lhs) and k + 2 < len(nodes):
            st2 = stmt_of(nodes[k + 1])
            nx = nodes[k + 2]
            # at the end of a function the else branch can come out as
            # `if (t2) { r = ...; return; } r = 0;`
            if isinstance(nx, If) and not nx.els and len(nx.then) == 2 \
                    and isinstance(nx.then[1], Jmp) and nx.then[1].kind == 'return' \
                    and k + 4 == len(nodes) and isinstance(stmt_of(nodes[k + 3]), Assign):
                nx.then = nx.then[:1]
                nx.els = [nodes[k + 3]]
                nodes = nodes[:k + 3]
            if isinstance(st2, Assign) and slot_of(st2.lhs) and slot_of(st2.rhs) is st.lhs.slot \
                    and isinstance(nx, If) and len(nx.then) == 1:
                inner = stmt_of(nx.then[0])
                c = call_of(inner.rhs) if isinstance(inner, Assign) else None
                if c is not None and isinstance(c.args[0] if c.args else None, Const) \
                        and getattr(c, 'target', None) in syms.funcs:
                    name = syms.funcs[c.target]
                    flag = c.args[0].v
                    cls = deleting_class(name)
                    if cls:
                        st.lhs.slot.temp = True
                        st2.lhs.slot.temp = True
                        inner.lhs.slot.temp = True if slot_of(inner.lhs) else None
                        out.append(StmtNode(DeleteStmt(st.rhs, cls, flag == 3)))
                        k += 3
                        continue
        # t = p; operator delete(t);  ->  delete (char*)p;  (t being the delete's temporary)
        if isinstance(st, Assign) and not st.op and slot_of(st.lhs) and k + 1 < len(nodes) \
                and ctx.get('top') is not None:
            nst = stmt_of(nodes[k + 1])
            c = call_of(nst.e) if isinstance(nst, ExprStmt) else None
            arg = c.args[0] if c is not None and c.fn == 'operator delete' and c.args else None
            if isinstance(arg, Cast):
                arg = arg.e
            if isinstance(arg, SlotVar) and arg.slot is st.lhs.slot:
                if '_counts' not in ctx:
                    ctx['_counts'] = slot_counts(ctx['top'])
                writes, reads = ctx['_counts']
                if writes[arg.slot] == 1 and reads[arg.slot] == 1:
                    arg.slot.temp = True
                    out.append(StmtNode(DeleteStmt(st.rhs, 'char', False)))
                    k += 2
                    continue
        # a class-typed local: constructed where it is declared, destroyed implicitly
        if isinstance(st, ExprStmt):
            c = call_of(st.e)
            obj = c.this if c is not None else None
            if isinstance(obj, AddrOfVar) and isinstance(obj.v, SlotVar):
                cls = getattr(c, 'cls', None)
                sl = obj.v.slot
                if cls and c.fn == cls.split('::')[-1]:
                    sl.cls = cls
                    info = layouts().structs.get(cls)
                    if info and ctx.get('lf') is not None:
                        ctx['lf'].struct_slot(sl.off, info[0], cls)
                    ctx.setdefault('inline_decls', []).append(sl)
                    out.append(StmtNode(DeclStmt(sl, cls, c)))
                    k += 1
                    continue
                if cls and c.fn == '~' + cls.split('::')[-1] and getattr(sl, 'cls', None) == cls:
                    k += 1
                    continue
        # destructors: the base class's destructor runs implicitly at the end (the last
        # such call; an earlier one is an explicit call in the source)
        if ctx.get('dtor') and isinstance(st, ExprStmt) and ctx.get('top') is nodes:
            c = call_of(st.e)
            name = syms.funcs.get(getattr(c, 'target', None)) if c is not None else None
            later = [x for x in nodes[k + 1:] if not isinstance(x, (Lbl, Jmp))]
            if name and name.rpartition('::')[2].startswith('~') and c.this is None and not later:
                k += 1
                continue
        # constructors: member construction is implicit, and so is `return this`
        if ctx.get('ctor') and isinstance(st, Return) and isinstance(st.e, ThisVar):
            k += 1
            continue
        if ctx.get('ctor') and isinstance(st, ExprStmt) and ctx.get('top') is nodes:
            c = call_of(st.e)
            name = syms.funcs.get(getattr(c, 'target', None)) if c is not None else None
            if c is not None and c.this is None and name:
                cls, _, meth = name.rpartition('::')
                if cls and meth == cls.split('::')[-1]:
                    # the base class constructor
                    ctx['base_init'] = (cls, c)
                    k += 1
                    continue
        if ctx.get('ctor') and isinstance(st, ExprStmt):
            c = call_of(st.e)
            if c is not None and c.this is not None and getattr(c, 'target', None) in syms.funcs:
                name = syms.funcs[c.target]
                cls, _, meth = name.rpartition('::')
                if cls and meth == cls.split('::')[-1]:
                    ctx.setdefault('members', []).append((member_offset(c.this), cls))
                    # stores to fields before a member's construction are initializers
                    # of fields declared before it
                    if ctx.get('top') is nodes:
                        inits = ctx.setdefault('initializers', [])
                        while out and isinstance(stmt_of(out[-1]), Assign) \
                                and this_field_offset(stmt_of(out[-1]).lhs) is not None:
                            a = stmt_of(out.pop())
                            inits.insert(0, (this_field_offset(a.lhs), a.lhs.ty, a.rhs))
                    k += 1
                    continue
        out.append(n)
        k += 1
    return out


# --- compiler temporaries ------------------------------------------------------------

def expr_children(e):
    for k, v in vars(e).items():
        if k in ('slot',):
            continue
        if isinstance(v, E):
            yield k, None, v
        elif isinstance(v, list):
            for n, x in enumerate(v):
                if isinstance(x, E):
                    yield k, n, x


def walk_expr(e):
    yield e
    for _, _, c in expr_children(e):
        yield from walk_expr(c)


def subst_expr(e, slot, val):
    """e with reads of `slot` replaced by val (in place where possible)."""
    if isinstance(e, SlotVar) and e.slot is slot and not getattr(e, 'whole', False):
        return val
    if isinstance(e, Bin) and e.op in ('+', '*') and e.ty in ('double', 'float') \
            and isinstance(e.b, SlotVar) and e.b.slot is slot and slot.float:
        # an FPU value spilled while the other operand (a call) was evaluated: it was
        # the left operand
        e.a, e.b = e.b, e.a
    for k, n, c in list(expr_children(e)):
        r = subst_expr(c, slot, val)
        if r is not c:
            if n is None:
                setattr(e, k, r)
            else:
                getattr(e, k)[n] = r
    return e


def stmt_exprs(st):
    """(holder, attribute) pairs for the expressions a statement reads."""
    if isinstance(st, Assign):
        out = [(st, 'rhs')]
        if not isinstance(st.lhs, SlotVar) or st.op:
            out.append((st, 'lhs'))
        return out
    if isinstance(st, (ExprStmt, Return)):
        return [(st, 'e')] if st.e is not None else []
    if isinstance(st, DeleteStmt):
        return [(st, 'e')]
    if isinstance(st, DeclStmt):
        return [(st.call, 'args')]
    return []


def node_exprs(n):
    """Expressions evaluated by a node itself (not its nested blocks)."""
    if isinstance(n, StmtNode):
        return stmt_exprs(n.s)
    if isinstance(n, (If, While, DoWhile)):
        return [(n, 'cond')] if n.cond is not None else []
    if isinstance(n, For):
        out = [(n, 'cond')] if n.cond is not None else []
        for st in n.inc or []:
            out += stmt_exprs(st)
        return out
    if isinstance(n, Switch):
        return [(n, 'expr')]
    return []


def blocks_of(n):
    out = []
    for attr in ('then', 'els', 'body'):
        b = getattr(n, attr, None)
        if isinstance(b, list):
            out.append(b)
    if isinstance(n, Switch):
        out += [b for _, _, b in n.cases]
    return out


def all_nodes(nodes):
    for n in nodes:
        yield n
        for b in blocks_of(n):
            yield from all_nodes(b)


def reads_of(holder, attr):
    v = getattr(holder, attr)
    items = v if isinstance(v, list) else [v]
    for x in items:
        if isinstance(x, E):
            yield from walk_expr(x)


def slot_counts(nodes):
    """{slot: (writes, reads)} over a node tree."""
    writes, reads = collections.Counter(), collections.Counter()
    for n in all_nodes(nodes):
        if isinstance(n, StmtNode) and isinstance(n.s, Assign) and isinstance(n.s.lhs, SlotVar):
            writes[n.s.lhs.slot] += 1
        if isinstance(n, For):
            for st in n.inc or []:
                if isinstance(st, Assign) and isinstance(st.lhs, SlotVar):
                    writes[st.lhs.slot] += 1
        for holder, attr in node_exprs(n):
            for e in reads_of(holder, attr):
                if isinstance(e, SlotVar):
                    reads[e.slot] += 1
    return writes, reads


def is_assign_const(n, slot, v):
    return isinstance(n, StmtNode) and isinstance(n.s, Assign) and not n.s.op \
        and isinstance(n.s.lhs, SlotVar) and n.s.lhs.slot is slot \
        and isinstance(n.s.rhs, Const) and n.s.rhs.v == v


def fold_temps(nodes, temps, this_class=None):
    """Compiler temporaries (slots no named local can occupy) back into expressions:
    `if (c) t = 1; else t = 0;` is the value of c, and a temporary written once and
    read once is its value at the place it is read."""
    if not temps:
        return nodes
    for n in all_nodes(nodes):
        for b in blocks_of(n):
            b[:] = fold_block(b, temps, this_class)
    nodes[:] = fold_block(nodes, temps, this_class)
    writes, reads = slot_counts(nodes)
    # The compiler reuses a temporary's slot from one statement to the next, so a slot can
    # be written several times; each value is read once, in the statement that follows.
    for lst in [nodes] + [b for n in all_nodes(nodes) for b in blocks_of(n)]:
        k = 0
        while k < len(lst) - 1:
            n = lst[k]
            if not (isinstance(n, StmtNode) and isinstance(n.s, Assign) and not n.s.op
                    and isinstance(n.s.lhs, SlotVar) and n.s.lhs.slot in temps):
                k += 1
                continue
            sl = n.s.lhs.slot
            if reads[sl] == 0 and isinstance(n.s.rhs, Cond):
                # a comparison whose value is dropped: (int)(c);
                lst[k] = StmtNode(ExprStmt(Cast('int', n.s.rhs)))
                writes[sl] -= 1
                if writes[sl] == 0:
                    sl.temp = True
                k += 1
                continue
            if reads[sl] != writes[sl]:
                k += 1
                continue
            nxt = lst[k + 1]
            found, count = None, 0
            for holder, attr in node_exprs(nxt):
                hits = sum(1 for e in reads_of(holder, attr) if isinstance(e, SlotVar) and e.slot is sl)
                if hits:
                    found, count = (holder, attr), count + hits
            if found is None or count != 1:
                k += 1
                continue
            holder, attr = found
            v = getattr(holder, attr)
            if isinstance(v, list):
                setattr(holder, attr, [subst_expr(x, sl, n.s.rhs) for x in v])
            else:
                setattr(holder, attr, subst_expr(v, sl, n.s.rhs))
            writes[sl] -= 1
            reads[sl] -= 1
            if writes[sl] == 0:
                sl.temp = True
            del lst[k]
            k = max(k - 1, 0)      # the statement before may now feed this one
    return nodes


def base_conversion(n, sl, this_class):
    """`if (p != 0) t = p + off; else t = 0;`: p converted to its base class at off."""
    import objdefs
    c, t, e = n.cond, n.then[0].s, n.els[0]
    if not (isinstance(c, Cond) and c.op == '!=' and isinstance(c.b, Const) and c.b.v == 0):
        return None
    if not is_assign_const(e, sl, 0) or t.op:
        return None
    r = t.rhs
    if isinstance(r, Cast):
        r = r.e
    if not (isinstance(r, Bin) and r.op == '+' and isinstance(r.b, Const)):
        return None
    base = r.a.e if isinstance(r.a, Cast) else r.a
    if not same(base, c.a):
        return None
    cls = this_class if isinstance(base, ThisVar) else 'CPlayer'
    name = objdefs.BASES.get((cls, r.b.v))
    if name is None:
        return None
    src = base if isinstance(base, ThisVar) else Cast(cls + '*', base)
    v = Cast(name + '*', src)
    return v


def fold_block(lst, temps, this_class=None):
    out = []
    for n in lst:
        if isinstance(n, If) and n.els and len(n.then) == 1 and len(n.els) == 1:
            t = n.then[0]
            if isinstance(t, StmtNode) and isinstance(t.s, Assign) and isinstance(t.s.lhs, SlotVar) \
                    and t.s.lhs.slot in temps:
                sl = t.s.lhs.slot
                v = base_conversion(n, sl, this_class)
                if v is not None:
                    sl.declared = v.ty
                    out.append(StmtNode(Assign(t.s.lhs, v)))
                    continue
                if is_assign_const(t, sl, 1) and is_assign_const(n.els[0], sl, 0):
                    out.append(StmtNode(Assign(t.s.lhs, n.cond)))
                    continue
                if is_assign_const(t, sl, 0) and is_assign_const(n.els[0], sl, 1):
                    out.append(StmtNode(Assign(t.s.lhs, negate(n.cond))))
                    continue
        out.append(n)
    return out


def deleting_class(name):
    m = re.match(r'\?\?_([EG])(\w+)@@', name)
    if m:
        return m.group(2)
    return None


def this_field_offset(lv):
    """The offset of a `this` field store target, or None."""
    if not isinstance(lv, Deref):
        return None
    a = lv.addr
    if isinstance(a, Cast) and isinstance(a.e, ThisVar):
        return 0
    if isinstance(a, Bin) and a.op == '+' and isinstance(a.a, Cast) and isinstance(a.a.e, ThisVar) \
            and isinstance(a.b, Const):
        return a.b.v
    return None


def member_offset(e):
    if isinstance(e, Bin) and isinstance(e.b, Const):
        return e.b.v
    return 0

# --- whole objects -----------------------------------------------------------------

def norm_type(t):
    if t in (None, 'this', 'void'):
        return 'int'
    if t == 'char*' or is_pointer_type(t):
        return 'char*'
    return t


def infer_signature(lf):
    """(thiscall, return type, parameter types) from a lifted function."""
    params = []
    off = 8
    limit = lf.ret_pop + 8 if lf.ret_pop else 8 + max([s.off - 8 + 4 for s in lf.slots.values()
                                                       if s.off > 0] + [0])
    while off < limit:
        sl = lf.slots.get(off)
        if sl is not None and getattr(sl, 'declared', None):
            t = sl.declared
        elif sl is not None:
            t = sl.ctype()
            if t == 'char' and not sl.signed:
                # only ever copied, never widened: callers push constants of 0x80 and
                # up unextended, so take it as unsigned
                t = 'BYTE'
        else:
            t = 'int'
        params.append(t)
        off += 8 if t == 'double' else STRUCT_SIZES.get(t, 4)
    rets = [norm_type(t) for t in lf.ret_types]
    ret = rets[0] if rets else 'void'
    if getattr(lf, 'struct_ret', None):
        return lf.this_slot is not None, lf.struct_ret, params[1:]   # hidden result pointer
    return lf.this_slot is not None, ret, params


def lift_object(img, syms, lo, hi, cls, names=None, passes=2):
    import objdefs
    names = dict(names or {})
    funcs = [f['addr'] for f in syms.inventory['functions'] if lo <= f['addr'] < hi]
    sigs = {}
    for a in funcs:
        if a not in syms.funcs:
            syms.funcs[a] = names.get(a, f'{cls}::Unk{a:x}')
    for _ in range(passes):
        for a in funcs:
            qual = syms.funcs[a]
            lf = None
            try:
                lf = Lifter2(img, syms, a, function_end(syms, a))
                lf.vfamily = vfamily(qual)
                lf.execute(sigs.get(a, (None, None))[1] if a in sigs else None)
                # (structured too, for what only shows then: a struct returned through
                # the hidden pointer)
                lf2, _b, _s = lift(img, syms, a, qual=qual)
                lf.struct_ret = lf2.struct_ret
            except Exception as e:
                sigs[a] = (True, 'void', [], f'{type(e).__name__}: {e} at {getattr(lf, "pc", 0):#x}')
                continue
            this, ret, params = infer_signature(lf)
            meth = qual.rsplit('::', 1)[-1]
            if a in objdefs.SIGNATURES:
                ret, params = objdefs.SIGNATURES[a]
                params = list(params)
            elif syms.protos.lookup(f'{base_of(qual)}::{meth}') and (
                    re.match(r'Vf\d+$', meth) or meth in ('Draw', 'Update')):
                # an override has the base class's signature
                ret, params = syms.protos.lookup(f'{base_of(qual)}::{meth}')
                params = list(params)
            sigs[a] = (this, ret, params, None)
            syms.protos.methods[qual] = [ret, params]
    out = []
    for a in funcs:
        qual = syms.funcs[a]
        this, ret, params, err = sigs[a]
        try:
            lf, body, st = lift(img, syms, a, qual=qual)
            text = body_text(lf, body, st)
            inits = []
            if lf.base_init:
                cls_, call = lf.base_init
                inits.append(cls_.split('::')[-1] + call.render()[len(call.fn):])
            # member fields must be declared as unkXX in the class
            inits += [f'unk{off:x}({rhs.text()})' for off, ty, rhs in lf.initializers]
            if inits:
                text = '    : ' + ', '.join(inits) + '\n' + text
            err = None
        except Exception as e:
            import traceback
            tb = traceback.extract_tb(e.__traceback__)[-1]
            text, err = None, f'{type(e).__name__}: {e} (lift.py:{tb.lineno})'
        out.append((a, qual, this, ret, params, text, err))
    return out


def gen_object(img, syms, obj):
    """Lift every function of an object (tools/objdefs.py) and write build/gen/<obj>.cpp
    with the definitions and build/gen/<obj>.h with the declarations."""
    import objdefs
    for o, (l, h, c, n) in objdefs.OBJECTS.items():
        for f in syms.inventory['functions']:
            if l <= f['addr'] < h and f['addr'] not in syms.funcs:
                syms.funcs[f['addr']] = n.get(f['addr'], f'{c}::Unk{f["addr"]:x}')
    lo, hi, cls, names = objdefs.OBJECTS[obj]
    syms.funcs.update(names)        # names given in objdefs win over old annotations
    results = lift_object(img, syms, lo, hi, cls, names)
    os.makedirs(os.path.join(REPO, 'build', 'gen'), exist_ok=True)
    cpp, decl = [], {}
    for a, qual, this, ret, params, text, err in results:
        if qual.startswith('?'):
            continue        # compiler-generated or from a library header
        klass, _, meth = qual.rpartition('::')
        inline = objdefs.is_inline(obj, a)
        head = signature_text(qual, ret, params, decl=inline)
        if err:
            body = f'{{\n    // LIFT FAILED: {err}\n}}'
        else:
            body = text
        d = decl.setdefault(klass, [])
        d.append(f'    // FUNCTION: {a:#x}')
        if inline:
            d.append('    ' + head)
            d += ['    ' + line if line else '' for line in body.split('\n')]
        else:
            d.append('    ' + signature_text(qual, ret, params, decl=True) + ';')
            cpp += [f'// FUNCTION: {a:#x}', head, body, '']
    with open(os.path.join(REPO, 'build', 'gen', obj + '.cpp'), 'w') as f:
        f.write('\n'.join(cpp))
    with open(os.path.join(REPO, 'build', 'gen', obj + '.h'), 'w') as f:
        for klass, lines in decl.items():
            f.write(f'// {klass}\n' + '\n'.join(lines) + '\n\n')
    return results


def add_class(header, obj, gen=None):
    """Declare a character class (or one of the other classes in objdefs.CLASSES) in efz.h
    if it isn't there yet. A class spread over several objects is declared from all of
    their generated headers; `gen(o)` generates a missing one."""
    import objdefs
    entries = [(o, cls, 'CPlayer', size) for o, cls, lo, hi, vt, ctor, size in objdefs.CHARACTERS]
    entries += [(c[0], c[1], c[2], c[9]) for c in objdefs.CLASSES]
    for o, cls, base, size in entries:
        if cls != objdefs.OBJECTS[obj][2]:
            continue
        # a generated class block is rebuilt each time
        m = re.search(rf'^// \w+: (?:one of the character classes|derived from \w+)\.\n// SIZE: '
                      rf'0x[0-9a-f]+\nclass {cls} : public \w+ {{\n.*?^}};\n\n', header, re.S | re.M)
        if m:
            header = header[:m.start()] + header[m.end():]
        elif re.search(rf'^class {cls}\b', header, re.M):
            continue
        parts = []
        for o2 in sorted((o2 for o2, v in objdefs.OBJECTS.items() if v[2] == cls),
                         key=lambda o2: objdefs.OBJECTS[o2][0]):
            path = os.path.join(REPO, 'build', 'gen', o2 + '.h')
            if not os.path.exists(path) and gen:
                gen(o2)
            text = open(path).read()
            parts.append(text.split(f'// {cls}\n', 1)[1].split('\n\n', 1)[0])
        body = '\n'.join(parts)
        slots = '|'.join(['Vf\\d+', 'Draw', 'Update'])
        body = re.sub(rf'^(    )(\w[^(\n]* (?:{slots})\()', r'\1virtual \2', body, flags=re.M)
        name = o[0].upper() + o[1:]
        what = 'one of the character classes' if base == 'CPlayer' else f'derived from {base}'
        block = (f'// {name}: {what}.\n'
                 f'// SIZE: {size:#x}\n'
                 f'class {cls} : public {base} {{\npublic:\n{body}\n')
        if base == 'CPlayer':
            block += f'\n    BYTE unk3138[{size:#x} - 0x3138];\n'
        elif size:
            block += f'\n    BYTE unk[{size:#x} - sizeof({base})];\n'
        block += '};\n\n'
        k = header.rindex('#endif')
        header = header[:k] + block + header[k:]
    return header


def signature_text(qual, ret, params, decl=False):
    name = qual.split('::')[-1] if decl else qual
    args = ', '.join(f'{t} p{n + 1}' for n, t in enumerate(params))
    if name.split('::')[-1].startswith('~') or name.split('::')[-1] == qual.split('::')[0]:
        return f'{name}({args})'
    return f'{ret} {name}({args})'


def main():
    img = Image(os.path.join(os.environ['EFZ_DIR'], 'efz.exe'))
    syms = Symbols(img)
    cmd = sys.argv[1]
    addr = int(sys.argv[2], 16) if cmd not in ('gen', 'write') else None
    if cmd == 'items':
        lf = Lifter2(img, syms, addr, function_end(syms, addr))
        dump_items(lf.execute())
    elif cmd == 'body':
        lf, body, st = lift(img, syms, addr)
        print(body_text(lf, body, st))
    elif cmd == 'gen':
        for a, qual, this, ret, params, text, err in gen_object(img, syms, sys.argv[2]):
            print(f'{a:#x} {qual}: ' + (err or 'ok'))
    elif cmd == 'write':
        # regenerate src/<obj>.cpp, keeping its leading comment and #includes
        obj = sys.argv[2]
        import objdefs
        hpath = os.path.join(REPO, 'src', 'efz.h')
        header = open(hpath, encoding='utf-8').read()
        for a, qual, this, ret, params, text, err in gen_object(img, syms, obj):
            if err:
                print(f'{a:#x} {qual}: {err}')
            if objdefs.is_inline(obj, a) or qual.startswith('?'):
                continue
            # keep the header's declaration in step with the definition
            decl = signature_text(qual, ret, params, decl=True)
            header = re.sub(rf'(// FUNCTION: {a:#x}\n[ \t]*(?:virtual )?)[^\n;]*;',
                            lambda m: m.group(1) + decl + ';', header)
        header = add_class(header, obj, gen=lambda o: gen_object(img, syms, o))
        open(hpath, 'w', encoding='utf-8').write(header)
        path = os.path.join(REPO, 'src', obj + '.cpp')
        old = open(path, encoding='utf-8').read() if os.path.exists(path) else ''
        incs = list(re.finditer(r'^#include .*\n', old, re.M))
        lo, hi, cls, _names = objdefs.OBJECTS[obj]
        prefix = old[:incs[-1].end()] if incs else (
            f'// {cls} ({lo:#x}-{hi - 1:#x}).\n'
            '#include <stdlib.h>\n#include <string.h>\n#include <math.h>\n#include "efz.h"\n')
        # keep the globals defined after the #includes (comment lines and declarations)
        if incs:
            kept = re.match(r'\n((?://[^\n]*\n|[^\n(/]*;\n)+)', old[incs[-1].end():])
            if kept:
                prefix += '\n' + kept.group(1)
        body = open(os.path.join(REPO, 'build', 'gen', obj + '.cpp')).read()
        # methods are annotated in the header
        body = re.sub(r'^// FUNCTION: 0x[0-9a-f]+\n(?=[^\n]*\b\w+::~?\w+\()', '', body, flags=re.M)
        with open(path, 'w', encoding='utf-8') as f:
            f.write(prefix + '\n' + body.rstrip() + '\n')
    elif cmd == 'object':
        hi, cls = int(sys.argv[3], 16), sys.argv[4]
        for a, qual, this, ret, params, text, err in lift_object(img, syms, addr, hi, cls):
            print(f'// FUNCTION: {a:#x}')
            if err:
                print(f'// LIFT FAILED: {err}')
                print(f'// {signature_text(qual, ret, params)};')
                continue
            print(signature_text(qual, ret, params))
            print(text)
            print()


if __name__ == '__main__':
    main()
