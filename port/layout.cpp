// The game's structures keep the original's layout in the native build: their pointers
// are 32-bit handles (port/guest.h), and the code still adds offsets to pointers it
// keeps in ints, copies whole structures and reads some from files. These checks hold
// every compiler to the sizes and offsets src/efz.h gives. The classes whose members
// follow a vtable pointer (the scenes and the animated backgrounds) are the exception:
// the native build's vtable pointer is 8 bytes, so their members come VPTR_PAD later,
// and their code only reaches them by name.
#include <stddef.h>

#include "efz.h"

#define OFFSET(T, member, at) static_assert(offsetof(T, member) == (at), #T "::" #member)
#define SIZE(T, size) static_assert(sizeof(T) == (size), "sizeof(" #T ")")
#define VPTR_PAD (sizeof(void*) - 4)

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif

SIZE(RECT, 0x10);
SIZE(PALETTEENTRY, 4);
SIZE(DIJOYSTATE, 0x50);
SIZE(WAVEFORMATEX, 0x12);
SIZE(F32, 4);
SIZE(PTR32(void), 4);

SIZE(EffectFrame, 0xc);
SIZE(EffectAnim, 8);
OFFSET(EffectAnim, frames, 4);
SIZE(PatternData, 8);
SIZE(PatternFrame, 0xc8);
OFFSET(PatternFrame, pushBox, 0x90);
OFFSET(PatternFrame, proration, 0xa4);
OFFSET(PatternFrame, hitVx, 0xb8);
SIZE(ObjBase, 0x50);
OFFSET(ObjBase, anims, 8);
OFFSET(ObjBase, surfaces, 0xc);
OFFSET(ObjBase, x, 0x18);
OFFSET(ObjBase, vx, 0x28);
OFFSET(ObjBase, facing, 0x48);
SIZE(PlayerObject, 0x98);
SIZE(BgObject, 0x70);
SIZE(Afterimages, 0x4f8);
SIZE(Effect, 0x70);
SIZE(EffectDesc, 0x48);
SIZE(CReplayFile, 0x10);
OFFSET(CReplayFile, m_read, 0xc);

SIZE(CGame, 0x142f0);
OFFSET(CGame, m_graphics, 0);
OFFSET(CGame, m_holdA, 0x18);
OFFSET(CGame, m_surfaces, 0x38);
OFFSET(CGame, m_stageSurface, 0xe98);
OFFSET(CGame, m_sounds, 0xea4);
OFFSET(CGame, m_music, 0xf26);
OFFSET(CGame, m_stage, 0xf32);
OFFSET(CGame, m_colorKey, 0xf34);
OFFSET(CGame, m_palette, 0xf35);
OFFSET(CGame, m_extraChars, 0x1341);
OFFSET(CGame, m_isCpu, 0x1343);
OFFSET(CGame, m_oddFrame, 0x1368);
OFFSET(CGame, m_background, 0x137c);
OFFSET(CGame, m_effectHead, 0x1380);
OFFSET(CGame, m_effects, 0x2a08);
OFFSET(CGame, m_effectAnims, 0x14208);
OFFSET(CGame, m_shake, 0x14210);
OFFSET(CGame, m_view, 0x14248);
OFFSET(CGame, m_fade, 0x14260);
OFFSET(CGame, m_replayMode, 0x14283);
OFFSET(CGame, m_replay, 0x14284);
OFFSET(CGame, m_ellipseIndex, 0x14294);

OFFSET(CGraphics, m_mode, 4);
OFFSET(CGraphics, m_palette, 5);
OFFSET(CGraphics, m_blend, 0x405);
OFFSET(CGraphics, m_quarterSquares, 0x20406);
OFFSET(CGraphics, m_dd, 0x20808);
OFFSET(CGraphics, m_ddpal, 0x20814);
OFFSET(CInput, m_joyState, 0x120);
OFFSET(CInput, m_bindings, 0x1c0);
OFFSET(CInput, m_keyboard, 0x1e8);
OFFSET(CSound, m_data, 0x10);
OFFSET(CSound, m_buffers, 0x4c0);

SIZE(CPlayer, 0x3138);
OFFSET(CPlayer, x, 0x20);
OFFSET(CPlayer, facing, 0x50);
OFFSET(CPlayer, m_opponent, 0x78);
OFFSET(CPlayer, m_paletteIndex, 0x8e);
OFFSET(CPlayer, m_comboDamage, 0x100);
OFFSET(CPlayer, m_hp, 0x108);
OFFSET(CPlayer, m_gauge, 0x148);
OFFSET(CPlayer, m_patterns, 0x164);
OFFSET(CPlayer, m_hitsLeft, 0x16c);
OFFSET(CPlayer, m_comboHits, 0x174);
OFFSET(CPlayer, m_objects, 0x4d0);
OFFSET(CPlayer, m_afterimages, 0x2bc0);
SIZE(CShiori, 0x3458);
SIZE(CSayuri, 0x3458);
SIZE(CNayuki, 0x3460);
SIZE(CMizukaB, 0x3460);
SIZE(CMizuka, 0x3460);
SIZE(CMisuzu, 0x3488);
SIZE(CMishio, 0x3478);
SIZE(CMisaki, 0x3448);
SIZE(CMio, 0x3458);
SIZE(CMinagi, 0x3458);
SIZE(CMayu, 0x3448);
SIZE(CMakoto, 0x3450);
SIZE(CMai, 0x3458);
SIZE(CKanna, 0x3458);
SIZE(CAyu, 0x3450);
SIZE(CAkane, 0x3450);
SIZE(CAkiko, 0x3468);
SIZE(CNanase, 0x3470);
SIZE(CNagamori, 0x34b0);
SIZE(CKaori, 0x3450);
SIZE(CKano, 0x3478);
SIZE(CIkumi, 0x3478);
SIZE(CEXNanase, 0x3468);
SIZE(CNayukiB, 0x3458);

OFFSET(CScene, lastMessage, 4 + VPTR_PAD);
OFFSET(CScene, m_players, 0xc + VPTR_PAD);
OFFSET(CScene, m_sound, 0x28 + VPTR_PAD);
OFFSET(CScene, m_palette, 0x2e + VPTR_PAD);
OFFSET(CAnimBg, m_number, 4 + VPTR_PAD);
OFFSET(CAnimBg, m_colorKey, 0x18 + VPTR_PAD);
