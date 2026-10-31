// The compatibility test's harness (docs/compat.md), in both the original's build (make
// trace) and the native one: it plays or records a fight without the menus and logs the
// game's state after every tick of it. Not part of efz.exe.
//
// Set by environment variables, read once at startup:
//   EFZ_TRACE         file to log to; nothing happens without it
//   EFZ_TRACE_PLAY    N-M: play replay\dataN-M.rep
//   EFZ_TRACE_RECORD  N-M:P1:P2:STAGE:PAL1:PAL2:SEED[:C1:C2]: record replay\dataN-M.rep,
//                     the characters, stage and palettes given (numbers as in the replay
//                     header). C1 and C2 say who plays each side: 0 (the default)
//                     scripted random input from SEED, 1 the game's CPU
//   EFZ_TRACE_SEED    the seed for rand() when playing a replay (default 1); recording
//                     seeds it with SEED
//   EFZ_TRACE_TICKS   stop after this many ticks of the fight
//   EFZ_TRACE_FAST    nonzero: don't wait between frames
//   EFZ_TRACE_DUMP    file to write the bytes of every hashed block to (see below), from
//                     tick EFZ_TRACE_DUMP_FROM (default 0) to EFZ_TRACE_DUMP_TO
//                     (default: the end), for finding the bytes two runs disagree on
// The game stops when the fight ends.
//
// The log starts with a line naming its format and the hashed blocks. Then each line is
// one tick: the tick, the replay file's read position, for each player its action and
// frame, position and velocity (the doubles' bits in hex), HP, HP when the combo began,
// the combo's damage and hits, gauge and facing; then, after a #, an FNV-1a hash of each
// block of the game's state:
//   p1, p2         the player: CPlayer's members, without its object table
//   p1obj, p2obj   its 64 objects (projectiles, parts of supers...)
//   p1char, p2char the character class's own members
//   scene          the fight scene's (CScene3's)
//   game           CGame's, without the effects
//   fx             the effects' ring buffer
// Pointers are left out (zeroed in the block): their values differ between builds.
//
// What makes two builds comparable on every byte: memory from `new` starts zeroed in both
// (the native game's arena always does; the original's heap holds garbage, which decides
// a few hits, docs/compat.md), sin, cos and atan2 are correctly rounded in both (the
// CPU's differ between CPUs), rand() is seeded the same in both, and while a replay
// plays the controls read as untouched.
#ifdef EFZ_TRACE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "efz.h"

static FILE* g_traceFile;
static int g_traceFast;
static long g_traceTicks;
static long g_traceTickLimit;
static int g_traceFought;
static int g_traceRecording;
static int g_tracePlaying;
static CPlayer* g_tracePlayers[2];
static FILE* g_traceDump;
static long g_traceDumpFrom;
static long g_traceDumpTo;

#ifndef EFZ_NATIVE
// The original's build: zeroed memory from `new`, as the native game's arena gives.
void* operator new(size_t size)
{
    void* p = malloc(size ? size : 1);

    if (p)
        memset(p, 0, size);
    return p;
}

// And in place of the C library's sin, cos and atan2, which are the CPU's fsin, fcos
// and fpatan, port/x87.cpp's correctly rounded ones (tools/x87ref.cpp, which MinGW
// builds): the CPU's last bits differ from one CPU to another. The result is left on
// the x87 stack with its 64-bit significand, as the instructions leave theirs.
extern "C" void EfzReferenceTrig(int op, double a, double b, unsigned char* out);

#pragma warning(disable : 4035) // no return value: it is in st(0)
extern "C" double __cdecl sin(double x)
{
    unsigned char r[10];

    EfzReferenceTrig(0, x, 0.0, r);
    __asm fld tbyte ptr r
}

extern "C" double __cdecl cos(double x)
{
    unsigned char r[10];

    EfzReferenceTrig(1, x, 0.0, r);
    __asm fld tbyte ptr r
}

extern "C" double __cdecl atan2(double y, double x)
{
    unsigned char r[10];

    EfzReferenceTrig(2, y, x, r);
    __asm fld tbyte ptr r
}
#pragma warning(default : 4035)
#endif

// --- Scripted input while recording: per player, a direction held for a while,
// buttons tapped now and then, and from time to time a motion: a special move's, a
// super's, a dash.

struct TraceBot {
    unsigned state;
    long tick;   // the tick `input` is for
    BYTE input;
    int dir;     // numpad direction, 5 neutral
    int dirLeft;
    BYTE buttons;
    int buttonsLeft;
    const char* motion;
    BYTE motionButton;
};
static TraceBot g_traceBots[2];

