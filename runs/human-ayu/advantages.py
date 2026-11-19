"""A red team's advantages (the user's, 9 November: "very high RG-invincible rate, so that
the agent learns not to keep inputting; 100%-250% damage; red team can abuse throwing, so
it won't keep guarding under pressure"), for any opponent, in training (finetune.py
--vs-rg, --vs-reversal, --vs-throw, --vs-damage) and in evaluations (evaluate.py
--p2-advantage):

- rg: the share of its guards the game makes recoil guards (efz_env_set_recoil_guard, as
  the game's CPU gets its own: the window opened as the hit lands), of the guards it holds
  the right way;
- reversal: of its recoil guards, the share after which, if the agent presses on (starts
  a move of its own within ARM steps: "an RG and an invincible during it", the user's
  read of a habit), it plays its fastest invincible move that comes out of a recoil guard
  and that its gauges allow (motions.json: the motion, as a person would input it);
- throw: the share of its chances to throw (both on the ground, within 28 pixels, the
  agent neither in a hit or guard reaction nor protected from throws, itself free to act;
  with patient, wake or jumpin, not in its first THROW_UP steps after rising: the throw
  fails there and the forward + C comes out as an attack into the agent's meaty)
  in which it throws (forward + C);
- damage: the scale on the damage the agent takes from its hits (efz_env_set_damage_scale);
- bait: of the agent's wake-up reversals (an invincible move within WAKE steps of rising)
  that it isn't committed against (free to act: standing, walking, crouching), the share
  it guards through (crouching: Ayu's invincible moves are all mid; seen as it starts, as
  the advantages see everything) and punishes with its fastest move that reaches and
  starts before the agent recovers (its own play sees the game late, too late for that).
  The user's games of 9 November: the agent rose with one on a third of its wake-ups and
  was hit back on half. Waiting on every wake-up instead gave up the opponent's okizeme
  for little: the agent rises with one on a fifth.

Three more (docs/training-v2.md: a person's defence, from the user's games of 10 November,
which no exploiter played):

- patient: after each of its guards ends, and as it rises from a knockdown (of the
  risings wake leaves), the share in which it holds a guard for PATIENCE steps (20; its
  rising too), pressing nothing: a
  fresh choice of crouching or standing each time (CROUCH of them), never the height the
  attack needs (the level-4 CPU's guard, which made mix-ups worth nothing). A guard
  during it starts the steps again. Its throws (throw) still come out of it. The user
  pressed a button after a guarded string 24% of the times, the exploiters 48%, people
  37%;
- wake: as it rises, the share in which it puts out its fastest invincible move its
  gauges allow on the first step it can: the motion input while rising, the button
  WAKE_BUTTON steps before the rise if the agent is then committed (in a move of its own,
  in the air within COMMITTED pixels, or standing in within MEATY_NEAR, not holding a
  guard: the user's reversals, 74% won, went into its meaties); else a patient guard (an
  agent that waits guards it and punishes it). The user rose with one on 27% of wake-ups and won
  74% of them; the exploiters 2%, people 11%;
- jumpin: on the agent's knockdown, the share in which it jumps in on the rise: it walks
  to the distance motions.py's jump probe found (an air attack that hits a crouching
  guard, a standing one holds it), jumps as the agent's knockdown has the probe's
  contact steps left plus JUMP_LATE, and presses the attack on the probe's step. The
  user's jump-ins hit the rising agent 76% of the times, the exploiters' 52%.

Habits (docs/training-v2.md, "Adapting during a match": an opponent a read pays against):

- blind: of its wake-up reversals (wake), the share that come out whether or not the
  agent is committed: a habit, which an agent that waits guards and punishes (without
  it the reversal reads the agent's commitment from the game as it is: no bait works);
- crouch: the share of its patient guards held crouching (0.85 unless given): a lean
  an okizeme of the other height opens;
- habits: the share of matches in which each of wake, blind, patient, crouch, throw,
  reversal and jumpin is drawn afresh for the match from HABITS (ranges about as wide
  as people's players'), in place of the profile's: opponents that differ from one match
  to the next, and are the same within one. told(i): the match's values, for an agent
  that is told them (finetune.py --tell: can PPO use a read at all?). In an environment
  with sets (EfzSB3VecEnv's sets) they are drawn a set, not a match. wide: the share of
  those drawn from HABITS (1 unless given); the rest from PEOPLE, ranges about as wide
  as the community's players are apart (docs/training-v2.md, "What people's habits look
  like": by player, a wake-up reversal on 0.00-0.27 of wake-ups, a move out of pressure
  on 0.27-0.48), where HABITS reaches further than people do, for a read that pays;
- adapt: its habits change within a set by how its own choices went (an opponent that
  learns the agent: "if it keeps one strategy it will be exploited", the user's, 15
  November): each time one of wake, reversal, throw, jumpin pays (the agent is hit, or
  thrown) that habit moves this share of the way to the most HABITS has for it, and each
  time it costs (itself hit first) to the least; crouch moves toward the guard that would
  have held (hit holding a standing guard: crouching more; a crouching one: less);
  patient up when its own play after a guard is hit, down when that play hits, or when
  it is thrown holding a guard; wake up when a guard on rising is opened. Each set starts
  from the profile's (or the set's drawn habits) again.
- tech: the share of the combos it takes in the air that it recovers from as soon as the
  game lets it (a button with back held, pressed again every other step: src/player.cpp's
  TryAirRecovery, once the untech time is out). The policies of the league seldom do
  (the agent's bigger combos end in their air recovery 10% of the time, in the user's
  41%, 15 November), so a combo that leaves its victim free in the air costs the agent
  nothing against them.
  With it: techway, the share of those recoveries made forward (0: all backward);
  techsafe (1: it presses out only while the agent cannot throw it, in a move of its own
  or more than TECH_SAFE pixels away, and otherwise falls: a recovery when it is safe);
  techhit, the share of its recoveries it follows with an attack at the agent (forward
  and B, pressed again every other step for TECH_HIT steps, while it is in the air and
  the agent within TECH_REACH pixels: what a person's recovery is for, and what makes a
  recovery left uncaught cost something).
- escape: the share of the times it is free on the ground in a corner, the agent on the
  open side within ESCAPE_NEAR pixels, that it jumps out over the agent: up-forward, a
  second jump forward at the top, then forward held (drawn once each time it comes free
  there; over its other habits, under the recovery). What a person does against pressure
  it cannot guard forever: how long the agent keeps it there is evaluate.py's `corner`.
"""

