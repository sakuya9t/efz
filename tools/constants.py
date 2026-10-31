#!/usr/bin/env python3
"""Replace bare numbers with the names of the constants they are, in src/*.cpp.

    tools/constants.py declare SPEC            write the constants' declarations into
                                               src/efz.h (between BEGIN/END constants
                                               markers, regenerated each time)
    tools/constants.py apply SPEC [files...]   rewrite the sources in place
    tools/constants.py check SPEC [files...]   what apply would change, as a diff

SPEC is tools/constants.txt.

SPEC lists the constants, one per line (# starts a comment):

    action Class 0xNN kName        an action (ObjBase::pattern) number; Class is the
                                   character class for 0xc8 and up, or CPlayer for the
                                   actions every character shares
    bound 0xNN kName               an action number as the bound of a range (`pattern <
                                   0xc8`): relational comparisons take these, else a
                                   shared action's name; a character's numbers stay
    command Class 0xNN kName       an m_command number, the character class's own or
                                   CPlayer's (shared)
    flag Struct::member 0xNN kName a bit of a flag word (PatternFrame::flagsAA, ...)
    effect 0xNN kName              an effect type (Effect::type, EffectDesc::type of a
                                   desc given to CGame::CreateEffect)

A number is replaced where clang shows what it is:
- actions: compared with, assigned to or the case label of a switch on an object's
  `pattern` (a player's, one of its objects', an afterimage's), an index into a
  player's `m_patterns` or `anims`, and an EffectDesc::type given to SpawnObject. In a
  character's methods its own actions and objects' are its constants; a number that
  isn't a shared action is left alone where the character can't be known (the
  opponent's pattern, CScene3's code).
- commands: compared with or assigned to `m_command`, a case of a switch on it, or the
  base of the `0x78 + strength` sums ReadCommand assigns.
- flags: `word & 0xNN` where the word is the flag member; a mask of several named bits
  becomes their `|`.
- effects: EffectDesc::type of a desc given to CreateEffect.
`declare` puts the shared actions, commands, bounds, flags and effects at namespace
scope (before the struct or class they belong to) and each character's actions and
commands in its class, each with the comment that follows it in SPEC up to a `;`.
"""
import collections
import difflib
import multiprocessing
import os
import re
import sys
import textwrap

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import members  # noqa: E402
from members import CK, ci, parse, functions_in, in_macro, BINARY, REPO, SRC  # noqa: E402

COMPARE = {'==', '!=', '<', '<=', '>', '>=', '='}
CHARACTER_FIRST = 0xc8


def read_comments(path):
    """{(kind, scope, value): comment} from SPEC: the text after # up to the first ;."""
    out = {}
    with open(path) as f:
        for line in f:
            body, _, comment = line.partition('#')
            fields = body.split()
            if not fields:
                continue
            kind = fields[0]
            scope = fields[1] if kind in ('action', 'command', 'flag') else ''
            value = int(fields[2 if scope else 1], 0)
            out[(kind, scope, value)] = comment.split(';')[0].strip()
    return out


# Where declare puts the namespace-scope constants: before these lines of efz.h.
ANCHORS = {'flag': 'struct PatternFrame {', 'action': 'class CPlayer : public ObjBase {',
           'effect': 'struct Effect {'}
BEGIN = '// BEGIN constants (tools/constants.py declare): '
END = '// END constants'


def enum_block(title, items, indent):
    """An enum of (name, value, comment), aligned, under a comment line."""
    pad = ' ' * indent
    width = max(len(f'{n} = {v:#x},') for n, v, _ in items)
    lines = [f'{pad}{BEGIN}{title}', f'{pad}enum {{']
    for name, value, comment in items:
        text = f'{name} = {value:#x},'
        if not comment:
            lines.append(f'{pad}    {text}')
            continue
        lead = f'{pad}    {text}{" " * (width - len(text))} // '
        parts = textwrap.wrap(comment, max(40, 92 - len(lead)))
        lines.append(lead + parts[0])
        lines += [' ' * (len(lead) - 3) + '// ' + p for p in parts[1:]]
    lines += [f'{pad}}};', f'{pad}{END}']
    return '\n'.join(lines) + '\n'


