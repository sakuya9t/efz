"""What tools/lift.py needs to know to generate a whole object file: its address range,
the class its functions belong to, and names for the ones that aren't plain methods.

Each entry: (first address, end address, default class, {address: qualified name}).
Names with a `??_` prefix are compiler-generated (vector deleting destructors) and are
not written out; the lifter only uses them to recognise `delete[]`.
"""

OBJECTS = {
    'player': (0x40e630, 0x412b10, 'CPlayer', {
        0x40eae0: 'CPlayer::CPlayer',
        0x40ecb0: 'CPlayer::~CPlayer',
        0x40f110: 'CPlayer::Vf0',
        0x410b70: 'CPlayer::Vf11',
        0x40edf0: 'CPlayer::Vf12',
        0x412820: 'PatternData::PatternData',
        0x412840: 'Afterimages::Afterimages',
        0x412870: '??_EPatternData@@QAEPAXI@Z',
        0x4128e0: 'PatternData::~PatternData',
        0x412910: 'Afterimages::Unk412910',
        0x412930: 'Afterimages::Unk412930',
        0x412a10: 'Afterimages::Unk412a10',
        0x412ad0: 'PatternData::Alloc',
    }),
    'playerobj': (0x412b10, 0x4136d0, 'CPlayer', {
        0x412b10: 'CPlayer::Vf9',
        0x412e60: 'CPlayer::Vf10',
    }),
}

# Character classes: (object, class, first address, end address, vtable, constructor,
# size from the scene code's `new`). Each derives from CPlayer and overrides its virtual
# slots (named VfN after the slot).
CHARACTERS = [
    ('shiori', 'CShiori', 0x4136d0, 0x434060, 0x787df8, 0x422d70, 0x3458),
]

CPLAYER_SLOT11 = 0x410b70     # the one slot characters inherit


def _vtable(addr, n=13):
    import os
    import struct
    import pefile
    global _IMAGE
    if '_IMAGE' not in globals():
        pe = pefile.PE(os.path.join(os.environ['EFZ_DIR'], 'efz.exe'))
        _IMAGE = pe.get_memory_mapped_image()
    return [struct.unpack_from('<I', _IMAGE, addr - 0x400000 + 4 * k)[0] for k in range(n)]


for _obj, _cls, _lo, _hi, _vt, _ctor, _size in CHARACTERS:
    _names = {_ctor: f'{_cls}::{_cls}'}
    for _k, _a in enumerate(_vtable(_vt)):
        if _a != CPLAYER_SLOT11:
            _names[_a] = f'{_cls}::Vf{_k}'
    OBJECTS[_obj] = (_lo, _hi, _cls, _names)

# Inline functions, emitted after the object's other functions: they are defined in a
# header, and the generator writes them as such.
INLINE_FROM = {'player': 0x412820}


def is_inline(obj, addr):
    return obj in INLINE_FROM and addr >= INLINE_FROM[obj]


# Base classes at a nonzero offset: converting a pointer to them is a null-checked
# addition, `p ? (char*)p + off : 0`.
BASES = {('CPlayer', 8): 'ObjBase'}

# Signatures the lifter can't infer: {address: (return type, [parameter types])}.
SIGNATURES = {
    0x412930: ('void', ['ObjBase*']),
    0x412a10: ('void', ['ObjBase*', 'char']),
    0x412b10: ('void', ['EffectDesc*']),     # CPlayer::Vf9 spawns an object
    0x413090: ('void', ['EffectDesc*']),
}
