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
KEYS = ('rg', 'reversal', 'throw', 'damage', 'bait', 'patient', 'wake', 'jumpin')


def parse(spec):
    """'rg=0.5,reversal=0.8,throw=0.3,damage=2' -> dict (left out: none)."""
    out = dict(rg=0.0, reversal=0.0, throw=0.0, damage=1.0, bait=0.0, patient=0.0, wake=0.0,
               jumpin=0.0)
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
                 patient=0.0, wake=0.0, jumpin=0.0):
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
        if jumpin > 0 and not self.plan:  # (Kanna: no jump of hers is one)
            self.jumpin = 0.0
        if wake > 0 and not self.wake_moves:  # (Minagi: no invincible move)
            self.wake = 0.0
        if (wake > 0 or patient > 0) and not self.rise:
            raise ValueError(f'wake, patient: no rising length for {char} in motions.json '
                             '(motions.py --add wake)')
        self.rng = np.random.default_rng(seed)
        self.resize(n)
        self.counts = dict(rg=0, armed=0, reversals=0, reversals_started=0, reversal_hit=0,
                           reversal_hit_back=0, throw_chances=0, throws=0,
                           wake_reversals=0, baited=0, baited_hit_us=0, bait_punishes=0,
                           bait_punished=0, guards_ended=0, patient_holds=0, rises=0,
                           rise_reversals=0, rise_reversals_held=0, rise_reversals_started=0, rise_reversal_hit=0,
                           rise_reversal_hit_back=0, rise_patient=0, knockdowns=0,
                           jumpins_armed=0, jumpins=0, jumpin_hit=0, jumpin_guarded=0,
                           jumpin_hit_back=0, jumpin_late=0)

    def resize(self, n):
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

    def step(self, i, v):
        a, o = int(round(v[SELF_ACT])), int(round(v[OPP_ACT]))
        hit = np.array([v[OPP_HITSTUN] > 0.5, v[SELF_HITSTUN] > 0.5])
        rose = hit & ~self.hit_prev[i]
        self.hit_prev[i] = hit
        if self.watch[i] > 0:  # who is hit first after its reversal
            self.watch[i] -= 1
            if rose[0] or rose[1]:
                self.counts['reversal_hit' if rose[0] else 'reversal_hit_back'] += 1
                self.watch[i] = 0
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
            if self.moves and self.rng.random() < self.reversal:
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
                if self.rng.random() < self.throw:
                    self.counts['throws'] += 1
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
                self.rise_watch[i] = 0
        if self.jump_watch[i] > 0:  # the jump-in: hit, guarded, or hit back
            self.jump_watch[i] -= 1
            if rose[0] or rose[1] or v[OPP_GUARDING] > 0.5:
                self.counts['jumpin_hit' if rose[0] else 'jumpin_hit_back' if rose[1]
                            else 'jumpin_guarded'] += 1
                self.jump_watch[i] = 0
        self.agent_k[i] = 0 if o != self.prev_opp[i] else self.agent_k[i] + 1
        self.own_up[i] = 0 if a in DOWN else min(999, self.own_up[i] + 1)
        if (self.wake > 0 or self.patient > 0) and a == RISING and self.prev[i] != RISING:
            self.counts['rises'] += 1
            u = self.rng.random()
            plan = self.pick_wake(v) if u < self.wake else None
            if plan:  # its directions during the rising, the button decided on WAKE_BUTTON before
                dirs, button = plan
                self.rise_wait[i] = max(0, self.rise - WAKE_BUTTON - (len(dirs) - 1))
                self.rise_plan[i], self.rise_delay[i], self.patience[i] = plan, len(dirs) - 1, 0
            elif self.wake <= u < self.wake + (1 - self.wake) * self.patient:  # of the rest
                self.counts['rise_patient'] += 1
                self.patience[i] = self.rise + RISE_PATIENCE
                self.guard_dir[i] = 1 if self.rng.random() < CROUCH else 4
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
                if committed:
                    self.counts['rise_reversals'] += 1
                    self.queue[i] = [(dirs[-1], button)] * WAKE_HOLD
                    self.rise_try[i] = WAKE_BUTTON + WAKE_HOLD + SETTLE_WAKE
                else:  # it waits: guarded and punished, which a person's never were
                    self.counts['rise_reversals_held'] += 1
                    self.queue[i] = []
                    self.patience[i] = WAKE_BUTTON + RISE_PATIENCE
                    self.guard_dir[i] = 1 if self.rng.random() < CROUCH else 4
        guarding = a in GUARDS
        if self.patient > 0 and self.guarding[i] and not guarding:  # a guard of its ended
            self.counts['guards_ended'] += 1
            if self.patience[i] > 0:  # guarding patiently still: as long again
                self.patience[i] = PATIENCE
            elif self.rng.random() < self.patient:
                self.counts['patient_holds'] += 1
                self.patience[i] = PATIENCE
                self.guard_dir[i] = 1 if self.rng.random() < CROUCH else 4
        self.guarding[i] = guarding
        if self.jumpin > 0:  # the agent's knockdown: a jump-in on it, drawn once
            if o in self.left:
                self.down_k[i] = 0 if o != self.prev_opp[i] else self.down_k[i] + 1
                if not self.decided[i]:
                    self.decided[i] = True
                    self.counts['knockdowns'] += 1
                    if self.rng.random() < self.jumpin:
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
            if a in FREE and self.rng.random() < self.bait:  # not committed: guard it through
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
    attach(venv) first. The game's part (rg, damage) is finetune.make_env's."""
    takes_index = True

    def __init__(self, inner, char, adv, seed=0, learner='ayu'):
        from efz_env.actions import ActionTable
        self.inner, self.adv = inner, adv
        self.table = ActionTable()
        self.index = {a: k for k, a in enumerate(self.table.actions)}
        self.logic = Advantages(char, 0, adv['reversal'], adv['throw'], seed,
                                adv.get('bait', 0.0), learner, adv.get('patient', 0.0),
                                adv.get('wake', 0.0), adv.get('jumpin', 0.0))
        self.venv = None
        self.only = None  # the environments that play with the advantages (None: all)

    def attach(self, venv):
        self.venv = venv
        self.logic.resize(venv.env.num_envs)

    def __call__(self, obs, idx):
        return self.post(np.asarray(self.inner(obs)).copy(), idx)

    def post(self, actions, idx):
        """The inner policy's actions for matches idx, with the advantages' inputs over
        them (efz_env.sb3.mixture calls the inner policy with others, then this)."""
        v = self.venv
        for k, i in enumerate(idx):
            i = int(i)
            if self.only is not None and not self.only[i]:
                continue
            if v._length[i] == 0:  # a new match
                self.logic.clear(i)
            o = self.logic.step(i, v.env.obs[i, 1])
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
                                adv.get('wake', 0.0), adv.get('jumpin', 0.0))
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