static unsigned TraceRandom(TraceBot* b)
{
    b->state ^= b->state << 13;
    b->state ^= b->state >> 17;
    b->state ^= b->state << 5;
    return b->state;
}

// Numpad direction to input bits for a player facing right (1) or left (-1).
static BYTE TraceDirection(int dir, int facing)
{
    BYTE bits = 0;
    int h = (dir - 1) % 3 - 1;
    if (dir >= 7)
        bits |= 8;
    if (dir <= 3)
        bits |= 4;
    if (facing < 0)
        h = -h;
    if (h > 0)
        bits |= 1;
    if (h < 0)
        bits |= 2;
    return bits;
}

static BYTE TraceBotInput(int player)
{
    // Each motion is entered one direction a frame, the button (if any) with the last.
    static const char* motions[] = {
        "236", "214", "623", "421", "41236", "63214", "2222", "6321469",
        "236236", "214214", "22", "632146", "641236", "2141236", "4123641236",
        "656", "454", "252", "2147", "2369", "28", "46", "64", "4446",
    };
    static const int dirs[] = {6, 6, 6, 6, 3, 3, 2, 1, 4, 7, 8, 9, 9, 5, 6, 2};
    TraceBot* b = &g_traceBots[player];
    int facing = 1;
    BYTE bits;

    if (b->tick == g_traceTicks)
        return b->input;
    b->tick = g_traceTicks;
    if (g_tracePlayers[player])
        facing = g_tracePlayers[player]->facing;
    if (b->motion) {
        bits = TraceDirection(*b->motion - '0', facing);
        b->motion++;
        if (!*b->motion) {
            bits |= b->motionButton;
            b->motion = NULL;
        }
        b->input = bits;
        return bits;
    }
    if (TraceRandom(b) % 30 == 0) {
        b->motion = motions[TraceRandom(b) % (sizeof(motions) / sizeof(motions[0]))];
        b->motionButton = 0x10 << (TraceRandom(b) % 4);
        if (TraceRandom(b) % 5 == 0)
            b->motionButton = 0;
        else if (TraceRandom(b) % 6 == 0)
            b->motionButton |= 0x10 << (TraceRandom(b) % 4);
    }
    if (b->dirLeft-- <= 0) {
        b->dir = dirs[TraceRandom(b) % (sizeof(dirs) / sizeof(dirs[0]))];
        b->dirLeft = 3 + TraceRandom(b) % 40;
    }
    if (b->buttonsLeft-- <= 0) {
        b->buttons = 0;
        if (TraceRandom(b) % 3 == 0) {
            b->buttons = 0x10 << (TraceRandom(b) % 4);
            if (TraceRandom(b) % 8 == 0)
                b->buttons |= 0x10 << (TraceRandom(b) % 4);
            b->buttonsLeft = 1 + TraceRandom(b) % 6;
        } else {
            b->buttonsLeft = TraceRandom(b) % 6;
        }
    }
    b->input = TraceDirection(b->dir, facing) | b->buttons;
    return b->input;
}

// --- The hooks.