def declare(spec_path):
    spec = read_spec(spec_path)
    notes = read_comments(spec_path)
    path = os.path.join(SRC, 'efz.h')
    with open(path, encoding='utf-8') as f:
        text = f.read()
    # Drop the blocks a previous declare wrote.
    text = re.sub(r'[ \t]*' + re.escape(BEGIN) + r'.*?' + re.escape(END) + r'\n', '', text,
                  flags=re.S)

    def items(kind, scope, table):
        return [(n, v, notes.get((kind, scope, v), '')) for v, n in sorted(table.items())]

    def before(anchor, block):
        nonlocal text
        i = text.index(anchor)
        text = text[:i] + block + '\n' + text[i:]

    shared = []
    if spec['action'].get('CPlayer'):
        shared.append(enum_block('the actions every character shares (ObjBase::pattern)',
                                 items('action', 'CPlayer', spec['action']['CPlayer']), 0))
    if spec['bound']:
        shared.append(enum_block('bounds of ranges of actions',
                                 items('bound', '', spec['bound']), 0))
    if spec['command'].get('CPlayer'):
        shared.append(enum_block('the commands every character shares (CPlayer::m_command)',
                                 items('command', 'CPlayer', spec['command']['CPlayer']), 0))
    if shared:
        before(ANCHORS['action'], '\n'.join(shared))
    flags = [enum_block(f'bits of {word}', items('flag', word, bits), 0)
             for word, bits in sorted(spec['flag'].items())]
    if flags:
        before(ANCHORS['flag'], '\n'.join(flags))
    if spec['effect']:
        before(ANCHORS['effect'], enum_block('effect types (Effect::type)',
                                             items('effect', '', spec['effect']), 0))
    for cls in sorted(set(spec['action']) | set(spec['command'])):
        if cls == 'CPlayer':
            continue
        m = re.search(r'\nclass ' + cls + r' : public CPlayer \{\npublic:\n', text)
        if not m:
            sys.exit(f'efz.h: no class {cls}')
        blocks = []
        if spec['action'].get(cls):
            blocks.append(enum_block(f'{cls}\'s own actions',
                                     items('action', cls, spec['action'][cls]), 4))
        if spec['command'].get(cls):
            blocks.append(enum_block(f'{cls}\'s own commands (ReadCommand)',
                                     items('command', cls, spec['command'][cls]), 4))
        text = text[:m.end()] + '\n'.join(blocks) + '\n' + text[m.end():]
    with open(path, 'w', encoding='utf-8') as f:
        f.write(text)
    print(f'{os.path.relpath(path, REPO)}: constants declared')


def read_spec(path):
    spec = {'action': collections.defaultdict(dict), 'command': collections.defaultdict(dict),
            'flag': collections.defaultdict(dict), 'effect': {}, 'bound': {}}
    with open(path) as f:
        for n, line in enumerate(f, 1):
            line = line.split('#')[0].split()
            if not line:
                continue
            kind = line[0]
            if kind in ('action', 'command'):
                spec[kind][line[1]][int(line[2], 0)] = line[3]
            elif kind in ('effect', 'bound'):
                spec[kind][int(line[1], 0)] = line[2]
            elif kind == 'flag':
                spec['flag'][line[1]][int(line[2], 0)] = line[3]
            else:
                sys.exit(f'{path}:{n}: unknown kind {kind}')
    return spec


def strip(c):
    """The node under parentheses and implicit casts."""
    while True:
        kids = list(c.get_children())
        if c.kind in (CK.PAREN_EXPR, CK.UNEXPOSED_EXPR) and len(kids) == 1:
            c = kids[0]
            continue
        if c.kind == CK.CSTYLE_CAST_EXPR and kids:
            c = kids[-1]
            continue
        return c


def literal(c):
    """(value, cursor) if c is an integer literal (under parens and casts)."""
    c = strip(c)
    if c.kind == CK.INTEGER_LITERAL:
        toks = [t.spelling for t in c.get_tokens()]
        if len(toks) == 1:
            try:
                return int(toks[0].rstrip('uUlL'), 0), c
            except ValueError:
                return None
    return None


def binop(c):
    if c.kind not in (CK.BINARY_OPERATOR, CK.COMPOUND_ASSIGNMENT_OPERATOR):
        return None
    return BINARY.get(members.lib.clang_getCursorBinaryOperatorKind(c))


def member_name(c):
    """The field a member access names, and the expression it is accessed on."""
    c = strip(c)
    if c.kind == CK.ARRAY_SUBSCRIPT_EXPR:     # afterimages' pattern[pos]
        c = strip(list(c.get_children())[0])
    if c.kind == CK.MEMBER_REF_EXPR and c.referenced is not None and \
            c.referenced.kind == CK.FIELD_DECL:
        kids = list(c.get_children())
        return c.referenced.spelling, c.referenced.semantic_parent.spelling, \
            (kids[0] if kids else None)
    return None


class Owner:
    """Whose actions a `pattern` belongs to: the method's own class (this, its objects,
    its afterimages) or unknown (another player)."""

    def __init__(self, cls):
        self.cls = cls

    def of(self, base):
        if base is None:                        # implicit this->pattern
            return self.cls
        b = strip(base)
        text = ''.join(t.spelling for t in b.get_tokens())
        if b.kind == CK.CXX_THIS_EXPR or text == 'this':
            return self.cls
        if text.startswith('m_objects[') or text.startswith('this->m_objects['):
            return self.cls
        if text in ('m_afterimages', 'this->m_afterimages'):
            return self.cls
        return None


