#!/usr/bin/env python3
"""Rewrite raw offset accesses into the members src/efz.h declares.

The lifter (tools/lift.py) writes every field access as a cast of a pointer plus an offset:

    *(short*)((char*)this + 0x2b00) = -0x1d;
    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)

This tool parses the sources with clang, follows each such address through the classes
efz.h declares (bases, nested structs, arrays, pointer members) and replaces it with the
member it names:

    unk2b00 = -0x1d;
    (*m_opponent)->x

The rewrite keeps the meaning exactly, so the compiled code is unchanged: an access whose
type differs from the member's becomes a cast of the member, `(short)m_frame`, or, where a
cast of the value would not do, a cast of its address, `*(short*)&m_frame`. Offsets that
fall in a class's unnamed padding are left alone and reported by `scan`.

Usage:
    tools/members.py scan [--json OUT] [files...]   accesses that hit padding, per class
    tools/members.py rewrite [files...]             rewrite src/*.cpp (and efz.h) in place
    tools/members.py check [files...]               what rewrite would change, as a diff
    tools/members.py layout                         check efz.h's offsets and sizes
    tools/members.py rename RENAMES                 rename members and methods: lines
                                                    "Class::member name"

Needs the libclang Python package (pip install libclang) and the toolchain's headers
(toolchain/setup.sh); efz.h is parsed as the compiler sees it, with the PSDK and DirectX
SDK headers. Run `make check` afterwards: the rebuilt efz.exe must still be identical.
"""
import collections
import ctypes
import difflib
import json
import multiprocessing
import os
import re
import sys

import clang.cindex as ci
from clang.cindex import CursorKind as CK
from clang.cindex import TypeKind as TK

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(REPO, 'src')
TOOLCHAIN = os.environ.get('EFZ_TOOLCHAIN', os.path.expanduser('~/tools/efz-toolchain'))
INCLUDE_DIRS = ['msvc71/include', 'psdk/Include', 'dxsdk/Include']
FARM = os.path.join(REPO, 'build', 'clang-include')

lib = ci.conf.lib
lib.clang_getCursorBinaryOperatorKind.argtypes = [ci.Cursor]
lib.clang_getCursorBinaryOperatorKind.restype = ctypes.c_int
lib.clang_getCursorUnaryOperatorKind.argtypes = [ci.Cursor]
lib.clang_getCursorUnaryOperatorKind.restype = ctypes.c_int

# Not calls: passing a struct by value wraps a call in an implicit copy with its extent.
EXPLICIT_KINDS = {CK.PAREN_EXPR, CK.CSTYLE_CAST_EXPR, CK.UNARY_OPERATOR, CK.BINARY_OPERATOR,
                  CK.COMPOUND_ASSIGNMENT_OPERATOR, CK.ARRAY_SUBSCRIPT_EXPR,
                  CK.CONDITIONAL_OPERATOR}


def in_macro(c):
    """Whether a cursor comes from a macro expansion (IDI_APPLICATION and the like): its
    nodes all get the macro name's extent, so an operator shares it with an operand."""
    if c.kind not in EXPLICIT_KINDS:
        return False
    e = c.extent
    for ch in c.get_children():
        ce = ch.extent
        if ce.start.offset == e.start.offset and ce.end.offset == e.end.offset:
            return True
    return False


# CXBinaryOperatorKind and CXUnaryOperatorKind (clang-c/Index.h)
BINARY = {3: '*', 4: '/', 5: '%', 6: '+', 7: '-', 8: '<<', 9: '>>', 11: '<', 12: '>',
          13: '<=', 14: '>=', 15: '==', 16: '!=', 17: '&', 18: '^', 19: '|', 20: '&&',
          21: '||', 22: '=', 23: '*=', 24: '/=', 25: '%=', 26: '+=', 27: '-=', 28: '<<=',
          29: '>>=', 30: '&=', 31: '^=', 32: '|=', 33: ','}
UNARY = {1: 'x++', 2: 'x--', 3: '++x', 4: '--x', 5: '&', 6: '*', 7: '+', 8: '-', 9: '~',
         10: '!'}

PRIMARY, UNARYP, OTHER = 0, 1, 2   # precedence of rendered text

STATEMENT_KINDS = {CK.COMPOUND_STMT, CK.CASE_STMT, CK.DEFAULT_STMT, CK.LABEL_STMT}


def include_farm():
    """Case-insensitive copies (symlinks) of the SDK include folders for clang on Linux."""
    stamp = os.path.join(FARM, '.done')
    if os.path.exists(stamp):
        return
    spellings = set()
    inc = re.compile(rb'#\s*include\s*[<"]([^>"]+)[>"]')
    for d in INCLUDE_DIRS:
        for root, _, files in os.walk(os.path.join(TOOLCHAIN, d)):
            for f in files:
                with open(os.path.join(root, f), 'rb') as fh:
                    for m in inc.finditer(fh.read()):
                        spellings.add(m.group(1).decode('latin1').replace('\\', '/'))
    for d in INCLUDE_DIRS:
        base = os.path.join(TOOLCHAIN, d)
        lower = {}
        for root, _, files in os.walk(base):
            for f in files:
                rel = os.path.relpath(os.path.join(root, f), base)
                lower[rel.lower()] = rel
        names = set(lower.values()) | set(lower) | {s for s in spellings if s.lower() in lower}
        for n in names:
            p = os.path.join(FARM, d.replace('/', '_'), n)
            os.makedirs(os.path.dirname(p), exist_ok=True)
            if not os.path.lexists(p):
                os.symlink(os.path.join(base, lower[n.lower()]), p)
    open(stamp, 'w').close()


def clang_args():
    args = ['-x', 'c++', '--target=i686-pc-windows-msvc', '-fms-extensions',
            '-fms-compatibility', '-fms-compatibility-version=13.10', '-fasm-blocks',
            '-std=c++03', '-nostdinc', '-nostdinc++', '-Wno-everything',
            '-DWIN32', '-DNDEBUG', '-D_WINDOWS', '-D_MBCS', '-D_MT']
    for d in INCLUDE_DIRS:
        args += ['-isystem', os.path.join(FARM, d.replace('/', '_'))]
    return args


