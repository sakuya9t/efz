"""The module 'rise' (python/efz_env/modules.py; evaluate.py --p1-module, play.py
--module): the agent's own wake-up, a move or a guard, by how each went in this match.

    rise[:prior=4,move=150,still=-165,super=-400,temperature=75,window=240,carry=false]

Why (the user's, 17 November: "risk management ... It should pay more attention when the
other side hit back"; docs/training-v2-log.md, "The league by the three measures"). Against
the user most of the agent's raw risky moves were wake-up reversals (23 of its 27 raw
236236A, 12 of 15 raw 641236A, 10 of 15 raw 623B), four in five whiffed or were guarded
and three in four of those were punished: about 1,100 HP a match. The league teaches the
habit: its opponents attack the agent's rising, and a reversal that is waited out is
rare there (the `crowd` profile guards 8% of them). People's own wake-up reversal pays
(Ayu players in the community's replays: 10% of their wake-ups, 527 HP ahead for it; a
guard, 56%, 168 behind) because it is used one rising in ten; the agent's, at one in
four and at every knockdown of a match alike, is read by anyone who looks. Training
does not make the policy use what it saw earlier in a match (the told-habits
experiment), so a module does: a person who is punished for the same wake-up move twice
stops, and starts again when the guard is what gets opened.

What it does. It keeps two accounts for the match, from what the agent sees: the HP
swing (the opponent's HP lost less its own, over `window` steps after it sees itself up,
or until it sees itself down again or the round ends) of the wake-ups it rose with a
move on (a move of its own seen within REVERSAL steps of rising), and of the others.
Each account's worth is its mean over a prior (`move`, `still` HP; `prior` wake-ups'
weight: people's and the league's numbers). When it sees itself knocked down it draws:
with the probability 1 / (1 + exp((worth of a move - worth of the others) /
temperature)) this rising is guarded through. A rising guarded through: while it sees
itself down, the policy's own action if that is a guard or a jump back (a back direction,
no button), else a guard, standing if it sees the opponent in the air and crouching
otherwise. The agent sees `delay` steps late, so this covers the first `delay` steps
after it is up, which is where a wake-up move would come out; then its own play again.

With the priors as they are nothing changes until something was punished: 1.5% of the
risings are guarded through at a match's start, 42% after one wake-up move that cost a
combo (1,300 HP), 90% after two; a guard that is opened as often brings the move back.

The one move. The class is not the leak: in the league a wake-up move pays as a class
(the module's own accounts against Ikumi's `exploiter18`: +174 a rising with a move, -77
without) and one move in it does not: the level-one super 236236A, 88 raw uses in 64
matches there, nine in ten of them wake-up ones, at -960 HP each; -166 to -494 against
the others measured, -625 against the user; people's wake-up supers are 641236A. So it
has an account of its own (`super`, the prior -400), and the module sees it coming: its
own play's inputs while it sees itself down are the module's to draw and play, and when
they hold two down-to-forward sweeps within RECENT steps and then press a button that
makes the level-one super (A, or any with one bar: the agent's is 236236C), this rising
is guarded through with the probability the super's account gives against the others'
(96% at a match's start; a super that hit brings it down).

Measured (Ikumi's `exploiter18`, 64 matches): with both the class's draw and the
super's, 93 of 103 supers seen coming were stopped (raw wake-up ones 79 to 13) and the
wins did not move (65.6% for 68.8%): the class's draw guarded another fifth of the
risings through and took the wake-up moves that pay (641236A halved) with it. So the
class's draw is off unless asked for (`moves=true`); the super's is what the module does.

The guard by sight (`guard=true`). The league's opponents leave the agent's rising
alone and a person does not (docs/training-v2-log.md, "The agent's own rising against an
attacker who is on it"): a move of the attacker's is out as the agent rises on 16-36% of
its knockdowns against eight of the eleven `exploiter18`s, 75% against the user, 56-58%
in the community's replays. Against the user's it lost 427 HP a knockdown (-65 where the
user was not on it): a move of its own into the meaty (a fifth of them, 697 lost each),
and a guard that is not one (of the 26 air attacks that hit it rising, 25 were in its
view, 14 steps late as it is, and it held a standing guard under 7). The strongest Ayu
player of the replays guards 53% of their risings and loses 13 HP a knockdown.
So, with `guard`: a rising on which it sees the attacker on it (while it sees itself
down: the attacker in a move of its own, or in the air within `fly` pixels; or merely
within `near`, which is off: measured with 130, an opponent that stands close to throw,
Ikumi's `exploiter18`, had every rising guarded and the wins went from 89% to 80%
through the game's code) is guarded through with a probability read from the match: the share of the risings it
has seen in it at which the attacker was in a move of its own as the agent saw itself up
(the measure above; what the agent did has no part in it), over a prior (`meaty`, 0.56,
the community's, counting as `met_prior` risings, 2); none are guarded at the rate `low`
(0.3), all at `high` (0.6), in a line between: 87% at a match's start, none after two
risings left alone, all against an attacker who is there each time. Two builds before
this one kept accounts of HP instead (such risings guarded through, against those left to
its own play): eleven risings a match at a thousand HP either way say nothing in time,
and "the attacker on it" is seen at nine knockdowns in ten (the move that knocked it down
is one), so the guard went on at two risings in three against everyone: level over the
eleven `exploiter18`s, and 10 points of its HP more lost against the three that leave its
rising alone (Ikumi's, which comes to throw: 51% to 61%). The guard is held by sight: standing while it sees the
attacker in the air, else its own play's guard, else crouching; no button and no jump.
`hold` (steps, 0: off): a rising guarded through goes on guarding by sight after it sees
itself up, for at most that many steps, while the attacker goes on (in a move of its own
or in the air within `fly`), until it has seen `gap` steps (8) without that, itself hit,
or the round over: against the user 97% of the hits it took 41-96 steps after a rising
came with a button of its own pressed in the 14 steps before.

`land` (false): under an attacker it sees in the air the standing guard is held only
until the attacker's landing has passed, then the crouching one: the landing predicted
from the height and the fall in the view (steps_to_land), since the view is `delay` steps
old and an empty jump's low comes 4 steps or more after the landing (the user's games of
19 November: lows after a jump hit the rising agent 7 times in 10; "often hit by lower
hit, especially when opponent approach in air but hit low"). On the user's 1,712 flights
the crouch then begins within 3 steps of the landing in 98% (14 steps after it before),
and 7.5% of the steps under a flight are crouched 3 steps or more early (a flight that
changed course after it was seen). `sight` (0: the agent's delay): the steps late the
guard's height is chosen from, where fewer is this one reaction made faster (the user, 19
November: "we can slightly tune the 14f ... the best competitive players' reaction times
are 120-170ms": 8 to 11 steps); it needs the host's `seen` views.

`recoil` (steps, 0: off): the answer to a recoil guard. When it sees (its view, `delay`
steps late) its opponent enter a recoil guard within `recoil_near` pixels (240) while it
sees itself in a move of its own, its inputs are the module's for at most that many
steps: nothing held until `recoil_press` steps (22) after the recoil guard, at least one
step, then the guard by sight, as on a rising: until it sees itself hit or down, the
round over, or the opponent free on the ground for `recoil_gap` steps (8: it let the
chance go, or its string is over). A guard of its own that it sees touched starts the
count of steps again: the guard goes on through the opponent's string (`recoil_let`,
false; true: its own play's again from the first guard it sees touched, as the first
builds were: of 107 counters guarded it then hit after 5, was hit after 22, most of them
in a guard it had let go, and neither after 80).

Whether it answers is read from the match, as its guard on rising is: the share of this
opponent's recoil guards of its moves after which it saw the opponent in a move of its
own (or itself hit) within `recoil_soon` steps (34: the freeze and twelve more), over a
prior (`recoil_counter`, 0.6, counting as `recoil_prior` recoil guards, 2); none are
answered at the rate `recoil_low` (0.3), all at `recoil_high` (0.6), in a line between.
So the first is answered, an opponent that counters at once goes on being answered, and
one whose recoil guards carry no threat is pressed on after two of them. Why: the level-4
CPU's counter starts 22 steps after its recoil guard at the median and the scripted
drill's 27, Nayuki's `exploiter18`'s 61; answered every time, the agent's next attack
after a recoil guard lands 9% of the time against her for 32% (24 traced matches each)
and it is hit 13% for 26%: against her the guard gives away more than it saves.

What follows its own recoil guard (`recoil_punish`: control bytes, e.g. 0x1,0x4,0x5,0x25
for 623B; none: nothing). When it sees itself in a recoil guard on the ground with the
opponent in a move of its own on the ground within `recoil_punish_near` pixels (48), the
guard goes on and then these inputs are played so that the last lands
`recoil_punish_at` steps (22) after its recoil guard: the first step the game takes a
move out of the pose, 11 after it sees it. Measured the same way (Ayu's recoil guard of
a 2A that the other side goes on pressing, or follows with a guard): a 2A or a 2B pressed
there is hit by the opponent's kept chain at step 23; 623A too; 623B (0xfc) with its
button at steps 20 to 23 hits for 745 HP and a knockdown either way, at 24 it is too
late. The answer's guard won nothing by itself (the drills, 20 November): this is what
the guard is for. The distance is the move's: in 24 traced matches with 80 pixels it hit
22 of 24 times from under 40 pixels, 8 of 12 from 40 to 55 and 3 of 15 from further, and
a miss was punished 15 times of 17.

The timing is the game's, measured frame by frame in the headless game (Ayu's 2A, 2C, 5B,
5C recoil-guarded, the counter a 2A at every delay):

- both players are frozen for about 20 steps, and no counter lands before step 23 (the
  level-4 CPU's first; a 2A pressed as early as the game takes it lands at 25);
- a back press from neutral makes the guards of the next 9 steps recoil guards, and a
  second press does not count for 18 steps after the first;
- the player whose move was recoil-guarded can recoil-guard the counter even from its
  move's recovery (m_canRecoilCounter, until its next move starts), where it has no plain
  guard until the move has ended (29 steps after the recoil guard for a 2A, 40 for a 2C).

So a press before step 15 has run out when the first counter lands, and one press at 22
covers the counters that land 23 to 31 steps after; from then the plain guard, where the
move has ended.

The chain it has pressed already (`recoil_clear`, true). A button pressed during a move
is kept (m_bufferedPress: the last one, with no end) and comes out as the freeze ends, 19
steps after the recoil guard: that ends the recoil counter and puts the agent in a move's
start as the counter lands. A later press takes the kept one's place, and an A does not
chain from a normal of the same stance or from a stronger one. So the second step of the
answer presses A (2A where the move it saw recoil-guarded was 2A) when that move was a
ground normal: a 5B kept after a 5A, a 5C after a 5B, a 2C after a 2A all stay in
(measured the same way). Not after a motion: an A after 236 is 236A (a traced 5C went
into a special by this press), so the press is made only when its own last
`recoil_steady` inputs (12, or as many as it keeps) all hold one direction.

Why (the recoil drill, and the level-4 CPU with its combos; 24 traced matches against
Kano's `exploiter18` with rg=0.3,reversal=0.8, the agent's side): it is the one hit after
51% of its recoil-guarded moves (98 of 193; 62% against the CPU), the hit lands 32 steps
after the recoil guard at the median (28 at the tenth percentile), a move of its own
comes out as the freeze ends after 40% of them, and it guards the counter after 19%. A
first build that pressed back as soon as it saw the recoil guard (step 12) guarded 71
counters of 172, one of them with a recoil guard, and was hit as often in the move that
was recoil-guarded (46 times for 14): the press had run out. With the press at 23: 107
counters of 184 guarded, 66 with a recoil guard, hit after 28%.

`press` (steps, 0: off): the guard under pressure. The league's opponents do not hold the
agent in a guard and a person does (the user's games of 21 November, "sucks under
pressure"): against them it guards 4 to 7 times a minute, a move pressed after a guard
gets away a third of the time and is hit 14 to 19%, a jump out is hit 16 to 18%; against
the user it guards 13 to 18 times a minute, the move is hit 42% and the jump 27% (2% get
away), and three quarters of the 1,890 HP a minute it lost under the user's pressure it
lost out of its guard (in the air 860, in a move 605; opened in its guard 300), 26 to 60
steps after the last guard. So a string (a guard of its own on the ground that it sees
touched, none seen in the `press` steps before) is drawn for once: one that is held is
guarded on by sight, from the first view of the guard until `press` steps (36) after the
last one it sees: until it sees itself hit or down, the opponent hit or down, the round
over, or the opponent further than `press_near` pixels (200) for `press_gap` steps (8).
Whether a string is held is read from the match, as the rising's guard is: what leaving
the guard has come to against what holding it has. Of its exits (a move of its own, or
itself in the air, seen within `press_exit` steps, 30, of a guard in a string not held),
those caught (it saw itself hit within `press_soon` steps, 50) less those that won (it
saw the opponent hit first), an exit, over a prior (`press_lost`, 0.1, counting as
`press_prior` exits, 4); less the share of its held strings in which it saw itself hit
or thrown while the hold was on, over a prior (`press_open`, 0.15, as `press_prior` held
strings). None are held where that difference is `press_low` (-0.05), all at
`press_high` (0.15), in a line between, and never more than 1 - `press_free` (0.34) of
them: a string in three is its own play's whatever the read says, so that the exits go
on being read. By evaluate.py's count (a move or a jump after a guard: hit, or hit
first) the league's opponents with combos stand at -0.06 an exit (a move wins 32% and is
caught 19%, a jump 9% and 16%) and the user's sessions of 19 to 21 November at +0.15 to
+0.21. No string is held at a match's start.

The first build (the user's games of 22 November, `round22c`) read the exits alone, over
a prior that held three strings in four, with no share kept free: a held string has no
exit, so the record that should have let go never filled: 51 of 52 strings held in the
first two matches (29% of the first in a forced guard), thrown for 627 HP a minute (130
before), 1,300 HP a minute less dealt; where exits were sampled they came out ahead (33
exits, 6 caught, 10 that hit first) and it stopped holding.

`plain` (false): the guard alone. The module then never draws its own play's action (no
super seen coming, no class's draw): a rising it does not guard through is the next
module's or its own play's, as the game's rise:1 is; with the module risk after it the
super's account is that module's.

options: moves (false), guard (false), plain (false), land (false), sight (0), recoil (0), recoil_near (240), recoil_gap (8),
recoil_press (22), recoil_clear (true), recoil_steady (12), recoil_let (false), recoil_prior (2),
recoil_counter (0.6), recoil_low (0.3), recoil_high (0.6), recoil_soon (34), recoil_punish (none),
recoil_punish_near (48), recoil_punish_at (22), prior (4), move (150), still (-165), super (-400),
meaty (0.56), low (0.3), high (0.6), met_prior (2), near (0), fly (200), hold (0), gap (8),
press (0), press_near (200), press_gap (8), press_exit (30), press_soon (50), press_prior (4),
press_lost (0.1), press_open (0.15), press_free (0.34), press_low (-0.05), press_high (0.15),
temperature (75),
window (240),
carry (false: a new match is another opponent; true: the same, the accounts kept and
scaled by `decay`, 0.7), seed.
"""