void TraceStart(CGame* game, CScene** scenes, BYTE* scene)
{
    const char* out = getenv("EFZ_TRACE");
    const char* play = getenv("EFZ_TRACE_PLAY");
    const char* record = getenv("EFZ_TRACE_RECORD");
    const char* ticks = getenv("EFZ_TRACE_TICKS");
    const char* fast = getenv("EFZ_TRACE_FAST");
    const char* dump = getenv("EFZ_TRACE_DUMP");
    const char* dumpFrom = getenv("EFZ_TRACE_DUMP_FROM");
    const char* dumpTo = getenv("EFZ_TRACE_DUMP_TO");
    const char* playSeed = getenv("EFZ_TRACE_SEED");
    int row, col, c1, c2, stage, pal1, pal2, cpu1, cpu2, n;
    unsigned seed;

    if (!out)
        return;
    g_traceFile = fopen(out, "wb"); // "\n" lines on every system
    fprintf(g_traceFile, "# efz-trace 2 p1 p1obj p1char p2 p2obj p2char scene game fx\n");
    if (dump)
        g_traceDump = fopen(dump, "wb");
    g_traceDumpFrom = dumpFrom ? atol(dumpFrom) : 0;
    g_traceDumpTo = dumpTo ? atol(dumpTo) : -1;
    g_traceFast = fast && atoi(fast) != 0;
    g_traceTickLimit = ticks ? atol(ticks) : -1;
    cpu1 = cpu2 = 0;
    if (play && sscanf(play, "%d-%d", &row, &col) == 2) {
        srand(playSeed ? (unsigned)atol(playSeed) : 1);
        g_tracePlaying = 1;
        // What the title's replay item and the replay menu set.
        game->unk1343[0] = 0;
        game->unk1343[1] = 0;
        game->unk1364 = 5;
        game->unk134e = 2;
        game->unk14281 = (char)(col - 1);
        game->unk14282 = (char)(row - 1);
        game->m_replayMode = 1;
        *scene = 2;
    } else if (record && (n = sscanf(record, "%d-%d:%d:%d:%d:%d:%d:%u:%d:%d", &row, &col, &c1,
                                     &c2, &stage, &pal1, &pal2, &seed, &cpu1, &cpu2)) >= 8) {
        CScene2* s2 = (CScene2*)scenes[2];
        if (n < 10)
            cpu1 = cpu2 = 0;
        srand(seed);
        g_traceBots[0].state = seed * 2 + 1;
        g_traceBots[1].state = seed * 2 + 2;
        g_traceBots[0].tick = g_traceBots[1].tick = -1;
        g_traceRecording = 1;
        // The replay menu's record item, then what character select leaves; a CPU side
        // as arcade mode marks it.
        game->unk1343[0] = (BYTE)(cpu1 != 0);
        game->unk1343[1] = (BYTE)(cpu2 != 0);
        game->unk1364 = 5;
        game->unk134e = 2;
        game->unk14281 = (char)(col - 1);
        game->unk14282 = (char)(row - 1);
        game->m_replayMode = 2;
        game->unkf32 = (char)stage;
        game->unk1358 = 1;
        game->unk135c = 0;
        game->unk1360 = 0;
        s2->Unk76da20(s2->m_player1Ref, s2->m_player2Ref, 0, (char)c1);
        s2->Unk76da20(s2->m_player2Ref, s2->m_player1Ref, 1, (char)c2);
        (*s2->m_player1Ref)->m_paletteIndex = (char)pal1;
        (*s2->m_player2Ref)->m_paletteIndex = (char)pal2;
        *scene = 2;
    }
}

int TraceFast()
{
    return g_traceFast;
}

int TraceQuit(BYTE scene)
{
    if (!g_traceFile)
        return 0;
    if (scene == 3)
        g_traceFought = 1;
    if ((g_traceFought && scene != 3) ||
        (g_traceTickLimit >= 0 && g_traceTicks >= g_traceTickLimit)) {
        fclose(g_traceFile);
        g_traceFile = NULL;
        if (g_traceDump)
            fclose(g_traceDump);
        g_traceDump = NULL;
        return 1;
    }
    return 0;
}

// --- The state's blocks: each is gathered into g_traceBlock, its pointers zeroed, then
// hashed and, while dumping, written out.

enum { TRACE_P1, TRACE_P1OBJ, TRACE_P1CHAR, TRACE_P2, TRACE_P2OBJ, TRACE_P2CHAR, TRACE_SCENE,
       TRACE_GAME, TRACE_FX, TRACE_BLOCKS };

static BYTE g_traceBlock[0x14400];
static unsigned g_traceLength;
static unsigned g_traceHashes[TRACE_BLOCKS];

static void TraceAdd(const void* p, unsigned size)
{
    memcpy(g_traceBlock + g_traceLength, p, size);
    g_traceLength += size;
}

// Zeroes `size` bytes at `field`, a member of the object `base` that starts the block.
static void TraceMask(const void* base, const void* field, unsigned size)
{
    memset(g_traceBlock + ((const char*)field - (const char*)base), 0, size);
}

static void TraceEnd(int block)
{
    unsigned h = 2166136261u;
    unsigned i;
    unsigned header[3];

    for (i = 0; i < g_traceLength; i++) {
        h ^= g_traceBlock[i];
        h *= 16777619u;
    }
    g_traceHashes[block] = h;
    if (g_traceDump && g_traceTicks >= g_traceDumpFrom &&
        (g_traceDumpTo < 0 || g_traceTicks <= g_traceDumpTo)) {
        header[0] = (unsigned)g_traceTicks;
        header[1] = (unsigned)block;
        header[2] = g_traceLength;
        fwrite(header, sizeof(header), 1, g_traceDump);
        fwrite(g_traceBlock, 1, g_traceLength, g_traceDump);
    }
    g_traceLength = 0;
}