import json
import os

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))

# Columns of a player's own view (efz_env_obs_name).
DX, SELF_GAUGE, SELF_RF, SELF_BLUE = 4, 9, 10, 11
SELF_Y, SELF_ACT, OPP_Y, OPP_ACT = 14, 18, 46, 50
FIRST_OWN = 0xc8  # tactics.FIRST_OWN: a character's own moves
SELF_HITSTUN, SELF_GUARDING, OPP_HITSTUN, OPP_GUARDING, OPP_THROW_PROTECTED = 20, 21, 52, 53, 60
OPP_ACT_FRAME = 51
DOWN = (0x60, 0x61, 0x62, 0x63)  # tactics.DOWN: wake-up, the two knockdowns, lying
WAKE = 8  # focus.WAKE_WINDOW: steps after a knockdown's end in which a reversal is a wake-up one
OUTCOME = 60  # steps after a reversal starts in which its outcome is counted
RG = (0xa8, 0xa9, 0xaa)
FREE = (0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xe, 0xf, 0x10)  # tactics.FREE
THROW_REACH = 28 / 640  # the game's throws reach 30 pixels (src/ayu.cpp etc.)
ARM = 30  # steps after a recoil guard in which the agent's next move sets off the reversal
# The reversal's input: its motion once, from the step of the recoil guard motions.py found
# it comes out from (rg_delay: the game drops what comes before; START if not known), then,
# should a longer freeze have dropped it, its button again every other step with the last
# direction held (a person's mashing; a motion input again can read as another, 2 3 6C
# 2 3 6C as 623C) until the move starts.
START, MASH = 8, 12
PATIENCE = 20     # steps a patient guard is held after a guard ends
RISE_PATIENCE = 40  # and after rising, when it guards on a wake-up (an okizeme is longer than a gap)
CROUCH = 0.85     # the share of patient guards held crouching (the rest standing)
JUMP_LATE = 4     # a jump-in's contact this many steps after the agent's first free step (1-2: it whiffs, the riser untouchable)
JUMP_NEAR = 12    # pixels: how close to the probe's distance the jump starts from
SETTLE_WAKE = 6   # steps after its input a wake-up reversal is looked for
GUARDS = list(range(0x96, 0x9d)) + [0xa8, 0xa9, 0xaa]  # tactics.GUARDS: guards, air guard, RG
RISING = 0x60
KNOCKDOWN = (0x61, 0x62, 0x63)
SELF_ACT_FRAME, SELF_AIRBORNE, OPP_AIRBORNE = 19, 39, 71
COMMITTED = 200   # pixels: an airborne agent this close commits it (a wake-up reversal's)
MEATY_NEAR = 70   # pixels: a grounded agent this close, not holding a guard, is read as a meaty
HOLDING = (0x2, 0x3, 0x8)  # tactics.BLOCKING: walking back, crouching (holding a guard)
WAKE_BUTTON = 2   # a wake-up reversal's button this many steps before its first free one: the
                  # game keeps a motion and a press made while rising (from 12 steps before)
                  # and starts the move on the first step it can (the user's, 10 November);
                  # after a throw that crossed sides it doesn't (motions.py's probes, all by
                  # throws, found only inputs after the rising: wake_delay)
WAKE_HOLD = 3     # steps the button is held
THROW_UP = 12     # steps after its own rising in which a person profile's throw isn't tried
                  # (it fails there: its forward + C comes out as an attack, punished)
KEYS = ('rg', 'reversal', 'throw', 'damage', 'bait', 'patient', 'wake', 'jumpin', 'blind',
        'crouch', 'habits', 'adapt', 'wide', 'tech', 'techway', 'techsafe', 'techhit',
        'escape')
SELF_X, OPP_X = 13, 45
ESCAPE_X, ESCAPE_NEAR = 0.8, 220   # a corner (of +-0.95), and the agent this close
ESCAPE_AGAIN, ESCAPE_STEPS = 14, 44  # the second jump's step, and the script's length
TECH_SAFE, TECH_HIT, TECH_REACH = 110, 24, 160  # (the air throw reaches 100 pixels)
AIR_HIT = range(0x32, 0x60)  # the hit reactions (src/efz.h); in the air: what a recovery ends
THROWN = tuple(range(0x64, 0x79))  # evaluate.THROWN: the poses a throw puts its victim in
THROW_WATCH = 30  # steps after its throw's press in which how it went is looked for
FREE_WATCH = 40   # ... after a guard it didn't hold on from, its own play's
# The inputs' advantages kept per environment (drawn a match with habits), and what a
# habit is drawn from.
KNOBS = ('wake', 'blind', 'patient', 'crouch', 'throw', 'reversal', 'jumpin', 'bait')
TOLD = 1 + len(KNOBS)  # told()'s features
HABITS = dict(wake=(0.0, 0.15, 0.4, 0.8), blind=(0.0, 1.0), patient=(0.0, 0.3, 0.9),
              crouch=(0.3, 0.6, 0.85, 1.0), throw=(0.0, 0.3, 0.9), reversal=(0.0, 0.3, 0.8),
              jumpin=(0.0, 0.2, 0.6))
PEOPLE = dict(wake=(0.0, 0.05, 0.1, 0.2, 0.3), blind=(0.0, 0.5, 1.0),
              patient=(0.2, 0.3, 0.5, 0.9), crouch=(0.6, 0.85, 1.0), throw=(0.4, 0.7, 0.9),
              reversal=(0.0, 0.04, 0.1, 0.3), jumpin=(0.0, 0.2, 0.4))
SPAN = {name: (min(v), max(v)) for name, v in HABITS.items()}  # adapt's least and most


