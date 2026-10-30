// The replay test's harness (docs/compat.md), in both the original's build (make trace)
// and the native one: it plays or records a replay without the menus and logs both
// players' status after every tick of the fight. Not part of efz.exe.
//
// Set by environment variables, read once at startup:
//   EFZ_TRACE         file to log to; nothing happens without it
//   EFZ_TRACE_PLAY    N-M: play replay\dataN-M.rep
//   EFZ_TRACE_RECORD  N-M:P1:P2:STAGE:PAL1:PAL2:SEED: record replay\dataN-M.rep, the
//                     characters, stage and palettes given (numbers as in the replay
//                     header), both players driven by scripted random input from SEED
//   EFZ_TRACE_TICKS   stop after this many ticks of the fight
//   EFZ_TRACE_FAST    nonzero: don't wait between frames
//   EFZ_TRACE_DUMP    file to write both players' memory to after every tick
//                     (TRACE_DUMP_SIZE bytes each), for finding the first byte two
//                     runs disagree on
// The game stops when the fight ends.
//
// Each line is one tick: the tick, the replay file's read position, then for each
// player its action and frame, position and velocity (the doubles' bits in hex), HP,
// HP when the combo began, the combo's damage and hits, gauge and facing.
#ifdef EFZ_TRACE
#include <stdio.h>
#include <stdlib.h>
#include "efz.h"

static FILE* g_traceFile;
static int g_traceFast;
static long g_traceTicks;
static long g_traceTickLimit;
static int g_traceFought;
static int g_traceRecording;
static CPlayer* g_tracePlayers[2];
static FILE* g_traceDump;
// The largest character class: every player is dumped at this size.
#define TRACE_DUMP_SIZE 0x34b0

// --- Scripted input while recording: per player, a direction held for a while,
// buttons tapped now and then, and from time to time a special move's motion.

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
    static const char* motions[] = {"236", "214", "623", "421", "41236", "63214", "2222", "6321469"};
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
    if (TraceRandom(b) % 40 == 0) {
        b->motion = motions[TraceRandom(b) % (sizeof(motions) / sizeof(motions[0]))];
        b->motionButton = 0x10 << (TraceRandom(b) % 4);
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
    int row, col, c1, c2, stage, pal1, pal2;
    unsigned seed;

    if (!out)
        return;
    g_traceFile = fopen(out, "w");
    if (dump)
        g_traceDump = fopen(dump, "wb");
    g_traceFast = fast && atoi(fast) != 0;
    g_traceTickLimit = ticks ? atol(ticks) : -1;
    if (play && sscanf(play, "%d-%d", &row, &col) == 2) {
        // What the title's replay item and the replay menu set.
        game->unk1343[0] = 0;
        game->unk1343[1] = 0;
        game->unk1364 = 5;
        game->unk134e = 2;
        game->unk14281 = (char)(col - 1);
        game->unk14282 = (char)(row - 1);
        game->m_replayMode = 1;
        *scene = 2;
    } else if (record && sscanf(record, "%d-%d:%d:%d:%d:%d:%d:%u", &row, &col, &c1, &c2,
                                &stage, &pal1, &pal2, &seed) == 8) {
        CScene2* s2 = (CScene2*)scenes[2];
        srand(seed);
        g_traceBots[0].state = seed * 2 + 1;
        g_traceBots[1].state = seed * 2 + 2;
        g_traceBots[0].tick = g_traceBots[1].tick = -1;
        g_traceRecording = 1;
        // The replay menu's record item, then what character select leaves.
        game->unk1343[0] = 0;
        game->unk1343[1] = 0;
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
    fprintf(g_traceFile, "%ld %lu", g_traceTicks, (unsigned long)scene->m_game->m_replay.m_read);
    TracePlayer(scene->m_players[0]);
    TracePlayer(scene->m_players[1]);
    fprintf(g_traceFile, "\n");
    if (g_traceDump) {
        for (i = 0; i < 2; i++)
            fwrite((CPlayer*)scene->m_players[i], 1, TRACE_DUMP_SIZE, g_traceDump);
    }
    g_traceTicks++;
}

int TraceInput(BYTE player, BYTE* input)
{
    if (!g_traceRecording || player > 1)
        return 0;
    *input = TraceBotInput(player);
    return 1;
}
#endif
