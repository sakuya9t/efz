/* efz_env: a batch of headless EFZ games for training agents, stepped in parallel.
 *
 * Each environment is a match: two players, a stage, best of rounds_to_win rounds. A
 * step runs frame_skip frames of the game (64 a second; each is three ticks of the
 * simulation, as in the game) with each player's controls held, then reports what each
 * player sees, its reward and whether the match ended. A side can be the game's own
 * CPU instead of the program. Ended matches start again at once by default (the step
 * returns the new match's first observation; the old one's last is in final_obs), or at
 * the next step, or when the program resets them (EfzEnvConfig.autoreset).
 *
 * The games are the recovered source's, unchanged: the same as the original's, tick
 * for tick (docs/headless.md has how that is tested). They run on num_threads threads,
 * each game in an arena of its own; a match starts from a copy of a game saved once
 * just after its intro, so resets cost a memcpy. All arrays are row-major, env first.
 * A batch is for one thread of the program at a time; batches can be used from
 * different threads at once. One data folder per process.
 *
 * Python: python/efz_env (ctypes, numpy). The C API is all there is to bind otherwise.
 */
#ifndef EFZ_ENV_H
#define EFZ_ENV_H

#include <stddef.h>
#include <stdint.h>

#if defined(_WIN32)
#if defined(EFZ_ENV_BUILD)
#define EFZ_ENV_API __declspec(dllexport)
#else
#define EFZ_ENV_API __declspec(dllimport)
#endif
#else
#define EFZ_ENV_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define EFZ_ENV_VERSION 10

/* What a step does when a match ends (EfzEnvConfig.autoreset). */
#define EFZ_AUTORESET_SAME_STEP 0 /* the next match starts in the same step: obs is its first
                                     view, final_obs the last of the match that ended */
#define EFZ_AUTORESET_NEXT_STEP 1 /* obs (and final_obs) is the last view; the next step
                                     starts the next match, ignoring its actions, with no
                                     reward (Gymnasium's default) */
#define EFZ_AUTORESET_DISABLED 2  /* the environment stays ended (its steps do nothing, its
                                     obs, info, terminated and truncated stay as at the end)
                                     until efz_env_reset starts it again */

/* Controls: one byte per player per step. With relative_actions the two horizontal
 * bits are forward (toward where the player faces) and back; otherwise screen right
 * and left. */
#define EFZ_RIGHT 0x01 /* or forward */
#define EFZ_LEFT 0x02  /* or back */
#define EFZ_DOWN 0x04
#define EFZ_UP 0x08
#define EFZ_A 0x10
#define EFZ_B 0x20
#define EFZ_C 0x40
#define EFZ_D 0x80

#define EFZ_CHARACTERS 25 /* character numbers 0-24, as the game's (efz_env_character_name) */
#define EFZ_STAGES 23     /* stages 0-22 */
#define EFZ_FRAME_WIDTH 320
#define EFZ_FRAME_HEIGHT 240

typedef struct EfzEnvConfig {
    int32_t num_envs;
    int32_t num_threads;        /* the threads stepping games: one pool for the process,
                                   shared by its batches, grown to the most any asks for
                                   (the calling thread counts as one); 0: one per
                                   hardware thread */
    int32_t frame_skip;         /* frames per step, the controls held; 1 */
    int32_t max_frames;         /* frames after which a match is cut short; 0 never */
    int32_t rounds_to_win;      /* 1-3; 2 */
    int32_t cpu_level;          /* 1-4: the game's CPU for sides it plays; 2 */
    int32_t damage_level;       /* 1 50%, 2 100%, 3 200% damage; 2 */
    int32_t skip_noninteractive;/* run on through frames where the controls do nothing (the
                                   round intros, KOs) within a step; 1 */
    int32_t relative_actions;   /* EFZ_RIGHT/EFZ_LEFT are forward/back; 1 */
    int32_t drawing;            /* draw the frames (sprites decoded, efz_env_render); 0. The
                                   game is the same either way, only slower drawn */
    int32_t cache_size;         /* matches (characters, stage...) kept ready to start; 64 */
    float reward_damage;        /* per 9999 HP (a full bar) dealt, and minus per taken; 1 */
    float reward_round;         /* per round won, minus per round lost; 0 */
    float reward_match;         /* for winning the match, minus for losing it; 1 */
    uint64_t seed;              /* draws characters and stages, and seeds each match's rand */
    int32_t autoreset;          /* EFZ_AUTORESET_*: what a step does when a match ends;
                                   EFZ_AUTORESET_SAME_STEP */
    int32_t first_intro;        /* a match starts at the fight scene's start, before its
                                   first round's intro, as the game shows it (to be watched,
                                   with skip_noninteractive 0); the intro's frames don't
                                   count in its frames (EfzInfo.frame, max_frames). 0: just
                                   after the intro (it is run through once, when the match
                                   is first made); 0 */
} EfzEnvConfig;