# --- types -----------------------------------------------------------------------------

def canon(t):
    return t.get_canonical()


def strip_typedefs(t):
    return t.get_canonical()


def is_record(t):
    return canon(t).kind == TK.RECORD


def is_pointer(t):
    return canon(t).kind == TK.POINTER


def pointee(t):
    return canon(t).get_pointee()


def type_key(t):
    """Types that compile alike: size and kind, ignoring int/long and typedefs."""
    c = canon(t)
    k = c.kind
    if k in (TK.CHAR_S, TK.SCHAR):
        return ('s', 1)
    if k in (TK.UCHAR, TK.CHAR_U, TK.BOOL):
        return ('u', 1) if k != TK.BOOL else ('bool', 1)
    if k == TK.SHORT:
        return ('s', 2)
    if k == TK.USHORT:
        return ('u', 2)
    if k in (TK.INT, TK.LONG):
        return ('s', 4)
    if k in (TK.UINT, TK.ULONG):
        return ('u', 4)
    if k in (TK.LONGLONG,):
        return ('s', 8)
    if k in (TK.ULONGLONG,):
        return ('u', 8)
    if k == TK.FLOAT:
        return ('f', 4)
    if k == TK.DOUBLE or k == TK.LONGDOUBLE:
        return ('f', 8)
    if k == TK.POINTER:
        return ('p', c.spelling)
    if k == TK.ENUM:
        return ('s', 4)
    return ('other', c.spelling)


def is_integral(t):
    return type_key(t)[0] in ('s', 'u')


def same_type(a, b):
    return type_key(a) == type_key(b)


def same_size_scalar(a, b):
    """Both integers, or pointer-sized integer and pointer, of the same size."""
    ka, kb = type_key(a), type_key(b)
    sa = 4 if ka[0] == 'p' else ka[1] if ka[0] in ('s', 'u') else None
    sb = 4 if kb[0] == 'p' else kb[1] if kb[0] in ('s', 'u') else None
    return sa is not None and sa == sb


def unqualified(t):
    return re.sub(r'\b(const|volatile) ', '', canon(t).spelling)


def spell(t):
    """How to write a type in a cast."""
    s = t.spelling
    s = re.sub(r'^(struct|class) ', '', s)
    s = s.replace(' *', '*')
    return s


# --- layouts ---------------------------------------------------------------------------

_lines = {}


def source_line(cursor):
    f = cursor.location.file
    if f is None:
        return ''
    if f.name not in _lines:
        with open(f.name, encoding='utf-8', errors='replace') as fh:
            _lines[f.name] = fh.read().split('\n')
    return _lines[f.name][cursor.location.line - 1]


class Field:
    def __init__(self, name, off, type_, base=False, line=''):
        self.name = name
        self.off = off
        self.type = type_
        self.size = canon(type_).get_size()
        self.base = base
        self.line = line

    @property
    def end(self):
        return self.off + self.size

    def is_hole(self):
        """Padding: an unnamed byte array (unk1234[...], data[...]) without a comment.
        A commented one is a real array whose purpose isn't known yet."""
        c = canon(self.type)
        if c.kind != TK.CONSTANTARRAY:
            return False
        e = canon(c.get_array_element_type()).kind
        return e in (TK.UCHAR, TK.CHAR_S, TK.SCHAR, TK.CHAR_U) and \
            re.match(r'(unk[0-9a-f]*|data|pad[0-9a-f]*)$', self.name) is not None and \
            '//' not in self.line


