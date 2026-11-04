/* efz_env: a batch of headless EFZ games for training agents, stepped in parallel.
 *
 * Each environment is a match: two players, a stage, best of rounds_to_win rounds. A
 * step runs frame_skip frames of the game (64 a second; each is three ticks of the
 * simulation, as in the game) with each player's controls held, then reports what each
 * player sees, its reward and whether the match ended. A side can be the game's own
 * CPU instead of the program. Ended matches start again at once (the step returns the
 * new match's first observation; the old one's last is in final_obs).
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

#define EFZ_ENV_VERSION 1

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
    int32_t frame;          /* frames into the match */
    int32_t episode;        /* matches this environment has started */
    int16_t hp[2];          /* 0-9999 */
    int16_t gauge[2];       /* 0-3000 */
    int8_t rounds_won[2];
    int8_t round;           /* the round being played, from 1 */
    int8_t winner;          /* of a match that ended this step: 0 or 1; -1 none (or cut short) */
    int8_t chars[2];        /* of the match the observation is from */
    int8_t stage;
    int8_t ended;           /* a match ended this step: its last observation is final_obs */
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
/* One step of every environment: actions[num_envs][2]. A side the CPU plays ignores its
 * byte. Returns when every environment has stepped. */
EFZ_ENV_API int efz_env_step(EfzEnv* env, const uint8_t* actions);
/* The same, returning at once: the step runs on the worker threads until
 * efz_env_step_wait. The buffers mustn't be read or changed in between. */
EFZ_ENV_API int efz_env_step_async(EfzEnv* env, const uint8_t* actions);
EFZ_ENV_API int efz_env_step_wait(EfzEnv* env);

/* Save states: the whole game of one environment, to go back to (search, curricula).
 * A state loads into any environment of any batch in the same process. */
EFZ_ENV_API size_t efz_env_state_size(EfzEnv* env, int32_t index);
EFZ_ENV_API size_t efz_env_save_state(EfzEnv* env, int32_t index, void* out, size_t size);
EFZ_ENV_API int efz_env_load_state(EfzEnv* env, int32_t index, const void* state, size_t size);

/* The frame last drawn by an environment, as EFZ_FRAME_WIDTH x EFZ_FRAME_HEIGHT RGB
 * triples. Needs config.drawing; returns 0 otherwise. */
EFZ_ENV_API int efz_env_render(EfzEnv* env, int32_t index, uint8_t* rgb);

/* Ticks of the simulation run by this batch so far (three per frame). */
EFZ_ENV_API uint64_t efz_env_ticks(const EfzEnv* env);
/* The last error, as text. */
EFZ_ENV_API const char* efz_env_error(const EfzEnv* env);

#ifdef __cplusplus
}
#endif

#endif