/* What an environment plays. Character and stage numbers -1 are drawn anew for each
 * match from the pool's set bits (0: every playable character, every stage). */
typedef struct EfzMatch {
    int8_t chars[2];     /* 0-24, or -1 */
    int8_t stage;        /* 0-22, or -1 */
    int8_t palettes[2];  /* -1: 0, and 1 for P2 in a mirror match */
    uint8_t cpu[2];      /* 1: the game's CPU plays this side, at cpu_level */
    uint8_t reserved;
    uint32_t char_pool[2];
    uint32_t stage_pool;
} EfzMatch;

/* Per environment, after each step and reset. */
typedef struct EfzInfo {
    int32_t frame;          /* frames into the match (with first_intro: since its intro) */
    int32_t episode;        /* matches this environment has started */
    int16_t hp[2];          /* 0-9999 */
    int16_t gauge[2];       /* 0-3000 */
    int8_t rounds_won[2];
    int8_t round;           /* the round being played, from 1 */
    int8_t winner;          /* of a match that ended this step: 0 or 1; -1 none (or cut short) */
    int8_t chars[2];        /* of the match the observation is from */
    int8_t stage;
    int8_t ended;           /* a match ended this step: its last observation is final_obs */
    uint8_t input[2];       /* each player's controls on the step's first frame, as the game
                               read them (forward/back with relative_actions): the step's
                               actions, the replay's in a replay played back
                               (efz_env_play), the CPU's directions and presses on its side */
    int8_t replay;          /* the match plays a replay back (efz_env_play) */
    int8_t reserved;
    float episode_return[2];/* of the match that ended, or so far */
} EfzInfo;

/* Where a step's results go. efz_env_buffers gives the environment's own; a program can
 * point obs and final_obs elsewhere (efz_env_set_obs_buffers), e.g. into page-locked
 * memory a GPU copies from. */
typedef struct EfzBuffers {
    float* obs;            /* [num_envs][2][obs_dim]: each player's view */
    float* final_obs;      /* [num_envs][2][obs_dim]: the last view of a match that ended */
    float* reward;         /* [num_envs][2] */
    uint8_t* terminated;   /* [num_envs]: the match was won */
    uint8_t* truncated;    /* [num_envs]: cut short at max_frames */
    EfzInfo* info;         /* [num_envs] */
} EfzBuffers;

typedef struct EfzEnv EfzEnv;

/* The defaults above. */
EFZ_ENV_API void efz_env_default_config(EfzEnvConfig* config);
/* Sets up the batch; data_dir is an EFZ 4.02 install (the folder with "system"). NULL
 * on failure, with the reason in error. Every environment plays random characters on
 * random stages, both sides the program's, until efz_env_set_matches says otherwise. */
EFZ_ENV_API EfzEnv* efz_env_create(const char* data_dir, const EfzEnvConfig* config,
                                    char* error, size_t error_size);
EFZ_ENV_API void efz_env_destroy(EfzEnv* env);