def parse(spec):
    """'rg=0.5,reversal=0.8,throw=0.3,damage=2' -> dict (left out: none)."""
    out = dict(rg=0.0, reversal=0.0, throw=0.0, damage=1.0, bait=0.0, patient=0.0, wake=0.0,
               jumpin=0.0, blind=0.0, crouch=CROUCH, habits=0.0, adapt=0.0, wide=1.0, tech=0.0,
               techway=0.0, techsafe=0.0, techhit=0.0, escape=0.0)
    for part in filter(None, (spec or '').split(',')):
        k, v = part.split('=')
        if k not in out:
            raise ValueError(f'advantage {k}: {", ".join(KEYS)}')
        out[k] = float(v)
    return out


def motions(char):
    return json.load(open(os.path.join(HERE, 'motions.json'))).get(char, {})


def wake_moves(char):
    """The character's invincible moves as wake-up reversals, those that beat a meaty most
    first (motions.py --add meaty: wake_wins), then the fastest: (dirs, button, needs,
    pattern, wake_delay, startup), from motions.json (motions.py --add wake)."""
    out = []
    for m in motions(char).get('invincible', []):
        if m.get('wake_delay') is None:
            continue
        motion = m['motion']
        dirs, button = [int(d) for d in motion[:-1]], motion[-1]
        needs = 'bar' if len(dirs) >= 6 else 'rf' if button == 'C' else None
        out.append((-m.get('wake_wins', 1.0), m['wake_start'], dirs, button, needs,
                    int(m['pattern'], 16), m['wake_delay'], m['startup']))
    return [m[2:] for m in sorted(out, key=lambda m: m[:2])]


def move_lengths(char):
    """The character's moves' lengths in steps (framedata.json): {pattern: steps}."""
    data = json.load(open(os.path.join(HERE, 'framedata.json'))).get(char, {})
    return {int(k, 16): m['steps'] for k, m in data.items() if m.get('steps') and int(k, 16) < 0x190}


def knockdown_left(char):
    """For the learner's knockdown (motions.py's: its parts' steps), the steps left until
    it is free, from the k-th step of a part: {action: [left at k=0, 1, ...]}."""
    parts = motions(char).get('knockdown') or []
    out, later = {}, 0
    for a, n in reversed(parts):
        out[a] = [n - k + later for k in range(n)]
        later += n
    return out


def invincible_moves(char):
    """The character's invincible moves (motions.json), fastest first: (directions,
    button, startup, needs) with needs 'bar' (a super: a level of power), 'rf' (a
    C-button special: half the RF gauge, or blue) or None."""
    data = json.load(open(os.path.join(HERE, 'motions.json'))).get(char, {})
    out = []
    for m in data.get('invincible', []):
        # Only those that come out of a recoil guard and win against pressure (motions.py)
        if not m.get('from_rg', True) or m.get('rg_hits', True) is not True:
            continue
        motion = m['motion']
        dirs, button = [int(d) for d in motion[:-1]], motion[-1]
        needs = 'bar' if len(dirs) >= 6 else 'rf' if button == 'C' else None
        out.append((dirs, button, m['startup'], needs, int(m['pattern'], 16),
                    m.get('rg_delay', START)))
    return sorted(out, key=lambda m: m[2])


def learner_reversals(char):
    """The learner's invincible attacks (framedata.json, throws left out): {pattern:
    (startup, steps)}."""
    data = json.load(open(os.path.join(HERE, 'framedata.json'))).get(char, {})
    return {int(k, 16): (m['startup'], m['steps']) for k, m in data.items()
            if m['invincible'] and m['startup'] is not None and m['level'] >= 10
            and int(k, 16) < 0x190}


def punishers(char):
    """The character's moves to punish with, fastest first: its invincible ones from
    neutral (motions.json, an attack that starts and hits fast), as (directions, button,
    startup, needs, reach in pixels)."""
    data = json.load(open(os.path.join(HERE, 'motions.json'))).get(char, {})
    fd = json.load(open(os.path.join(HERE, 'framedata.json'))).get(char, {})
    out = []
    for m in data.get('invincible', []):
        motion = m['motion']
        dirs, button = [int(d) for d in motion[:-1]], motion[-1]
        needs = 'bar' if len(dirs) >= 6 else 'rf' if button == 'C' else None
        reach = fd.get(m['pattern'], {}).get('reach') or 0
        out.append((dirs, button, m['startup'] + len(dirs) - 1, needs, reach))
    return sorted(out, key=lambda m: m[2])


