"""ctypes binding of the efz_env library (port/headless/efz_env.h).

The library is found, in order, at $EFZ_ENV_LIBRARY, next to this package, or in the
repository's build folders (build/*/, build/*/Release|RelWithDebInfo/), so that a
checkout built with CMake works without installing anything.
"""

import ctypes
import glob
import os
import sys

VERSION = 10

# EfzEnvConfig.autoreset
AUTORESET_SAME_STEP = 0
AUTORESET_NEXT_STEP = 1
AUTORESET_DISABLED = 2

if sys.platform == 'win32':
    _NAMES = ['efz_env.dll', 'libefz_env.dll']
elif sys.platform == 'darwin':
    _NAMES = ['libefz_env.dylib']
else:
    _NAMES = ['libefz_env.so']


class Config(ctypes.Structure):
    _fields_ = [
        ('num_envs', ctypes.c_int32),
        ('num_threads', ctypes.c_int32),
        ('frame_skip', ctypes.c_int32),
        ('max_frames', ctypes.c_int32),
        ('rounds_to_win', ctypes.c_int32),
        ('cpu_level', ctypes.c_int32),
        ('damage_level', ctypes.c_int32),
        ('skip_noninteractive', ctypes.c_int32),
        ('relative_actions', ctypes.c_int32),
        ('drawing', ctypes.c_int32),
        ('cache_size', ctypes.c_int32),
        ('reward_damage', ctypes.c_float),
        ('reward_round', ctypes.c_float),
        ('reward_match', ctypes.c_float),
        ('seed', ctypes.c_uint64),
        ('autoreset', ctypes.c_int32),
        ('first_intro', ctypes.c_int32),
    ]


class Match(ctypes.Structure):
    _fields_ = [
        ('chars', ctypes.c_int8 * 2),
        ('stage', ctypes.c_int8),
        ('palettes', ctypes.c_int8 * 2),
        ('cpu', ctypes.c_uint8 * 2),
        ('reserved', ctypes.c_uint8),
        ('char_pool', ctypes.c_uint32 * 2),
        ('stage_pool', ctypes.c_uint32),
    ]


class Info(ctypes.Structure):
    _fields_ = [
        ('frame', ctypes.c_int32),
        ('episode', ctypes.c_int32),
        ('hp', ctypes.c_int16 * 2),
        ('gauge', ctypes.c_int16 * 2),
        ('rounds_won', ctypes.c_int8 * 2),
        ('round', ctypes.c_int8),
        ('winner', ctypes.c_int8),
        ('chars', ctypes.c_int8 * 2),
        ('stage', ctypes.c_int8),
        ('ended', ctypes.c_int8),
        ('input', ctypes.c_uint8 * 2),
        ('replay', ctypes.c_int8),
        ('reserved', ctypes.c_int8),
        ('episode_return', ctypes.c_float * 2),
    ]


class Buffers(ctypes.Structure):
    _fields_ = [
        ('obs', ctypes.POINTER(ctypes.c_float)),
        ('final_obs', ctypes.POINTER(ctypes.c_float)),
        ('reward', ctypes.POINTER(ctypes.c_float)),
        ('terminated', ctypes.POINTER(ctypes.c_uint8)),
        ('truncated', ctypes.POINTER(ctypes.c_uint8)),
        ('info', ctypes.POINTER(Info)),
    ]


class SoundEvent(ctypes.Structure):
    _fields_ = [
        ('kind', ctypes.c_int32),
        ('slot', ctypes.c_int32),
        ('value', ctypes.c_int32),
        ('file', ctypes.c_char * 48),
    ]


class AgentInfo(ctypes.Structure):
    _fields_ = [
        ('width', ctypes.c_int32),
        ('actions', ctypes.c_int32),
        ('frame_skip', ctypes.c_int32),
        ('history', ctypes.c_int32),
        ('delay', ctypes.c_int32),
        ('character', ctypes.c_int32),
        ('routes', ctypes.c_int32),
        ('pool', ctypes.c_int32),
        ('replan', ctypes.c_int32),
        ('chooser', ctypes.c_int32),
        ('format', ctypes.c_int32),
        ('name', ctypes.c_char * 64),
        ('version', ctypes.c_char * 64),
        ('modules', ctypes.c_char * 64),
    ]


class Plan(ctypes.Structure):
    _fields_ = [
        ('outcome', ctypes.c_int32),
        ('chosen', ctypes.c_int32),
        ('options', ctypes.c_int32),
        ('frames', ctypes.c_int32),
        ('route', ctypes.c_int32 * 64),
        ('at', ctypes.c_int32 * 64),
        ('dealt', ctypes.c_float * 64),
        ('expected', ctypes.c_float * 168),
        ('ms', ctypes.c_double),
    ]


