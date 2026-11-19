"""How combos end and what a throw is, as runs/human-ayu counts them (tactics.endings,
tactics.grabs: evaluate.py's combo_ends and grabs), and the scripted opponents' air
recovery (advantages.py's tech), a corner held (evaluate.corner), a risky move's cost
(tactics.risks) and the reward for getting away (focus.py's 'out')."""

import os
import sys
import unittest

import numpy as np

RUNS = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                    'runs', 'human-ayu')
sys.path.insert(0, RUNS)
try:
    import advantages
    import tactics
    MISSING = None
except ImportError as e:  # pragma: no cover
    MISSING = str(e)

try:
    import focus
    NO_FOCUS = None
except ImportError as e:  # pragma: no cover (stable-baselines3)
    NO_FOCUS = str(e)

N = len(tactics.OBS) if not MISSING else 0
# (the opponents' moves, made on each machine from the game: not in the repository)
NO_MOVES = not os.path.exists(os.path.join(RUNS, 'motions.json'))
ME_ACT, OPP_ACT, ME_STUN, OPP_STUN, ME_AIR, OPP_AIR, ME_HP, OPP_HP, DX = 0, 1, 4, 5, 6, 7, 14, 15, 18


def match(T=400):
    c = np.zeros((T, N), np.float32)
    c[:, ME_HP] = c[:, OPP_HP] = 1.0
    c[:, DX] = 60 / 640
    return c