class Advantages:
    """The per-environment logic: step(i, view) gives the controls that override the
    opponent's own on this step, as (numpad direction, buttons), or None."""

    def __init__(self, char, n, reversal=0.0, throw=0.0, seed=0, bait=0.0, learner='ayu',
                 patient=0.0, wake=0.0, jumpin=0.0, blind=0.0, crouch=CROUCH, habits=0.0,
                 adapt=0.0, wide=1.0, tech=0.0, techway=0.0, techsafe=0.0, techhit=0.0,
                 escape=0.0):
        self.wide, self.tech, self.escape = wide, tech, escape
        self.techway, self.techsafe, self.techhit = techway, techsafe, techhit
        self.base = dict(wake=wake, blind=blind, patient=patient, crouch=crouch, throw=throw,
                         reversal=reversal, jumpin=jumpin, bait=bait)
        self.habits, self.adapt = habits, adapt
        if habits > 0 or adapt > 0:  # what a match may come to: the most of each, for what is loaded
            reversal, throw = max(reversal, max(HABITS['reversal'])), max(throw, max(HABITS['throw']))
            patient, wake = max(patient, max(HABITS['patient'])), max(wake, max(HABITS['wake']))
            jumpin = max(jumpin, max(HABITS['jumpin']))
        self.moves = invincible_moves(char) if reversal > 0 else []
        self.patterns = {m[4] for m in self.moves}
        self.reversal, self.throw, self.bait = reversal, throw, bait
        self.patient, self.wake, self.jumpin = patient, wake, jumpin
        self.person = patient > 0 or wake > 0 or jumpin > 0  # its throws not as it rises
        self.theirs = learner_reversals(learner) if bait > 0 else {}
        self.punish_moves = punishers(char) if bait > 0 else []
        self.wake_moves = wake_moves(char) if wake > 0 else []
        self.wake_patterns = ({int(k, 16) for k, m in json.load(open(os.path.join(
            HERE, 'framedata.json'))).get(char, {}).items() if m['invincible']}
            | {m[3] for m in self.wake_moves}) if wake > 0 else set()  # (the game may give another)
        self.their_lengths = move_lengths(learner) if wake > 0 else {}
        self.rise = motions(char).get('rise') or 0
        self.jump = (motions(char).get('jump') or {}) if jumpin > 0 else {}
        self.plan = self.jump.get('jumpin')  # None: no jump-in found for the character
        self.plans = self.jump.get('plans') or ([self.plan] if self.plan else [])
        self.soonest = min((p['contact'] - JUMP_LATE for p in self.plans), default=0)
        self.left = knockdown_left(learner) if jumpin > 0 else {}
        if jumpin > 0 and not self.left:
            raise ValueError(f'jumpin: no knockdown for {learner} in motions.json (motions.py '
                             '--add wake)')
        self.off = set()  # the knobs the character has nothing for
        if jumpin > 0 and not self.plan:  # (Kanna: no jump of hers is one)
            self.jumpin = 0.0
            self.off.add('jumpin')
        if wake > 0 and not self.wake_moves:  # (Minagi: no invincible move)
            self.wake = 0.0
            self.off.add('wake')
        if (wake > 0 or patient > 0) and not self.rise:
            raise ValueError(f'wake, patient: no rising length for {char} in motions.json '
                             '(motions.py --add wake)')
        self.rng = np.random.default_rng(seed)
        self.habit_rng = np.random.default_rng([seed, 0x4ab17])  # (its own: the play's draws as without)
        self.resize(n)
        self.counts = dict(recoveries=0, rg=0, armed=0, reversals=0, reversals_started=0, reversal_hit=0,
                           reversal_hit_back=0, throw_chances=0, throws=0,
                           wake_reversals=0, baited=0, baited_hit_us=0, bait_punishes=0,
                           bait_punished=0, guards_ended=0, patient_holds=0, rises=0,
                           rise_reversals=0, rise_reversals_blind=0, rise_reversals_held=0, rise_reversals_started=0, rise_reversal_hit=0,
                           rise_reversal_hit_back=0, rise_patient=0, knockdowns=0,
                           jumpins_armed=0, jumpins=0, jumpin_hit=0, jumpin_guarded=0,
                           jumpin_hit_back=0, jumpin_late=0, adapted=0)

    def resize(self, n):
        self.tech_on, self.tech_step = np.zeros(n, bool), np.zeros(n, int)
        self.tech_fwd, self.tech_hits = np.zeros(n, bool), np.zeros(n, bool)
        self.tech_rec, self.tech_left = np.zeros(n, bool), np.zeros(n, int)
        self.esc_step, self.esc_drawn = np.zeros(n, int), np.zeros(n, bool)
        self.tech_waited = np.zeros(n, bool)
        self.k = {name: np.full(n, 0.0 if name in self.off else float(v))
                  for name, v in self.base.items()}  # each environment's, this match
        for i in range(n if self.habits > 0 else 0):  # (an evaluation's matches: one each)
            self.draw(i)
        self.queue = [[] for _ in range(n)]
        self.prev = np.full(n, -1)
        self.prev_opp = np.full(n, -1)
        self.was_close = np.zeros(n, bool)
        self.armed = np.zeros(n, int)  # steps left in which the agent's move sets one off
        self.trying = np.zeros(n, int)  # steps left to start a reversal in
        self.watch = np.zeros(n, int)  # steps left to see a started reversal's outcome
        self.hit_prev = np.zeros((n, 2), bool)
        self.baiting = np.zeros(n, int)  # 2: guarding its reversal
        self.since_up = np.full(n, 999)  # steps since the agent rose from a knockdown
        self.blocked = np.zeros(n, bool)  # it guarded the reversal
        self.free_steps = np.zeros(n, int)  # steps out of guard since
        self.punish = np.zeros(n, int)  # steps left to see the baited reversal punished
        self.guarding = np.zeros(n, bool)  # its guard on the step before
        self.patience = np.zeros(n, int)  # steps left of a patient guard
        self.guard_dir = np.ones(n, int)  # 1 crouching, 4 standing
        self.rise_try = np.zeros(n, int)  # steps left for a wake-up reversal to come out
        self.rise_plan = [None] * n  # a wake-up reversal's input, waiting for its first step
        self.rise_wait = np.zeros(n, int)  # steps until then
        self.rise_delay = np.zeros(n, int)  # its wake_delay
        self.rise_need = np.zeros(n, int)  # the steps the agent must stay committed for
        self.agent_k = np.zeros(n, int)  # steps the agent has been in its action
        self.own_up = np.full(n, 999)  # steps since its own knockdown ended
        self.rise_watch = np.zeros(n, int)  # steps left to see one's outcome
        self.down_k = np.zeros(n, int)  # steps the agent has been in its knockdown's part
        self.jumping = np.zeros(n, bool)  # a jump-in planned on this knockdown
        self.decided = np.zeros(n, bool)  # this knockdown's jump-in drawn
        self.jump_watch = np.zeros(n, int)  # steps left to see a jump-in's outcome
        self.throw_watch = np.zeros(n, int)  # ... a throw's
        self.free_watch = np.zeros(n, int)  # ... its own play's after a guard it didn't hold on from
        self.rise_guard = np.zeros(n, int)  # ... a guard's on rising

    def learn(self, i, name, paid):
        """adapt: environment i's habit `name` after a choice of its kind paid, or cost."""
        if self.adapt <= 0 or name in self.off:
            return
        lo, hi = SPAN[name]
        k = self.k[name][i]
        self.k[name][i] = k + self.adapt * ((hi if paid else lo) - k)
        self.counts['adapted'] += 1

    def draw(self, i):
        """The match's habits for environment i: HABITS' in a share `habits` of the
        matches, else the profile's."""
        drawn = self.habit_rng.random() < self.habits
        table = HABITS if self.wide >= 1 or self.habit_rng.random() < self.wide else PEOPLE
        for name, v in self.base.items():
            if drawn and name in table:
                v = table[name][int(self.habit_rng.integers(len(table[name])))]
            self.k[name][i] = 0.0 if name in self.off else v

    def told(self, i):
        """What a player told of environment i's habits this match sees (TOLD features):
        1, then the habits in KNOBS' order."""
        return np.array([1.0] + [self.k[name][i] for name in KNOBS], np.float32)

    def clear(self, i):
        self.queue[i] = []
        self.prev[i] = self.prev_opp[i] = -1
        self.was_close[i] = False
        self.armed[i] = self.trying[i] = self.watch[i] = 0
        self.baiting[i] = self.punish[i] = 0
        self.since_up[i] = 999
        self.guarding[i] = False
        self.patience[i] = self.rise_try[i] = self.rise_watch[i] = 0
        self.rise_plan[i], self.rise_wait[i], self.agent_k[i] = None, 0, 0
        self.own_up[i] = 999
        self.down_k[i] = self.jump_watch[i] = 0
        self.jumping[i] = self.decided[i] = False
        self.throw_watch[i] = self.free_watch[i] = self.rise_guard[i] = 0

    def pick(self, v):
        """The fastest invincible move its gauges allow, as its input: the motion, then the
        button mashed with the last direction held."""
        for dirs, button, _, needs, pattern, delay in self.moves:
            if needs == 'bar' and v[SELF_GAUGE] < 1 / 3:
                continue
            if needs == 'rf' and v[SELF_RF] < 0.5 and v[SELF_BLUE] < 0.5:
                continue
            last = dirs[-1]
            return ([(d, '') for d in dirs[:-1]] + [(last, button)]
                    + [(last, ''), (last, button)] * MASH), delay
        return None

    def escaping(self, i, v):
        """The jump out of a corner: its controls on this step, or None."""
        a = int(round(v[SELF_ACT]))
        k = self.esc_step[i]
        if k > 0:  # on its way out
            if v[SELF_HITSTUN] > 0.5 or k >= ESCAPE_STEPS or (k > 8 and v[SELF_AIRBORNE] < 0.5):
                self.esc_step[i] = 0
                return None
            self.esc_step[i] += 1
            if k < ESCAPE_AGAIN:
                return (9, '')
            if k == ESCAPE_AGAIN:
                return (5, '')       # (the stick let go: the second jump is a new press)
            return (9, '') if k < ESCAPE_AGAIN + 4 else (6, '')
        cornered = (abs(float(v[SELF_X])) > ESCAPE_X and abs(float(v[OPP_X])) < abs(float(v[SELF_X]))
                    and abs(float(v[DX])) * 640 <= ESCAPE_NEAR)
        free = a in FREE and v[SELF_AIRBORNE] < 0.5 and v[SELF_HITSTUN] < 0.5
        if not (cornered and free):
            self.esc_drawn[i] = False
            return None
        if self.esc_drawn[i]:
            return None
        self.esc_drawn[i] = True
        if self.rng.random() >= self.escape:
            return None
        self.counts['escapes'] = self.counts.get('escapes', 0) + 1
        self.esc_step[i] = 1
        return (9, '')

    def step(self, i, v):
        out = self.act(i, v)
        if self.escape > 0:
            esc = self.escaping(i, v)
            if esc is not None:
                out = esc
        if self.tech > 0:  # recovering in the air from the agent's combo: over anything else
            a = int(round(v[SELF_ACT]))
            if a in AIR_HIT:
                if self.tech_step[i] == 0:  # a new combo on it: does it recover from this one
                    self.tech_on[i] = self.rng.random() < self.tech
                    if self.techway > 0 or self.techhit > 0:
                        self.tech_fwd[i] = self.rng.random() < self.techway
                        self.tech_hits[i] = self.rng.random() < self.techhit
                self.tech_step[i] += 1
                self.tech_left[i] = 0
                if self.tech_on[i] and v[SELF_AIRBORNE] > 0.5:
                    if self.techsafe > 0 and v[OPP_ACT] < FIRST_OWN - 0.5 and \
                            abs(float(v[DX])) * 640 <= TECH_SAFE:
                        if not self.tech_waited[i]:  # (once a combo)
                            self.counts['tech_unsafe'] = self.counts.get('tech_unsafe', 0) + 1
                        self.tech_waited[i] = True
                        return (4, '')  # the agent free beside it: it falls
                    return (6 if self.tech_fwd[i] else 4, 'A' if self.tech_step[i] % 2 else '')
            else:
                rec = a in (0x9d, 0x9e)
                if self.tech_step[i] and self.tech_on[i] and rec:
                    self.counts['recoveries'] += 1
                self.tech_step[i] = 0
                self.tech_waited[i] = False
                if self.tech_rec[i] and not rec and self.tech_hits[i]:
                    self.tech_left[i] = TECH_HIT   # out of its recovery: the attack
                    self.counts['tech_hits'] = self.counts.get('tech_hits', 0) + 1
                self.tech_rec[i] = rec
                if self.tech_left[i] > 0:
                    self.tech_left[i] -= 1
                    if v[SELF_AIRBORNE] > 0.5 and v[SELF_HITSTUN] < 0.5 and \
                            abs(float(v[DX])) * 640 <= TECH_REACH:
                        return (6, 'B' if self.tech_left[i] % 2 else '')
                    self.tech_left[i] = 0
        return out

    def act(self, i, v):
        a, o = int(round(v[SELF_ACT])), int(round(v[OPP_ACT]))
        hit = np.array([v[OPP_HITSTUN] > 0.5, v[SELF_HITSTUN] > 0.5])
        rose = hit & ~self.hit_prev[i]
        self.hit_prev[i] = hit
        if self.watch[i] > 0:  # who is hit first after its reversal
            self.watch[i] -= 1
            if rose[0] or rose[1]:
                self.counts['reversal_hit' if rose[0] else 'reversal_hit_back'] += 1
                self.learn(i, 'reversal', bool(rose[0]))
                self.watch[i] = 0
        if self.throw_watch[i] > 0:  # its throw: the agent thrown, or itself hit first
            self.throw_watch[i] -= 1
            if o in THROWN or rose[1]:
                self.learn(i, 'throw', o in THROWN)
                self.throw_watch[i] = 0
        if self.trying[i] and a in self.patterns:  # it came out: let it play
            self.counts['reversals_started'] += 1
            self.trying[i] = 0
            self.queue[i] = []
            self.watch[i] = OUTCOME
        if self.trying[i] and not self.queue[i]:
            self.trying[i] = 0  # it didn't come out
        if self.armed[i] > 0:
            self.armed[i] -= 1
            plan = self.pick(v) if o != self.prev_opp[i] and o >= FIRST_OWN else None
            if plan:  # the agent presses on: from the step of the recoil guard it comes out on
                seq, delay = plan
                self.counts['reversals'] += 1
                since = ARM - 1 - self.armed[i]
                self.armed[i] = 0
                self.trying[i] = 1
                self.queue[i] = [(5, '')] * max(0, delay - since) + seq
        out = self.step_bait(i, v, a, o, rose)
        if out is not None:
            self.prev[i], self.prev_opp[i] = a, o
            return out
        self.step_person(i, v, a, o, rose)
        if a in RG and self.prev[i] not in RG:
            self.counts['rg'] += 1
            if self.moves and self.rng.random() < self.k['reversal'][i]:
                self.counts['armed'] += 1
                self.armed[i] = ARM
        if self.queue[i]:
            out = self.queue[i].pop(0)
        if out is None and self.throw > 0:
            close = (abs(v[DX]) < THROW_REACH and v[SELF_Y] >= 0 and v[OPP_Y] >= 0
                     and v[OPP_HITSTUN] < 0.5 and v[OPP_GUARDING] < 0.5
                     and v[OPP_THROW_PROTECTED] < 0.5 and a in FREE
                     and (self.own_up[i] > THROW_UP or not self.person))  # (not as it rises)
            if close and not self.was_close[i]:
                self.counts['throw_chances'] += 1
                if self.rng.random() < self.k['throw'][i]:
                    self.counts['throws'] += 1
                    self.throw_watch[i] = THROW_WATCH
                    self.queue[i] = [(6, 'C')]  # a fresh press: forward + C
                    out = (6, '')
            self.was_close[i] = close
        if out is None:
            out = self.hold(i, v, a, o)
        self.prev[i], self.prev_opp[i] = a, o
        return out

    def pick_wake(self, v):
        """Its fastest invincible move on rising its gauges allow: (its motion's
        directions, its button), or None."""
        for dirs, button, needs, _, delay, startup in self.wake_moves:
            if needs == 'bar' and v[SELF_GAUGE] < 1 / 3:
                continue
            if needs == 'rf' and v[SELF_RF] < 0.5 and v[SELF_BLUE] < 0.5:
                continue
            return dirs, button
        return None

    def step_person(self, i, v, a, o, rose):
        """patient, wake and jumpin: their outcomes seen, and what each starts on this step
        (a wake-up reversal or a jump-in into the queue, a patient guard's steps)."""
        if self.rise_try[i] > 0:  # did the wake-up reversal come out, and who was hit first
            self.rise_try[i] -= 1
            if a in self.wake_patterns and a != self.prev[i]:
                self.counts['rise_reversals_started'] += 1
                self.rise_try[i], self.rise_watch[i] = 0, OUTCOME
        if self.rise_watch[i] > 0:
            self.rise_watch[i] -= 1
            if rose[0] or rose[1]:
                self.counts['rise_reversal_hit' if rose[0] else 'rise_reversal_hit_back'] += 1
                self.learn(i, 'wake', bool(rose[0]))
                self.rise_watch[i] = 0
        if self.adapt > 0:
            if rose[1] and self.patience[i] > 0:  # hit holding a guard: the other height held
                self.learn(i, 'crouch', self.guard_dir[i] == 4)
            if a in THROWN and self.prev[i] not in THROWN and self.patience[i] > 0:
                self.learn(i, 'patient', False)  # thrown holding one
            if self.rise_guard[i] > 0:  # a guard on rising, opened
                self.rise_guard[i] -= 1
                if rose[1] or a in THROWN:
                    self.learn(i, 'wake', True)
                    self.rise_guard[i] = 0
            if self.free_watch[i] > 0:  # its own play after a guard: who is hit first
                self.free_watch[i] -= 1
                if rose[0] or rose[1]:
                    self.learn(i, 'patient', bool(rose[1]))
                    self.free_watch[i] = 0
        if self.jump_watch[i] > 0:  # the jump-in: hit, guarded, or hit back
            self.jump_watch[i] -= 1
            if rose[0] or rose[1] or v[OPP_GUARDING] > 0.5:
                self.counts['jumpin_hit' if rose[0] else 'jumpin_hit_back' if rose[1]
                            else 'jumpin_guarded'] += 1
                if rose[0] or rose[1]:
                    self.learn(i, 'jumpin', bool(rose[0]))
                self.jump_watch[i] = 0
        self.agent_k[i] = 0 if o != self.prev_opp[i] else self.agent_k[i] + 1
        self.own_up[i] = 0 if a in DOWN else min(999, self.own_up[i] + 1)
        if (self.wake > 0 or self.patient > 0) and a == RISING and self.prev[i] != RISING:
            self.counts['rises'] += 1
            u = self.rng.random()
            wake, patient = self.k['wake'][i], self.k['patient'][i]
            plan = self.pick_wake(v) if u < wake else None
            if plan:  # its directions during the rising, the button decided on WAKE_BUTTON before
                dirs, button = plan
                self.rise_wait[i] = max(0, self.rise - WAKE_BUTTON - (len(dirs) - 1))
                self.rise_plan[i], self.rise_delay[i], self.patience[i] = plan, len(dirs) - 1, 0
            elif wake <= u < wake + (1 - wake) * patient:  # of the rest
                self.counts['rise_patient'] += 1
                self.patience[i] = self.rise_guard[i] = self.rise + RISE_PATIENCE
                self.guard_dir[i] = 1 if self.rng.random() < self.k['crouch'][i] else 4
        if self.rise_plan[i] is not None:
            if self.rise_wait[i] > 0:  # until its motion's first step
                self.rise_wait[i] -= 1
                if self.rise_wait[i] == 0 and self.rise_delay[i] > 0:  # its directions (harmless)
                    self.queue[i] = [(d, '') for d in self.rise_plan[i][0][:-1]]
                    self.rise_wait[i], self.rise_delay[i] = self.rise_delay[i], 0
            if self.rise_wait[i] == 0:  # the button's step: is the agent committed?
                (dirs, button), self.rise_plan[i] = self.rise_plan[i], None
                near = abs(v[DX]) * 640
                committed = (o >= FIRST_OWN  # into its meaty (the user's 74%), or its jump-in
                             or (v[OPP_AIRBORNE] > 0.5 and near < COMMITTED)
                             # or as it stands in to meaty (a read: it does, 70% of times)
                             or (v[OPP_AIRBORNE] < 0.5 and o in FREE and o not in HOLDING
                                 and near < MEATY_NEAR))
                blind = self.k['blind'][i]
                if not committed and blind > 0 and self.rng.random() < blind:
                    committed = True  # a habit: it comes out anyway
                    self.counts['rise_reversals_blind'] += 1
                if committed:
                    self.counts['rise_reversals'] += 1
                    self.queue[i] = [(dirs[-1], button)] * WAKE_HOLD
                    self.rise_try[i] = WAKE_BUTTON + WAKE_HOLD + SETTLE_WAKE
                else:  # it waits: guarded and punished, which a person's never were
                    self.counts['rise_reversals_held'] += 1
                    self.queue[i] = []
                    self.patience[i] = WAKE_BUTTON + RISE_PATIENCE
                    self.guard_dir[i] = 1 if self.rng.random() < self.k['crouch'][i] else 4
        guarding = a in GUARDS
        if self.patient > 0 and self.guarding[i] and not guarding:  # a guard of its ended
            self.counts['guards_ended'] += 1
            if self.patience[i] > 0:  # guarding patiently still: as long again
                self.patience[i] = PATIENCE
            elif self.rng.random() < self.k['patient'][i]:
                self.counts['patient_holds'] += 1
                self.patience[i] = PATIENCE
                self.guard_dir[i] = 1 if self.rng.random() < self.k['crouch'][i] else 4
            else:
                self.free_watch[i] = FREE_WATCH
        self.guarding[i] = guarding
        if self.jumpin > 0:  # the agent's knockdown: a jump-in on it, drawn once
            if o in self.left:
                self.down_k[i] = 0 if o != self.prev_opp[i] else self.down_k[i] + 1
                if not self.decided[i]:
                    self.decided[i] = True
                    self.counts['knockdowns'] += 1
                    if self.rng.random() < self.k['jumpin'][i]:
                        self.jumping[i] = True
                        self.counts['jumpins_armed'] += 1
            else:
                self.decided[i] = self.jumping[i] = False

    def hold(self, i, v, a, o):
        """With nothing queued: a planned jump-in's walk to its distance and its jump, else
        a patient guard's step, else None (its own policy)."""
        if self.jumping[i]:
            if o not in self.left:
                self.jumping[i] = False
                return None
            if a not in FREE or v[SELF_AIRBORNE] > 0.5:
                return None  # (not free yet: its own policy's, as the game allows)
            left = self.left[o]
            rem = left[min(self.down_k[i], len(left) - 1)]
            d = abs(v[DX]) * 640
            # A plan from about this distance whose contact falls on the rise (+-1 step)
            go = [p for p in self.plans if abs(p['distance'] - d) <= JUMP_NEAR / 2
                  and abs(p['contact'] - JUMP_LATE - rem) <= 1]
            if go:
                p = max(go, key=lambda p: p['contact'])
                self.jumping[i] = False
                pre, press = self.jump['prejump'], p['press']
                seq = ([(p.get('way', 9), '')] * pre + [(5, '')] * (press - pre) + [(5, p['button'])]
                       + [(5, '')] * max(0, pre + self.jump['air'] - press))
                self.counts['jumpins'] += 1
                self.jump_watch[i] = p['contact'] + 12
                self.queue[i] = seq[1:]
                return seq[0]
            if rem < self.soonest - 1:  # too late for every plan
                self.jumping[i] = False
                self.counts['jumpin_late'] += 1
                return None
            near = min(self.plans, key=lambda p: abs(p['distance'] - d))['distance']
            return (6, '') if d > near + 4 else (4, '') if d < near - 4 else (5, '')
        if self.patience[i] > 0:
            self.patience[i] -= 1
            return (int(self.guard_dir[i]), '')
        return None

    def punish_with(self, v, left):
        """The input of the fastest punisher that reaches and starts within `left` steps: a
        throw within its reach (both on the ground), else a move."""
        dist = abs(v[DX]) * 640
        if abs(v[DX]) < THROW_REACH and v[SELF_Y] >= 0 and v[OPP_Y] >= 0 and left > 2:
            return [(6, ''), (6, 'C')]
        for dirs, button, startup, needs, reach in self.punish_moves:
            if startup >= left or reach < dist:
                continue
            if needs == 'bar' and v[SELF_GAUGE] < 1 / 3:
                continue
            if needs == 'rf' and v[SELF_RF] < 0.5 and v[SELF_BLUE] < 0.5:
                continue
            return [(d, '') for d in dirs[:-1]] + [(dirs[-1], button)]
        return None

    def step_bait(self, i, v, a, o, rose):
        """The bait's control for this step (a guard), or None."""
        if self.punish[i] > 0:  # after a baited reversal: is it punished?
            self.punish[i] -= 1
            if rose[0]:
                self.counts['bait_punished'] += 1
                self.punish[i] = 0
        if self.bait <= 0:
            return None
        if o in DOWN:
            self.since_up[i] = 0
        elif self.since_up[i] < 999:
            self.since_up[i] += 1
        if (self.baiting[i] == 0 and o in self.theirs and o != self.prev_opp[i]
                and self.since_up[i] <= WAKE):  # a wake-up reversal
            self.counts['wake_reversals'] += 1
            if a in FREE and self.rng.random() < self.k['bait'][i]:  # not committed: guard it through
                self.counts['baited'] += 1
                self.baiting[i], self.blocked[i], self.free_steps[i] = 2, False, 0
                self.queue[i], self.armed[i], self.trying[i] = [], 0, 0
        if self.baiting[i] == 2:
            if rose[1]:
                self.counts['baited_hit_us'] += 1
            guarding = v[SELF_GUARDING] > 0.5
            self.blocked[i] |= guarding
            self.free_steps[i] = 0 if guarding else self.free_steps[i] + 1
            done = (o not in self.theirs  # its move ended
                    or (self.blocked[i] and self.free_steps[i] >= 2)  # its hits are over
                    or (not self.blocked[i] and v[OPP_ACT_FRAME] > self.theirs[o][0] + 10))
            if done:
                self.baiting[i] = 0
                self.punish[i] = 45
                left = self.theirs[o][1] - v[OPP_ACT_FRAME] if o in self.theirs else 0
                seq = self.punish_with(v, left)
                if seq:  # its fastest move that reaches and starts before the agent recovers
                    self.counts['bait_punishes'] += 1
                    self.queue[i] = seq
                    return self.queue[i].pop(0)
                return None
            return (1, '')
        return None

    def take(self):
        c = dict(self.counts)
        for k in self.counts:
            self.counts[k] = 0
        return c