class Rewriter:
    def __init__(self, spec, data, path):
        self.spec, self.data, self.path = spec, data, path
        self.edits = {}
        self.stats = collections.Counter()

    def put(self, lit, text, kind):
        off = lit.extent.start.offset
        end = lit.extent.end.offset
        if lit.location.file is None or os.path.abspath(lit.location.file.name) != self.path:
            return
        self.edits[off] = (end, text)
        self.stats[kind] += 1

    def action_name(self, cls, owner, value, in_class):
        """The constant for action `value` of a player of class `owner` (None if not
        known), as written in a method of `in_class`."""
        if value < CHARACTER_FIRST:
            name = self.spec['action']['CPlayer'].get(value)
            # A character's own constant of that name would hide the shared one.
            if name and in_class not in (None, 'CPlayer') and \
                    name in self.spec['action'].get(in_class, {}).values():
                return '::' + name
            return name
        name = None
        if owner is not None and owner != 'CPlayer':
            name = self.spec['action'].get(owner, {}).get(value)
        if name is not None:
            return name if owner == in_class else f'{owner}::{name}'
        # The objects every character has are shared constants too.
        name = self.spec['action']['CPlayer'].get(value)
        if name and in_class not in (None, 'CPlayer') and \
                    name in self.spec['action'].get(in_class, {}).values():
            return '::' + name
        return name

    def command_name(self, cls, value):
        """The constant for command `value` in a method of `cls`: its own, else shared."""
        own = self.spec['command'].get(cls, {}).get(value) if cls else None
        if own:
            return own
        name = self.spec['command']['CPlayer'].get(value)
        if name and cls not in (None, 'CPlayer') and \
                name in self.spec['command'].get(cls, {}).values():
            return '::' + name
        return name

    def run(self, fn):
        cls = fn.semantic_parent.spelling if fn.kind in (
            CK.CXX_METHOD, CK.CONSTRUCTOR, CK.DESTRUCTOR) else None
        owner = Owner(cls)
        descs = self.effect_descs(fn)
        self.visit(fn, cls, owner, descs)

    def effect_descs(self, fn):
        """{variable name: 'object' | 'effect'}: what each EffectDesc local is given to."""
        uses = collections.defaultdict(set)
        for c in fn.walk_preorder():
            if c.kind == CK.CALL_EXPR and c.spelling in ('SpawnObject', 'CreateEffect'):
                for a in c.get_arguments():
                    toks = [t.spelling for t in a.get_tokens()]
                    names = [t for t in toks if re.match(r'[A-Za-z_]\w*$', t) and t not in (
                        'EffectDesc', 'p1')]
                    if names:
                        uses[names[-1]].add('object' if c.spelling == 'SpawnObject' else 'effect')
        return {k: next(iter(v)) for k, v in uses.items() if len(v) == 1}

    def visit(self, c, cls, owner, descs):
        for x in c.get_children():
            if in_macro(x):
                continue
            op = binop(x)
            kids = list(x.get_children())
            if op is not None and len(kids) == 2:
                self.binary(x, op, kids, cls, owner, descs)
            elif x.kind == CK.ARRAY_SUBSCRIPT_EXPR and len(kids) == 2:
                m = member_name(kids[0])
                lit = literal(kids[1])
                if m and lit and m[0] in ('m_patterns', 'anims') and m[1] in ('CPlayer', 'ObjBase'):
                    name = self.action_name(cls, owner.of(m[2]), lit[0], cls)
                    if name:
                        self.put(lit[1], name, 'action')
            elif x.kind == CK.SWITCH_STMT:
                self.switch(x, kids, cls, owner)
            self.visit(x, cls, owner, descs)

    def switch(self, x, kids, cls, owner):
        m = member_name(kids[0])
        if not m:
            return
        if m[0] == 'pattern':
            kind = 'action'
        elif m[0] == 'm_command':
            kind = 'command'
        else:
            return
        own = owner.of(m[2])
        body = kids[-1]
        for c in body.walk_preorder():
            if c.kind == CK.SWITCH_STMT and c != x:
                break
            if c.kind == CK.CASE_STMT:
                lit = literal(list(c.get_children())[0])
                if not lit:
                    continue
                name = self.action_name(cls, own, lit[0], cls) if kind == 'action' else \
                    self.command_name(cls, lit[0])
                if name:
                    self.put(lit[1], name, kind)

    def binary(self, x, op, kids, cls, owner, descs):
        a, b = kids
        # flags: word & mask
        if op == '&':
            for word, mask in ((a, b), (b, a)):
                m = member_name(word)
                lit = literal(mask)
                if m and lit:
                    bits = self.spec['flag'].get(f'{m[1]}::{m[0]}')
                    if bits:
                        text = self.mask(bits, lit[0])
                        if text:
                            self.put(lit[1], text, 'flag')
            return
        if op in COMPARE:
            for side, other in ((a, b), (b, a)):
                m = member_name(side)
                if not m:
                    continue
                if m[0] == 'pattern' and m[1] in ('ObjBase', 'Afterimages'):
                    for lit in self.literals(other):
                        if op in ('==', '!=', '='):
                            name = self.action_name(cls, owner.of(m[2]), lit[0], cls)
                        else:
                            # A range: a declared bound, or a shared action (their
                            # numbers are grouped); a character's own stay numbers.
                            name = self.spec['bound'].get(lit[0])
                            if name is None and lit[0] < CHARACTER_FIRST:
                                name = self.action_name(cls, None, lit[0], cls)
                        if name:
                            self.put(lit[1], name, 'action')
                elif m[0] == 'm_command' and op in ('==', '!=', '='):
                    for lit in self.literals(other, sums=True):
                        name = self.command_name(cls, lit[0])
                        if name:
                            self.put(lit[1], name, 'command')
                elif m[0] == 'type' and m[1] == 'EffectDesc' and op == '=':
                    var = ''.join(t.spelling for t in strip(m[2]).get_tokens()) if m[2] else ''
                    use = descs.get(var.lstrip('&*'))
                    for lit in self.literals(other):
                        if use == 'object':
                            name = self.action_name(cls, cls, lit[0], cls)
                            kind = 'action'
                        elif use == 'effect':
                            name = self.spec['effect'].get(lit[0])
                            kind = 'effect'
                        else:
                            name = None
                        if name:
                            self.put(lit[1], name, kind)

    def literals(self, c, sums=False):
        """The literals an assigned or compared value is made of: itself, both arms of
        a ?:, and (for commands) the literal term of a sum."""
        lit = literal(c)
        if lit:
            return [lit]
        s = strip(c)
        if s.kind == CK.CONDITIONAL_OPERATOR:
            out = []
            for k in list(s.get_children())[1:]:
                out += self.literals(k, sums)
            return out
        if sums and binop(s) == '+':
            out = []
            for k in s.get_children():
                ks = strip(k)
                if binop(ks) == '+':
                    out += self.literals(ks, sums)
                else:
                    lit = literal(ks)
                    if lit and lit[0] >= 8:
                        out.append(lit)
            return out[:1]
        return []

    @staticmethod
    def mask(bits, value):
        names = []
        rest = value
        for bit in sorted(bits):
            if rest & bit == bit and bin(bit).count('1') == 1:
                names.append(bits[bit])
                rest &= ~bit
        if rest or not names:
            return bits.get(value)
        return names[0] if len(names) == 1 else '(' + ' | '.join(names) + ')'

    def apply(self):
        out = self.data
        for off in sorted(self.edits, reverse=True):
            end, text = self.edits[off]
            out = out[:off] + text.encode('utf-8') + out[end:]
        return out