EFZ_ENV_API int32_t efz_env_version(void);
EFZ_ENV_API int32_t efz_env_num_envs(const EfzEnv* env);
EFZ_ENV_API int32_t efz_env_obs_dim(void);
/* The name of observation feature i, or NULL past the end. */
EFZ_ENV_API const char* efz_env_obs_name(int32_t i);
/* The character's folder name ("akane"), or NULL. */
EFZ_ENV_API const char* efz_env_character_name(int32_t character);

EFZ_ENV_API void efz_env_buffers(EfzEnv* env, EfzBuffers* out);
EFZ_ENV_API void efz_env_set_obs_buffers(EfzEnv* env, float* obs, float* final_obs);

/* What each environment plays from its next match on: matches[num_envs], or one for all
 * when count is 1. */
EFZ_ENV_API int efz_env_set_matches(EfzEnv* env, const EfzMatch* matches, int32_t count);

/* Starts a new match in the environments whose mask byte is set (mask NULL: all). Their
 * observations, info and zero rewards are in the buffers when it returns. */
EFZ_ENV_API int efz_env_reset(EfzEnv* env, const uint8_t* mask);
/* Seeds environment `index` as efz_env_create's seed seeds them all: what its following
 * matches draw (characters and stages from pools, each match's rand) follows from `seed`
 * alone, so the same seed, the same matches and the same actions play the same games in
 * any environment. Takes effect from its next match (efz_env_reset, or an autoreset). */
EFZ_ENV_API int efz_env_seed(EfzEnv* env, int32_t index, uint64_t seed);

/* Records environment `index`'s next match as a replay, as the replay menu's record item
 * does: the game writes replay\data<page>-<slot>.rep (page and slot 1-9) in the save
 * folder (the data folder unless efz_env_set_save_dir says otherwise), which EFZ's replay
 * menu plays back. The match is built from its start (the loading and the intro, as the
 * menus start it), not from the saved copy; when it is won the game plays on to the end
 * of the match and closes the file as it does after a match. A match cut short, or reset,
 * ends the file where it is. Both players must be the program's: a replay doesn't hold
 * the CPU's decisions. Returns -1 (efz_env_error says why) if they aren't. */
EFZ_ENV_API int efz_env_record(EfzEnv* env, int32_t index, int32_t page, int32_t slot);
/* Plays a replay back in environment `index`, as the replay menu's play item does, for
 * its next match (efz_env_reset, or an autoreset): `path` is a .rep file (UTF-8), the
 * game's own or EfzRevival's (its block after the game's part is left unread). The match
 * is built from the replay's characters, stage and palettes, from the loading on; each
 * step the replay's inputs play instead of the step's actions, and info.input says what
 * they were, with info.replay set. It ends when it is won (terminated, as the original
 * was) or when the replay runs out (truncated: a match cut short, or a showcase that
 * just stops). rounds_to_win and damage_level must be the replay's (EfzRevival's
 * netplay: 2 and 2). Afterwards the environment plays its matches as before. A save state
 * of a replay played back loads as a match of the program's from there. Returns -1
 * (efz_env_error says why) if the file can't be read or isn't a replay. */
EFZ_ENV_API int efz_env_play(EfzEnv* env, int32_t index, const char* path);
/* Sets player `player`'s (0 or 1) gauges in environment `index`'s match now, as
 * training mode's refill sets them: the power gauge (0-3000: a level per 1000), the RF
 * gauge (0-1000) and whether it is blue (full: 22C, Instant Charge, then gives back
 * five times the gauge in proration). A value below 0 leaves that gauge as it is. The
 * observation and info are written again. Returns -1 if the environment has no match. */
EFZ_ENV_API int efz_env_set_gauges(EfzEnv* env, int32_t index, int32_t player, int32_t power,
                                   double rf, int32_t blue);
/* Scales the damage player `player` (0 or 1) of environment `index` takes from hits
 * (CPlayer::DefenseFactor: guarded hits' chip damage is the game's), from its next step
 * on and in every match after until set again: an advantage for the other side, a red
 * team's (its hits worth what a person's combos are). 1 is the game's; 0 < scale <= 100.
 * Not while a replay is played back or recorded (they stay EFZ's). An addition to
 * version 5: a library without it is otherwise the same. Returns -1 for a bad argument. */