import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))

from efz_env import modules
from efz_env.actions import ActionTable

TABLE = ActionTable()
INDEX = {a: k for k, a in enumerate(TABLE.actions)}
ROUND_OVER = 3
SELF_HP, OPP_HP, SELF_ACT, OPP_ACT, OPP_AIR, DX, SELF_HITSTUN = 8, 40, 18, 50, 71, 4, 20
SELF_AIR = 39
OPP_Y, OPP_VY = 46, 48                      # the attacker's height (/ 240, up negative), fall (/ 20)
PIXELS = 640.0                              # dx's scale
DOWN = frozenset((0x60, 0x61, 0x62, 0x63))  # rising, the two knockdowns, lying
RG = frozenset((0xa8, 0xa9, 0xaa))          # a recoil guard: standing, crouching, in the air
GUARDS = frozenset(range(0x96, 0x9d)) | RG  # a guard touched (tactics.GUARDS)
FREE = frozenset((0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xe, 0xf, 0x10))  # free to do anything (tactics.FREE)


def reacting(a):
    """An action that is a hit reaction, a knockdown or a throw's pose."""
    return 0x32 <= a < 0x7a


FIRST_OWN = 0xc8                            # the character's own moves from here
REVERSAL = 10                               # steps after rising in which a move is a wake-up one
HP = 9999.0
CROUCH_GUARD, STAND_GUARD = INDEX[(1, '')], INDEX[(4, '')]
IDLE = INDEX[(5, '')]                       # nothing held: before a back press that opens the recoil-guard window
PRESS_A, PRESS_2A = INDEX[(5, 'A')], INDEX[(2, 'A')]  # a press that takes a kept chain's place
NORMALS = range(0xc8, 0xcf)                 # the ground normals (5A 5B 5C, 6C, 2A 2B 2C)
MOVE_2A = 0xcc
BACK = (1, 4, 7)                            # a guard's directions, and the jump back
MOVE, STILL, SUPER = 0, 1, 2
ACCOUNTS = ('move', 'still', 'super')
SUPER_MOVE = 0x13b   # Ayu's 236236 super at level one (236236A, or B or C with one bar)
SUPER_LEVEL = dict(A=1, B=2, C=3)  # the level a button asks for; the bars cap it
SELF_GAUGE = 9       # self_gauge: the power gauge, 1.0 three bars
RECENT = 24          # steps in which its own inputs make a motion


