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

# Inline functions, emitted after the object's other functions: they are defined in a
# header, and the generator writes them as such.
def is_inline(obj, addr):
    lo, hi, cls, names = OBJECTS[obj]
    return obj == 'player' and addr >= 0x412820


# Base classes at a nonzero offset: converting a pointer to them is a null-checked
# addition, `p ? (char*)p + off : 0`.
BASES = {('CPlayer', 8): 'ObjBase'}

# Signatures the lifter can't infer: {address: (return type, [parameter types])}.
SIGNATURES = {
    0x412930: ('void', ['ObjBase*']),
    0x412a10: ('void', ['ObjBase*', 'char']),
}
