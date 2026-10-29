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
        0x40f110: 'CPlayer::StartPattern',
        0x410b70: 'CPlayer::Load',
        0x40edf0: 'CPlayer::Reset',
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
        0x412b10: 'CPlayer::SpawnObject',
        0x412e60: 'CPlayer::RemoveObject',
    }),
}

# Inline methods of shared classes, named wherever their copy happens to be emitted.
SHARED = {
    0x434010: 'ObjBase::SetVelocity',
    0x4c0480: 'ObjBase::AngleTo',
}

# Character classes: (object, class, first address, end address, vtable, constructor,
# size from the scene code's `new`). Each derives from CPlayer and overrides its virtual
# slots (named as PLAYER_SLOTS below). Each is two objects, as in the original:
# <object>_vf6 holds UpdatePattern (the per-state update), which comes first, up to the
# constructor, and <object> the rest of the class. The split shows in .rdata, where
# UpdatePattern's floating-point constants precede the string section the constructor's
# folder name is in.
CHARACTERS = [
    ('shiori', 'CShiori', 0x4136d0, 0x434060, 0x787df8, 0x422d70, 0x3458),
    ('sayuri', 'CSayuri', 0x434060, 0x451850, 0x788138, 0x4463e0, 0x3458),
    ('nayuki', 'CNayuki', 0x451850, 0x46d970, 0x788270, 0x461090, 0x3460),
    ('mizukab', 'CMizukaB', 0x4c04b0, 0x4e7ec0, 0x7884f0, 0x4d2850, 0x3460),
    ('mizuka', 'CMizuka', 0x4e7ec0, 0x50c4b0, 0x7885d0, 0x4f8300, 0x3460),
    ('misuzu', 'CMisuzu', 0x50c4b0, 0x530bc0, 0x788650, 0x519e00, 0x3488),
    ('mishio', 'CMishio', 0x530bc0, 0x5571f0, 0x788768, 0x546480, 0x3478),
    ('misaki', 'CMisaki', 0x5571f0, 0x5736d0, 0x788808, 0x567900, 0x3448),
    ('mio', 'CMio', 0x5736d0, 0x59c4a0, 0x78887c, 0x588310, 0x3458),
    ('minagi', 'CMinagi', 0x59c4a0, 0x5c8580, 0x788940, 0x5a9fa0, 0x3458),
    ('mayu', 'CMayu', 0x5c8580, 0x5e85f0, 0x788a68, 0x5dddf0, 0x3448),
    ('makoto', 'CMakoto', 0x5e85f0, 0x607930, 0x788ac8, 0x5f6d90, 0x3450),
    ('mai', 'CMai', 0x607930, 0x62a5e0, 0x788b7c, 0x6163b0, 0x3458),
    ('kanna', 'CKanna', 0x667570, 0x683550, 0x788ce0, 0x675c80, 0x3458),
    ('ayu', 'CAyu', 0x6d93f0, 0x6f2f20, 0x788e4c, 0x6e8130, 0x3450),
    ('akane', 'CAkane', 0x6f2f20, 0x712500, 0x788eb0, 0x7039d0, 0x3450),
    ('akiko', 'CAkiko', 0x712500, 0x730710, 0x788f58, 0x7219a0, 0x3468),
    ('nanase', 'CNanase', 0x46d970, 0x49d610, 0x788334, 0x48a720, 0x3470),
    ('nagamori', 'CNagamori', 0x49d610, 0x4c04b0, 0x7883fc, 0x4add90, 0x34b0),
    ('kaori', 'CKaori', 0x62a5e0, 0x6429c0, 0x788bf8, 0x638d90, 0x3450),
    ('kano', 'CKano', 0x6429c0, 0x667570, 0x788c78, 0x653a20, 0x3478),
    ('ikumi', 'CIkumi', 0x683550, 0x6be9c0, 0x788d74, 0x6a59c0, 0x3478),
    ('exnanase', 'CEXNanase', 0x6be9c0, 0x6d93f0, 0x788de4, 0x6cfbb0, 0x3468),
    ('nayukib', 'CNayukiB', 0x730710, 0x750d30, 0x788fb8, 0x73e790, 0x3458),
]