def combo(c, at, steps, then, damage=0.2, air=True):
    """The viewer's combo on the opponent from `at`: an air hit reaction for `steps`, then
    the action `then` for 30 steps."""
    c[at:at + steps, OPP_ACT] = 0x3b
    c[at:at + steps, OPP_STUN] = 1
    c[at:at + steps + 30, OPP_AIR] = float(air)
    c[at + steps:at + steps + 30, OPP_ACT] = then
    c[at + 2:, OPP_HP] -= damage


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Endings(unittest.TestCase):
    def sides(self, c):
        live = np.ones(len(c), bool)
        return tactics.Side(c, 0), tactics.Side(c, 1), live

    def test_a_knockdown_a_recovery_and_a_standing_end(self):
        c = match(600)
        combo(c, 20, 30, 0x62)               # lies
        combo(c, 120, 30, 0x9e)              # recovers in the air
        c[450:460, OPP_ACT], c[450:460, OPP_STUN] = 0x32, 1  # a ground hit, then standing
        c[451:, OPP_HP] -= 0.01
        me, opp, live = self.sides(c)
        got = tactics.endings(me, opp, live)
        self.assertEqual([r['kind'] for r in got], ['knockdown', 'recovery', 'standing'])
        self.assertAlmostEqual(got[0]['damage'], 0.2 * 9999, delta=1)
        self.assertEqual(got[1]['next'], 'nothing')
        self.assertFalse(got[1]['busy'])
        rep = tactics.endings_report(got)
        self.assertEqual((rep['n'], rep['n_big']), (3, 2))
        self.assertEqual(rep['big']['knockdown'], 0.5)
        self.assertEqual(rep['big']['recovery'], 0.5)

    def test_hit_again_lying_is_the_same_combo_and_who_is_hit_after_a_recovery(self):
        c = match()
        combo(c, 20, 30, 0x61)               # lies, hittable ...
        c[55:70, OPP_ACT], c[55:70, OPP_STUN] = 0x3b, 1   # ... and is hit again
        c[70:100, OPP_ACT] = 0x9d            # then recovers
        c[70:75, ME_ACT] = 0xc9              # the viewer still in a move
        c[90:100, ME_STUN] = 1               # and hit first after it
        me, opp, live = self.sides(c)
        got = tactics.endings(me, opp, live)
        self.assertEqual(len(got), 1)
        self.assertEqual((got[0]['kind'], got[0]['busy'], got[0]['next']),
                         ('recovery', True, 'hit back'))

    def test_throws_and_chances(self):
        c = match()
        c[:, DX] = 30 / 640                  # within a throw's reach, both free: a chance
        c[100:110, ME_ACT] = 0xdc            # a throw tried
        c[110:120, ME_ACT] = 0xdd            # ... that caught
        c[200:230, ME_AIR] = c[200:230, OPP_AIR] = 1
        c[210:215, ME_ACT] = 0xf8            # an air throw tried (not Ayu: 0xf8), missed
        me, opp, live = self.sides(c)
        g = tactics.grabs(me, opp, c[:, DX], live)[0]
        self.assertEqual((g['throw_tries'], g['throws'], g['air_tries'], g['air_throws']),
                         (1, 1, 1, 0))
        self.assertGreaterEqual(g['throw_chances'], 1)
        self.assertGreaterEqual(g['air_chances'], 1)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Risks(unittest.TestCase):
    """A risky move's result and what a miss costs (tactics.risks: evaluate.py's risks)."""

    def ayu(self, T=900):
        c = match(T)
        c[:, 10] = tactics.names().index('ayu')   # the viewer's character
        return c

    def test_a_hit_a_punished_guard_a_whiff_and_a_combo_piece(self):
        c = self.ayu()
        c[20:54, ME_ACT] = 0xfb                              # 623C that hits:
        c[24:60, OPP_ACT], c[24:60, OPP_STUN] = 0x3b, 1
        c[26:, OPP_HP] -= 0.1
        c[200:234, ME_ACT] = 0xfb                            # one recoil-guarded,
        c[204:214, OPP_ACT] = 0xa8
        c[240:290, ME_ACT], c[240:290, ME_STUN] = 0x3b, 1    # and punished for a fifth
        c[242:, ME_HP] -= 0.2
        c[400:434, ME_ACT] = 0xfc                            # 623B in the air: nothing came
        c[600:640, OPP_ACT], c[600:640, OPP_STUN] = 0x3b, 1  # 236C inside a combo
        c[610:635, ME_ACT] = 0x106
        me, opp = tactics.Side(c, 0), tactics.Side(c, 1)
        got = tactics.risks(me, opp, np.ones(len(c), bool))
        self.assertEqual([(r['move'], r['combo'], r.get('result')) for r in got],
                         [('623C', False, 'hit'), ('623C', False, 'rg'), ('623B', False, 'whiff'),
                          ('236C', True, None)])
        self.assertAlmostEqual(got[0]['dealt'], 0.1 * 9999, delta=1)
        self.assertTrue(got[1]['punished'])
        self.assertAlmostEqual(got[1]['lost'], 0.2 * 9999, delta=1)
        self.assertFalse(got[1]['back'] or got[1]['ic'])
        self.assertFalse(got[2]['punished'])
        rep = tactics.risks_report(got, 1.0)
        self.assertEqual((rep['623C']['n'], rep['623C']['hit'], rep['623C']['rg']), (2, 0.5, 0.5))
        self.assertEqual((rep['623C']['punished'], rep['623C']['lost']), (1.0, 2000))
        self.assertEqual(rep['623C']['net'], -500)           # (1000 dealt - 2000 lost) / 2
        self.assertEqual((rep['236C']['in_combo'], rep['236C']['n']), (1.0, 0))

    def test_a_wake_up_one_is_told_from_the_others(self):
        c = self.ayu(600)
        c[80:120, ME_ACT] = 0x62                             # down, rising,
        c[120:140, ME_ACT] = 0x60
        c[140:200, ME_ACT] = 0x13b                           # and a super as it gets up:
        c[160:175, OPP_ACT] = 0x96                           # guarded,
        c[210:250, ME_ACT], c[210:250, ME_STUN] = 0x3b, 1    # punished for a tenth;
        c[212:, ME_HP] -= 0.1
        c[400:460, ME_ACT] = 0x13b                           # one in the open that hits
        c[420:450, OPP_ACT], c[420:450, OPP_STUN] = 0x3b, 1
        c[422:, OPP_HP] -= 0.3
        me, opp = tactics.Side(c, 0), tactics.Side(c, 1)
        got = tactics.risks(me, opp, np.ones(len(c), bool))
        self.assertEqual([(r['result'], r['wake']) for r in got], [('guarded', True), ('hit', False)])
        rep = tactics.risks_report(got, 1.0)['0x13b']
        self.assertEqual((rep['wake'], rep['wake_hit'], rep['wake_net'], rep['net']),
                         (0.5, 0.0, -1000, 1000))

    def test_an_answer_recoil_guarded_and_a_cancel_are_seen(self):
        c = self.ayu(400)
        c[20:40, ME_ACT] = 0xfa                              # 623A guarded,
        c[24:34, OPP_ACT] = 0x96
        c[40:50, ME_ACT] = 0xa7                              # cancelled (Instant Charge),
        c[60:66, ME_ACT] = 0xa8                              # and the answer recoil-guarded
        me, opp = tactics.Side(c, 0), tactics.Side(c, 1)
        got = tactics.risks(me, opp, np.ones(len(c), bool))
        self.assertEqual(len(got), 1)
        self.assertEqual((got[0]['result'], got[0]['punished'], got[0]['back'], got[0]['ic']),
                         ('guarded', False, True, True))


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Flights(unittest.TestCase):
    """An air dash, what followed it and what came of it (tactics.flights)."""

    def test_a_flight_into_a_move_that_hits_one_back_into_nothing(self):
        c = match(500)
        c[:, 10] = tactics.names().index('ayu')
        c[40:110, ME_AIR] = 1
        c[50:62, ME_ACT] = 0xa5                              # a flight forward,
        c[66:80, ME_ACT] = 0xc9                              # a move in the air,
        c[72:90, OPP_ACT], c[72:90, OPP_STUN] = 0x32, 1      # that hits
        c[300:312, ME_ACT] = 0xa6                            # one back: nothing after it
        c[300:330, ME_AIR] = 1
        me, opp = tactics.Side(c, 0), tactics.Side(c, 1)
        got = tactics.flights(me, opp, np.ones(len(c), bool))
        self.assertEqual([(r['back'], r['next'], r['came']) for r in got],
                         [(False, 'air move', 'hit'), (True, 'nothing', 'nothing')])
        rep = tactics.flights_report(got, 1.0)
        self.assertEqual((rep['n'], rep['back'], rep['mix']), (2, 0.5, 1.0))
        self.assertEqual(rep['came']['hit'], 0.5)
        self.assertEqual(rep['where'], {'open': dict(per_min=2.0, hit=0.5, was_hit=0.0)})

    def test_where_a_flight_is_flown_from(self):
        c = match(600)
        c[:, 10] = tactics.names().index('ayu')
        c[40:50, OPP_ACT] = 0x96                             # the opponent guards,
        c[60:72, ME_ACT] = 0xa5                              # a flight out of the string;
        c[200:260, OPP_ACT], c[200:260, OPP_STUN] = 0x32, 1  # it is hit,
        c[220:232, ME_ACT] = 0xa5                            # one inside the combo;
        c[300:360, OPP_ACT] = 0x62                           # it is down,
        c[320:332, ME_ACT] = 0xa5                            # one over it;
        c[500:512, ME_ACT] = 0xa6                            # and one in the open
        me, opp = tactics.Side(c, 0), tactics.Side(c, 1)
        got = tactics.flights(me, opp, np.ones(len(c), bool))
        self.assertEqual([r['where'] for r in got], ['string', 'combo', 'okizeme', 'open'])
        self.assertEqual(tactics.flights_report([], 1.0), dict(per_min=0.0, n=0))

    def test_the_opponent_s_risks_are_the_player_s_to_punish(self):
        c = match(300)
        c[:, 11] = tactics.names().index('ayu')              # the opponent is Ayu
        c[20:54, OPP_ACT] = 0xfb                             # her 623C, guarded,
        c[24:34, ME_ACT] = 0x96
        c[60:80, OPP_ACT], c[60:80, OPP_STUN] = 0x32, 1      # and punished
        c[62:, OPP_HP] -= 0.1
        got = tactics.measure(c)['risks_def']
        self.assertEqual([(r['move'], r['result'], r['punished']) for r in got],
                         [('623C', 'guarded', True)])


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Ledger(unittest.TestCase):
    """Where the HP goes (tactics.losses: evaluate.py's ledger)."""

    def hit(self, c, at, lost=0.1, steps=30):
        c[at:at + steps, ME_ACT], c[at:at + steps, ME_STUN] = 0x3b, 1
        c[at + 1:, ME_HP] -= lost

    def test_a_jump_in_hit_by_where_it_came_from_and_by_what(self):
        c = match(900)
        c[40:60, ME_AIR], c[45:60, ME_ACT] = 1, 0xd0         # a jump with a move, in the open,
        self.hit(c, 60)                                      # met from the ground
        c[200:260, OPP_ACT] = 0x62                           # the opponent is down:
        c[240:262, ME_AIR], c[245:262, ME_ACT] = 1, 0xd0     # a jump at its rising,
        c[255:300, OPP_AIR] = 1                              # met in the air
        self.hit(c, 262)
        c[400:410, OPP_ACT] = 0x96                           # it guards,
        c[420:440, ME_AIR], c[425:440, ME_ACT] = 1, 0xd0     # a jump out of the string,
        self.hit(c, 440)
        c[600:620, ME_AIR] = 1                               # and one hit without a move out
        self.hit(c, 620, lost=0.05)
        me, opp = tactics.Side(c, 0), tactics.Side(c, 1)
        got = tactics.losses(me, opp, np.ones(len(c), bool))
        self.assertEqual([(r['kind'], r.get('where'), r.get('by')) for r in got],
                         [('in the air, attacking', 'open', 'ground'),
                          ('in the air, attacking', 'okizeme', 'air'),
                          ('in the air, attacking', 'pressure', 'ground'),
                          ('in the air, not attacking', None, None)])
        rep = tactics.losses_report(got, 1.0)
        self.assertEqual((rep['hp'], rep['times']), (3500, 4.0))
        self.assertEqual(rep['kinds']['in the air, attacking'], dict(hp=3000, times=3.0, each=1000))
        self.assertEqual(rep['air_where'], dict(okizeme=1000, open=1000, pressure=1000))
        self.assertEqual(rep['air_by'], dict(air=1000, ground=2000))

    def test_on_the_ground_and_between_rounds(self):
        c = match(900)
        c[20:40, ME_ACT] = 0xca                              # a move in neutral, beaten
        self.hit(c, 40)
        c[200:215, ME_ACT] = 0x99                            # a guard, then opened
        self.hit(c, 220)
        c[400:432, ME_ACT] = 0xca                            # a move the opponent guarded,
        c[405:415, OPP_ACT] = 0x96
        self.hit(c, 432)                                     # punished before it is over
        c[600:640, ME_ACT] = 0x62                            # down, then hit as it stands
        self.hit(c, 650)
        self.hit(c, 800)                                     # and standing free
        live = np.ones(len(c), bool)
        c[870:, ME_HP] = 1.0                                 # a new round: nothing lost by it
        c[860:, OPP_HP] -= 0.3
        live[860:880] = False                                # (the opponent's HP between rounds)
        me, opp = tactics.Side(c, 0), tactics.Side(c, 1)
        self.assertEqual([r['kind'] for r in tactics.losses(me, opp, live)],
                         ['in a move, in neutral', 'opened after guarding',
                          'its move guarded, then punished', 'rising, not acting',
                          'free on the ground'])
        self.assertEqual(tactics.losses(opp, me, live), [])
        m = tactics.measure(c)
        self.assertEqual((len(m['losses']), len(m['losses_opp'])), (5, 1))

    def test_the_net_by_the_situation_an_exchange_began_in(self):
        c = match(1200)
        c[20:60, OPP_ACT] = 0x62                             # the opponent is down, rises,
        c[70:100, OPP_ACT], c[70:100, OPP_STUN] = 0x3b, 1    # and is hit: my okizeme
        c[72:, OPP_HP] -= 0.2
        c[200:240, ME_ACT] = 0x62                            # I am down, rise, and am hit
        self.hit(c, 250)
        c[400:410, OPP_ACT] = 0x96                           # it guards, then hits me out of it
        self.hit(c, 430)
        c[600:625, ME_AIR], c[605:625, ME_ACT] = 1, 0xd0     # I jump in and am hit
        self.hit(c, 625)
        c[800:830, OPP_AIR] = 1                              # it jumps in and is hit
        c[825:860, OPP_ACT], c[825:860, OPP_STUN] = 0x3b, 1
        c[827:, OPP_HP] -= 0.1
        c[1000:1030, ME_ACT] = 0xca                          # on the ground, I am hit
        self.hit(c, 1030, lost=0.05)
        me, opp = tactics.Side(c, 0), tactics.Side(c, 1)
        got = tactics.exchanges(me, opp, np.ones(len(c), bool))
        self.assertEqual(sorted((s, round(v)) for s, v in got),
                         sorted([('my okizeme', 2000), ('its okizeme', -1000), ('my pressure', -1000),
                                 ('I came by air', -1000), ('it came by air', 1000),
                                 ('on the ground', -500)]))
        rep = tactics.exchanges_report(got, 1.0)
        self.assertEqual(rep['net'], -500)
        self.assertEqual(rep['my okizeme'], dict(net=2000, gained=2000, lost=0))
        self.assertEqual(rep['my pressure'], dict(net=-1000, gained=0, lost=1000))
        self.assertEqual(rep['both in the air'], dict(net=0, gained=0, lost=0))