class Layouts:
    def __init__(self, tu):
        self.tu = tu
        self.cache = {}
        self.base_offsets = {}

    def record_decl(self, t):
        return canon(t).get_declaration()

    def fields(self, t):
        decl = self.record_decl(t)
        key = decl.get_usr() or decl.spelling
        if key in self.cache:
            return self.cache[key]
        ct = canon(t)
        out = []
        for c in decl.get_children():
            if c.kind == CK.CXX_BASE_SPECIFIER:
                out.append(Field(None, self.base_offset(ct, c.type), c.type, base=True))
            elif c.kind == CK.FIELD_DECL:
                off = ct.get_offset(c.spelling)
                if off < 0:
                    continue
                out.append(Field(c.spelling, off // 8, c.type, line=source_line(c)))
        out.sort(key=lambda f: (f.off, 0 if f.base else 1))
        self.cache[key] = out
        return out

    def base_offset(self, derived, base):
        """Offset of a non-virtual base: where its first field lands in the derived class."""
        key = (canon(derived).spelling, canon(base).spelling)
        if key in self.base_offsets:
            return self.base_offsets[key]
        # MSVC puts the vtable pointer first when the derived class introduces it and the
        # base has none; the base then starts at the class's alignment.
        bdecl = canon(base).get_declaration()
        ddecl = canon(derived).get_declaration()
        base_poly = has_vtable(bdecl)
        derived_poly = has_vtable(ddecl)
        if derived_poly and not base_poly:
            off = max(4, canon(derived).get_align())
        else:
            off = 0
        self.base_offsets[key] = off
        return off


def has_vtable(decl):
    for c in decl.get_children():
        if c.kind == CK.CXX_METHOD and c.is_virtual_method():
            return True
        if c.kind == CK.CXX_BASE_SPECIFIER and has_vtable(canon(c.type).get_declaration()):
            return True
    return False


# --- expression values -----------------------------------------------------------------

class Ptr:
    """A pointer rvalue to an object of a known type: `this`, a variable, a member."""
    def __init__(self, target, text=None, prec=PRIMARY, is_this=False, cursor=None):
        self.target = target
        self.text = text
        self.prec = prec
        self.is_this = is_this
        self.cursor = cursor


class Addr:
    """(char*)ptr + offset + index * scale ...: a byte address inside *ptr."""
    def __init__(self, ptr, const=0, terms=()):
        self.ptr = ptr
        self.const = const
        self.terms = list(terms)   # [(cursor, scale)]


class TAddr:
    """(U*)addr"""
    def __init__(self, utype, addr):
        self.utype = utype
        self.addr = addr


class LVal:
    """A resolved member: text, the member's declared type and the access's type."""
    def __init__(self, text, prec, decl_type, access_type):
        self.text = text
        self.prec = prec
        self.T = decl_type
        self.U = access_type


def num(n):
    """A number as the lifter writes it: decimal below 10, hex above."""
    return str(n) if -10 < n < 10 else hex(n) if n > 0 else '-' + hex(-n)


def paren(text, prec, need=PRIMARY):
    return text if prec <= need else '(' + text + ')'


def node_key(c):
    """A cursor's identity: its hash alone collides in files this size."""
    e = c.extent
    return (c.hash, c.kind.value, e.start.offset, e.end.offset)


class Unresolved(Exception):
    pass


class Rewriter:
    def __init__(self, tu, data, path, layouts, scan=None):
        self.tu = tu
        self.data = data
        self.path = path
        self.layouts = layouts
        self.scan = scan          # collections of hole hits, or None
        self.memo = {}
        self.edits = []
        self.locals = set()
        self.stats = collections.Counter()
        self.ctx_of = {}
        self.subobject = False

    # source text
    def text(self, c):
        e = c.extent
        return self.data[e.start.offset:e.end.offset].decode('utf-8')

    def in_file(self, c):
        f = c.location.file
        return f is not None and os.path.abspath(f.name) == self.path

    # --- semantic values ---------------------------------------------------------------

    def children(self, c):
        return [x for x in c.get_children() if x.kind != CK.TYPE_REF and
                x.kind != CK.TEMPLATE_REF and x.kind != CK.NAMESPACE_REF]

    def strip(self, c):
        """Skip parentheses and implicit conversions."""
        while c.kind in (CK.PAREN_EXPR, CK.UNEXPOSED_EXPR):
            ch = self.children(c)
            if len(ch) != 1:
                break
            c = ch[0]
        return c

    def int_value(self, c):
        c = self.strip(c)
        if c.kind == CK.INTEGER_LITERAL:
            tok = ''.join(t.spelling for t in c.get_tokens())
            tok = tok.rstrip('uUlL')
            return int(tok, 0)
        if c.kind == CK.UNARY_OPERATOR and UNARY.get(lib.clang_getCursorUnaryOperatorKind(c)) == '-':
            v = self.int_value(self.children(c)[0])
            return None if v is None else -v
        return None

    def sem(self, c):
        key = node_key(c)
        if key in self.memo:
            return self.memo[key]
        v = self._sem(c)
        self.memo[key] = v
        return v

    def _sem(self, c):
        k = c.kind
        if k in (CK.PAREN_EXPR, CK.UNEXPOSED_EXPR):
            ch = self.children(c)
            if len(ch) == 1:
                v = self.sem(ch[0])
                return v
            return None
        if k == CK.CXX_THIS_EXPR:
            return Ptr(pointee(c.type), 'this', PRIMARY, is_this=True)
        if k in (CK.DECL_REF_EXPR, CK.MEMBER_REF_EXPR, CK.ARRAY_SUBSCRIPT_EXPR):
            if is_pointer(c.type) and is_record(pointee(c.type)):
                return Ptr(pointee(c.type), cursor=c)
            return None
        if k == CK.CSTYLE_CAST_EXPR:
            ch = self.children(c)
            if not ch:
                return None
            inner = self.sem(ch[-1])
            t = c.type
            if not is_pointer(t):
                return None
            pt = pointee(t)
            if canon(pt).kind in (TK.CHAR_S, TK.SCHAR, TK.UCHAR, TK.CHAR_U):
                # (char*)p: a byte address
                p = self.as_ptr(inner)
                if p is not None:
                    return Addr(p)
                if isinstance(inner, Addr):
                    return inner
                if isinstance(inner, TAddr) and canon(inner.utype).get_size() == 1:
                    return inner.addr
                return None
            if isinstance(inner, Addr):
                return TAddr(pt, inner)
            if isinstance(inner, TAddr):
                return TAddr(pt, inner.addr)
            p = self.as_ptr(inner)
            if p is not None:
                return TAddr(pt, Addr(p))
            return None
        if k == CK.BINARY_OPERATOR:
            op = BINARY.get(lib.clang_getCursorBinaryOperatorKind(c))
            ch = self.children(c)
            if op in ('+', '-') and len(ch) == 2:
                left = self.sem(ch[0])
                if not isinstance(left, Addr):
                    p = self.as_ptr(left)
                    # (char*)p + n, or a pointer member read as an int: *(int*)(...) + n
                    if p is None or not (self.is_byte_pointer(ch[0].type) or
                                         type_key(ch[0].type) in (('s', 4), ('u', 4))):
                        return None
                    left = Addr(p)
                if not is_integral(ch[1].type):
                    return None
                return self.add_term(left, ch[1], -1 if op == '-' else 1)
            return None
        if k == CK.UNARY_OPERATOR:
            op = UNARY.get(lib.clang_getCursorUnaryOperatorKind(c))
            if op == '*':
                inner = self.sem(self.children(c)[0])
                if isinstance(inner, Addr) and self.is_byte_pointer(self.children(c)[0].type):
                    inner = TAddr(pointee(self.children(c)[0].type), inner)
                if isinstance(inner, TAddr):
                    return self.resolve(inner, c)
                p = self.as_ptr(inner)
                if p is not None and not isinstance(inner, Ptr):
                    pass
                return None
            return None
        return None

    def is_byte_pointer(self, t):
        return is_pointer(t) and canon(pointee(t)).kind in (TK.CHAR_S, TK.SCHAR, TK.UCHAR,
                                                            TK.CHAR_U)

    def as_ptr(self, v):
        """A pointer value with a known target, from a Ptr or a pointer member's value."""
        if isinstance(v, Ptr):
            return v
        if isinstance(v, LVal) and is_pointer(v.T):
            t = pointee(v.T)
            if canon(t).kind in (TK.VOID, TK.CHAR_S, TK.SCHAR, TK.UCHAR, TK.CHAR_U):
                return None
            return Ptr(t, v.text, v.prec)
        return None

    def add_term(self, addr, c, sign):
        v = self.int_value(c)
        a = Addr(addr.ptr, addr.const, addr.terms)
        if v is not None:
            a.const += sign * v
            return a
        if sign < 0:
            return None
        s = self.strip(c)
        if s.kind == CK.BINARY_OPERATOR:
            op = BINARY.get(lib.clang_getCursorBinaryOperatorKind(s))
            ch = self.children(s)
            if op == '*':
                k = self.int_value(ch[1])
                if k is not None:
                    a.terms.append((ch[0], k))
                    return a
            if op == '<<':
                k = self.int_value(ch[1])
                if k is not None:
                    a.terms.append((ch[0], 1 << k, 'shl'))
                    return a
        a.terms.append((c, 1))
        return a

    # --- member lookup -----------------------------------------------------------------

    def resolve(self, taddr, node):
        """*(U*)addr -> LVal, or None (recording padding hits)."""
        addr = taddr.addr
        U = taddr.utype
        try:
            text, prec, T = self.walk(addr, U, node)
        except Unresolved:
            return None
        return LVal(text, prec, T, U)

    def walk(self, addr, U, node, want_address=False, want=None):
        """Follow addr through the layouts; returns (text, prec, declared type)."""
        p = addr.ptr
        t = p.target
        off = addr.const
        terms = list(addr.terms)
        usize = canon(U).get_size() if U is not None else None
        top_record = canon(t).spelling
        top_off = off
        prec = PRIMARY
        last = None
        if p.is_this:
            text, sep = '', ''
        else:
            ptext, pprec = self.ptr_text(p)
            tsize = canon(t).get_size()
            term = None
            for i, tm in enumerate(terms):
                if tm[1] == tsize and canon(t).kind != TK.RECORD or \
                        tm[1] == tsize and off < tsize:
                    term = tm
                    del terms[i]
                    break
            if term is not None:
                # pointer arithmetic over an array: p[i]
                text = paren(ptext, pprec) + '[' + self.render(term[0], 'rvalue')[0] + ']'
                sep = '.'
            elif canon(t).kind == TK.RECORD and off >= tsize:
                # a constant index into an array: anims[0x27].frames
                text, sep = paren(ptext, pprec) + '[' + num(off // tsize) + ']', '.'
                off %= tsize
            elif canon(t).kind == TK.RECORD:
                text, sep = paren(ptext, pprec), '->'
            elif off % tsize == 0 and off // tsize:
                text, sep = paren(ptext, pprec) + '[' + num(off // tsize) + ']', '.'
                off = 0
            else:
                text, sep, prec = '*' + paren(ptext, pprec, UNARYP), '.', UNARYP
        while True:
            ct = canon(t)
            if want is not None and off == 0 and not terms and (not text or sep == '->') and \
                    unqualified(ct) == unqualified(want) and ct.kind == TK.RECORD:
                # a base class subobject: this, or what a pointer points to
                self.subobject = True
                return text, prec, t
            if want is not None and off == 0 and not terms and text and sep != '->':
                # an address: stop at the member of the wanted type, or at an array of it
                if unqualified(ct) == unqualified(want) or (
                        ct.kind == TK.CONSTANTARRAY and
                        unqualified(ct.get_array_element_type()) == unqualified(want)):
                    return text, prec, t
            if ct.kind == TK.RECORD and off == 0 and not terms and U is not None and \
                    canon(U).spelling == ct.spelling:
                # the whole struct: *(PatternFrame*)p
                if not text:
                    text, prec = '*this', UNARYP
                elif sep == '->':
                    text, prec = '*' + paren(text, prec, UNARYP), UNARYP
                return text, prec, t
            if ct.kind == TK.RECORD:
                f = self.field_at(t, off, U if not terms else None)
                if f is None:
                    self.miss(ct.spelling, off, U, node, terms, why='no field', top=top_record)
                    raise Unresolved
                if f.is_hole():
                    self.miss(ct.spelling, off, U, node, terms, why='hole', top=top_record)
                    raise Unresolved
                if not f.base:
                    last = (ct.spelling, f.off, f.name)
                off -= f.off
                if not f.base:
                    if not text:
                        text = 'this->' + f.name if f.name in self.locals else f.name
                    else:
                        text = paren(text, prec) + sep + f.name
                    prec = PRIMARY
                    sep = '.'
                t = f.type
                continue
            if ct.kind == TK.CONSTANTARRAY:
                et = ct.get_array_element_type()
                esize = canon(et).get_size()
                idx = off // esize
                off -= idx * esize
                term = None
                for i, tm in enumerate(terms):
                    if tm[1] == esize:
                        term = tm
                        del terms[i]
                        break
                if term is not None:
                    if idx != 0:
                        self.miss(top_record, top_off, U, node, terms, why='index+offset')
                        raise Unresolved
                    itext = self.render(term[0], 'rvalue')[0]
                    text = paren(text, prec) + '[' + itext + ']'
                else:
                    text = paren(text, prec) + '[' + num(idx) + ']'
                prec = PRIMARY
                sep = '.'
                t = et
                continue
            # a scalar
            if terms or (off != 0 and (U is None or want_address)):
                self.miss(top_record, top_off, U, node, terms, why='inside scalar')
                raise Unresolved
            if off != 0 or (usize is not None and ct.get_size() != usize and not want_address):
                # part of a member: *(char*)&unk168, *((char*)&unk1378 + 1)
                self.miss(top_record, top_off, U, node, terms, why='size')
                if not text:
                    raise Unresolved
                if off:
                    text = '*(' + spell(U) + '*)((char*)&' + text + ' + ' + num(off) + ')'
                else:
                    text = '*(' + spell(U) + '*)&' + text
                return text, UNARYP, U
            if not text:
                raise Unresolved
            if self.scan is not None and U is not None and last is not None:
                self.scan.append({'node': node_key(node), 'top': top_record, 'record': last[0],
                                  'off': last[1], 'name': last[2], 'type': spell(U),
                                  'decl': spell(t), 'size': canon(U).get_size(),
                                  'terms': [], 'why': 'ok', 'file': os.path.basename(self.path),
                                  'line': node.location.line})
            return text, prec, t

    def ptr_text(self, p):
        if p.cursor is not None:
            return self.render(p.cursor, 'rvalue')
        return p.text, p.prec

    def field_at(self, t, off, U):
        fields = self.layouts.fields(t)
        hits = [f for f in fields if f.off <= off < f.end or (f.size == 0 and f.off == off)]
        if not hits:
            return None
        if len(hits) > 1 and U is not None:
            # a union: prefer the member of the access's type
            for f in hits:
                if not f.base and f.off == off and same_type(f.type, U):
                    return f
        # prefer a base or record that contains it, then the first
        return hits[0]

    def miss(self, record, off, U, node, terms, why, top=None):
        if self.scan is None or U is None:
            return
        self.scan.append({'node': node_key(node), 'top': top,
            'record': record, 'off': off, 'type': spell(U) if U is not None else None,
            'size': canon(U).get_size() if U is not None else None,
            'terms': [t[1] for t in terms], 'why': why,
            'file': os.path.basename(self.path), 'line': node.location.line})

    # --- rendering ---------------------------------------------------------------------

    def render(self, c, ctx):
        """(text, prec) for cursor c, with every resolvable access rewritten."""
        if in_macro(c):
            return self.text(c), self.prec_of(c)
        self.ctx_of.setdefault(node_key(self.strip(c)), ctx)
        k = c.kind
        if k == CK.BINARY_OPERATOR:
            op = BINARY.get(lib.clang_getCursorBinaryOperatorKind(c))
            ch = self.children(c)
            if op in ('+', '-') and self.is_byte_pointer(c.type):
                # (char*)this + 0x94 -> m_name
                v = self.sem(c)
                if isinstance(v, Addr):
                    r = self.address_text(v, c.type, c)
                    if r is not None:
                        return r
            if op == '=' and len(ch) == 2:
                self.ctx_of.setdefault(node_key(self.strip(ch[0])), 'assign')
                v = self.sem(ch[0])
                if isinstance(v, LVal):
                    return self.render_assign(c, v, ch[0], ch[1], ctx)
        if k == CK.COMPOUND_ASSIGNMENT_OPERATOR:
            op = BINARY.get(lib.clang_getCursorBinaryOperatorKind(c))
            ch = self.children(c)
            self.ctx_of.setdefault(node_key(self.strip(ch[0])), 'compound' + op)
            v = self.sem(ch[0])
            if isinstance(v, LVal):
                return self.render_compound(c, v, op, ch[0], ch[1], ctx)
        if k == CK.UNARY_OPERATOR:
            op = UNARY.get(lib.clang_getCursorUnaryOperatorKind(c))
            ch = self.children(c)
            if op in ('x++', 'x--', '++x', '--x'):
                self.ctx_of.setdefault(node_key(self.strip(ch[0])), 'incdec')
                v = self.sem(ch[0])
                if isinstance(v, LVal):
                    return self.render_incdec(c, v, op, ctx)
            if op == '&':
                self.ctx_of.setdefault(node_key(self.strip(ch[0])), 'addrof')
                v = self.sem(ch[0])
                if isinstance(v, LVal):
                    self.stats['addr-of'] += 1
                    if same_type(v.T, v.U) and canon(v.T).spelling == canon(v.U).spelling:
                        return '&' + v.text, UNARYP
                    return '(' + spell(v.U) + '*)&' + v.text, UNARYP
            if op == '*':
                v = self.sem(c)
                if isinstance(v, LVal):
                    return self.render_value(v, ctx)
        if k == CK.MEMBER_REF_EXPR:
            r = self.render_base_member(c)
            if r is not None:
                return r
        if k in (CK.PAREN_EXPR,):
            ch = self.children(c)
            if len(ch) == 1:
                inner, prec = self.render(ch[0], ctx)
                if prec == PRIMARY and inner != self.text(ch[0]):
                    # parentheses around a rewritten member
                    return inner, PRIMARY
                return '(' + inner + ')', PRIMARY
        if k == CK.CSTYLE_CAST_EXPR:
            r = self.render_cast(c, ctx)
            if r is not None:
                return r
        return self.render_generic(c, ctx)

    def render_generic(self, c, ctx):
        e = c.extent
        start, end = e.start.offset, e.end.offset
        out = []
        pos = start
        child_ctx = 'stmt' if c.kind in STATEMENT_KINDS else 'rvalue'
        for ch in c.get_children():
            ce = ch.extent
            if ce.start.file is None or os.path.abspath(ce.start.file.name) != self.path:
                continue
            s, t = ce.start.offset, ce.end.offset
            if s < pos or t > end:
                continue
            rtext, _ = self.render(ch, child_ctx)
            orig = self.data[s:t].decode('utf-8')
            if rtext == orig:
                continue
            out.append(self.data[pos:s].decode('utf-8'))
            out.append(rtext)
            pos = t
        if not out:
            return self.data[start:end].decode('utf-8'), self.prec_of(c)
        out.append(self.data[pos:end].decode('utf-8'))
        return ''.join(out), self.prec_of(c)

    def prec_of(self, c):
        k = c.kind
        if k in (CK.DECL_REF_EXPR, CK.MEMBER_REF_EXPR, CK.CALL_EXPR, CK.PAREN_EXPR,
                 CK.ARRAY_SUBSCRIPT_EXPR, CK.INTEGER_LITERAL, CK.FLOATING_LITERAL,
                 CK.CXX_THIS_EXPR, CK.STRING_LITERAL, CK.CHARACTER_LITERAL):
            return PRIMARY
        if k in (CK.UNARY_OPERATOR, CK.CSTYLE_CAST_EXPR):
            return UNARYP
        if k == CK.UNEXPOSED_EXPR:
            ch = self.children(c)
            if len(ch) == 1 and ch[0].extent.start.offset == c.extent.start.offset and \
                    ch[0].extent.end.offset == c.extent.end.offset:
                return self.prec_of(ch[0])
        return OTHER

    def render_base_member(self, c):
        """((ObjBase*)((char*)this + 8))->AngleTo -> AngleTo: the inherited member, without
        the null test an upcast would compile to."""
        ch = self.children(c)
        if not ch:
            return None
        base = self.strip(ch[0])
        if base.kind != CK.CSTYLE_CAST_EXPR or not is_pointer(base.type):
            return None
        v = self.sem(base)
        if not isinstance(v, TAddr) or not is_record(v.utype):
            return None
        try:
            self.subobject = False
            text, prec, T = self.walk(v.addr, None, c, want_address=True, want=v.utype)
        except Unresolved:
            return None
        if not self.subobject:
            return None
        self.stats['access'] += 1
        if not text:
            return c.spelling, PRIMARY
        return paren(text, prec) + '->' + c.spelling, PRIMARY

    def render_value(self, v, ctx):
        """An access used as a value (or in a context we don't otherwise know)."""
        self.stats['access'] += 1
        if canon(v.T).spelling == canon(v.U).spelling:
            return v.text, v.prec
        if ctx in ('rvalue', 'stmt') and (canon(v.T).kind != TK.RECORD):
            if same_type(v.T, v.U) and not is_pointer(v.U):
                return v.text, v.prec
            self.stats['value-cast'] += 1
            return '(' + spell(v.U) + ')' + v.text, UNARYP
        self.stats['address-cast'] += 1
        return '*(' + spell(v.U) + '*)&' + v.text, UNARYP

    def render_cast(self, c, ctx):
        """(X)access: drop a cast that the member's type makes redundant."""
        ch = self.children(c)
        if not ch:
            return None
        v = self.sem(ch[-1])
        X = c.type
        if isinstance(v, LVal):
            if canon(X).spelling == canon(v.T).spelling and same_size_scalar(v.U, v.T) and \
                    (is_pointer(X) or same_type(v.U, v.T) or is_pointer(v.U)):
                # (CGraphics*)*(int*)(this + 0x20) -> m_graphics
                self.stats['access'] += 1
                return v.text, v.prec
            if canon(X).spelling == canon(v.T).spelling and is_integral(X) and \
                    same_size_scalar(v.U, v.T):
                # (WORD)*(short*)p with a WORD member
                self.stats['access'] += 1
                return v.text, v.prec
            if (is_pointer(X) or type_key(X) in (('s', 4), ('u', 4))) and \
                    is_pointer(v.T) and same_size_scalar(v.U, v.T):
                self.stats['access'] += 1
                return '(' + spell(X) + ')' + v.text, UNARYP
            return None
        # an address that isn't dereferenced: (Afterimages*)((char*)this + 0x2bc0)
        if isinstance(v, (Addr, TAddr)) and is_pointer(X):
            addr = v if isinstance(v, Addr) else v.addr
            want = pointee(X)
            r = self.address_text(addr, X, c)
            if r is not None:
                return r
        return None

    def address_text(self, addr, X, node):
        """&member for an address cast to pointer type X, or None."""
        want = pointee(X)
        if not addr.ptr or (addr.const == 0 and not addr.terms):
            return None
        try:
            self.subobject = False
            text, prec, T = self.walk(addr, None, node, want_address=True, want=want)
            if self.subobject:
                # (ObjBase*)this would test this for null; &pattern doesn't
                text, prec, T = self.walk(addr, None, node, want_address=True)
        except Unresolved:
            return None
        ct = canon(T)
        self.stats['address'] += 1
        if ct.kind == TK.CONSTANTARRAY:
            et = ct.get_array_element_type()
            if unqualified(et) == unqualified(want):
                return text, PRIMARY
            return '(' + spell(X) + ')' + text, UNARYP
        if unqualified(ct) == unqualified(want):
            return '&' + text, UNARYP
        return '(' + spell(X) + ')&' + text, UNARYP

    def render_assign(self, c, v, lhs, rhs, ctx):
        self.stats['access'] += 1
        rtext, rprec = self.render(rhs, 'rvalue')
        exact = canon(v.T).spelling == canon(v.U).spelling
        if exact:
            return v.text + ' = ' + rtext, OTHER
        rs = self.strip(rhs)
        if ctx == 'stmt' and same_size_scalar(v.U, v.T):
            rv = self.sem(rhs)
            if isinstance(rv, LVal) and canon(rv.T).spelling == canon(v.T).spelling and \
                    same_size_scalar(rv.U, rv.T):
                return v.text + ' = ' + rv.text, OTHER
            if is_pointer(v.T):
                # *(int*)(this + 0x14) = (int)p2 -> m_player1Ref = p2
                if rs.kind == CK.CSTYLE_CAST_EXPR:
                    inner = self.children(rs)[-1]
                    if canon(self.strip(inner).type).spelling == canon(v.T).spelling or \
                            self.sem_type_is(inner, v.T):
                        itext, iprec = self.render(inner, 'rvalue')
                        return v.text + ' = ' + itext, OTHER
                if canon(rs.type).spelling == canon(v.T).spelling:
                    return v.text + ' = ' + rtext, OTHER
                self.stats['value-cast'] += 1
                return v.text + ' = (' + spell(v.T) + ')' + paren(rtext, rprec, UNARYP), OTHER
            if is_integral(v.T) and is_integral(v.U) and is_integral(rs.type):
                return v.text + ' = ' + rtext, OTHER
        self.stats['address-cast'] += 1
        return '*(' + spell(v.U) + '*)&' + v.text + ' = ' + rtext, OTHER

    def sem_type_is(self, c, T):
        v = self.sem(c)
        if isinstance(v, LVal):
            return canon(v.T).spelling == canon(T).spelling
        if isinstance(v, Ptr) and is_pointer(T):
            return canon(v.target).spelling == canon(pointee(T)).spelling
        return False

    def render_compound(self, c, v, op, lhs, rhs, ctx):
        self.stats['access'] += 1
        rtext, rprec = self.render(rhs, 'rvalue')
        if canon(v.T).spelling == canon(v.U).spelling or (same_type(v.T, v.U) and not is_pointer(v.T)):
            return v.text + ' ' + op + ' ' + rtext, OTHER
        self.stats['address-cast'] += 1
        return '*(' + spell(v.U) + '*)&' + v.text + ' ' + op + ' ' + rtext, OTHER

    def render_incdec(self, c, v, op, ctx):
        self.stats['access'] += 1
        sym = '++' if '++' in op else '--'
        exact = canon(v.T).spelling == canon(v.U).spelling or \
            (same_type(v.T, v.U) and not is_pointer(v.T))
        if exact or (ctx == 'stmt' and is_integral(v.T) and is_integral(v.U) and
                     same_size_scalar(v.T, v.U)):
            body, prec = v.text, v.prec
        else:
            self.stats['address-cast'] += 1
            body, prec = '(*(' + spell(v.U) + '*)&' + v.text + ')', PRIMARY
        if op.startswith('x'):
            return body + sym, PRIMARY
        return sym + body, UNARYP

    # --- driver ------------------------------------------------------------------------

    def run(self, cursors):
        for c in cursors:
            if c.kind in (CK.CXX_METHOD, CK.FUNCTION_DECL, CK.CONSTRUCTOR, CK.DESTRUCTOR) \
                    and c.is_definition():
                body = [x for x in c.get_children() if x.kind == CK.COMPOUND_STMT]
                if not body:
                    continue
                b = body[0]
                self.locals = set()
                for x in c.walk_preorder():
                    if x.kind in (CK.VAR_DECL, CK.PARM_DECL):
                        self.locals.add(x.spelling)
                orig = self.text(b)
                new, _ = self.render(b, 'stmt')
                if new != orig:
                    self.edits.append((b.extent.start.offset, b.extent.end.offset, new))

    def apply(self):
        data = self.data
        for s, e, new in sorted(self.edits, reverse=True):
            data = data[:s] + new.encode('utf-8') + data[e:]
        return data


def functions_in(tu, path):
    """Top-level function definitions in path, including methods defined in classes."""
    out = []

    def visit(c):
        for x in c.get_children():
            f = x.location.file
            if f is None or os.path.abspath(f.name) != path:
                continue
            if x.kind in (CK.CXX_METHOD, CK.FUNCTION_DECL, CK.CONSTRUCTOR, CK.DESTRUCTOR):
                if x.is_definition():
                    out.append(x)
            elif x.kind in (CK.CLASS_DECL, CK.STRUCT_DECL, CK.UNION_DECL, CK.NAMESPACE):
                visit(x)
    visit(tu.cursor)
    return out


def parse(path, index):
    include_farm()
    tu = index.parse(path, clang_args())
    errors = [d for d in tu.diagnostics if d.severity >= 3 and
              'interlockedbittest' not in d.spelling]
    if errors:
        for d in errors[:10]:
            print(f'{path}: {d}', file=sys.stderr)
        raise RuntimeError(f'{path}: clang found {len(errors)} errors')
    return tu


def process(path, index, scan=None):
    """Rewrite one file; returns (old bytes, new bytes, stats)."""
    path = os.path.abspath(path)
    if path.endswith('.h'):
        # parse the header through a source that includes it
        tu = parse(os.path.join(SRC, 'main.cpp'), index)
    else:
        tu = parse(path, index)
    with open(path, 'rb') as f:
        data = f.read()
    hits = [] if scan is not None else None
    rw = Rewriter(tu, data, path, Layouts(tu), hits)
    rw.run(functions_in(tu, path))
    if scan is not None:
        for h in hits:
            h['ctx'] = rw.ctx_of.get(tuple(h.pop('node')), '?')
            scan.append(h)
    return data, rw.apply(), rw.stats


def default_files():
    files = sorted(os.path.join(SRC, f) for f in os.listdir(SRC) if f.endswith('.cpp'))
    return files + [os.path.join(SRC, 'efz.h')]


def check_layout():
    """Members named unk<hex>, and members commented `// +0x..`, must sit at that offset
    in their class, and a class annotated `// SIZE: 0x..` must have that size."""
    header = os.path.join(SRC, 'efz.h')
    tu = parse(os.path.join(SRC, 'main.cpp'), ci.Index.create())
    with open(header, encoding='utf-8') as f:
        lines = f.read().split('\n')
    layouts = Layouts(tu)
    errors = 0
    seen = set()

    def visit(c):
        nonlocal errors
        for x in c.get_children():
            f = x.location.file
            if f is None or os.path.abspath(f.name) != header:
                continue
            if x.kind in (CK.CLASS_DECL, CK.STRUCT_DECL, CK.UNION_DECL) and x.is_definition():
                if x.hash in seen:
                    continue
                seen.add(x.hash)
                t = x.type
                size = canon(t).get_size()
                above = lines[x.extent.start.line - 2] if x.extent.start.line > 1 else ''
                m = re.match(r'\s*// SIZE: (0x[0-9a-f]+)', above)
                if m and int(m.group(1), 16) != size:
                    print(f'{x.spelling}: size {size:#x}, annotated {m.group(1)}')
                    errors += 1
                for fl in layouts.fields(t):
                    if fl.base:
                        continue
                    want = None
                    m = re.match(r'unk([0-9a-f]+)$', fl.name)
                    if m:
                        want = int(m.group(1), 16)
                    decl = [d for d in x.get_children() if d.kind == CK.FIELD_DECL and
                            d.spelling == fl.name]
                    if decl:
                        line = lines[decl[0].location.line - 1]
                        m2 = re.search(r'//\s*\+(0x[0-9a-f]+)\b', line)
                        if m2 and want is None:
                            want = int(m2.group(1), 16)
                    if want is not None and want != fl.off:
                        print(f'{x.spelling}::{fl.name} is at {fl.off:#x}')
                        errors += 1
                visit(x)
    visit(tu.cursor)
    print(f'{len(seen)} classes checked, {errors} errors')
    return errors


# --- renaming ----------------------------------------------------------------------

def read_renames(path):
    """{(class, member): new name} from lines "Class::member name" (# starts a comment)."""
    out = {}
    with open(path, encoding='utf-8') as f:
        for line in f:
            line = line.split('#', 1)[0].strip()
            if not line:
                continue
            qual, new = line.split()
            cls, member = qual.rsplit('::', 1)
            out[(cls, member)] = new
    return out


def rename_work(job):
    """Edits [(offset, old, new)] for one file; efz.h is reached through main.cpp."""
    path, renames = job
    src = os.path.join(SRC, 'main.cpp') if path.endswith('.h') else path
    tu = parse(src, ci.Index.create())
    with open(path, 'rb') as f:
        data = f.read()
    edits = {}
    problems = []

    def target(c):
        if c.kind in (CK.FIELD_DECL, CK.CXX_METHOD):
            d = c.canonical if c.kind == CK.CXX_METHOD else c
        elif c.kind in (CK.MEMBER_REF_EXPR, CK.MEMBER_REF, CK.DECL_REF_EXPR, CK.OVERLOADED_DECL_REF):
            d = c.referenced
        else:
            return None
        if d is None or d.kind not in (CK.FIELD_DECL, CK.CXX_METHOD):
            return None
        cls = d.semantic_parent.spelling if d.semantic_parent else None
        return renames.get((cls, d.spelling))

    def visit(c, names):
        for x in c.get_children():
            f = x.location.file
            if f is None or os.path.abspath(f.name) != path:
                continue
            inner = names
            if x.kind in (CK.CXX_METHOD, CK.FUNCTION_DECL, CK.CONSTRUCTOR, CK.DESTRUCTOR):
                inner = {y.spelling for y in x.walk_preorder()
                         if y.kind in (CK.VAR_DECL, CK.PARM_DECL)}
            new = target(x)
            if new is not None:
                off = x.location.offset
                old = x.spelling if x.kind in (CK.FIELD_DECL, CK.CXX_METHOD) else \
                    x.referenced.spelling
                if data[off:off + len(old)].decode('utf-8', 'replace') != old:
                    problems.append(f'{os.path.relpath(path, REPO)}:{x.location.line}: '
                                    f'{old} not at its location (macro?)')
                else:
                    before = data[:off].rstrip()
                    implicit = x.kind == CK.MEMBER_REF_EXPR and not (
                        before.endswith(b'.') or before.endswith(b'->'))
                    text = new
                    if implicit and new in names:
                        text = 'this->' + new
                    edits[off] = (old, text)
            visit(x, inner)
    visit(tu.cursor, set())
    return path, data, edits, problems


def rename(path_list, renames):
    files = path_list or default_files()
    include_farm()
    with multiprocessing.Pool() as pool:
        results = pool.map(rename_work, [(p, renames) for p in files])
    total = 0
    bad = False
    for path, data, edits, problems in results:
        for p in problems:
            print(p)
            bad = True
        if not edits:
            continue
        out = data
        for off in sorted(edits, reverse=True):
            old, new = edits[off]
            out = out[:off] + new.encode('utf-8') + out[off + len(old):]
        with open(path, 'wb') as f:
            f.write(out)
        total += len(edits)
        print(f'{os.path.relpath(path, REPO)}: {len(edits)} references')
    print(f'{total} references renamed')
    return bad


def main():
    args = sys.argv[1:]
    if args and args[0] == 'rename':
        renames = read_renames(args[1])
        sys.exit(1 if rename([os.path.abspath(a) for a in args[2:]], renames) else 0)
    if not args or args[0] not in ('scan', 'rewrite', 'check', 'layout'):
        print(__doc__)
        sys.exit(2)
    mode = args.pop(0)
    if mode == 'layout':
        include_farm()
        sys.exit(1 if check_layout() else 0)
    out_json = None
    if '--json' in args:
        i = args.index('--json')
        out_json = args[i + 1]
        del args[i:i + 2]
    files = [os.path.abspath(a) for a in args] or default_files()
    include_farm()
    total = collections.Counter()
    hits = []
    # efz.h last: the sources include it, so it mustn't change while they are parsed
    headers = [f for f in files if f.endswith('.h')]
    sources = [f for f in files if not f.endswith('.h')]
    with multiprocessing.Pool() as pool:
        results = pool.imap(work, [(path, mode == 'scan') for path in sources])
        for path, (old, new, stats, h) in zip(sources, results):
            hits += h
            total.update(stats)
            report(mode, path, old, new, stats)
    for path in headers:
        old, new, stats, h = work((path, mode == 'scan'))
        hits += h
        total.update(stats)
        report(mode, path, old, new, stats)
    if mode == 'scan':
        if out_json:
            with open(out_json, 'w') as f:
                json.dump(hits, f)
        summary = collections.Counter((h['record'], h['off'], h['type'], h['why']) for h in hits)
        for (rec, off, t, why), n in sorted(summary.items(), key=lambda kv: (
                kv[0][0], kv[0][1], str(kv[0][2]), kv[0][3])):
            print(f'{rec:12} {off:#7x} {t or "-":14} {why:14} {n}')
    print(f'total: {dict(total)}', file=sys.stderr)


def work(job):
    path, scan = job
    hits = [] if scan else None
    old, new, stats = process(path, ci.Index.create(), hits)
    return old, new, stats, hits or []


def report(mode, path, old, new, stats):
    rel = os.path.relpath(path, REPO)
    if mode == 'rewrite' and new != old:
        with open(path, 'wb') as f:
            f.write(new)
        print(f'{rel}: {stats["access"]} accesses, {stats["value-cast"]} value casts, '
              f'{stats["address-cast"]} address casts')
    elif mode == 'check' and new != old:
        sys.stdout.writelines(difflib.unified_diff(
            old.decode('utf-8').splitlines(True), new.decode('utf-8').splitlines(True),
            rel, rel))


if __name__ == '__main__':
    main()