def work(job):
    path, spec = job
    tu = parse(path, ci.Index.create())
    with open(path, 'rb') as f:
        data = f.read()
    rw = Rewriter(spec, data, path)
    for fn in functions_in(tu, path):
        rw.run(fn)
    return path, data, rw.apply(), rw.stats


def main():
    if len(sys.argv) < 3 or sys.argv[1] not in ('apply', 'check', 'declare'):
        print(__doc__)
        sys.exit(2)
    if sys.argv[1] == 'declare':
        declare(sys.argv[2])
        return
    mode, spec = sys.argv[1], read_spec(sys.argv[2])
    files = [os.path.abspath(a) for a in sys.argv[3:]] or members.default_files()
    files = [f for f in files if f.endswith('.cpp')]
    members.include_farm()
    total = collections.Counter()
    with multiprocessing.Pool() as pool:
        for path, old, new, stats in pool.imap(work, [(p, spec) for p in files]):
            total.update(stats)
            if old == new:
                continue
            rel = os.path.relpath(path, REPO)
            if mode == 'apply':
                with open(path, 'wb') as f:
                    f.write(new)
                print(f'{rel}: {dict(stats)}')
            else:
                sys.stdout.writelines(difflib.unified_diff(
                    old.decode('utf-8').splitlines(True), new.decode('utf-8').splitlines(True),
                    rel, rel))
    print(f'total: {dict(total)}', file=sys.stderr)


if __name__ == '__main__':
    main()