EFZ_ENV_API int efz_env_set_damage_scale(EfzEnv* env, int32_t index, int32_t player,
                                         float scale);
/* Makes `chance` (0-1) of player `player`'s guards in environment `index` recoil guards,
 * as the game's CPU makes its own (it opens the recoil-guard window at random): of the
 * guards it holds the right way against a hit that can be guarded, decided as the hit
 * lands, by a generator of its own (the game's rand() runs as it would). From its next
 * step on, in every match after, until set again; not while a replay is played back or
 * recorded; never for the game's CPU. 0 is the game's. An addition to version 5, as
 * efz_env_set_damage_scale. Returns -1 for a bad argument. */
EFZ_ENV_API int efz_env_set_recoil_guard(EfzEnv* env, int32_t index, int32_t player,
                                         float chance);
/* Who plays player `player` (0 or 1) of environment `index`'s match from its next step
 * on: the game's CPU (on: 1, at cpu_level) or the step's actions (0), until the match ends
 * (the next begins as efz_env_set_matches says) or it is set again. For an opponent that
 * is the CPU in part: its neutral and its guard the CPU's, its combos an agent's. The
 * observation is written again (it says who plays). On the copies an attached agent plans
 * on (efz_env_agent_attach) neither side is the CPU's: a plan plays both players' inputs
 * and would otherwise read the CPU's coming decisions off the copy. Not while a replay is
 * played back or recorded. An addition to version 5, as efz_env_set_damage_scale. Returns
 * -1 if the environment has no fight. */
EFZ_ENV_API int efz_env_set_cpu(EfzEnv* env, int32_t index, int32_t player, int32_t on);
/* Where the game writes files (replays): `dir`, or the data folder for NULL. For the
 * process, as the data folder is. */
EFZ_ENV_API int efz_env_set_save_dir(EfzEnv* env, const char* dir);
/* One step of every environment: actions[num_envs][2]. A side the CPU plays ignores its
 * byte. Returns when every environment has stepped. */
EFZ_ENV_API int efz_env_step(EfzEnv* env, const uint8_t* actions);
/* The same, returning at once: the step runs on the worker threads until
 * efz_env_step_wait. The buffers mustn't be read or changed in between. */
EFZ_ENV_API int efz_env_step_async(EfzEnv* env, const uint8_t* actions);
EFZ_ENV_API int efz_env_step_wait(EfzEnv* env);

/* Save states: the whole game of one environment, to go back to (search, curricula).
 * A state loads into any environment of any batch in the same process. Another process's
 * is refused (-1, efz_env_error says why) unless the library is loaded at the same address
 * there: the game's objects hold the addresses of its code. To keep a position across
 * processes, keep how to reach it (a replay and a step: efz_env_play). */
EFZ_ENV_API size_t efz_env_state_size(EfzEnv* env, int32_t index);
EFZ_ENV_API size_t efz_env_save_state(EfzEnv* env, int32_t index, void* out, size_t size);
EFZ_ENV_API int efz_env_load_state(EfzEnv* env, int32_t index, const void* state, size_t size);

/* The frame last drawn by an environment, as EFZ_FRAME_WIDTH x EFZ_FRAME_HEIGHT RGB
 * triples. Needs config.drawing; returns 0 otherwise. */
EFZ_ENV_API int efz_env_render(EfzEnv* env, int32_t index, uint8_t* rgb);

/* The sounds the games asked for, for a program that plays them (the library plays none).
 * efz_env_sound_log turns the log on (1) or off (0) for every batch of the process; it
 * is off by default and costs nothing then. efz_env_sound_events moves up to `max` of an
 * environment's events, oldest first, into `out` and returns how many; it keeps its last
 * 256 until they are taken. A play restarts its slot; the sound effects and voices play
 * at -500 (SetVolume after loading them), the music at 0 until a volume event for it. */