// The size of the character class a player is, by its m_charId (CScene2::Unk76da20).
static unsigned TraceClassSize(CPlayer* p)
{
    switch (p->m_charId) {
    case 0: return sizeof(CNanase);
    case 1: return sizeof(CAyu);
    case 2: return sizeof(CMai);
    case 3: return sizeof(CMakoto);
    case 4: return sizeof(CAkane);
    case 5: return sizeof(CMayu);
    case 6: return sizeof(CNagamori);
    case 7: return sizeof(CMisaki);
    case 8: return sizeof(CShiori);
    case 9: return sizeof(CSayuri);
    case 0xa: return sizeof(CNayuki);
    case 0xb: return sizeof(CMio);
    case 0xc: return sizeof(CEXNanase);
    case 0xd: return sizeof(CKaori);
    case 0xe: return sizeof(CIkumi);
    case 0xf: return sizeof(CMishio);
    case 0x10: return sizeof(CAkiko);
    case 0x11: return sizeof(CNayukiB);
    case 0x12: return sizeof(CMizukaB);
    case 0x13: return sizeof(CKanna);
    case 0x14: return sizeof(CKano);
    case 0x15: return sizeof(CMinagi);
    case 0x16: return sizeof(CNayuki);
    case 0x17: return sizeof(CMisuzu);
    case 0x18: return sizeof(CMizuka);
    }
    return sizeof(CPlayer);
}

// Zeroes a member of the character class in the character block.
static void TraceMaskMember(CPlayer* p, const void* field, unsigned size)
{
    TraceMask((char*)p + sizeof(CPlayer), field, size);
}

// The character classes' pointers: Nanase's and Ikumi's second animation and pattern
// tables, and the first ones saved while the second are in use.
static void TraceMaskCharacter(CPlayer* p)
{
    CNanase* nanase = (CNanase*)p;
    CIkumi* ikumi = (CIkumi*)p;

    switch (p->m_charId) {
    case 0:
        TraceMaskMember(p, &nanase->unk345c, sizeof(nanase->unk345c));
        TraceMaskMember(p, &nanase->unk3460, sizeof(nanase->unk3460));
        TraceMaskMember(p, &nanase->unk3464, sizeof(nanase->unk3464));
        TraceMaskMember(p, &nanase->unk3468, sizeof(nanase->unk3468));
        break;
    case 0xe:
        TraceMaskMember(p, &ikumi->unk3464, sizeof(ikumi->unk3464));
        TraceMaskMember(p, &ikumi->unk3468, sizeof(ikumi->unk3468));
        TraceMaskMember(p, &ikumi->unk346c, sizeof(ikumi->unk346c));
        TraceMaskMember(p, &ikumi->unk3470, sizeof(ikumi->unk3470));
        break;
    }
}

static void TraceHashPlayer(CPlayer* p, int block)
{
    int i;

    TraceAdd(p, sizeof(CPlayer));
    TraceMask(p, p, 8); // the vtable pointer, and in the original's build 4 bytes padding
    TraceMask(p, &p->anims, sizeof(p->anims));
    TraceMask(p, &p->surfaces, sizeof(p->surfaces));
    TraceMask(p, &p->m_opponent, sizeof(p->m_opponent));
    TraceMask(p, &p->m_game, sizeof(p->m_game));
    TraceMask(p, &p->m_graphics, sizeof(p->m_graphics));
    TraceMask(p, &p->m_input, sizeof(p->m_input));
    TraceMask(p, &p->m_sound, sizeof(p->m_sound));
    TraceMask(p, &p->m_patterns, sizeof(p->m_patterns));
    TraceMask(p, p->m_objects, sizeof(p->m_objects)); // the next block
    TraceEnd(block);

    TraceAdd(p->m_objects, sizeof(p->m_objects));
    for (i = 0; i < 0x40; i++) {
        TraceMask(p->m_objects, &p->m_objects[i].anims, sizeof(p->m_objects[i].anims));
        TraceMask(p->m_objects, &p->m_objects[i].surfaces, sizeof(p->m_objects[i].surfaces));
    }
    TraceEnd(block + 1);

    TraceAdd((char*)p + sizeof(CPlayer), TraceClassSize(p) - sizeof(CPlayer));
    TraceMaskCharacter(p);
    TraceEnd(block + 2);
}