class Game:
    """What focus.Focus reads of EfzSB3VecEnv: player 1's current views."""

    def __init__(self, n=1):
        self.obs = np.zeros((n, 2, 168), np.float32)
        self.final_obs = np.zeros((n, 2, 168), np.float32)


class Venv:
    def __init__(self, n=1):
        self.num_envs, self.env = n, Game(n)
        self.observation_space = self.action_space = None

    def reset(self):
        return self.env.obs[:, 0]

    def step_wait(self):
        n = self.num_envs
        return self.env.obs[:, 0], np.zeros(n, np.float32), np.zeros(n, bool), [{}] * n


@unittest.skipIf(MISSING or NO_FOCUS, f'needs runs/human-ayu and stable-baselines3: {MISSING or NO_FOCUS}')
class Out(unittest.TestCase):
    """focus.py's 'out': an air recovery not caught, and a corner left."""

    def play(self, views):
        venv = Venv()
        f = focus.Focus(venv, 'out', coef=0.5)
        venv.env.obs[0, 0] = views[0]
        f.reset()
        total = 0.0
        for v in views[1:]:
            venv.env.obs[0, 0] = v
            total += float(f.step_wait()[1][0])
        return total, f.take()

    def view(self, act=0, x=0.0, opp_x=0.0, dx=100, guard=False):
        v = np.zeros(168, np.float32)
        v[focus.ACT_SELF], v[focus.X_SELF], v[focus.X_OPP] = act, x, opp_x
        v[focus.DX], v[focus.GUARDING_SELF] = dx / 640, float(guard)
        return v

    def test_a_recovery_pays_when_it_is_not_caught(self):
        hit, rec, free = self.view(0x3b), self.view(0x9e), self.view(0)
        total, n = self.play([hit] * 3 + [rec] * 10 + [free] * focus.OUT_WINDOW)
        self.assertEqual((total, n['recoveries']), (0.5, 1))
        total, n = self.play([hit] * 3 + [rec] * 10 + [hit] * 5 + [free] * focus.OUT_WINDOW)
        self.assertEqual((total, n['recoveries']), (0.0, 0))   # hit again inside the window
        total, n = self.play([free] * 3 + [rec] * 10 + [free] * focus.OUT_WINDOW)
        self.assertEqual(total, 0.0)                           # not out of a hit

    def test_a_corner_left_pays_when_it_was_pressed_there(self):
        held = self.view(x=0.9, opp_x=0.6, guard=True)
        out = self.view(x=0.4, opp_x=0.6)
        total, n = self.play([held] * 30 + [out] * 5)
        self.assertEqual((total, n['corners']), (0.5, 1))
        total, n = self.play([held] * 5 + [out] * 5)           # too short a stay
        self.assertEqual(total, 0.0)
        idle = self.view(x=0.9, opp_x=0.6)
        total, n = self.play([idle] * 30 + [out] * 5)          # never pressed there
        self.assertEqual(total, 0.0)
        knocked = self.view(0x3b, x=0.4, opp_x=0.6)
        total, n = self.play([held] * 30 + [knocked] * 5)      # hit out of it: not its doing
        self.assertEqual(total, 0.0)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Corner(unittest.TestCase):
    def test_a_stay_in_the_corner_and_how_it_ends(self):
        import evaluate
        import tactics
        T = 200
        c = np.zeros((T, len(tactics.OBS)), np.float32)
        c[:, 14], c[:, 15] = 1.0, 1.0                 # both at full HP
        c[:, 18] = 100 / 640                          # 100 pixels apart
        x = np.zeros((T, 2), np.float32)
        x[:, 0] = 0.5                                 # the player
        x[20:140, 1] = 0.9                            # the opponent in the corner for 120 steps,
        x[140:, 1], x[140:, 0] = 0.3, 0.6             # then over the player and out,
        c[136:150, 7] = 1.0                           # through the air
        c[60:, 15] = 0.9                              # having lost a tenth of its HP there
        stays = evaluate.corner(c, x)
        self.assertEqual(len(stays), 1)
        steps, dealt, lost, how = stays[0]
        self.assertEqual((steps, how), (120, 1))
        self.assertAlmostEqual(dealt, 999.9, delta=1)
        self.assertEqual(lost, 0)
        x[:, 1] = 0.2                                 # midscreen all along: none
        self.assertEqual(evaluate.corner(c, x), [])


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
@unittest.skipIf(NO_MOVES, 'no runs/human-ayu/motions.json: python runs/human-ayu/motions.py makes it')
class Tech(unittest.TestCase):
    def view(self, act=0, air=False):
        v = np.zeros(168, np.float32)
        v[advantages.SELF_ACT] = act
        v[advantages.SELF_AIRBORNE] = float(air)
        v[advantages.DX] = 300 / 640
        return v

    def test_it_presses_back_and_a_button_every_other_step_in_the_air(self):
        self.assertEqual(advantages.parse('tech=0.9')['tech'], 0.9)
        logic = advantages.Advantages('mai', 1, tech=1.0)
        logic.clear(0)
        self.assertIsNone(logic.step(0, self.view()))
        got = [logic.step(0, self.view(0x3b, air=True)) for _ in range(4)]
        self.assertEqual(got, [(4, 'A'), (4, ''), (4, 'A'), (4, '')])
        self.assertIsNone(logic.step(0, self.view(0x32)))        # hit on the ground: nothing
        logic.step(0, self.view(0x3b, air=True))
        logic.step(0, self.view(0x9e, air=True))                 # it recovered
        self.assertEqual(logic.take()['recoveries'], 1)

    def test_it_recovers_only_when_it_is_safe(self):
        logic = advantages.Advantages('mai', 1, tech=1.0, techsafe=1.0)
        logic.clear(0)
        near = self.view(0x3b, air=True)
        near[advantages.DX] = 60 / 640                           # the agent free beside it
        self.assertEqual(logic.step(0, near), (4, ''))           # it falls
        busy = near.copy()
        busy[advantages.OPP_ACT] = advantages.FIRST_OWN + 5      # the agent in a move of its own
        self.assertIn(logic.step(0, busy), [(4, 'A'), (4, '')])
        far = self.view(0x3b, air=True)                          # 300 pixels away
        self.assertEqual(sorted(logic.step(0, far) for _ in range(2)), [(4, ''), (4, 'A')])
        self.assertEqual(logic.take()['tech_unsafe'], 1)

    def test_it_attacks_out_of_its_recovery_and_recovers_forward(self):
        self.assertEqual(advantages.parse('tech=1,techhit=1,techway=1')['techhit'], 1.0)
        logic = advantages.Advantages('mai', 1, tech=1.0, techhit=1.0, techway=1.0)
        logic.clear(0)
        self.assertEqual(logic.step(0, self.view(0x3b, air=True)), (6, 'A'))   # forward
        logic.step(0, self.view(0x9d, air=True))                 # in its recovery
        free = self.view(0xe, air=True)
        free[advantages.DX] = 80 / 640
        got = [logic.step(0, free) for _ in range(4)]            # out of it, the agent near
        self.assertEqual(sorted(set(got)), [(6, ''), (6, 'B')])
        away = self.view(0xe, air=True)                          # the agent 300 pixels away
        self.assertIsNone(logic.step(0, away))
        self.assertEqual(logic.take()['tech_hits'], 1)

    def test_it_jumps_out_of_a_corner_when_it_is_free_there(self):
        self.assertEqual(advantages.parse('escape=1')['escape'], 1.0)
        logic = advantages.Advantages('mai', 1, escape=1.0)
        logic.clear(0)
        v = self.view()                                          # standing, free
        v[advantages.SELF_X], v[advantages.OPP_X] = 0.9, 0.7     # in the corner, the agent inside
        v[advantages.DX] = 100 / 640
        self.assertEqual(logic.step(0, v), (9, ''))
        up = v.copy()
        up[advantages.SELF_AIRBORNE] = 1.0
        got = [logic.step(0, up) for _ in range(20)]
        self.assertIn((5, ''), got)                              # the stick let go once,
        self.assertEqual(got[-1], (6, ''))                       # the second jump, then forward
        self.assertEqual(logic.take()['escapes'], 1)
        mid = self.view()                                        # midscreen: nothing
        mid[advantages.SELF_X], mid[advantages.OPP_X] = 0.2, 0.0
        logic2 = advantages.Advantages('mai', 1, escape=1.0)
        logic2.clear(0)
        self.assertIsNone(logic2.step(0, mid))

    def test_none_of_it_at_zero(self):
        logic = advantages.Advantages('mai', 1)
        logic.clear(0)
        self.assertIsNone(logic.step(0, self.view(0x3b, air=True)))