class OkiPlan(ctypes.Structure):
    _fields_ = [
        ('outcome', ctypes.c_int32),
        ('lead', ctypes.c_int32),
        ('options', ctypes.c_int32),
        ('chosen', ctypes.c_int32),
        ('frames', ctypes.c_int32),
        ('option_size', ctypes.c_int32),
        ('entry', ctypes.c_int32 * 32),
        ('kind', ctypes.c_int32 * 32),
        ('first', ctypes.c_int32 * (32 * 5)),
        ('option', ctypes.c_int32 * 512),
        ('worth', ctypes.c_double * (32 * 5)),
        ('expected', ctypes.c_double * 32),
        ('mix', ctypes.c_double * 32),
        ('ms', ctypes.c_double),
        ('adv', ctypes.c_int32),
        ('waited', ctypes.c_int32),
        ('view', ctypes.c_float * 168),
    ]


def _candidates():
    env = os.environ.get('EFZ_ENV_LIBRARY')
    if env:
        yield env
    here = os.path.dirname(os.path.abspath(__file__))
    for name in _NAMES:
        yield os.path.join(here, name)
    repo = os.path.dirname(os.path.dirname(here))
    for config in ('Release', 'RelWithDebInfo', ''):
        for name in _NAMES:
            pattern = os.path.join(repo, 'build', '*', config, name)
            yield from sorted(glob.glob(pattern), key=os.path.getmtime, reverse=True)