# Other functions of character objects with known roles.
EXTRA_NAMES = {
    0x48ab00: 'CNanase::~CNanase',     # never called: players are deleted as CPlayer
    0x6a5dc0: 'CIkumi::~CIkumi',
}

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


# CPlayer's virtual slots, as src/efz.h names them.
PLAYER_SLOTS = ['StartPattern', 'DrawGauge', 'ReadCommand', 'Move', 'StartCommand',
                'CpuInput', 'UpdatePattern', 'UpdateObjects', 'Vf8', 'SpawnObject',
                'RemoveObject', 'Load', 'Reset']

for _obj, _cls, _lo, _hi, _vt, _ctor, _size in CHARACTERS:
    _names = {_ctor: f'{_cls}::{_cls}'}
    _names.update({a: n for a, n in SHARED.items() if _lo <= a < _hi})
    _names.update({a: n for a, n in EXTRA_NAMES.items() if _lo <= a < _hi})
    for _k, _a in enumerate(_vtable(_vt)):
        if _a != CPLAYER_SLOT11:
            _names[_a] = f'{_cls}::{PLAYER_SLOTS[_k]}'
    OBJECTS[_obj + '_vf6'] = (_lo, _ctor, _cls, _names)
    OBJECTS[_obj] = (_ctor, _hi, _cls, _names)

# Classes other than characters: (object, class, base, first address, end address,
# vtable, slot names, constructor, destructor, size, {address: name}, inline from).
# The destructors set the vtable but are never called.
SCENE_SLOTS = ['Draw', 'Update', 'Vf2']
BG_SLOTS = ['Vf0', 'Vf1']
_BG_BASE = {0x750d30: 'CAnimBg::Load', 0x751030: 'CAnimBg::Unk751030',
            0x7519f0: 'CAnimBg::CAnimBg', 0x751a10: '??_GEffectAnim@@QAEPAXI@Z'}
_SCENE_BASE = {0x759c10: 'CScene::CScene', 0x759c90: 'CScene::Unk759c90',
               0x759e20: 'CScene::Unk759e20'}
CLASSES = [
    ('bg01', 'CBg01', 'CAnimBg', 0x750d30, 0x751a40, 0x7890b0, BG_SLOTS, 0x751370, 0x751500, 0x1c,
     _BG_BASE, 0x7519f0),
    ('bg10', 'CBg10', 'CAnimBg', 0x751a40, 0x7520b0, 0x7890c0, BG_SLOTS, 0x751a40, 0x751bc0, 0x1c,
     {}, None),
    ('bg12', 'CBg12', 'CAnimBg', 0x7520b0, 0x752900, 0x7890c8, BG_SLOTS, 0x7520b0, 0x752240, 0x1c,
     {}, None),
    ('bg16', 'CBg16', 'CAnimBg', 0x752900, 0x753260, 0x7890d0, BG_SLOTS, 0x752900, 0x752a90, 0x1c,
     {}, None),
    ('scene1', 'CScene1', 'CScene', 0x753260, 0x759f30, 0x7892c0, SCENE_SLOTS, 0x753260, 0x7538b0,
     0x560, _SCENE_BASE, 0x759c10),
    ('scene6', 'CScene6', 'CScene', 0x759f30, 0x75db70, 0x7895a8, SCENE_SLOTS, 0x759f30, 0x75a3b0,
     0x760, {}, None),
    ('scene3', 'CScene3', 'CScene', 0x75db70, 0x76c6f0, 0x7895dc, SCENE_SLOTS, 0x7633a0, 0x763c00,
     0x598, {}, None),
    ('scene2', 'CScene2', 'CScene', 0x76c6f0, 0x76e480, 0x7896b4, SCENE_SLOTS, 0x76c6f0, 0x76c740,
     0x438, {}, None),
    ('scene8', 'CScene8', 'CScene', 0x76e480, 0x7712f0, 0x7897dc, SCENE_SLOTS, 0x76e480, 0x76efe0,
     0x758, {}, None),
    ('scene5', 'CScene5', 'CScene', 0x7712f0, 0x7758b0, 0x789874, SCENE_SLOTS, 0x7712f0, 0x771400,
     0x474, {0x775810: '?pow@@YANHH@Z', 0x775830: '??$_Pow_int@H@@YAHHH@Z'}, None),
    ('scene7', 'CScene7', 'CScene', 0x7758b0, 0x775d60, 0x7898c0, SCENE_SLOTS, 0x7758b0, 0x7759a0,
     0x448, {}, None),
    ('scene0', 'CScene0', 'CScene', 0x775d60, 0x77697e, 0x789980, SCENE_SLOTS, 0x775d60, 0x775f30,
     0x44c, {}, None),
]