typedef struct EfzSoundEvent {
    int32_t kind;   /* 0 play, 1 stop, 2 volume */
    int32_t slot;   /* the sound slot */
    int32_t value;  /* play: 1 when it loops; volume: hundredths of a decibel (-10000 silent) */
    char file[48];  /* the .wav relative to the data folder ("wave\se\05.wav",
                       "ayu\wave\12.wav", "wave\bgm\bgm23.wav"); "" if not known */
} EfzSoundEvent;
EFZ_ENV_API void efz_env_sound_log(int32_t on);
EFZ_ENV_API int32_t efz_env_sound_events(EfzEnv* env, int32_t index, EfzSoundEvent* out,
                                         int32_t max);

/* Ticks of the simulation run by this batch so far (three per frame). */
EFZ_ENV_API uint64_t efz_env_ticks(const EfzEnv* env);
/* The last error, as text. */
EFZ_ENV_API const char* efz_env_error(const EfzEnv* env);

/* Trained agents as the game plays them (port/agent/policy.h, docs/agents.md): an agent
 * file that python/examples/export_agent.py writes from a model.zip, its network run
 * here, with no Python machine learning. For checking an exported agent against its
 * model, and for playing one as the game would. */
typedef struct EfzAgent EfzAgent;
typedef struct EfzAgentInfo {
    int32_t width;      /* the numbers its network takes: a view, then its input history */
    int32_t actions;
    int32_t frame_skip; /* frames each decision is held for */
    int32_t history;    /* steps of its own inputs it sees */
    int32_t delay;      /* decisions late it sees the game */
    int32_t character;  /* the character it plays (0-24), -1 any */
    int32_t routes;     /* its combo library's routes (0: it plays its own combos) */
    int32_t pool;       /* the planner's entries: the routes, and with replan those joined
                           where a later move of theirs hit */
    int32_t replan;     /* 1: planned again at each new move's hit of a combo */
    int32_t chooser;    /* 1: it has a chooser (played when a combo's first plan is late) */
    int32_t format;     /* the file's */
    char name[64];
    char version[64];   /* as exported (export_agent.py --version), "" none */
    char modules[64];   /* what it is made of, as "policy:1,routes:1,chooser:1" (cut to
                           fit: efz_env_agent_modules has all of it) */
} EfzAgentInfo;
/* NULL on failure, with the reason in error. */
EFZ_ENV_API EfzAgent* efz_env_agent_load(const char* path, char* error, size_t error_size);
EFZ_ENV_API void efz_env_agent_free(EfzAgent* agent);
EFZ_ENV_API void efz_env_agent_info(const EfzAgent* agent, EfzAgentInfo* info);
/* What it is made of, whole (EfzAgentInfo's modules holds 63 characters): into out[size],
 * cut to fit; returns its length. */
EFZ_ENV_API int32_t efz_env_agent_modules(const EfzAgent* agent, char* out, size_t size);
/* The log-probability of each action for n views of `width` numbers: out[n][actions]. */
EFZ_ENV_API void efz_env_agent_log_probs(const EfzAgent* agent, const float* views, int32_t n,
                                     float* out);
/* The agent playing a side as the game plays it: efz_env_agent_reset at a match's start (its
 * draws seeded), then each frame the player's view (efz_env_obs_dim numbers, as a step
 * gives them) and whether the controls do anything (no intro, no KO); the frame's control
 * byte, forward and back relative to where the player faces. deterministic: the likeliest
 * action instead of a draw. */
EFZ_ENV_API void efz_env_agent_reset(EfzAgent* agent, uint64_t seed);
EFZ_ENV_API uint8_t efz_env_agent_step(EfzAgent* agent, const float* view, int32_t actionable,
                                   int32_t deterministic);
/* The action of its last decision; -1 before the first. */
EFZ_ENV_API int32_t efz_env_agent_last_action(const EfzAgent* agent);