def set_env(env, indices, side, adv):
    """The game's part of the advantages, on environments `indices` of an EfzVecEnv:
    the recoil-guard share of player `side` and the damage the other takes."""
    for i in indices:
        if adv['rg'] > 0:
            env.set_recoil_guard(int(i), side, adv['rg'])
        if adv['damage'] != 1:
            env.set_damage_scale(int(i), 1 - side, adv['damage'])


class AdvantagedOpponent:
    """finetune.py's: an EfzSB3VecEnv opponent (player 2) with the advantages' inputs.
    attach(venv) first. The game's part (rg, damage) is finetune.make_env's. alt: a second
    profile's advantages, played in the environments of `second` (finetune.py
    --vs-profile2)."""
    takes_index = True

    def __init__(self, inner, char, adv, seed=0, learner='ayu', alt=None):
        from efz_env.actions import ActionTable
        self.inner, self.adv = inner, adv
        self.table = ActionTable()
        self.index = {a: k for k, a in enumerate(self.table.actions)}
        logic = lambda a, seed: Advantages(char, 0, a['reversal'], a['throw'], seed,
                                           a.get('bait', 0.0), learner, a.get('patient', 0.0),
                                           a.get('wake', 0.0), a.get('jumpin', 0.0),
                                           a.get('blind', 0.0), a.get('crouch', CROUCH),
                                           a.get('habits', 0.0), a.get('adapt', 0.0),
                                           a.get('wide', 1.0), a.get('tech', 0.0),
                                a.get('techway', 0.0), a.get('techsafe', 0.0),
                                a.get('techhit', 0.0), a.get('escape', 0.0))
        self.logic = logic(adv, seed)
        self.alt = logic(alt, seed + 7919) if alt is not None else None
        self.venv = None
        self.only = None    # the environments that play with the advantages (None: all)
        self.second = None  # and those of them that play with alt's
        self.mine = None    # the environments it plays in at all (None: all)

    def attach(self, venv):
        self.venv = venv
        self.logic.resize(venv.env.num_envs)
        if self.alt is not None:
            self.alt.resize(venv.env.num_envs)
        if hasattr(venv, 'on_end'):
            venv.on_end.append(self.new_match)

    def of(self, i):
        """The advantages environment i plays with (None: without)."""
        if (self.mine is not None and not self.mine[i]) or \
                (self.only is not None and not self.only[i]):
            return None
        if self.alt is not None and self.second is not None and self.second[i]:
            return self.alt
        return self.logic

    def new_match(self, ended):
        """The matches that ended (EfzSB3VecEnv's on_end): the next ones' habits drawn
        where a set starts (the environment's sets: every match, without them), and told
        to the learner where the environment tells (its extra features)."""
        v = self.venv
        fresh = getattr(v, 'new_set', None)
        for i in np.flatnonzero(ended):
            i = int(i)
            if self.mine is not None and not self.mine[i]:
                continue
            logic = self.of(i)
            if logic is not None and (logic.habits > 0 or logic.adapt > 0) and \
                    (fresh is None or fresh[i]):
                logic.draw(i)
            if v.extra is not None:
                v.extra[i, 0] = logic.told(i) if logic is not None else 0.0

    def __call__(self, obs, idx):
        return self.post(np.asarray(self.inner(obs)).copy(), idx)

    def post(self, actions, idx):
        """The inner policy's actions for matches idx, with the advantages' inputs over
        them (efz_env.sb3.mixture calls the inner policy with others, then this)."""
        v = self.venv
        for k, i in enumerate(idx):
            i = int(i)
            logic = self.of(i)
            if logic is None:
                continue
            if v._length[i] == 0:  # a new match
                logic.clear(i)
            o = logic.step(i, v.env.obs[i, 1])
            if o is not None:
                actions[k] = self.index[o]
        return actions