# Classes whose leading functions were a source file of their own in the original:
# {object: (name of that file's object, address where the class's own object starts)}.
# CScene3's drawing helpers come before the constructor, but their floating-point
# constants precede the string section the rest of the class starts with.
SPLIT = {'scene3': ('scene3_draw', 0x7633a0)}

for _obj, _cls, _base, _lo, _hi, _vt, _slots, _ctor, _dtor, _size, _extra, _inl in CLASSES:
    _names = {_ctor: f'{_cls}::{_cls}', _dtor: f'{_cls}::~{_cls}'}
    for _k, _a in enumerate(_vtable(_vt, len(_slots))):
        _names[_a] = f'{_cls}::{_slots[_k]}'
    _names.update(_extra)
    if _obj in SPLIT:
        _first, _lo2 = SPLIT[_obj]
        OBJECTS[_first] = (_lo, _lo2, _cls, _names)
        _lo = _lo2
    OBJECTS[_obj] = (_lo, _hi, _cls, _names)

# Inline functions, emitted after the object's other functions: they are defined in a
# header, and the generator writes them as such.
INLINE_FROM = {'player': 0x412820}
INLINE_FROM.update({c[0]: c[11] for c in CLASSES if c[11]})


def is_inline(obj, addr):
    return (obj in INLINE_FROM and addr >= INLINE_FROM[obj]) or addr in SHARED


# Base classes at a nonzero offset: converting a pointer to them is a null-checked
# addition, `p ? (char*)p + off : 0`.
BASES = {('CPlayer', 8): 'ObjBase'}

# Signatures the lifter can't infer: {address: (return type, [parameter types])}.
SIGNATURES = {
    0x412930: ('void', ['ObjBase*']),
    0x412a10: ('void', ['ObjBase*', 'char']),
    0x412b10: ('void', ['EffectDesc*']),     # CPlayer::Vf9 spawns an object
    0x413090: ('void', ['EffectDesc*']),
    0x434010: ('void', ['double', 'double']),
    0x4c0480: ('double', ['double', 'double']),
}
SIGNATURES[0x7679b0] = ('int', ['int', 'int', 'CollisionInfo*', 'CollisionInfo*'])
SIGNATURES[0x767f60] = ('void', ['int', 'int', 'CollisionInfo*', 'CollisionInfo*'])
SIGNATURES[0x7697d0] = ('void', ['int', 'int', 'int', 'CollisionInfo*'])
SIGNATURES[0x76bd40] = ('void', ['int', 'int', 'CollisionInfo*', 'CollisionInfo*', 'int'])
SIGNATURES[0x759c90] = ('void', ['PALETTEENTRY*', 'BYTE', 'int', 'int'])
SIGNATURES[0x759e20] = ('void', ['PALETTEENTRY*', 'BYTE'])
_SCENE_ARGS = ['HWND', 'CPlayer**', 'CPlayer**', 'CGame*', 'CGraphics*', 'CInput*', 'CSound*']
for _a in (0x759c10, 0x775d60, 0x753260, 0x76c6f0, 0x7633a0, 0x7712f0, 0x759f30, 0x7758b0,
           0x76e480):
    SIGNATURES[_a] = ('void', _SCENE_ARGS)

