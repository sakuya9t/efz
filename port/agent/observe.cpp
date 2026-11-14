// An agent's view of a fight (observe.h): moved here from port/headless/env.cpp, the same
// numbers computed the same way.
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>

#include "efz.h"
#include "agent/observe.h"

namespace efz {
namespace agent {

namespace {

const char* const kGlobalNames[kGlobalFeatures] = {
    "frame",       // frames into the match / max_frames (or / 10000)
    "round",       // the round being played, from 1
    "intro",       // a round's intro is running: the controls do nothing
    "round_over",  // a KO happened and the next round hasn't started
    "dx",          // the opponent's x minus the viewer's, / 640
    "dy",          // the opponent's y minus the viewer's, / 240
    "side",        // the viewer is player 1 (0) or 2 (1)
    "rounds_to_win",
};

const char* const kPlayerNames[kPlayerFeatures] = {
    "hp",            // / 9999
    "gauge",         // / 3000: a level per 1000
    "rf_gauge",      // / 1000
    "rf_blue",       // the RF gauge filled and turned blue
    "guard_gauge",   // / 360
    "x",             // (x - 320) / 320: the stage is 0-640
    "y",             // / 240: 0 on the ground, negative in the air
    "vx",            // / 20
    "vy",            // / 20
    "facing",        // 1 right, -1 left
    "action",        // the action (pattern) number: categorical, 0-~600
    "action_frame",  // the frame of the action's animation
    "hitstun",       // in a hit reaction
    "guarding",
    "dashing",
    "hitstop",       // / 30
    "freeze",        // a super's flash stops the opponent
    "invulnerable",
    "no_guard",
    "armor",
    "throw_protected",
    "untech",        // ticks before an air recovery, / 100
    "combo_hits",    // / 30
    "proration",     // / 10000
    "rounds_won",
    "air_actions",   // double jumps and air dashes used
    "character",     // 0-24: categorical
    "own_action",    // the action is the character's own (a move), not common
    "cpu",           // the game's CPU plays this side
    "sealed",        // Akiko's seal level
    "combo_damage",  // / 9999, while a combo goes on
    "airborne",
};

const char* const kObjectNames[kObjectFeatures] = {
    "active", "x", "y", "vx", "vy", "can_hit",
};

const char* const kCharacterNames[kCharacters] = {
    "nanase", "ayu", "mai", "makoto", "akane", "mayu", "nagamori", "misaki", "shiori",
    "sayuri", "nayuki", "mio", "exnanase", "kaori", "ikumi", "mishio", "akiko", "nayukib",
    "mizukab", "kanna", "kano", "minagi", "nayuki2", "misuzu", "mizuka",
};

// The names, made once (a function's static: thread-safe, and no <mutex>, which some
// toolchains' threads lack).
struct Names {
    char at[kObsDim][40];
    Names();
};

Names::Names()
{
    char (*g_names)[40] = at;
    int n = 0;
    for (int i = 0; i < kGlobalFeatures; i++)
        snprintf(g_names[n++], sizeof(g_names[0]), "%s", kGlobalNames[i]);
    for (int p = 0; p < 2; p++) {
        for (int i = 0; i < kPlayerFeatures; i++)
            snprintf(g_names[n++], sizeof(g_names[0]), "%s_%s", p ? "opp" : "self",
                     kPlayerNames[i]);
    }
    for (int p = 0; p < 2; p++) {
        for (int k = 0; k < kObjects; k++) {
            for (int i = 0; i < kObjectFeatures; i++)
                snprintf(g_names[n++], sizeof(g_names[0]), "%s_obj%d_%s", p ? "opp" : "self", k,
                         kObjectNames[i]);
        }
    }
}

float Clamp(double v, double lo, double hi)
{
    return (float)(v < lo ? lo : v > hi ? hi : v);
}

void WritePlayer(float* o, CPlayer* p)
{
    o[0] = p->m_hp / 9999.0f;
    o[1] = p->m_gauge / 3000.0f;
    o[2] = (float)(p->m_rfGauge / 1000.0);
    o[3] = p->m_rfBlue != 0;
    o[4] = (float)p->m_guardGauge / 360.0f;
    o[5] = (float)((p->x - 320.0) / 320.0);
    o[6] = (float)(p->y / 240.0);
    o[7] = Clamp(p->vx / 20.0, -10, 10);
    o[8] = Clamp(p->vy / 20.0, -10, 10);
    o[9] = p->facing;
    o[10] = p->pattern;
    o[11] = p->frame;
    o[12] = p->IsInHitstun() != 0;
    o[13] = p->IsGuarding() != 0;
    o[14] = p->IsDashing() != 0;
    o[15] = p->m_hitstop / 30.0f;
    o[16] = p->m_freezeTime > 0;
    o[17] = p->m_invulTime > 0;
    o[18] = p->m_noGuardTime > 0;
    o[19] = p->m_armorTime > 0;
    o[20] = p->m_throwProtect > 0;
    o[21] = p->m_untechTime / 100.0f;
    o[22] = p->m_comboHits / 30.0f;
    o[23] = (float)(p->m_proration / 10000.0);
    o[24] = p->m_roundsWon;
    o[25] = p->m_airActions;
    o[26] = p->m_charId;
    o[27] = p->pattern >= kFirstCharacterAction;
    o[28] = p->m_cpu != 0;
    o[29] = (float)p->m_sealLevel;
    o[30] = p->m_comboHits > 0 ? p->m_comboDamage / 9999.0f : 0.0f;
    o[31] = p->y < 0.0;
}

// The `owner`'s active objects nearest the viewer, nearest first.
void WriteObjects(float* o, CPlayer* owner, CPlayer* viewer)
{
    int slots[0x40];
    double dist[0x40];
    int n = 0;
    for (int k = 0; k < 0x40; k++) {
        if (!owner->m_objectActive[k])
            continue;
        const PlayerObject& obj = owner->m_objects[k];
        slots[n] = k;
        dist[n] = fabs(obj.x - viewer->x) + fabs(obj.y - viewer->y);
        n++;
    }
    for (int k = 0; k < kObjects; k++, o += kObjectFeatures) {
        if (k >= n) {
            memset(o, 0, kObjectFeatures * sizeof(float));
            continue;
        }
        int best = k;
        for (int j = k + 1; j < n; j++) {
            if (dist[j] < dist[best])
                best = j;
        }
        std::swap(slots[k], slots[best]);
        std::swap(dist[k], dist[best]);
        const PlayerObject& obj = owner->m_objects[slots[k]];
        o[0] = 1.0f;
        o[1] = (float)((obj.x - viewer->x) / 320.0);
        o[2] = (float)(obj.y / 240.0);
        o[3] = Clamp(obj.vx / 20.0, -10, 10);
        o[4] = Clamp(obj.vy / 20.0, -10, 10);
        o[5] = obj.hitsLeft > 0;
    }
}

} // namespace

void WriteView(float* o, CScene3* fight, CGame* game, int v, int frame, int maxFrames)
{
    CPlayer* self = fight->m_players[v];
    CPlayer* opp = fight->m_players[1 - v];
    int max = maxFrames > 0 ? maxFrames : 10000;
    o[0] = (float)frame / max;
    o[1] = game->m_round;
    o[2] = game->m_intro != 0;
    o[3] = game->m_roundOver != 0;
    o[4] = (float)((opp->x - self->x) / 640.0);
    o[5] = (float)((opp->y - self->y) / 240.0);
    o[6] = (float)v;
    o[7] = game->m_roundsToWin;
    o += kGlobalFeatures;
    WritePlayer(o, self);
    WritePlayer(o + kPlayerFeatures, opp);
    o += 2 * kPlayerFeatures;
    WriteObjects(o, self, self);
    WriteObjects(o + kObjects * kObjectFeatures, opp, self);
}

const char* ObservationName(int i)
{
    static const Names names;
    return i >= 0 && i < kObsDim ? names.at[i] : nullptr;
}

const char* CharacterName(int c)
{
    return c >= 0 && c < kCharacters ? kCharacterNames[c] : nullptr;
}

} // namespace agent
} // namespace efz