/* An agent with routes (export_agent.py --library): one plan as the game makes it at the
 * agent's hit (port/agent/routes.h), on environment `index`'s game as it is (left as it
 * was): the agent (player `side`) plays `actions` (count, its inputs until it sees the
 * hit), the opponent holding back, then the agent's routes that begin with `starter` and
 * its own play (history: its input history after those actions, history x 6, newest
 * first; prev: its last control byte) are played on copies, the opponent guarding once
 * it can. late: the frames since the hit (the routes played that much further in);
 * extra (extra_count): one more option, actions from where `actions` leave the game (at a
 * replan, the rest of the route being played). For checking the game's planner against
 * runs/human-ayu/redteam.py's. 0, or -1 (efz_env_error: no routes, not in a fight). */
typedef struct EfzPlan {
    int32_t outcome;       /* 1 planned, 2 not (the opponent isn't a victim), 3 the copies
                              couldn't be played; with efz_env_agent_plan_budget: 4 chosen
                              from the options played inside the cost (the first played is
                              the extra if there is one, else its own play), 0 dropped */
    int32_t chosen;        /* the option chosen (an index into route[]), -1 its own play */
    int32_t options;       /* the options tried: route[], at[], dealt[] */
    int32_t frames;        /* frames played on copies */
    int32_t route[64];     /* a route (its index in the agent's), -2 the extra, -1 its own play */
    int32_t at[64];        /* the route's step it was joined at (0: from its start) */
    float dealt[64];       /* the most each dealt (HP) */
    float expected[168];   /* the agent's view once it sees its hit, after `actions` */
    double ms;
} EfzPlan;
EFZ_ENV_API int32_t efz_env_agent_plan(EfzAgent* agent, EfzEnv* env, int32_t index,
                                       int32_t side, int32_t starter, const int32_t* actions,
                                       int32_t count, const float* history, uint8_t prev,
                                       int32_t deterministic, uint64_t seed, int32_t late,
                                       const int32_t* extra, int32_t extra_count, EfzPlan* out);
/* An agent with a chooser: what it says from `input` (the agent's network's: a view, then
 * its input history; on the frame it sees its hit of `starter`), its routes played from
 * step `offset`: the route it picks (its index in the agent's), -1 its own play, -2 no
 * chooser; values (routes + 1, or NULL): what it says each route and its own play (the
 * last) would deal, in HP. */
EFZ_ENV_API int32_t efz_env_agent_choose(const EfzAgent* agent, const float* input,
                                         int32_t starter, int32_t offset, float* values);

/* An agent with a planned okizeme (the module okiplan:1, port/agent/mix.h): the entries of
 * its library (0: it has none). */
EFZ_ENV_API int32_t efz_env_agent_oki_entries(const EfzAgent* agent);
/* A plan at the opponent's knockdown in environment `index`, as the game makes one, for a
 * test that it is runs/human-ayu/okiplan.py's. actions (count): the agent's inputs for the
 * frames until the plan is played (none: from the game as it is); history, prev: its input
 * history after them; shares: of the five answers; seen: its views then, (delay + 1)
 * newest first, or NULL (those of the frames `actions` are played on). The environment is
 * left as it was. 0, or -1 with efz_env_error. */
typedef struct EfzOkiPlan {
    int32_t outcome;       /* 1 planned, 2 nothing to plan (not down, or up too soon), 3 the
                              copies couldn't be played */
    int32_t lead;          /* frames to the rising */
    int32_t options;       /* the options tried: the entries, a wait, its own play */
    int32_t chosen;        /* the one drawn */
    int32_t frames;        /* frames played on copies */
    int32_t option_size;   /* the drawn option's actions (0: its own play) */
    int32_t entry[32];     /* the library's entries tried (options - 2) */
    int32_t kind[32];      /* each option's kind: the library's, -1 the wait, -2 its own play */
    int32_t first[32 * 5]; /* [option][answer]: who hit first (1 the agent, -1 the opponent) */
    int32_t option[512];
    double worth[32 * 5];  /* [option][answer] */
    double expected[32];
    double mix[32];
    double ms;
    int32_t adv;           /* the pressure's: the frame advantage planned at */
    int32_t waited;        /* the pressure's: frames of guard before the follow-up */
    float view[168];       /* the agent's view after `actions`, on the copy */
} EfzOkiPlan;
EFZ_ENV_API int32_t efz_env_agent_oki_plan(EfzAgent* agent, EfzEnv* env, int32_t index,
                                           int32_t side, const int32_t* actions, int32_t count,
                                           const float* history, uint8_t prev,
                                           int32_t deterministic, uint64_t seed,
                                           const double* shares, const float* seen,
                                           EfzOkiPlan* out);