def steps_to_land(y, vy, vy_before):
    """The steps until a player in the air lands, from its height and fall in a view
    (opp_y, opp_vy) and its fall a step before: the game's arithmetic as fitted on the
    user's flights (y a step: 2.478 vy + 2.037 g; g the fall's gain a step, 0.09 where
    the two views give none). port/agent/policy.cpp's StepsToLand."""
    y, vy = float(y) * 240, float(vy) * 20
    g = vy - float(vy_before) * 20
    if not 0.02 < g < 0.5:
        g = 0.09
    n = 0
    while y < 0 and n < 200:
        y += 2.478 * vy + 2.037 * g
        vy += g
        n += 1
    return n


def sweeps(dirs):
    """How many times the directions go from down to forward (2 ... 6): two is 236236's
    motion and nothing else's (641236 has one, 623 none)."""
    n, want = 0, 2
    for d in dirs:
        if d == want:
            n, want = (n, 6) if want == 2 else (n + 1, 2)
    return n


class Rise(modules.Module):
    """stats(): knockdowns (it saw), guarded (the risings it guarded through by the
    accounts), supers (the wake-up 236236A it saw coming in its own inputs), stopped (of
    those, guarded instead), kept (of the guarded steps, the policy's own guard), and per
    account its wake-ups and mean swing."""
    name = 'rise'

    def __init__(self, prior=4.0, move=150.0, still=-165.0, super=-400.0, temperature=75.0,
                 window=240, carry=False, decay=0.7, seed=0, width=None, moves=False,
                 guard=False, meaty=0.56, low=0.3, high=0.6, met_prior=2.0, near=0.0,
                 fly=200.0, hold=0, gap=8, plain=False, land=False, sight=0, recoil=0,
                 recoil_near=240.0, recoil_gap=8, recoil_press=22, delay=None,
                 recoil_clear=True, recoil_steady=12, recoil_let=False, recoil_prior=2.0,
                 recoil_counter=0.6, recoil_low=0.3, recoil_high=0.6, recoil_soon=34,
                 recoil_punish='', recoil_punish_near=48.0, recoil_punish_at=22, press=0,
                 press_near=200.0, press_gap=8, press_exit=30, press_soon=50, press_prior=4.0,
                 press_lost=0.1, press_low=-0.05, press_high=0.15, press_open=0.15,
                 press_free=0.34):
        # moves: also guard a rising through by the class account (any wake-up move's);
        # measured without a gain, and it takes the wake-up moves that pay with it
        self.moves = moves in (True, 1, 'true', 'True', '1')
        # guard: a rising the attacker is seen on is guarded through, by sight
        self.guard = guard in (True, 1, 'true', 'True', '1')
        self.near, self.fly = float(near), float(fly)
        self.hold, self.gap = int(hold), int(gap)
        self.plain = plain in (True, 1, 'true', 'True', '1')
        # land: the standing guard under a flight only until its landing has passed;
        # sight: the steps late the guard's height is chosen from (0: the delay)
        self.land = land in (True, 1, 'true', 'True', '1')
        self.sight = int(sight)
        # recoil: the steps its inputs are a guard by sight for, from where it sees its
        # move recoil-guarded (0: off)
        self.recoil, self.recoil_near = int(float(recoil)), float(recoil_near)
        self.recoil_gap = int(float(recoil_gap))
        # recoil_press: the step after the recoil guard at which back is pressed; the
        # agent sees the recoil guard `delay` steps after it (the host's views say how
        # many: ctx.seen; `delay` here only where a host gives none)
        self.recoil_press, self.delay = int(float(recoil_press)), delay
        # recoil_clear: a press that takes the place of a chain it pressed before it saw
        self.recoil_clear = recoil_clear in (True, 1, 1.0, 'true', 'True', '1')
        # ... only when its last recoil_steady inputs hold one direction (no motion in them)
        self.recoil_steady = int(float(recoil_steady))
        # recoil_let: its own play's again from the first guard of its own it sees touched
        self.recoil_let = recoil_let in (True, 1, 1.0, 'true', 'True', '1')
        # the answer's read: how often this opponent counters soon after its recoil guard
        self.recoil_prior, self.recoil_counter = float(recoil_prior), float(recoil_counter)
        self.recoil_low = float(recoil_low)
        self.recoil_high = max(float(recoil_high), self.recoil_low + 1e-6)
        self.recoil_soon = int(float(recoil_soon))
        # recoil_punish: the inputs after its own recoil guard (control bytes -> actions)
        if isinstance(recoil_punish, str):
            recoil_punish = [int(x, 0) for x in recoil_punish.replace(' ', '').split(',') if x]
        table = [int(b) for b in TABLE.table]
        self.punish = [table.index(int(b)) for b in recoil_punish]
        self.punish_near, self.punish_at = float(recoil_punish_near), int(float(recoil_punish_at))
        # press: the steps after a guard it sees touched for which a held string is guarded on
        self.press, self.press_near = int(float(press)), float(press_near)
        self.press_gap, self.press_exit = int(float(press_gap)), int(float(press_exit))
        self.press_soon = int(float(press_soon))
        # the string's read: what leaving the guard has come to (caught less won, an exit)
        self.press_prior, self.press_lost = float(press_prior), float(press_lost)
        # ... against what holding it has (the held strings opened), and the share of
        # strings never held
        self.press_open = float(press_open)
        self.press_free = min(1.0, max(0.0, float(press_free)))
        self.press_low = float(press_low)
        self.press_high = max(float(press_high), self.press_low + 1e-6)
        self.prior = float(prior)
        self.priors = (float(move), float(still), float(super))
        # the guard's read: how often an attacker is in a move as the agent rises (the
        # prior, counting as met_prior risings), and the rates between which the guard
        # goes from never to always
        self.meaty, self.met_prior = float(meaty), float(met_prior)
        self.low, self.high = float(low), max(float(high), float(low) + 1e-6)
        self.temperature, self.window = float(temperature), int(window)
        self.carry, self.decay, self.width = bool(carry), float(decay), width
        self.rng = np.random.default_rng(seed)
        self.n_ = dict(knockdowns=0, guarded=0, supers=0, stopped=0, steps=0, kept=0, met=0,
                       met_guarded=0, stood=0, held=0, risings=0, attacked=0, landed=0,
                       recoils=0, recoil_steps=0, recoil_cleared=0, recoil_answered=0,
                       recoil_punished=0, strings=0, strings_held=0, press_steps=0, exits=0,
                       exits_caught=0, exits_won=0, holds_opened=0)
        self.all = np.zeros((len(ACCOUNTS), 2))  # every match's: [account] -> (wake-ups, swing's sum)
        self.batch(0)

    def batch(self, n):
        self.n = n
        self.count = np.zeros((n, len(ACCOUNTS)))  # this match's (or set's) wake-ups by account
        self.total = np.zeros((n, len(ACCOUNTS)))  # ... and their swings' sum
        self.seen = np.zeros(n)         # this match's risings it saw
        self.on = np.zeros(n)           # ... and of them, the attacker in a move as it rose
        self.met = np.zeros(n, bool)    # this rising: the attacker was seen on it
        self.drawn = np.zeros(n, bool)  # ... and its guard was drawn for
        self.holding = np.zeros(n, int)  # steps its guard may go on for, now that it is up
        self.vy = np.full((n, 2), np.nan)  # the attacker's fall in its view: now's, the step before's
        self.quiet = np.zeros(n, int)    # ... and the steps the attacker has not gone on
        self.was_down = np.zeros(n, bool)
        self.was_rg = np.zeros(n, bool)   # the opponent in a recoil guard in the view before
        self.answer = np.zeros(n, int)    # steps left of its answer to a recoil guard
        self.first = np.zeros(n, int)     # ... whose first steps (nothing held) are to come
        self.clear = np.full(n, -1)       # ... the press on the second of them (-1: none)
        self.rseen = np.zeros(n)          # this match's recoil guards of its moves it saw
        self.ron = np.zeros(n)            # ... and of them, a move of the opponent's soon after
        self.rwatch = np.zeros(n, int)    # steps left of looking for one
        self.was_mine = np.zeros(n, bool)  # itself in a recoil guard in the view before
        self.punishing = np.zeros(n, bool)  # its own recoil guard's follow-up is on
        self.pwait = np.zeros(n, int)      # ... the steps of guard before its inputs
        self.pstep = np.zeros(n, int)      # ... and the next of them
        self.let = np.zeros(n, int)       # ... and the steps the opponent has been free on the ground
        self.pressing = np.zeros(n, int)  # steps left of a held string's guard
        self.pfar = np.zeros(n, int)      # ... and the steps the opponent has been out of reach
        self.pheld = np.zeros(n, bool)    # this string is held
        self.psince = np.full(n, 10000)   # steps since it saw itself in a guard on the ground
        self.pexit = np.zeros(n, bool)    # this string's exit was counted
        self.pseen = np.zeros(n)          # this match's exits it saw
        self.pon = np.zeros(n)            # ... and of them, the ones caught less the ones that won
        self.pwatch = np.zeros(n, int)    # steps left of looking for what came of one
        self.pholds = np.zeros(n)         # this match's held strings
        self.popen = np.zeros(n)          # ... and of them, the ones it was hit or thrown in
        self.pcounted = np.zeros(n, bool)  # this held string was counted opened
        self.veto = np.zeros(n, bool)   # this rising is guarded through
        self.asked = np.zeros(n, bool)  # this rising's super was drawn for already
        self.dirs = [[] for _ in range(n)]  # its inputs' directions since the knockdown: (step, direction)
        self.step = np.zeros(n, int)
        # the wake-up being followed: [age, moved, own HP, its HP, the move it rose with]
        self.open = [None] * n

    def reset(self, mask=None):
        mask = np.ones(self.n, bool) if mask is None else np.asarray(mask, bool)
        for i in np.flatnonzero(mask):
            self.close(int(i), None)
            self.dirs[int(i)] = []
        scale = self.decay if self.carry else 0.0
        self.count[mask] *= scale
        self.total[mask] *= scale
        self.seen[mask] *= scale
        self.on[mask] *= scale
        self.was_down[mask] = self.veto[mask] = self.asked[mask] = False
        self.met[mask] = self.drawn[mask] = False
        self.holding[mask] = self.quiet[mask] = 0
        self.was_rg[mask] = False
        self.answer[mask] = self.let[mask] = self.first[mask] = 0
        self.clear[mask] = -1
        self.rseen[mask] *= scale
        self.ron[mask] *= scale
        self.rwatch[mask] = 0
        self.was_mine[mask] = self.punishing[mask] = False
        self.pressing[mask] = self.pfar[mask] = self.pwatch[mask] = 0
        self.pheld[mask] = self.pexit[mask] = self.pcounted[mask] = False
        self.psince[mask] = 10000
        self.pseen[mask] *= scale
        self.pon[mask] *= scale
        self.pholds[mask] *= scale
        self.popen[mask] *= scale
        self.vy[mask] = np.nan

    def worth(self, i):
        """(a wake-up move's, the others', the wake-up 236236A's) expected swing for
        environment i."""
        return tuple((self.prior * self.priors[k] + self.total[i, k]) /
                     (self.prior + self.count[i, k]) for k in range(len(ACCOUNTS)))

    def chance(self, i, account=MOVE):
        """The probability that a rising with a move of `account` is guarded through
        (against the risings without a move)."""
        worth = self.worth(i)
        return 1.0 / (1.0 + np.exp(np.clip((worth[account] - worth[STILL]) / self.temperature,
                                           -50, 50)))

    def rate(self, i):
        """How often this match's attacker has been in a move as the agent rose, over
        the prior."""
        return (self.met_prior * self.meaty + self.on[i]) / (self.met_prior + self.seen[i])

    def guard_chance(self, i):
        """The probability that a rising the attacker is on is guarded through by sight:
        none at the rate `low`, all at `high`."""
        return float(np.clip((self.rate(i) - self.low) / (self.high - self.low), 0.0, 1.0))

    def recoil_chance(self, i):
        """The probability that a recoil guard of its move is answered with the guard:
        by how often this opponent has countered soon after one, over the prior."""
        rate = ((self.recoil_prior * self.recoil_counter + self.ron[i]) /
                (self.recoil_prior + self.rseen[i]))
        return float(np.clip((rate - self.recoil_low) / (self.recoil_high - self.recoil_low), 0.0, 1.0))

    def press_chance(self, i):
        """The probability that a string is held (guarded on): by what leaving its guard
        has come to in this match (caught less won, an exit) less what holding it has
        (the held strings opened), each over its prior; never more than 1 - press_free."""
        rate = ((self.press_prior * self.press_lost + self.pon[i]) /
                (self.press_prior + self.pseen[i]))
        rate -= ((self.press_prior * self.press_open + self.popen[i]) /
                 (self.press_prior + self.pholds[i]))
        chance = np.clip((rate - self.press_low) / (self.press_high - self.press_low), 0.0, 1.0)
        return float(min(chance, 1.0 - self.press_free))

    def pressed(self, i, v, a, down):
        """watch()'s part for the guard under pressure: the strings, the held one's
        steps, and what came of the exits."""
        theirs = int(round(float(v[OPP_ACT])))
        hit, over = reacting(a), bool(down or v[ROUND_OVER] != 0)
        guard = a in GUARDS and not v[SELF_AIR] > 0
        if self.pwatch[i] > 0:  # an exit: caught, or not
            if hit:
                self.pon[i] += 1
                self.n_['exits_caught'] += 1
                self.pwatch[i] = 0
            elif reacting(theirs) and not over:
                self.pon[i] -= 1
                self.n_['exits_won'] += 1
                self.pwatch[i] = 0
            elif guard or over:
                self.pwatch[i] = 0
            else:
                self.pwatch[i] -= 1
        if (hit and self.pheld[i] and not self.pcounted[i] and self.psince[i] <= self.press):
            self.pcounted[i] = True  # hit or thrown in a held string: what holding cost
            self.popen[i] += 1
            self.n_['holds_opened'] += 1
        if guard and not over:
            if self.psince[i] > self.press:  # a new string: held or not, by the ones before
                self.pheld[i] = self.rng.random() < self.press_chance(i)
                self.pexit[i] = self.pcounted[i] = False
                self.pholds[i] += int(self.pheld[i])
                self.n_['strings'] += 1
                self.n_['strings_held'] += int(self.pheld[i])
            self.psince[i] = 0
            if self.pheld[i]:
                self.pressing[i], self.pfar[i] = self.press, 0
            return
        self.psince[i] = min(self.psince[i] + 1, 10000)
        if self.pressing[i] > 0:
            self.pressing[i] -= 1
            far = abs(float(v[DX])) * PIXELS > self.press_near
            self.pfar[i] = self.pfar[i] + 1 if far else 0
            if over or hit or reacting(theirs) or self.pfar[i] >= self.press_gap:
                self.pressing[i] = 0
        elif (self.psince[i] <= self.press_exit and not self.pexit[i] and not over and not hit
              and (a >= FIRST_OWN or v[SELF_AIR] > 0)):
            self.pexit[i] = True  # it left its guard: a move, or a jump
            self.pseen[i] += 1
            self.pwatch[i] = self.press_soon
            self.n_['exits'] += 1

    def on_it(self, v):
        """The attacker as the agent sees it: in a move of its own, or near, or in the
        air within reach."""
        d = abs(float(v[DX])) * PIXELS
        return bool(int(round(float(v[OPP_ACT]))) >= FIRST_OWN or d < self.near
                    or (v[OPP_AIR] > 0 and d <= self.fly))

    def stands(self, i, ctx):
        """The guard's height under the attacker as the guard sees it: True, a standing
        guard (it is in the air and, with land, not down yet as it fell)."""
        seen = ctx.seen
        if seen is None or not (self.land or self.sight):
            return bool(ctx.view[OPP_AIR] > 0)
        delay = len(seen) - 1
        s = min(self.sight, delay) if self.sight > 0 else delay
        v = seen[s]
        if not v[OPP_AIR] > 0:
            return False
        if self.land:
            before = seen[s + 1][OPP_VY] if s < delay else self.vy[i, 1]
            if steps_to_land(v[OPP_Y], v[OPP_VY], before) < s:
                self.n_['landed'] += 1
                return False
        return True

    def steady(self, hist):
        """Its last recoil_steady inputs (efz_env.history's rows, newest first) all hold
        one direction: no motion that a press would complete."""
        if hist is None or self.recoil_steady <= 0:
            return True
        h = np.asarray(hist, np.float32).reshape(-1, 6)[:self.recoil_steady, :2]
        return bool((h == h[0]).all())

    def cleared(self, i):
        """The answer's second step, once: the press that takes a kept chain's place."""
        if self.answer[i] != self.recoil - 2:
            return False
        self.n_['recoil_cleared'] += 1
        return True

    def close(self, i, view):
        """The followed wake-up's swing into its account (view None: dropped)."""
        rec, self.open[i] = self.open[i], None
        if rec is None or view is None:
            return
        mine = max(0.0, rec[2] - float(view[SELF_HP]) * HP)
        theirs = max(0.0, rec[3] - float(view[OPP_HP]) * HP)
        k = SUPER if rec[4] == SUPER_MOVE else MOVE if rec[1] else STILL
        self.count[i, k] += 1
        self.total[i, k] += theirs - mine
        self.all[k] += (1, theirs - mine)

    def watch(self, i, ctx):
        v = ctx.view
        a = int(round(float(v[SELF_ACT])))
        down = a in DOWN
        self.step[i] += 1
        now = float(v[OPP_VY])  # (the fall in the view one older than the oldest kept)
        self.vy[i] = (now, now if np.isnan(self.vy[i, 0]) else self.vy[i, 0])
        rec = self.open[i]
        if rec is not None:
            rec[0] += 1
            if rec[0] <= REVERSAL and a >= FIRST_OWN and not rec[1]:
                rec[1], rec[4] = True, a
            # (until it sees the round over, itself down again, or `window` steps on)
            if v[ROUND_OVER] != 0 or down or rec[0] >= self.window:
                self.close(i, v)
        if down and not self.was_down[i]:
            self.n_['knockdowns'] += 1
            self.veto[i] = self.moves and self.rng.random() < self.chance(i)
            self.n_['guarded'] += int(self.veto[i])
            self.asked[i], self.dirs[i] = False, []
            self.met[i] = self.drawn[i] = False
        if down and self.guard and self.on_it(v):
            self.met[i] = True
        if self.holding[i] > 0:  # up and guarding on: until the attacker has let up
            self.holding[i] -= 1
            going = bool(int(round(float(v[OPP_ACT]))) >= FIRST_OWN or
                         (v[OPP_AIR] > 0 and abs(float(v[DX])) * PIXELS <= self.fly))
            self.quiet[i] = 0 if going else self.quiet[i] + 1
            if (down or v[ROUND_OVER] != 0 or v[SELF_HITSTUN] > 0 or 0x32 <= a < 0x60
                    or self.quiet[i] >= self.gap):
                self.holding[i] = 0
        if self.recoil > 0:  # its move recoil-guarded, as it sees it
            theirs = int(round(float(v[OPP_ACT])))
            rg = theirs in RG
            if self.rwatch[i] > 0:  # its recoil guard followed by a move of its own, soon
                if theirs >= FIRST_OWN or v[SELF_HITSTUN] > 0 or 0x32 <= a < 0x60:
                    self.ron[i] += 1
                    self.rwatch[i] = 0
                else:
                    self.rwatch[i] -= 1
            if self.answer[i] > 0:
                free = theirs in FREE and not v[OPP_AIR] > 0
                self.let[i] = self.let[i] + 1 if free else 0
                if a in GUARDS and not self.recoil_let:  # its guard touched: on, through the string
                    self.answer[i], self.first[i] = self.recoil, 0
                if (down or v[ROUND_OVER] != 0 or v[SELF_HITSTUN] > 0 or 0x32 <= a < 0x60
                        or (a in GUARDS and self.recoil_let) or self.let[i] >= self.recoil_gap):
                    self.answer[i] = 0
            mine = a in (0xa8, 0xa9)  # its own recoil guard, on the ground
            if self.punishing[i] and (down or v[ROUND_OVER] != 0 or v[SELF_HITSTUN] > 0
                                      or 0x32 <= a < 0x60):
                self.punishing[i] = False
            if (mine and not self.was_mine[i] and self.punish and not self.punishing[i]
                    and v[ROUND_OVER] == 0 and not v[OPP_AIR] > 0 and theirs >= FIRST_OWN
                    and abs(float(v[DX])) * PIXELS <= self.punish_near):
                late = (len(ctx.seen) - 1 if ctx.seen is not None else
                        int(self.delay) if self.delay is not None else 0)
                wait = self.punish_at - len(self.punish) + 1 - late  # the guard's steps before them
                if wait >= 0:
                    self.punishing[i], self.pwait[i], self.pstep[i] = True, wait, 0
                    self.answer[i] = 0
                    self.n_['recoil_punished'] += 1
            self.was_mine[i] = mine
            if (rg and not self.was_rg[i] and a >= FIRST_OWN and v[ROUND_OVER] == 0
                    and abs(float(v[DX])) * PIXELS <= self.recoil_near):
                self.n_['recoils'] += 1
                answer = self.rng.random() < self.recoil_chance(i)  # (by the ones before)
                self.rseen[i] += 1
                self.rwatch[i] = self.recoil_soon
                if answer:
                    late = (len(ctx.seen) - 1 if ctx.seen is not None else
                            int(self.delay) if self.delay is not None else 0)
                    self.answer[i], self.let[i] = self.recoil, 0
                    self.first[i] = max(1, self.recoil_press - late)
                    self.clear[i] = ((PRESS_2A if a == MOVE_2A else PRESS_A)
                                     if self.recoil_clear and a in NORMALS and self.first[i] >= 2
                                     and self.steady(ctx.hist) else -1)
                    self.n_['recoil_answered'] += 1
            self.was_rg[i] = rg
        if self.press > 0:
            self.pressed(i, v, a, down)
        if self.was_down[i] and not down:
            if v[ROUND_OVER] == 0:  # the guard's read: was the attacker in a move as it rose
                self.seen[i] += 1
                self.n_['risings'] += 1
                if int(round(float(v[OPP_ACT]))) >= FIRST_OWN:
                    self.on[i] += 1
                    self.n_['attacked'] += 1
            if (self.veto[i] and self.met[i] and self.guard and v[ROUND_OVER] == 0
                    and (a < 0x32 or a >= 0x96)):
                self.holding[i], self.quiet[i] = self.hold, 0
            self.veto[i] = False
            if v[ROUND_OVER] == 0 and (a < 0x32 or a >= 0x96):  # up, not hit as it lay
                moved = a >= FIRST_OWN
                self.open[i] = [0, moved, float(v[SELF_HP]) * HP, float(v[OPP_HP]) * HP,
                                a if moved else None]
        self.was_down[i] = down

    def act(self, i, ctx):
        v = ctx.view
        if self.punishing[i] and not self.was_down[i]:  # what follows its own recoil guard
            if self.pwait[i] > 0:
                self.pwait[i] -= 1
                return STAND_GUARD if self.stands(i, ctx) else CROUCH_GUARD
            action = self.punish[self.pstep[i]]
            self.pstep[i] += 1
            if self.pstep[i] >= len(self.punish):
                self.punishing[i] = False
            return int(action)
        if self.answer[i] > 0 and not self.was_down[i]:  # its answer to a recoil guard
            self.answer[i] -= 1
            self.n_['recoil_steps'] += 1
            if self.first[i] > 0:
                self.first[i] -= 1
                if self.clear[i] >= 0 and self.cleared(i):
                    return int(self.clear[i])
                return IDLE
            return STAND_GUARD if self.stands(i, ctx) else CROUCH_GUARD
        if not self.was_down[i]:
            if self.holding[i] > 0:  # (its guard going on, by sight)
                self.n_['held'] += 1
                return STAND_GUARD if self.stands(i, ctx) else CROUCH_GUARD
            if self.pressing[i] > 0:  # (a held string's guard, by sight)
                self.n_['press_steps'] += 1
                return STAND_GUARD if self.stands(i, ctx) else CROUCH_GUARD
            return None
        own = None
        if self.plain:  # the guard alone: drawn once, held by sight, else not its step
            if not (self.guard and self.met[i]):
                return None
            if not self.drawn[i]:
                self.drawn[i] = True
                self.n_['met'] += 1
                if self.rng.random() < self.guard_chance(i):
                    self.veto[i] = True
                    self.n_['met_guarded'] += 1
            if not self.veto[i]:
                return None
            self.n_['steps'] += 1
            stand = self.stands(i, ctx)
            self.n_['stood'] += int(stand)
            return STAND_GUARD if stand else CROUCH_GUARD
        if ctx.policy is not None and ctx.hist is not None:  # its own play's action now
            x = np.concatenate([np.asarray(v, np.float32).reshape(-1),
                                np.asarray(ctx.hist, np.float32).reshape(-1)])
            own = int(np.asarray(ctx.policy(x[None, :self.width or len(x)])).reshape(-1)[0])
            direction, buttons = TABLE.actions[own]
            dirs = self.dirs[i]
            if not dirs or dirs[-1][1] != direction:
                dirs.append((int(self.step[i]), direction))
            recent = [d for t, d in dirs if t > self.step[i] - RECENT]
            bars = int(float(v[SELF_GAUGE]) * 3 + 1e-4)
            level = min(max([SUPER_LEVEL.get(b, 0) for b in buttons] or [0]), bars)
            if (not self.veto[i] and not self.asked[i] and level == 1
                    and sweeps(recent) >= 2):
                # 236236 and a button that makes it the level-one super, while it sees
                # itself down: the wake-up super is coming
                self.asked[i] = True
                self.n_['supers'] += 1
                if self.rng.random() < self.chance(i, SUPER):
                    self.veto[i] = True
                    self.n_['stopped'] += 1
        sight = False
        if self.guard and self.met[i]:
            if not self.drawn[i]:  # the attacker is on it: this rising's guard, drawn once
                self.drawn[i] = True
                self.n_['met'] += 1
                if not self.veto[i] and self.rng.random() < self.guard_chance(i):
                    self.veto[i] = True
                    self.n_['met_guarded'] += 1
            sight = bool(self.veto[i])
        if not self.veto[i]:
            return own  # (its own play, as this module drew it: what it read is what is played)
        self.n_['steps'] += 1
        if sight:  # held by sight: standing under an attacker in the air, no jump, no button
            if self.stands(i, ctx):
                self.n_['stood'] += 1
                return STAND_GUARD
            if own in (CROUCH_GUARD, STAND_GUARD):
                self.n_['kept'] += 1
                return own
            return CROUCH_GUARD
        if own is not None:
            direction, buttons = TABLE.actions[own]
            if not buttons and direction in BACK:
                self.n_['kept'] += 1
                return own
        return STAND_GUARD if v[OPP_AIR] > 0 else CROUCH_GUARD

    def stats(self):
        out = dict(self.n_)
        for k, name in enumerate(ACCOUNTS):
            n = self.all[k, 0]
            out[name] = dict(n=int(n), swing=round(float(self.all[k, 1] / n)) if n else None)
        return out


@modules.register('rise')
def rise(agent, where, files, options, data):
    """options: the file's head."""
    o = dict(options)
    keys = ('prior', 'move', 'still', 'super', 'temperature', 'window', 'carry', 'decay', 'seed',
            'moves', 'guard', 'meaty', 'low', 'high', 'met_prior', 'near', 'fly', 'hold', 'gap',
            'plain', 'land', 'sight', 'recoil', 'recoil_near', 'recoil_gap', 'recoil_press', 'delay', 'recoil_clear', 'recoil_steady', 'recoil_let', 'recoil_prior',
            'recoil_counter', 'recoil_low', 'recoil_high', 'recoil_soon', 'recoil_punish',
            'recoil_punish_near', 'recoil_punish_at', 'press', 'press_near', 'press_gap',
            'press_exit', 'press_soon', 'press_prior', 'press_lost', 'press_low', 'press_high',
            'press_open', 'press_free')
    unknown = sorted(set(o) - set(keys))
    if unknown:
        raise ValueError(f"rise: no option {', '.join(unknown)}")
    width = agent.model.observation_space.shape[0] if agent is not None else None
    return Rise(width=width, **{k: o[k] for k in keys if k in o})
