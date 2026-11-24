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

Three more (docs/training-v2-log.md: a person's defence, from the user's games of 10 November,
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

- low: of those jump-ins, the share that are empty: the same walk and the same jump
  with no button in the air, and as it lands its fastest crouching normal that has to be
  guarded low (framedata.json; none for the character: a jump-in as before). The user's
  games of 19 November: against a riser that stands under a jump, lows after a jump hit
  7 times in 10 ("often hit by lower hit, especially when opponent approach in air but
  hit low").

Habits (docs/training-v2-log.md, "Adapting during a match": an opponent a read pays against):

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
  as the community's players are apart (docs/training-v2-log.md, "What people's habits look
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
- weak: the share of matches (of sets, in an environment with sets) in which one area of
  the profile is drawn to be its weak one, its knobs (WEAK_AREAS) at WEAK of the profile's
  values, the others as they are: an opponent strong everywhere but in one area, which
  area drawn afresh (docs/training-v2-log.md, "Playing to the opponent's weak areas": the
  best players are about 10/10 everywhere with a relative 8/10 somewhere). The area is
  drawn among those the profile has a knob above 0 in; with habits, after them.
- escape: the share of the times it is free on the ground in a corner, the agent on the
  open side within ESCAPE_NEAR pixels, that it jumps out over the agent: up-forward, a
  second jump forward at the top, then forward held (drawn once each time it comes free
  there; over its other habits, under the recovery). What a person does against pressure
  it cannot guard forever: how long the agent keeps it there is evaluate.py's `corner`.
- mash: the share of its guards after which, on the first step it is free on the ground,
  it presses its fastest normal that reaches the agent (pokes: three presses, every other
  step), blind: whatever the agent is doing (the user's, 22 November: "in order to learn
  how to handle pressure, it needs to understand how to pressure properly, especially at
  corners". A move pressed against the agent's pressure gets away 18 to 23% of the time
  for the league's opponents and about half the time for the user; people's own pressure
  lets 37% out. The league's opponents sit in a guard seven times in ten and nothing
  there makes a gap in a string cost). A string with no gap beats the button and one
  with a gap, or a walk back in, is hit by it: what a tight string is worth. Before a
  patient guard (the rest of its guards are patient's); under throw and the reversals.
- gap: the same button with a read: within GAP_AFTER steps of a guard of its, free on
  the ground and the agent in reach, the share of the gaps in the agent's pressure it
  presses its fastest normal into: the agent between two moves (walking or running back
  in: a reset), in a move's start with more steps left than the normal takes, or past a
  move's active steps (framedata.json's startup, counted from the step the action
  began); once a move or a stretch between two. Blind (mash) the button loses to the
  agent's strings three times in four; a person presses where the string has a hole
  (the user's buttons get away half the time). What a reset and a loose string cost.
- press: the share of its chances to press in which it does (docs/training-v2-log.md, "The
  league's pressure": the league's opponents make the agent guard 1-6 times a minute and
  1.2 times a string, a person 21-40 and 3-4, and nothing trained held it in a guard). A
  chance: itself free on the ground, the agent on the ground within PRESS_FAR pixels,
  not down, not in a hit reaction and not in a move of its own; once as that comes to be
  so, and every PRESS_AGAIN steps while it stays so. It goes in (a run from further than
  PRESS_WALK pixels, else a walk) and, PRESS_MARGIN pixels inside its reach, presses its
  string's first normal (pokes: its 2A). As each is guarded it presses, every other step until it starts, the
  next of PRESS_ORDER that the game cancels it into (motions.py --add pokes: tried on a
  guard), that the string has not had and that reaches from PRESS_PUSH pixels further
  (a guard pushes the two apart): 2A 5A 5B 2B 2C at the most, the 2C
  in PRESS_END of its strings. Its string over, it holds a crouching guard for one of
  PRESS_STAGGER's steps and the next chance is drawn at once: it stays on the agent. A
  normal of its own play that the agent guards (its okizeme's, a landing caught: where a
  person's strings begin, nine in ten on the agent's rising or its landing) is a chance
  too: the string goes on from it. It lets go on its way in when the agent is in a move
  within PRESS_CLEAR pixels or leaves the ground, and at any step when it is hit itself; when its move hits (its
  own play and its file's routes take the combo) or is recoil-guarded (reversal's and its
  own play's). Under throw, wake, bait and the reversal's inputs; over a patient guard
  that is not being held.
- object: the share of its chances to put an object out in which it does (the user's,
  21 November: the agent "sucks under pressure and handle objects"; half of the contacts
  on its guard in the user's games came with an object of the user's out, the league's
  Sayuri has one out a tenth of the time). Its moves: those that leave it free on the
  ground with an object of theirs out (motions.py --add objects: tried in the game), the
  one with the most cover its gauges allow, none that costs a level of power. A chance:
  itself free on the ground with no object of its own out, and the agent knocked down
  with the move's length (less OBJECT_LATE) left to lie, once a knockdown (on the first
  step it is free in it); or the agent
  on the ground OBJECT_FAR pixels away or more and in no move, every OBJECT_AGAIN steps.
  With press it then goes in behind it. Over press and a planned jump-in; under the
  rest. A character with no such move (Mishio, Mayu): none of it.
- meaty: the share of the agent's knockdowns in which it times its string's first normal
  (press's: its 2A) on the agent's rising (the user's strings, 22 November: 3.3 to 4.9 a
  minute begin there, of 6 to 10; press alone begins them on an agent standing free,
  where a person's almost never do). Drawn once a knockdown, on the first step it is free
  on the ground in it with no jump-in planned, and only where it can be in reach in time
  (MEATY_PACE pixels a step, more once its ways there have covered more: a full combo
  leaves the agent 280 pixels away, Kano covers 160 in a knockdown; those are its own
  play's): it goes into its reach (a run from further
  than PRESS_WALK pixels; a walk for a character whose run leaves the ground, seen once),
  waits there, and presses so that the normal touches MEATY_LATE steps after the agent's
  first free one (motions.py's knockdown lengths and --add pokes' steps from a press to
  its contact): what is left to the riser is a guard or an invincible move. Guarded, the
  string goes on as press's (with press at 0 too). It lets go when the agent is up before
  that or lies another way than the probe's, when it is not free itself, and when it is
  not in reach in time.
- antiair: the share of the agent's jumps at it that it anti-airs (the user's, 21
  November: the agent "relys heavily on air-to-air"; in the user's games the agent in the
  air loses 1,600 to 2,000 HP a minute to moves from the ground, to the league's
  opponents with combos 1,100, to those without 500: nothing trained made a jump cost).
  A chance: the agent in the air for ANTIAIR_SEE steps or more (what a person has seen),
  not in a hit reaction and not moving away, itself free on the ground, and the agent in
  a place it has a sure anti-air from (motions.py --add antiair: each of its normals and
  its 623A/623B tried in the game against an Ayu's jump-ins from every distance, empty,
  guarding and with each air button early and late, by where the jumper was; sure: it
  hit first in ANTIAIR_SURE of the tries from there and was hit first in ANTIAIR_LOSS at
  the most), on its way down (against an agent on its way up, which jumps again or
  dashes on, the same moves hit 19% of the time and 64% falling); once a jump, at the
  first such place. What the probe's Ayu did not do it learns in the game: each move's
  record against each kind of jump (the action the jumper is in and how fast it falls:
  at its top the agent still chooses its air button's step, and a late B out of a
  second jump beats moves that are sure at an empty one), and after ANTIAIR_PROVE tries
  a move that was hit first more than half as often as it hit is left out there (the
  next sure move from the place instead, or none), until ANTIAIR_AGAIN such chances
  have gone by and half the record is forgotten. Over press, object and a planned
  jump-in; under throw and the reversals' inputs.
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
        'escape', 'low', 'weak', 'press', 'object', 'meaty', 'antiair', 'mash', 'gap')
OBJECT_FAR = 160      # pixels: the agent this far, on the ground and in no move, is a chance for an object
OBJECT_AGAIN = 45     # steps from such a chance to the next
OBJECT_LATE = 10      # steps of its move that may be left when the agent rises
OBJECT_TRY = 10       # steps after its input in which the move is looked for
SELF_OBJECTS = tuple(range(72, 120, 6))  # efz_env_obs_name: self_obj0_active ... self_obj7_active
PRESS_FAR, PRESS_WALK, PRESS_MARGIN = 260, 110, 4  # pixels (press)
POKE_SHORT = 20       # pixels: a normal's reach in framedata.json over where it touches a guard from
PRESS_CLEAR = 150     # pixels: nearer than this a move of the agent's stops its way in
PRESS_PUSH = 18       # pixels a guard pushes the two apart before a string's next normal is out
PRESS_AGAIN = 30      # steps from a chance to press to the next
PRESS_STEPS = 80      # its way in at the longest
PRESS_CHAIN = 14      # steps a string's next normal is pressed for
PRESS_STRING = 70     # steps one of its normals may be out
PRESS_END = 0.4       # the share of its strings that may go on to a 2C
PRESS_ORDER = ('2A', '5A', '5B', '2B', '2C')  # a string's normals, in the order it takes them
PRESS_STAGGER = (0, 0, 6, 14)  # steps of a crouching guard between two of its strings
ANTIAIR_SURE = 0.7    # an anti-air: the share of its tries from a place in which it hit first, at the least
ANTIAIR_LOSS = 0.1    # ... and in which it was hit first, at the most
ANTIAIR_TRIES = 4     # ... of this many tries
ANTIAIR_SEE = 11      # steps the agent has been in the air before it is answered (a person's sight)
ANTIAIR_WATCH = 40    # steps after its press in which how it went is looked for
MASH_PRESSES = 3      # mash: its button this many times, every other step
MASH_WATCH = 30       # ... and the steps after in which who was hit first is looked for
GAP_AFTER = 45        # gap: steps after a guard of its in which a gap in the agent's pressure is looked for
GAP_ACTIVE = 3        # ... a move's steps after its start in which it is taken to be out
GAP_PRESSES = 2       # ... its button this many times, every other step
DASH_STOP = 0xb2      # tactics: the run's stop
ANTIAIR_PROVE = 6     # tries of a move at a kind of jump before its record there is judged
ANTIAIR_AGAIN = 40    # chances a move was left out for its record before half of the record is forgotten
ANTIAIR_FALL = (2.0, 5.0)  # a kind of jump: the jumper falls under 2 pixels a step (the top), under 5, faster
MEATY_LATE = 2        # a meaty's contact this many steps after the agent's first free step
MEATY_TOUCH = 5       # steps from a normal's press to its contact, where that was not tried
MEATY_PACE = 2.5      # pixels a step it is taken to cover on its way to the agent lying, until
MEATY_PACE_MOST = 8.0  # it has been seen to cover more (a run's: at the most this)
DASH = 0xa3           # tactics.DASH: the run
NORMALS = {0xc8: '5A', 0xc9: '5B', 0xca: '5C', 0xcc: '2A', 0xcd: '2B', 0xce: '2C'}  # their actions
LOW_PRESSES = 3   # an empty jump's low: the button this many times, every other step, from its landing
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
# weak's areas (areas.py's names for the opponent's skills) and their knobs, and the share
# of the profile's value an area's knobs keep where it is drawn to be the weak one.
WEAK_AREAS = {'okizeme': ('jumpin', 'bait', 'meaty'), 'okizeme defence': ('wake', 'blind'),
              'anti-pressure': ('reversal', 'patient', 'throw', 'mash', 'gap'), 'pressure': ('press', 'object')}
WEAK = 0.25


def parse(spec):
    """'rg=0.5,reversal=0.8,throw=0.3,damage=2' -> dict (left out: none)."""
    out = dict(rg=0.0, reversal=0.0, throw=0.0, damage=1.0, bait=0.0, patient=0.0, wake=0.0,
               jumpin=0.0, blind=0.0, crouch=CROUCH, habits=0.0, adapt=0.0, wide=1.0, tech=0.0,
               techway=0.0, techsafe=0.0, techhit=0.0, escape=0.0, low=0.0, weak=0.0, press=0.0,
               object=0.0, meaty=0.0, antiair=0.0, mash=0.0, gap=0.0)
    for part in filter(None, (spec or '').split(',')):
        k, v = part.split('=')
        if k not in out:
            raise ValueError(f'advantage {k}: {", ".join(KEYS)}')
        out[k] = float(v)
    return out


_MOTIONS = {}  # motions.json as read, by its time of change (megabytes: read once, not once a habit)


def motions(char):
    path = os.path.join(HERE, 'motions.json')
    stamp = os.path.getmtime(path)
    if _MOTIONS.get('stamp') != stamp:
        _MOTIONS.update(stamp=stamp, data=json.load(open(path)))
    return _MOTIONS['data'].get(char, {})


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


def low_normal(char):
    """The button of the character's fastest crouching normal that has to be guarded low
    (2A, 2B, 2C: the actions 0xcc, 0xcd, 0xce of every character; framedata.json's
    startup and guard), or None."""
    fd = json.load(open(os.path.join(HERE, 'framedata.json'))).get(char, {})
    lows = [(fd[a]['startup'], b) for a, b in (('0xcc', 'A'), ('0xcd', 'B'), ('0xce', 'C'))
            if fd.get(a, {}).get('guard') == 'low' and fd[a].get('startup')]
    return min(lows)[1] if lows else None


def pokes(char):
    """press's normals: (first, {name: (reach, action, touch)}, {name: [the names it
    cancels into on a guard]}) for 5A 5B 2A 2B 2C; touch: the steps from its press to its
    contact (meaty's). first: the string's first, its 2A (the first
    of PRESS_ORDER it has: the lows come in the string). The
    reach is the distance in pixels a guard is touched from, and the cancels those the
    game takes there (motions.py --add pokes: both tried in the game). Not probed: the
    crouching normals alone, framedata.json's reach less POKE_SHORT (the move's own box
    reaches 2 to 32 pixels further than it touches), each cancelled into the stronger."""
    fd = json.load(open(os.path.join(HERE, 'framedata.json'))).get(char, {})
    probed = motions(char).get('pokes')
    if probed:
        moves = {n: (m['reach'], int(m['action'], 16), int(m.get('touch') or MEATY_TOUCH))
                 for n, m in probed.items() if n in PRESS_ORDER}
        chains = {n: [x for x in probed['chains'].get(n, []) if x in moves] for n in moves}
    else:
        moves = {}
        for n, a in (('2A', 0xcc), ('2B', 0xcd), ('2C', 0xce)):
            m = fd.get(hex(a), {})
            if m.get('startup') and (m.get('reach') or 0) > POKE_SHORT:
                moves[n] = (m['reach'] - POKE_SHORT, a, int(m['startup']) + 1)
        chains = {n: [x for x in moves if x > n] for n in moves}
    first = next((n for n in PRESS_ORDER if n in moves), None)
    return first, moves, chains


def startups(char):
    """gap's read of the agent's moves: {action: (steps to its first active one, its steps
    in all)} from framedata.json, the ground moves with both known."""
    fd = json.load(open(os.path.join(HERE, 'framedata.json'))).get(char, {})
    return {int(a, 16): (int(m['startup']), int(m['steps'])) for a, m in fd.items()
            if m.get('startup') and m.get('steps')}


def antiairs(char):
    """antiair's table: ((pixels across, up a cell), {(across, up, falling, in):
    [(directions, button, action)]}): for each place of a jumper (motions.py --add
    antiair: the cell of the distance between the two and of the jumper's height, falling
    1 on its way down, in the action it is in: a jump, a second jump, an air move) the
    moves that hit an Ayu's jump-in first from there in ANTIAIR_SURE of ANTIAIR_TRIES
    tries or more and were hit first in ANTIAIR_LOSS at the most, the surest first; the
    places of a jumper on its way down only."""
    probed = motions(char).get('antiair')
    if not probed:
        return (16, 24), {}
    best = {}
    for name, m in probed['moves'].items():
        dirs, button = [int(d) for d in name[:-1]], name[-1]
        for key, x in m['cells'].items():
            n = sum(x)
            if n < ANTIAIR_TRIES or x[0] < ANTIAIR_SURE * n or x[2] > ANTIAIR_LOSS * n:
                continue
            score = (x[0] - 2 * x[2]) / n
            part = key.split(',')
            if len(part) < 4:
                continue  # (a table from before the jumper's action was counted)
            cell = tuple(int(c) for c in part[:3]) + (int(part[3], 16),)
            if not cell[2]:
                continue  # (on its way up it jumps again or dashes away: 19% hit there, 64% falling)
            best.setdefault(cell, []).append((score, dirs, button, int(m['action'], 16)))
    return tuple(probed['cell']), {c: [b[1:] for b in sorted(found, key=lambda b: -b[0])]
                                   for c, found in best.items()}


def object_moves(char):
    """object's moves: the character's moves that leave it free with an object of theirs
    out (motions.py --add objects), the most cover first, without its supers and its D
    moves: (directions, button, needs, action, steps), needs 'rf' for a C special."""
    out = []
    for m in motions(char).get('objects') or []:
        motion = m['motion']
        dirs, button = [int(d) for d in motion[:-1]], motion[-1]
        if len(dirs) >= 6 or button == 'D':
            continue
        out.append((dirs, button, 'rf' if button == 'C' else None, int(m['pattern'], 16),
                    m['steps']))
    return out


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
                 escape=0.0, low=0.0, weak=0.0, press=0.0, object=0.0, meaty=0.0,
                 antiair=0.0, mash=0.0, gap=0.0):
        self.wide, self.tech, self.escape = wide, tech, escape
        self.mash, self.gap = mash, gap
        self.gap_moves = startups(learner) if gap > 0 else {}
        self.object = object
        self.object_moves = object_moves(char) if object > 0 else []
        self.lying = knockdown_left(learner) if object > 0 or meaty > 0 else {}
        self.press, self.meaty = press, meaty
        self.antiair = antiair
        self.aa_cell, self.aa_table = antiairs(char) if antiair > 0 else ((16, 24), {})
        self.air_run = False  # its run leaves the ground (seen once: Sayuri's, Mayu's): it walks in
        self.pace = MEATY_PACE  # the pixels a step its ways to an agent lying have covered, at the most
        self.poke, self.pokes, self.chains = pokes(char) if press > 0 or meaty > 0 or mash > 0 or gap > 0 \
            else (None, {}, {})
        self.weak, self.weak_area = weak, None
        self.low = low
        self.low_button = low_normal(char) if low > 0 else None
        self.techway, self.techsafe, self.techhit = techway, techsafe, techhit
        self.base = dict(wake=wake, blind=blind, patient=patient, crouch=crouch, throw=throw,
                         reversal=reversal, jumpin=jumpin, bait=bait, press=press,
                         object=object, meaty=meaty, antiair=antiair, mash=mash,
                         gap=gap)
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
        if object > 0 and not self.object_moves:
            self.object = 0.0
            self.off.add('object')
        if press > 0 and not self.poke:
            self.press = 0.0
            self.off.add('press')
        if meaty > 0 and not (self.poke and self.lying):
            self.meaty = 0.0
            self.off.add('meaty')
        if antiair > 0 and not self.aa_table:
            self.antiair = 0.0
            self.off.add('antiair')
        if mash > 0 and not self.pokes:
            self.mash = 0.0
            self.off.add('mash')
        if gap > 0 and not (self.pokes and self.gap_moves):
            self.gap = 0.0
            self.off.add('gap')
        self.rng = np.random.default_rng(seed)
        self.habit_rng = np.random.default_rng([seed, 0x4ab17])  # (its own: the play's draws as without)
        self.resize(n)
        self.counts = dict(recoveries=0, rg=0, armed=0, reversals=0, reversals_started=0, reversal_hit=0,
                           reversal_hit_back=0, throw_chances=0, throws=0,
                           wake_reversals=0, baited=0, baited_hit_us=0, bait_punishes=0,
                           bait_punished=0, guards_ended=0, patient_holds=0, rises=0,
                           rise_reversals=0, rise_reversals_blind=0, rise_reversals_held=0, rise_reversals_started=0, rise_reversal_hit=0,
                           rise_reversal_hit_back=0, rise_patient=0, knockdowns=0,
                           jumpins_armed=0, jumpins=0, lowins=0, jumpin_hit=0, jumpin_guarded=0,
                           jumpin_hit_back=0, jumpin_late=0, adapted=0, weak_okizeme=0,
                           weak_okizeme_defence=0, weak_anti_pressure=0, weak_pressure=0,
                           press_chances=0, presses=0, press_pokes=0, press_guarded=0,
                           press_hit=0, press_rg=0, press_hit_back=0, press_let_go=0,
                           press_joined=0, object_chances=0, objects=0, objects_started=0,
                           meaty_chances=0, meaties=0, meaty_pokes=0, meaty_guarded=0,
                           meaty_hit=0, meaty_hit_back=0, meaty_whiff=0, meaty_late=0,
                           meaty_far=0, meaty_busy=0, meaty_apart=0,
                           antiair_chances=0, antiairs=0, antiair_hit=0, antiair_hit_back=0,
                           antiair_nothing=0, antiair_left_out=0,
                           mash_chances=0, mashes=0, mash_far=0, mash_hit=0, mash_hit_back=0,
                           mash_nothing=0, gap_chances=0, gaps=0, gap_hit=0, gap_hit_back=0,
                           gap_nothing=0)

    def resize(self, n):
        self.tech_on, self.tech_step = np.zeros(n, bool), np.zeros(n, int)
        self.tech_fwd, self.tech_hits = np.zeros(n, bool), np.zeros(n, bool)
        self.tech_rec, self.tech_left = np.zeros(n, bool), np.zeros(n, int)
        self.esc_step, self.esc_drawn = np.zeros(n, int), np.zeros(n, bool)
        self.tech_waited = np.zeros(n, bool)
        self.k = {name: np.full(n, 0.0 if name in self.off else float(v))
                  for name, v in self.base.items()}  # each environment's, this match
        self.weak_area = [None] * n  # each environment's weak area this match, or None
        for i in range(n if self.habits > 0 or self.weak > 0 else 0):  # (an evaluation's
            self.draw(i)                                                # matches: one each)
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
        self.object_wait = np.zeros(n, int)  # object: steps until its next chance in the open
        self.object_try = np.zeros(n, int)   # steps left for its move to start
        self.object_min = np.full(n, 8)      # the fewest objects of its own seen out this match
        self.object_act = np.full(n, -1)     # the move it put in
        self.object_down = np.zeros(n, int)  # steps the agent has been in its knockdown's part
        self.object_drawn = np.zeros(n, bool)  # this knockdown's chance drawn
        self.press_mode = np.zeros(n, int)  # press: 1 on its way in, 2 in its string
        self.press_step = np.zeros(n, int)  # steps on its way in, or since a normal was first pressed or began
        self.press_wait = np.zeros(n, int)  # steps until its next chance
        self.press_at = [None] * n          # the string's normal it is at (its name)
        self.press_had = [set() for _ in range(n)]  # the normals this string has had
        self.press_c = np.zeros(n, bool)    # this string may go on to a 2C
        self.press_run = np.zeros(n, bool)  # this way in is a run
        self.press_out = np.zeros(n, bool)  # that normal has started
        self.press_touch = np.zeros(n, bool)  # ... and was guarded
        self.press_guard = np.zeros(n, bool)  # the wait is a crouching guard's (after a string)
        self.press_seen = np.full(n, -1)    # its own play's normal a chance was drawn on
        self.press_frame = np.zeros(n, int)  # the agent's action's frame on the step before
        self.aa_y = np.zeros(n)              # antiair: the agent's height on the step before
        self.aa_d = np.zeros(n)              # ... and the distance between them
        self.aa_air = np.zeros(n, int)       # steps the agent has been in the air
        self.aa_drawn = np.zeros(n, bool)    # this jump's chance drawn
        self.aa_watch = np.zeros(n, int)     # steps left to see its anti-air's outcome
        self.mash_watch = np.zeros(n, int)   # mash: steps left to see its button's outcome
        self.gap_watch = np.zeros(n, int)    # gap: the same of its button in a gap
        self.gap_after = np.zeros(n, int)    # steps left after its last guard in which a gap is looked for
        self.gap_o = np.full(n, -1)          # the agent's action on the step before
        self.gap_since = np.zeros(n, int)    # ... and the steps it has been in it
        self.gap_drawn = np.zeros(n, bool)   # this action's (or this free stretch's) chance drawn
        self.aa_kind = [None] * n            # ... and the move and kind of jump it was pressed at
        self.aa_left = [set() for _ in range(n)]  # the moves left out in this jump for their record
        self.aa_record = {}                  # (move, jumper's action, fall): [hit, hit back, nothing, left out]
        self.meaty_drawn = np.zeros(n, bool)  # meaty: this knockdown's chance drawn
        self.meaty_from = np.zeros(n)         # the distance its way to the agent lying began at
        self.press_meaty = np.zeros(n, bool)  # the normal out is a meaty's, its outcome not seen yet
        self.press_raw = np.zeros(n, bool)  # the normal pressed is its way in's (from free), not a chain's

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
        if self.habits > 0:
            drawn = self.habit_rng.random() < self.habits
            table = HABITS if self.wide >= 1 or self.habit_rng.random() < self.wide else PEOPLE
        else:
            drawn, table = False, {}
        for name, v in self.base.items():
            if drawn and name in table:
                v = table[name][int(self.habit_rng.integers(len(table[name])))]
            self.k[name][i] = 0.0 if name in self.off else v
        self.weak_area[i] = None
        if self.weak > 0 and self.habit_rng.random() < self.weak:
            areas = [a for a, knobs in WEAK_AREAS.items() if any(self.k[k][i] > 0 for k in knobs)]
            if areas:
                area = areas[int(self.habit_rng.integers(len(areas)))]
                for k in WEAK_AREAS[area]:
                    self.k[k][i] *= WEAK
                self.weak_area[i] = area
                counts = getattr(self, 'counts', None)  # (not yet, while the constructor sizes)
                if counts is not None:
                    key = 'weak_' + area.replace(' ', '_').replace('-', '_')
                    counts[key] = counts.get(key, 0) + 1

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
        self.press_mode[i] = self.press_step[i] = self.press_wait[i] = 0
        self.object_wait[i] = self.object_try[i] = 0
        self.object_min[i], self.object_act[i] = 8, -1
        self.object_down[i], self.object_drawn[i] = 0, False
        self.press_out[i] = self.press_touch[i] = self.press_guard[i] = False
        self.press_seen[i] = -1
        self.meaty_drawn[i] = self.press_meaty[i] = False
        self.aa_y[i] = self.aa_d[i] = 0.0
        self.aa_air[i] = self.aa_watch[i] = self.mash_watch[i] = 0
        self.gap_watch[i] = self.gap_after[i] = self.gap_since[i] = 0
        self.gap_o[i], self.gap_drawn[i] = -1, False
        self.aa_drawn[i] = False
        self.aa_left[i].clear()
        self.press_at[i], self.press_had[i] = None, set()

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
        if self.antiair > 0:
            got = self.antiairing(i, v, a, o, rose, out is None)
            if got is not None:
                out = got
        if self.object > 0:
            got = self.objecting(i, v, a, o, out is None)
            if got is not None:
                out = got
        if self.press > 0 or self.meaty > 0:
            if out is None:
                out = self.pressing(i, v, a, o, rose)
            else:  # (another habit's input: the press let go)
                self.press_mode[i] = 0
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
        if self.mash_watch[i] > 0:  # its button after a guard: who was hit first
            self.mash_watch[i] -= 1
            if rose[0] or rose[1]:
                self.counts['mash_hit' if rose[0] else 'mash_hit_back'] += 1
                self.mash_watch[i] = 0
            elif self.mash_watch[i] == 0:
                self.counts['mash_nothing'] += 1
        mashed = False
        if self.mash > 0 and self.guarding[i] and not guarding and a in FREE \
                and v[SELF_AIRBORNE] < 0.5 and not self.queue[i]:
            # a guard of its ended and it is free: its fastest normal that reaches, blind
            self.counts['mash_chances'] += 1
            if self.rng.random() < self.k['mash'][i]:
                d = abs(float(v[DX])) * 640
                near = [(m[2], n) for n, m in self.pokes.items() if d <= m[0]]
                if near:
                    name = min(near)[1]
                    way = int(name[0])
                    self.queue[i] = [(way, name[1]), (way, '')] * MASH_PRESSES
                    self.counts['mashes'] += 1
                    self.mash_watch[i] = MASH_WATCH
                    self.patience[i] = 0
                    mashed = True
                else:
                    self.counts['mash_far'] += 1
        if self.gap > 0:
            mashed = self.gapping(i, v, a, o, rose, guarding, mashed) or mashed
        if self.patient > 0 and self.guarding[i] and not guarding:  # a guard of its ended
            self.counts['guards_ended'] += 1
            if mashed:
                pass
            elif self.patience[i] > 0:  # guarding patiently still: as long again
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

    def gapping(self, i, v, a, o, rose, guarding, busy):
        """gap: within GAP_AFTER steps of a guard of its, free on the ground and the agent
        on the ground in reach of a normal of its: its fastest such normal into the queue
        where the agent cannot hit it first (between two moves, in a move's start with
        more steps left than the normal takes, or past its active steps), once a move of
        the agent's or a stretch between two. True: pressed."""
        if self.gap_watch[i] > 0:  # its button: who was hit first
            self.gap_watch[i] -= 1
            if rose[0] or rose[1]:
                self.counts['gap_hit' if rose[0] else 'gap_hit_back'] += 1
                self.gap_watch[i] = 0
            elif self.gap_watch[i] == 0:
                self.counts['gap_nothing'] += 1
        between = o in FREE or o in (DASH, DASH_STOP)
        if o != self.gap_o[i]:
            if not (between and (self.gap_o[i] in FREE or self.gap_o[i] in (DASH, DASH_STOP))):
                self.gap_drawn[i] = False  # (a new move, or the stretch after one)
            self.gap_o[i], self.gap_since[i] = o, 0
        else:
            self.gap_since[i] += 1
        if guarding:
            self.gap_after[i] = GAP_AFTER
            return False
        if self.gap_after[i] <= 0:
            return False
        self.gap_after[i] -= 1
        if busy or self.gap_drawn[i] or self.queue[i] or a not in FREE or v[SELF_AIRBORNE] > 0.5 \
                or v[OPP_AIRBORNE] > 0.5 or v[OPP_HITSTUN] > 0.5 or v[OPP_GUARDING] > 0.5:
            return False
        d = abs(float(v[DX])) * 640
        near = [(m[2], n) for n, m in self.pokes.items() if d <= m[0]]
        if not near:
            return False
        touch, name = min(near)
        if not between:
            move = self.gap_moves.get(o)
            if move is None:
                return False
            since = int(self.gap_since[i])
            if since < move[0]:
                if move[0] - since <= touch:
                    return False  # (it comes out first)
            elif since < move[0] + GAP_ACTIVE:
                return False  # (out)
        self.gap_drawn[i] = True
        self.counts['gap_chances'] += 1
        if self.rng.random() >= self.k['gap'][i]:
            return False
        way = int(name[0])
        self.queue[i] = [(way, name[1]), (way, '')] * GAP_PRESSES
        self.counts['gaps'] += 1
        self.gap_watch[i] = MASH_WATCH
        self.patience[i] = 0
        return True

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
                if self.low_button and self.rng.random() < self.low:
                    # the same jump, empty, and a low as it lands
                    seq = ([(p.get('way', 9), '')] * pre + [(5, '')] * self.jump['air']
                           + [(2, self.low_button), (2, '')] * LOW_PRESSES)
                    self.counts['lowins'] += 1
                    self.jump_watch[i] = pre + self.jump['air'] + 24
                else:
                    seq = ([(p.get('way', 9), '')] * pre + [(5, '')] * (press - pre)
                           + [(5, p['button'])]
                           + [(5, '')] * max(0, pre + self.jump['air'] - press))
                    self.jump_watch[i] = p['contact'] + 12
                self.counts['jumpins'] += 1
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

    def antiairing(self, i, v, a, o, rose, free_hand):
        """antiair: the first step of its anti-air at the agent jumping in (the rest into
        the queue), or None. free_hand: no other habit has this step."""
        y, d = float(v[OPP_Y]), abs(float(v[DX])) * 640
        before = self.aa_y[i]
        falling, closing = y > before, d <= self.aa_d[i] + 0.5
        self.aa_y[i], self.aa_d[i] = y, d
        if self.aa_watch[i] > 0:  # its anti-air: who was hit first
            self.aa_watch[i] -= 1
            if rose[0] or rose[1]:
                self.counts['antiair_hit' if rose[0] else 'antiair_hit_back'] += 1
                self.aa_record[self.aa_kind[i]][0 if rose[0] else 1] += 1
                self.aa_watch[i] = 0
            elif self.aa_watch[i] == 0:
                self.counts['antiair_nothing'] += 1
                self.aa_record[self.aa_kind[i]][2] += 1
        if v[OPP_AIRBORNE] < 0.5 or v[OPP_HITSTUN] > 0.5 or o in THROWN:
            self.aa_air[i], self.aa_drawn[i] = 0, False
            self.aa_left[i].clear()
            return None
        self.aa_air[i] += 1
        if self.aa_drawn[i] or self.aa_air[i] < ANTIAIR_SEE or not closing or not free_hand \
                or a not in FREE or v[SELF_AIRBORNE] > 0.5:
            return None
        fall = (y - before) * 480
        fall = 0 if fall < ANTIAIR_FALL[0] else 1 if fall < ANTIAIR_FALL[1] else 2
        move = None
        for found in self.aa_table.get((int(d // self.aa_cell[0]),
                                        int(-y * 480 // self.aa_cell[1]), int(falling), o), ()):
            kind = (found[2], o, fall)
            rec = self.aa_record.setdefault(kind, [0, 0, 0, 0])
            if sum(rec[:3]) >= ANTIAIR_PROVE and 2 * rec[1] > rec[0]:
                if kind not in self.aa_left[i]:  # (its record against this kind of jump: left out, counted once a jump)
                    self.aa_left[i].add(kind)
                    self.counts['antiair_left_out'] += 1
                    rec[3] += 1
                    if rec[3] >= ANTIAIR_AGAIN:
                        rec[:] = [rec[0] // 2, rec[1] // 2, rec[2] // 2, 0]
                continue
            move = found
            break
        if move is None:
            return None
        self.aa_drawn[i] = True  # (once a jump: the first place it has a sure move from)
        self.counts['antiair_chances'] += 1
        if self.rng.random() >= self.k['antiair'][i]:
            return None
        dirs, button, _ = move
        self.counts['antiairs'] += 1
        self.aa_watch[i], self.aa_kind[i] = ANTIAIR_WATCH, kind
        seq = [(way, '') for way in dirs[:-1]] + [(dirs[-1], button)]
        self.queue[i] = seq[1:]
        return seq[0]

    def objecting(self, i, v, a, o, free_hand):
        """object: the first step of a move that puts an object out (the rest into the
        queue), or None. free_hand: no other habit has this step."""
        n = int(sum(v[k] > 0.5 for k in SELF_OBJECTS))
        self.object_min[i] = min(self.object_min[i], n)
        if self.object_try[i] > 0:  # did it start
            self.object_try[i] -= 1
            if a == self.object_act[i]:
                self.counts['objects_started'] += 1
                self.object_try[i] = 0
        if self.object_wait[i] > 0:
            self.object_wait[i] -= 1
        if o in self.lying:  # the agent knocked down: the steps into this part of it
            self.object_down[i] = 0 if o != self.prev_opp[i] else self.object_down[i] + 1
        else:
            self.object_drawn[i] = False
        if not free_hand or a not in FREE or v[SELF_AIRBORNE] > 0.5 or n > self.object_min[i]:
            return None
        if o in self.lying:  # once a knockdown, on the first step it is free in it
            if self.object_drawn[i]:
                return None
            self.object_drawn[i] = True
            part = self.lying[o]
            left = part[min(int(self.object_down[i]), len(part) - 1)]
        elif (self.object_wait[i] == 0 and abs(float(v[DX])) * 640 >= OBJECT_FAR
              and v[OPP_AIRBORNE] < 0.5 and o < FIRST_OWN and o not in DOWN
              and v[OPP_HITSTUN] < 0.5):
            left = 999
            self.object_wait[i] = OBJECT_AGAIN
        else:
            return None
        move = None
        for dirs, button, needs, act, steps in self.object_moves:
            if steps - OBJECT_LATE > left:
                continue
            if needs == 'rf' and v[SELF_RF] < 0.5 and v[SELF_BLUE] < 0.5:
                continue
            move = (dirs, button, act)
            break
        if move is None:
            return None
        self.counts['object_chances'] += 1
        if self.rng.random() >= self.k['object'][i]:
            return None
        dirs, button, act = move
        self.counts['objects'] += 1
        self.object_act[i], self.object_try[i] = act, len(dirs) + OBJECT_TRY
        self.jumping[i] = False  # (in the place of a jump-in planned on this knockdown)
        seq = [(d, '') for d in dirs[:-1]] + [(dirs[-1], button), (dirs[-1], '')]
        self.queue[i] = seq[1:]
        return seq[0]

    def press_over(self, i, wait, guard=False):
        self.press_mode[i], self.press_wait[i], self.press_guard[i] = 0, wait, guard
        self.press_meaty[i] = False
        return None

    def press_next(self, i, name, d):
        """The normal a string goes on with from `name`, guarded at d pixels: the first of
        PRESS_ORDER it cancels into, has not had and reaches (PRESS_PUSH further: the guard
        pushes them apart meanwhile), or None."""
        for n in PRESS_ORDER:
            if n in self.chains.get(name, ()) and n not in self.press_had[i] \
                    and d + PRESS_PUSH <= self.pokes[n][0] and (self.press_c[i] or n != '2C'):
                return n
        return None

    def press_go(self, i, name, raw):
        """`name` pressed: the string's next normal, or its first (raw: from free)."""
        self.press_mode[i], self.press_step[i], self.press_at[i] = 2, 0, name
        self.press_out[i] = self.press_touch[i] = False
        self.press_raw[i] = raw
        if not raw:  # (a string's next: the meaty before it was guarded)
            self.press_meaty[i] = False
        self.press_had[i].add(name)
        return (int(name[0]), name[1])

    def pressing(self, i, v, a, o, rose):
        """press and meaty: its control on this step (its way in, a normal of its string,
        the guard between two strings, its wait by the agent lying), or None."""
        mode = self.press_mode[i]
        frame, self.press_frame[i] = self.press_frame[i], int(round(float(v[OPP_ACT_FRAME])))
        # A contact on the agent's guard: it starts, or starts again (tactics.Side.contact)
        touch = o in GUARDS and (o != self.prev_opp[i] or self.press_frame[i] < frame)
        if v[SELF_HITSTUN] > 0.5 or a in DOWN or a in THROWN:  # hit itself: let go
            if mode:
                self.counts['press_hit_back'] += 1
            if self.press_meaty[i]:
                self.counts['meaty_hit_back'] += 1
            return self.press_over(i, PRESS_AGAIN)
        d = abs(float(v[DX])) * 640
        there = (v[OPP_AIRBORNE] < 0.5 and o not in DOWN and o not in THROWN
                 and v[OPP_HITSTUN] < 0.5 and d <= PRESS_FAR)
        if a == DASH and v[SELF_AIRBORNE] > 0.5:
            self.air_run = True  # (no normal on the ground comes out of it)
        if mode == 0:
            if self.press_wait[i] > 0:
                self.press_wait[i] -= 1
                return (1, '') if self.press_guard[i] and a in FREE and v[SELF_AIRBORNE] < 0.5 else None
            mode = self.press_chance(i, v, a, o, d, there, touch)
            if mode is None or mode == 0:
                return None
            if mode == 2:  # (its own play's normal guarded: the string's next, pressed)
                return (int(self.press_at[i][0]), self.press_at[i][1])
        self.press_step[i] += 1
        k = int(self.press_step[i])
        if mode == 3:  # by the agent lying: into its reach, its normal timed on the rise
            if o not in self.lying or a >= FIRST_OWN or a in GUARDS or v[SELF_AIRBORNE] > 0.5:
                # (the agent is up already or lies another way, or itself not free)
                self.counts['meaty_late' if o not in self.lying else 'meaty_busy'] += 1
                return self.press_over(i, 0)
            part = self.lying[o]
            left = part[min(int(self.agent_k[i]), len(part) - 1)]
            reach, _, lead = self.pokes[self.poke]
            near = d <= reach - PRESS_MARGIN
            if k >= 15 and not near:  # (what its way covers a step: the next chances' measure)
                self.pace = max(self.pace, min(MEATY_PACE_MOST, (self.meaty_from[i] - d) / k))
            if left + MEATY_LATE <= lead:  # pressed now, it touches as the agent can be touched
                if not near:
                    self.counts['meaty_far'] += 1
                    return self.press_over(i, 0)
                self.counts['meaty_pokes'] += 1
                out = self.press_go(i, self.poke, True)
                self.press_meaty[i] = True
                return out
            if near:
                return (5, '')
            # (66, the run: forward let go first, its own play may be holding it)
            return (5, '') if self.press_run[i] and k in (1, 3) else (6, '')
        if mode == 1:  # on its way in
            if not there or (o >= FIRST_OWN and d <= PRESS_CLEAR) or k > PRESS_STEPS \
                    or not (a in FREE or a == DASH) or v[SELF_AIRBORNE] > 0.5:
                self.counts['press_let_go'] += 1
                return self.press_over(i, PRESS_AGAIN)
            if d <= self.pokes[self.poke][0] - PRESS_MARGIN:
                self.counts['press_pokes'] += 1
                return self.press_go(i, self.poke, True)
            return (5, '') if self.press_run[i] and k == 2 else (6, '')  # (66: the run)
        name = self.press_at[i]
        way, button, act = int(name[0]), name[1], self.pokes[name][1]
        if rose[0]:  # it hit: the combo is its own play's and its routes'
            self.counts['press_hit'] += 1
            if self.press_meaty[i]:
                self.counts['meaty_hit'] += 1
            return self.press_over(i, PRESS_AGAIN)
        if o in RG:
            self.counts['press_rg'] += 1
            return self.press_over(i, PRESS_AGAIN)
        if not self.press_out[i]:  # pressed, not started yet: the button every other step
            if a == act:
                self.press_out[i], self.press_touch[i], self.press_step[i] = True, False, 0
            elif k > PRESS_CHAIN or not ((a in FREE or a == DASH) if self.press_raw[i] else a in NORMALS):
                return self.press_over(i, int(self.rng.choice(PRESS_STAGGER)), True)
            else:
                return (way, '' if k % 2 else button)
        if a != act or k > PRESS_STRING:  # its string over: a guard, and the next chance
            if self.press_meaty[i]:
                self.counts['meaty_whiff'] += 1
            return self.press_over(i, int(self.rng.choice(PRESS_STAGGER)), True)
        if touch and not self.press_touch[i]:
            self.press_touch[i] = True
            self.counts['press_guarded'] += 1
            if self.press_meaty[i]:
                self.counts['meaty_guarded'] += 1
                self.press_meaty[i] = False
            nxt = self.press_next(i, name, d)
            if nxt is not None:
                return self.press_go(i, nxt, False)
        return (1, '')

    def press_chance(self, i, v, a, o, d, there, touch):
        """With nothing of its own going on: the chance this step is, drawn. 3: a meaty on
        the agent's knockdown; 2: its own play's normal guarded, the string's next pressed;
        1: its way in begins; 0 or None: nothing."""
        grounded = v[SELF_AIRBORNE] < 0.5
        idle = a in FREE and grounded and self.patience[i] == 0 and not self.jumping[i]
        if self.meaty > 0:  # the agent's knockdown: once, on the first step it is free in it
            if o not in self.lying:
                self.meaty_drawn[i] = False
            elif not self.meaty_drawn[i] and idle:
                self.meaty_drawn[i] = True
                part = self.lying[o]
                left = part[min(int(self.agent_k[i]), len(part) - 1)]
                reach, _, lead = self.pokes[self.poke]
                if d - (reach - PRESS_MARGIN) > self.pace * max(0, left + MEATY_LATE - lead):
                    self.counts['meaty_apart'] += 1  # (not to be reached in time: its own play's)
                else:
                    self.counts['meaty_chances'] += 1
                    if self.rng.random() < self.k['meaty'][i]:
                        self.counts['meaties'] += 1
                        self.press_had[i] = set()
                        self.press_c[i] = self.rng.random() < PRESS_END
                        self.press_mode[i], self.press_step[i] = 3, 0
                        self.press_run[i] = d > PRESS_WALK and not self.air_run
                        self.meaty_from[i] = d
                        return 3
        if self.press <= 0:
            return None
        if a not in NORMALS:
            self.press_seen[i] = -1
        elif a != self.press_seen[i] and touch and grounded:
            self.press_seen[i] = a  # its own play's normal, guarded: the string goes on from it
            self.press_had[i] = {NORMALS[a]}
            self.press_c[i] = self.rng.random() < PRESS_END
            nxt = self.press_next(i, NORMALS[a], d)
            if nxt is None:
                return None
            self.counts['press_chances'] += 1
            if self.rng.random() >= self.k['press'][i]:
                return self.press_over(i, PRESS_AGAIN)
            self.counts['presses'] += 1
            self.counts['press_joined'] += 1
            self.press_go(i, nxt, False)
            return 2
        if not (there and idle and o < FIRST_OWN):
            return None
        self.counts['press_chances'] += 1
        if self.rng.random() >= self.k['press'][i]:
            return self.press_over(i, PRESS_AGAIN)
        self.counts['presses'] += 1
        self.press_had[i] = set()
        self.press_c[i] = self.rng.random() < PRESS_END
        self.press_mode[i], self.press_step[i] = 1, 0
        self.press_run[i] = d > PRESS_WALK and not self.air_run
        return 1

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
                                a.get('techhit', 0.0), a.get('escape', 0.0),
                                a.get('low', 0.0), a.get('weak', 0.0), a.get('press', 0.0),
                                a.get('object', 0.0), a.get('meaty', 0.0),
                                a.get('antiair', 0.0), a.get('mash', 0.0),
                                a.get('gap', 0.0))
        self.logic = logic(adv, seed)
        self.alt = logic(alt, seed + 7919) if alt is not None else None
        self.venv = None
        self.forced = {}    # this step's advantages' inputs, by environment (their bytes)
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
        # An inner opponent that is an agent file (native_agent.NativeOpponent) writes its
        # control bytes through the environment's opponent_controls, after these actions:
        # the advantages' inputs are written over them again, last.
        self.forced = {}
        if hasattr(venv, 'opponent_controls'):
            venv.opponent_controls.append(_Last(self.controls))
        if hasattr(self.inner, 'attach'):  # (the file's players, in this opponent's matches)
            if hasattr(self.inner, 'mine'):
                self.inner.mine = self.mine
            self.inner.attach(venv)

    def controls(self, out):
        for i, byte in self.forced.items():
            out[i] = byte

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
            if logic is not None and (logic.habits > 0 or logic.adapt > 0 or logic.weak > 0) and \
                    (fresh is None or fresh[i]):
                logic.draw(i)
            if v.extra is not None:
                v.extra[i, 0] = logic.told(i) if logic is not None else 0.0

    def __call__(self, obs, idx):
        inner = self.inner(obs, idx) if getattr(self.inner, 'takes_index', False) else self.inner(obs)
        return self.post(np.asarray(inner).copy(), idx)

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
            self.forced.pop(i, None)
            if o is not None:
                actions[k] = self.index[o]
                self.forced[i] = int(self.table.table[self.index[o]])
        return actions


class _Last:
    """An opponent_controls hook that runs after the others (efz_env.sb3: `order`)."""
    order = 1

    def __init__(self, hook):
        self.hook = hook

    def __call__(self, out):
        self.hook(out)


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
                                adv.get('techhit', 0.0), adv.get('escape', 0.0),
                                adv.get('low', 0.0), adv.get('weak', 0.0), adv.get('press', 0.0),
                                adv.get('object', 0.0), adv.get('meaty', 0.0),
                                adv.get('antiair', 0.0), adv.get('mash', 0.0),
                                adv.get('gap', 0.0))
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