def _bind(lib):
    P = ctypes.c_void_p
    sig = {
        'efz_env_version': (ctypes.c_int32, []),
        'efz_env_default_config': (None, [ctypes.POINTER(Config)]),
        'efz_env_create': (P, [ctypes.c_char_p, ctypes.POINTER(Config), ctypes.c_char_p,
                               ctypes.c_size_t]),
        'efz_env_destroy': (None, [P]),
        'efz_env_num_envs': (ctypes.c_int32, [P]),
        'efz_env_obs_dim': (ctypes.c_int32, []),
        'efz_env_obs_name': (ctypes.c_char_p, [ctypes.c_int32]),
        'efz_env_character_name': (ctypes.c_char_p, [ctypes.c_int32]),
        'efz_env_buffers': (None, [P, ctypes.POINTER(Buffers)]),
        'efz_env_set_obs_buffers': (None, [P, P, P]),
        'efz_env_set_matches': (ctypes.c_int, [P, ctypes.POINTER(Match), ctypes.c_int32]),
        'efz_env_reset': (ctypes.c_int, [P, P]),
        'efz_env_seed': (ctypes.c_int, [P, ctypes.c_int32, ctypes.c_uint64]),
        'efz_env_record': (ctypes.c_int, [P, ctypes.c_int32, ctypes.c_int32, ctypes.c_int32]),
        'efz_env_play': (ctypes.c_int, [P, ctypes.c_int32, ctypes.c_char_p]),
        'efz_env_set_gauges': (ctypes.c_int, [P, ctypes.c_int32, ctypes.c_int32, ctypes.c_int32,
                                              ctypes.c_double, ctypes.c_int32]),
        'efz_env_set_save_dir': (ctypes.c_int, [P, ctypes.c_char_p]),
        'efz_env_step': (ctypes.c_int, [P, P]),
        'efz_env_step_async': (ctypes.c_int, [P, P]),
        'efz_env_step_wait': (ctypes.c_int, [P]),
        'efz_env_state_size': (ctypes.c_size_t, [P, ctypes.c_int32]),
        'efz_env_save_state': (ctypes.c_size_t, [P, ctypes.c_int32, P, ctypes.c_size_t]),
        'efz_env_load_state': (ctypes.c_int, [P, ctypes.c_int32, P, ctypes.c_size_t]),
        'efz_env_render': (ctypes.c_int, [P, ctypes.c_int32, P]),
        'efz_env_ticks': (ctypes.c_uint64, [P]),
        'efz_env_sound_log': (None, [ctypes.c_int32]),
        'efz_env_sound_events': (ctypes.c_int32, [P, ctypes.c_int32, P, ctypes.c_int32]),
        'efz_env_error': (ctypes.c_char_p, [P]),
        'efz_env_agent_load': (P, [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_size_t]),
        'efz_env_agent_free': (None, [P]),
        'efz_env_agent_info': (None, [P, ctypes.POINTER(AgentInfo)]),
        'efz_env_agent_log_probs': (None, [P, P, ctypes.c_int32, P]),
        'efz_env_agent_reset': (None, [P, ctypes.c_uint64]),
        'efz_env_agent_step': (ctypes.c_uint8, [P, P, ctypes.c_int32, ctypes.c_int32]),
        'efz_env_agent_last_action': (ctypes.c_int32, [P]),
        'efz_env_agent_plan': (ctypes.c_int32, [P, P, ctypes.c_int32, ctypes.c_int32,
                                                ctypes.c_int32, P, ctypes.c_int32, P,
                                                ctypes.c_uint8, ctypes.c_int32, ctypes.c_uint64,
                                                ctypes.c_int32, P, ctypes.c_int32,
                                                ctypes.POINTER(Plan)]),
        'efz_env_agent_choose': (ctypes.c_int32, [P, P, ctypes.c_int32, ctypes.c_int32, P]),
    }
    # (a library built before the planned okizeme has none of these)
    newer = {
        'efz_env_agent_oki_entries': (ctypes.c_int32, [P]),
        'efz_env_agent_oki_plan': (ctypes.c_int32, [P, P, ctypes.c_int32, ctypes.c_int32, P,
                                                    ctypes.c_int32, P, ctypes.c_uint8,
                                                    ctypes.c_int32, ctypes.c_uint64, P, P,
                                                    ctypes.POINTER(OkiPlan)]),
        'efz_env_agent_counts': (None, [P, P, ctypes.c_int32, ctypes.c_double, P, P]),
        'efz_env_agent_press_entries': (ctypes.c_int32, [P]),
        'efz_env_agent_press_plan': (ctypes.c_int32, [P, P, ctypes.c_int32, ctypes.c_int32, P,
                                                      ctypes.c_int32, P, ctypes.c_uint8,
                                                      ctypes.c_int32, ctypes.c_uint64, P,
                                                      ctypes.c_uint8, ctypes.POINTER(OkiPlan)]),
        'efz_env_agent_press_shares': (None, [P, ctypes.c_double, P]),
        'efz_env_agent_attach': (ctypes.c_int32, [P, P, ctypes.c_int32, ctypes.c_int32,
                                                  ctypes.c_uint64]),
        'efz_env_agent_stats': (None, [P, P]),
        'efz_env_agent_throw_plan': (ctypes.c_int32, [P, P, ctypes.c_int32, ctypes.c_int32, P,
                                                      ctypes.c_int32, P, ctypes.c_uint8,
                                                      ctypes.c_int32, ctypes.POINTER(OkiPlan)]),
        'efz_env_agent_air_stats': (None, [P, P]),
        'efz_env_agent_rise_stats': (None, [P, P]),
        'efz_env_agent_next_match': (None, [P]),
        'efz_env_agent_risk_stats': (None, [P, P]),
        'efz_env_agent_modules': (ctypes.c_int32, [P, ctypes.c_char_p, ctypes.c_size_t]),
        'efz_env_agent_risk_starts': (ctypes.c_int32, [P, P, ctypes.c_int32, ctypes.c_int32,
                                                       ctypes.c_int32, ctypes.POINTER(ctypes.c_double)]),
    }
    sig.update({name: s for name, s in newer.items() if hasattr(lib, name)})
    for name, (restype, argtypes) in sig.items():
        f = getattr(lib, name)
        f.restype = restype
        f.argtypes = argtypes
    # Additions to the version that a library built before them lacks.
    optional = {
        'efz_env_set_damage_scale': (ctypes.c_int, [P, ctypes.c_int32, ctypes.c_int32,
                                                    ctypes.c_float]),
        'efz_env_set_recoil_guard': (ctypes.c_int, [P, ctypes.c_int32, ctypes.c_int32,
                                                    ctypes.c_float]),
    }
    for name, (restype, argtypes) in optional.items():
        f = getattr(lib, name, None)
        if f is not None:
            f.restype = restype
            f.argtypes = argtypes
    return lib


_lib = None


def library():
    """The loaded library (ctypes.CDLL: calls release the GIL while the games run)."""
    global _lib
    if _lib is not None:
        return _lib
    tried = []
    for path in _candidates():
        if not os.path.isfile(path):
            continue
        tried.append(path)
        lib = _bind(ctypes.CDLL(path))
        if lib.efz_env_version() != VERSION:
            raise RuntimeError(f'{path} is efz_env version {lib.efz_env_version()}, '
                               f'this package wants {VERSION}: rebuild it')
        _lib = lib
        return lib
    raise OSError('efz_env library not found: build it (cmake -B build/headless '
                  '-DEFZ_GAME=OFF && cmake --build build/headless --config Release) '
                  'or set EFZ_ENV_LIBRARY to its path')