/* An agent with a planned pressure (the module pressplan:1, mix.h's Press): its library's
 * entries (0: none); a plan on the frame a move of the agent's touches the opponent's
 * guard in environment `index` (MixPlanner::BeginPress: actions, its inputs for the
 * frames until it sees the guard; history, prev: its input history before them; hold: the
 * control byte the opponent holds until the plan's start), the drawn option the frames of
 * guard until the agent is free and then the follow-up; and the answers' shares from the
 * agent's counts (efz_env_agent_counts) for `prior`. */
EFZ_ENV_API int32_t efz_env_agent_press_entries(const EfzAgent* agent);
EFZ_ENV_API int32_t efz_env_agent_press_plan(EfzAgent* agent, EfzEnv* env, int32_t index,
                                             int32_t side, const int32_t* actions,
                                             int32_t count, const float* history, uint8_t prev,
                                             int32_t deterministic, uint64_t seed,
                                             const double* shares, uint8_t hold,
                                             EfzOkiPlan* out);
EFZ_ENV_API void efz_env_agent_press_shares(const EfzAgent* agent, double prior, double* shares);
/* An agent with the catch (the module airthrow:1, mix.h's Catch): a plan on the frame the
 * opponent's air recovery begins in environment `index` (MixPlanner::BeginThrow: actions,
 * its inputs for the frames until it sees the recovery; near: the most pixels apart). In
 * `out`: outcome (1: a throw that catches inside the recovery, 2: none), lead (the frames
 * of the recovery left after `actions`), option (the throw's actions), adv (the frame of
 * them it catches on, -1), waited (the throws looked at), view, frames, ms. The
 * environment is left as it was. 0, or -1 with efz_env_error. */
EFZ_ENV_API int32_t efz_env_agent_throw_plan(EfzAgent* agent, EfzEnv* env, int32_t index,
                                             int32_t side, const int32_t* actions,
                                             int32_t count, const float* history, uint8_t prev,
                                             int32_t near, EfzOkiPlan* out);
/* An attached agent's catches (16): asked, with a throw found, played, late, elsewhere,
 * none found, apart, frames on copies, milliseconds. */
EFZ_ENV_API void efz_env_agent_air_stats(const EfzAgent* agent, int32_t* stats);
/* An attached agent's raw specials (12; the module risk:1): presses that would start a
 * move with an account, those stopped, let out, and of the ones let out the moves seen;
 * the same four of its jumps at the opponent (risk_jump), and the jump's account: the
 * jumps counted, in hundredths, their worth in HP, and the probability the next is
 * stopped, in thousandths. */
EFZ_ENV_API void efz_env_agent_risk_stats(const EfzAgent* agent, int32_t* stats);
/* The move with an account (its action; -1 none) that `action` of the agent's would start
 * for player `side` of environment `index` as it is (the press, then nothing, the other
 * player pressing nothing), and the probability the agent would stop that press now. The
 * environment is left as it was. */
EFZ_ENV_API int32_t efz_env_agent_risk_starts(EfzAgent* agent, EfzEnv* env, int32_t index,
                                              int32_t side, int32_t action, double* chance);
/* A new match against the same opponent, for an agent attached or not: what it keeps
 * from match to match kept (its counts of the opponent, its risings' counts, older),
 * where efz_env_agent_reset on a detached agent starts it afresh. */