// The scene's members one by one: the native build's vtable pointer is 8 bytes, which
// moves them (port/layout.cpp). Left out: its pointers, WndProc's lastMessage, and the
// frames-per-second count (unk434, unk438, unk43c), which follows the clock.
static void TraceHashScene(CScene3* s)
{
    TraceAdd(&s->unk2c, sizeof(s->unk2c));
    TraceAdd(&s->unk2d, sizeof(s->unk2d));
    TraceAdd(s->m_palette, sizeof(s->m_palette));
    TraceAdd(&s->m_colorKey, sizeof(s->m_colorKey));
    TraceAdd(&s->unk440, sizeof(s->unk440));
    TraceAdd(&s->unk444, sizeof(s->unk444));
    TraceAdd(&s->unk448, sizeof(s->unk448));
    TraceAdd(&s->unk44c, sizeof(s->unk44c));
    TraceAdd(&s->unk450, sizeof(s->unk450));
    TraceAdd(&s->unk454, sizeof(s->unk454));
    TraceAdd(&s->unk458, sizeof(s->unk458));
    TraceAdd(&s->unk45c, sizeof(s->unk45c));
    TraceAdd(&s->unk460, sizeof(s->unk460));
    TraceAdd(s->unk464, sizeof(s->unk464));
    TraceAdd(&s->unk574, sizeof(s->unk574));
    TraceAdd(&s->unk576, sizeof(s->unk576));
    TraceAdd(&s->unk578, sizeof(s->unk578));
    TraceAdd(&s->unk580, sizeof(s->unk580));
    TraceAdd(&s->unk588, sizeof(s->unk588));
    TraceAdd(&s->unk58c, sizeof(s->unk58c));
    TraceAdd(&s->unk590, sizeof(s->unk590));
    TraceEnd(TRACE_SCENE);
}

static void TraceHashGame(CGame* g)
{
    const char* fx = (const char*)&g->m_effectHead;
    unsigned fxSize = (unsigned)((const char*)&g->m_effectAnims - fx);

    TraceAdd(g, sizeof(CGame));
    TraceMask(g, &g->m_graphics, sizeof(g->m_graphics));
    TraceMask(g, &g->m_input, sizeof(g->m_input));
    TraceMask(g, &g->m_sound, sizeof(g->m_sound));
    TraceMask(g, g->m_surfaces, sizeof(g->m_surfaces));
    TraceMask(g, &g->unke98, sizeof(g->unke98));
    TraceMask(g, &g->unke9c, sizeof(g->unke9c));
    TraceMask(g, &g->m_objectSurface, sizeof(g->m_objectSurface));
    TraceMask(g, &g->m_background, sizeof(g->m_background));
    TraceMask(g, &g->m_effectAnims, sizeof(g->m_effectAnims));
    TraceMask(g, &g->m_replay.m_handle, sizeof(g->m_replay.m_handle));
    TraceMask(g, fx, fxSize); // the next block
    TraceEnd(TRACE_GAME);

    TraceAdd(fx, fxSize);
    TraceEnd(TRACE_FX);
}

// A double's bits, most significant first.
static void TraceDouble(double d)
{
    DWORD* w = (DWORD*)&d;

    fprintf(g_traceFile, " %08x%08x", w[1], w[0]);
}

static void TracePlayer(CPlayer* p)
{
    fprintf(g_traceFile, " | %x %x", p->pattern, p->frame);
    TraceDouble(p->x);
    TraceDouble(p->y);
    TraceDouble(p->vx);
    TraceDouble(p->vy);
    fprintf(g_traceFile, " %d %d %d %d %d %d", p->m_hp, p->m_comboStartHp, p->m_comboDamage,
            p->m_comboHits, p->m_gauge, p->facing);
}

void TraceTick(CScene3* scene)
{
    int i;

    for (i = 0; i < 2; i++)
        g_tracePlayers[i] = scene->m_players[i];
    if (!g_traceFile)
        return;
    TraceHashPlayer(scene->m_players[0], TRACE_P1);
    TraceHashPlayer(scene->m_players[1], TRACE_P2);
    TraceHashScene(scene);
    TraceHashGame(scene->m_game);
    fprintf(g_traceFile, "%ld %lu", g_traceTicks, (unsigned long)scene->m_game->m_replay.m_read);
    TracePlayer(scene->m_players[0]);
    TracePlayer(scene->m_players[1]);
    fprintf(g_traceFile, " #");
    for (i = 0; i < TRACE_BLOCKS; i++)
        fprintf(g_traceFile, " %08x", g_traceHashes[i]);
    fprintf(g_traceFile, "\n");
    g_traceTicks++;
}

// The controls: the bots' while recording, untouched while playing (the replay supplies
// the players' input; this keeps what the menus' and CGame's polling see the same).
int TraceInput(BYTE player, BYTE* input)
{
    if (g_tracePlaying) {
        *input = 0;
        return 1;
    }
    if (!g_traceRecording || player > 1)
        return 0;
    *input = TraceBotInput(player);
    return 1;
}
#endif