class AdvantagedAgent:
    """evaluate.py's: an efz_env.agent.Agent with the advantages, its game's part set on
    the evaluation's environment as it attaches."""

    def __init__(self, agent, char, adv, seed=0, learner='ayu'):
        from efz_env.actions import encode
        self.agent, self.adv, self.encode = agent, adv, encode
        self.logic = Advantages(char, 0, adv['reversal'], adv['throw'], seed,
                                adv.get('bait', 0.0), learner, adv.get('patient', 0.0),
                                adv.get('wake', 0.0), adv.get('jumpin', 0.0),
                                adv.get('blind', 0.0), adv.get('crouch', CROUCH),
                                adv.get('habits', 0.0), adv.get('adapt', 0.0),
                                adv.get('wide', 1.0), adv.get('tech', 0.0),
                                adv.get('techway', 0.0), adv.get('techsafe', 0.0),
                                adv.get('techhit', 0.0), adv.get('escape', 0.0))
        self.env = self.side = None

    def __getattr__(self, name):  # the rest is the agent's
        return getattr(self.agent, name)

    def attach(self, env, side):
        self.env, self.side = env, side
        set_env(env, range(env.num_envs), side, self.adv)
        if hasattr(self.agent, 'attach'):
            self.agent.attach(env, side)

    def batch(self, n):
        self.agent.batch(n)
        self.logic.resize(n)

    def reset(self, mask=None):
        self.agent.reset(mask)
        for i in (range(len(self.logic.queue)) if mask is None else np.flatnonzero(mask)):
            self.logic.clear(int(i))

    def controls(self, obs, step):
        own = np.asarray(self.agent.controls(obs, step)).copy()
        now = self.env.obs[:, self.side]  # the game as it is, not as the agent sees it
        for i in range(len(own)):
            o = self.logic.step(i, now[i])
            if o is not None:
                own[i] = self.encode(*o)
        return own