EFZ_ENV_API void efz_env_agent_next_match(EfzAgent* agent);
/* An agent's risings (16; the module rise:1): the knockdowns it saw, those the attacker
 * was on, of them the ones guarded through, the steps it held a guard for, of them
 * standing, the probability the next such rising is guarded through, in thousandths; and
 * what that is read from, in hundredths: the risings it saw, and of them those at which
 * the attacker was in a move of its own; then the steps it crouched under an attacker
 * it still saw in the air, whose landing as predicted had passed (rise_land); its moves
 * it saw recoil-guarded, the steps it answered them with a guard (rise_recoil), and the
 * presses that took a kept chain's place (rise_recoil_clear); of the recoil guards
 * seen those it answered, and the probability the next is, in thousandths; its own
 * recoil guards followed by its punish (rise_recoil_punish); the steps guarded on
 * after it saw itself up (rise_hold). */
EFZ_ENV_API void efz_env_agent_rise_stats(const EfzAgent* agent, int32_t* stats);
/* Its guard under pressure (rise_press), 7 numbers: the strings it saw (a guard of its
 * own touched), those held (guarded on), the steps guarded on, the exits it saw out of
 * strings not held, of them the ones caught, the probability the next string is held,
 * in thousandths, and the exits that won (the opponent hit first). */
EFZ_ENV_API void efz_env_agent_press_stats(const EfzAgent* agent, int32_t* stats);
/* The agent plays player `side` of environment `index` as it plays in the game: its
 * combos' routes and its okizeme planned on copies of that environment (what the file
 * has of them), every plan worked to its end on the step that needs it (the game's
 * fast-forward). From then on efz_env_agent_step is given that player's view of the
 * environment as it is, before the step its control byte is for; efz_env_agent_reset
 * starts a match. The environment must outlive the agent, or the agent be detached
 * (env NULL). stats (24, or NULL, read at any time through efz_env_agent_stats): the
 * routes' plans made and those that chose a route, then the okizeme's: plans asked, made,
 * played (an option not its own play), late, elsewhere, nothing, apart, frames on copies;
 * the milliseconds the routes' plans took in all and the okizeme's; the routes' plans
 * dropped; then the pressure's: asked, made, played, late, elsewhere, nothing, apart,
 * frames, milliseconds.
 * 0, or -1 with efz_env_error. */
EFZ_ENV_API int32_t efz_env_agent_attach(EfzAgent* agent, EfzEnv* env, int32_t index,
                                         int32_t side, uint64_t seed);
EFZ_ENV_API void efz_env_agent_stats(const EfzAgent* agent, int32_t* stats);
/* An attached agent's routes' plans as a machine with less time makes them: `cost`, the
 * work a plan may take before the agent sees its hit, in frames on copies (one of its own
 * play's counts `own`: the network's decision, 15 as measured, 27 before 19 November's
 * faster network; own <= 0: 15. cost 0: no limit, every plan worked to its end as
 * efz_env_agent_attach says); a plan not done by then is chosen from the options played
 * so far (settle 1: the game's way) or dropped whole (0: the game's way before 19
 * November). The user's machine in the sessions of 16-19 November: about 7,700 (26% of
 * the plans late at own 27). efz_env_agent_stats's last two (of 24) count them: the
 * plans dropped as late, and those settled. For an agent with routes, attached or not
 * (efz_env_agent_plan's one plan takes it too). -1 without routes. */
EFZ_ENV_API int32_t efz_env_agent_plan_budget(EfzAgent* agent, int32_t cost, int32_t settle,
                                              int32_t own);
/* The agent's counts of its opponent (port/agent/mix.h's Counts, efz_env.memory's): mode 0
 * takes a view (the agent's), 1 forgets everything (another opponent), 2 ends a match
 * against the same one (view NULL for 1 and 2). counts (12, or NULL): wake-ups, of them a
 * move, an invincible one, a jump, a backdash; guards ended, the same four after them; its
 * guards on the ground, of them crouching. shares (5, or NULL): the answers' shares for
 * `prior`. */
EFZ_ENV_API void efz_env_agent_counts(EfzAgent* agent, const float* view, int32_t mode,
                                      double prior, float* counts, double* shares);

#ifdef __cplusplus
}
#endif

#endif
