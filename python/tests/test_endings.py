"""How combos end and what a throw is, as runs/human-ayu counts them (tactics.endings,
tactics.grabs: evaluate.py's combo_ends and grabs), and the scripted opponents' air
recovery (advantages.py's tech), a corner held (evaluate.corner), a risky move's cost
(tactics.risks) and the reward for getting away (focus.py's 'out')."""

import os
import sys
import unittest
from unittest import mock

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
        # The super is a risky move as one of the frame data's invincible ones; the frame
        # data (framedata.json) is made on each machine, not in the repository: given here,
        # and no startups.
        ayu = tactics.names().index('ayu')
        with mock.patch.object(tactics, 'frame_data', lambda: {ayu: ({0x13b}, [])}), \
                mock.patch.object(tactics, 'startups', lambda: {}):
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
class OverAnAgentFile(unittest.TestCase):
    """The advantages' inputs over an opponent that is an agent file: its own control
    bytes come through the environment's opponent_controls after the opponents' actions
    (native_agent.NativeOpponent), and the scripted input is written over them last."""

    def test_the_script_has_the_last_word(self):
        import advantages
        from types import SimpleNamespace
        from efz_env.actions import ActionTable
        table = ActionTable()
        venv = SimpleNamespace(env=SimpleNamespace(num_envs=3, obs=np.zeros((3, 2, 168), np.float32)),
                               _length=np.ones(3, int), opponent_controls=[], extra=None)
        # (The character's moves, motions.json, are made on each machine, not in the
        # repository: none here, the script below plays for them.)
        with mock.patch.object(advantages, 'motions', lambda char: {}), \
                mock.patch.object(advantages, 'invincible_moves', lambda char: []):
            opp = advantages.AdvantagedOpponent(lambda obs: np.zeros(len(obs), np.int64), 'kano',
                                                advantages.parse('reversal=1'))
        opp.attach(venv)
        venv.opponent_controls.insert(0, lambda out: out.__setitem__(slice(None), 0x55))  # the file's own
        venv.opponent_controls.append(lambda out: out.__setitem__(2, 0x66))  # (one registered later)
        script = {0: (4, ''), 1: None, 2: None}
        opp.logic.step = lambda i, o: script[i]
        actions = opp.post(np.zeros(3, np.int64), [0, 1, 2])
        out = table.to_bytes(actions).copy()
        for hook in sorted(venv.opponent_controls, key=lambda h: getattr(h, 'order', 0)):  # (efz_env.sb3's)
            hook(out)
        back = int(table.table[{a: k for k, a in enumerate(table.actions)}[(4, '')]])
        self.assertEqual(out.tolist(), [back, 0x55, 0x66])
        script[0] = None  # the script lets go: the file's own again
        opp.post(np.zeros(3, np.int64), [0, 1, 2])
        out[:] = 0
        for hook in sorted(venv.opponent_controls, key=lambda h: getattr(h, 'order', 0)):
            hook(out)
        self.assertEqual(out.tolist(), [0x55, 0x55, 0x66])


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

    def test_what_was_on_the_screen_when_it_was_hit(self):
        c = match(900)
        first = len(tactics.OBS) - 8                         # the opponent's objects' columns
        c[30:62, OPP_ACT] = 0x100                            # a move out for 30 steps,
        c[50:60, ME_ACT] = 0xca                              # one of its own started into it
        self.hit(c, 60)
        c[230:262, OPP_ACT] = 0x100                          # one out as long,
        self.hit(c, 260)                                     # met standing still
        c[455:462, OPP_ACT] = 0x100                          # a fast one: nothing to see
        c[450:460, ME_ACT] = 0xca
        self.hit(c, 460)
        c[600:662, first] = 1                                # an object, its owner free again,
        c[640:660, ME_AIR] = 1                               # and a jump into it
        self.hit(c, 660)
        me, opp = tactics.Side(c, 0), tactics.Side(c, 1)
        got = tactics.losses(me, opp, np.ones(len(c), bool))
        self.assertEqual([(r['thing'], r['out_for'], r['began']) for r in got],
                         [('move', 30, True), ('move', 30, False), ('move', 5, False),
                          ('object', 60, True)])
        into = tactics.losses_report(got, 1.0)['into']
        self.assertEqual(into, dict(seen=dict(hp=3000, times=3.0), began=dict(hp=2000, times=2.0),
                                    object=dict(hp=1000, times=1.0)))

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


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Rounds(unittest.TestCase):
    """tactics.rounds: what is made of a lead, and a round that is there to close."""

    def sides(self, c):
        return tactics.Side(c, 0), tactics.Side(c, 1), (c[:, 16] == 0) & (c[:, 17] == 0)

    def two(self, gap):
        c = match(420)
        c[50:200, OPP_HP] = 0.2                # led from step 50, the opponent at a fifth
        c[150:200, OPP_HP] = 0.0               # and the round won
        if gap:                                # (a record with the steps between rounds)
            c[200:220, 17] = 1.0
            c[200:220, OPP_HP] = 0.0
        c[250:, ME_HP] = 0.5                   # the second: behind,
        c[300:, ME_HP] = 0.05                  # and lost at the record's end
        return c

    def test_a_round_led_and_closed_and_one_lost_from_behind(self):
        for gap in (True, False):              # an evaluation's record, a replay dataset's
            got = tactics.rounds(*self.sides(self.two(gap)))
            self.assertEqual([r['won'] for r in got], [True, False])
            first, second = got
            self.assertEqual(first['lead'], (True, 0.0))
            self.assertEqual(first['close'][0], True)
            self.assertEqual(first['close'][1], 150)   # steps from the fifth to the end
            self.assertIsNone(first['behind'])
            self.assertEqual(second['behind'], False)
            self.assertIsNone(second['lead'])
            self.assertIsNone(second['close'])
        rep = tactics.rounds_report(got)
        self.assertEqual((rep['n'], rep['won']), (2, 0.5))
        self.assertEqual(rep['lead']['kept'], 1.0)
        self.assertEqual(rep['behind']['turned'], 0.0)
        self.assertEqual(rep['close']['seconds'], 2.5)

    def test_a_round_the_record_cuts_short_is_none(self):
        c = match(300)
        c[100:, OPP_HP] = 0.5                  # ahead, and the record ends
        self.assertEqual(tactics.rounds(*self.sides(c)), [])
        self.assertIsNone(tactics.rounds_report([]))

    def test_the_raw_moves_as_one_account(self):
        rec = lambda **kw: dict(dict(move='623B', combo=False, result='hit', dealt=0, lost=0,
                                     punished=False, back=False, ic=False, wake=False), **kw)
        recs = [rec(dealt=1000), rec(result='guarded', lost=600, punished=True),
                rec(result='whiff', ic=True), rec(combo=True, dealt=2000)]
        got = tactics.raw_report(recs, 0.5)
        self.assertEqual((got['n'], got['per_min']), (3, 1.5))        # the combo's piece is not one
        self.assertEqual((got['net'], got['hp_per_min']), (133, 200))  # (1000 - 600) / 3; a minute
        self.assertEqual((got['missed'], got['punished'], got['cancelled']), (0.667, 0.5, 0.5))


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


@unittest.skipIf(MISSING or NO_FOCUS, f'needs runs/human-ayu and stable-baselines3: {MISSING or NO_FOCUS}')
class Press(unittest.TestCase):
    """focus.py's 'press': the opponent's guard touched, and a hit soon after it."""

    def play(self, views, name='press'):
        venv = Venv()
        f = focus.Focus(venv, name, coef=0.5)
        venv.env.obs[0, 0] = views[0]
        f.reset()
        total = 0.0
        for v in views[1:]:
            venv.env.obs[0, 0] = v
            total += float(f.step_wait()[1][0])
        return round(total, 6), f.take()

    def view(self, opp=0, frame=0, corner=False, air=False):
        v = np.zeros(168, np.float32)
        v[focus.ACT_OPP], v[focus.FRAME_OPP] = opp, frame
        if corner:  # the opponent at a wall, the learner 100 pixels in front of it
            v[focus.X_OPP], v[focus.X_SELF], v[focus.DX] = 0.9, 0.6, 100 / 640
        v[focus.AIR_OPP] = float(air)
        return v

    def test_in_a_corner_the_pressure_pays_double_and_a_jump_out_caught_pays(self):
        """corner: press's events CORNER_TIMES as much with the opponent held in a corner,
        and a hit on the opponent in the air there (its jump out caught)."""
        T = focus.CORNER_TIMES
        free, hit = self.view(0, corner=True), self.view(0x3b, corner=True)
        guard = [self.view(0x97, k, corner=True) for k in range(8)]
        total, n = self.play([free] * 3 + guard + [free] * 10, 'corner')
        self.assertEqual((total, n['contacts']), (0.5 * focus.PRESS_CONTACT * T, 1))
        total, n = self.play([free] * 3 + guard + [hit] * 5, 'corner')
        self.assertEqual((total, n['opened'], n['caught']), (0.5 * focus.PRESS_CONTACT * T + 0.5 * T, 1, 0))
        up = [self.view(0x9, corner=True, air=True)] * 6
        total, n = self.play([free] * 3 + up + [self.view(0x3b, corner=True, air=True)] * 4, 'corner')
        self.assertEqual((total, n['caught'], n['opened']), (0.5 * T, 1, 0))
        total, n = self.play([free] * 3 + up + [self.view(0x9, air=True)] * 6 + [self.view(0x3b, air=True)] * 4,
                             'corner')                                    # out of the corner first: nothing
        self.assertEqual((total, n['caught']), (0.0, 0))
        free, hit = self.view(0), self.view(0x3b)                         # midscreen: as press
        guard = [self.view(0x97, k) for k in range(8)]
        total, n = self.play([free] * 3 + guard + [hit] * 5, 'corner')
        self.assertEqual((total, n['opened']), (0.5 * focus.PRESS_CONTACT + 0.5, 1))

    def test_a_guard_touched_pays_a_share_and_a_hit_after_it_in_full(self):
        free, hit = self.view(0), self.view(0x3b)
        guard = [self.view(0x97, k) for k in range(8)]
        total, n = self.play([free] * 3 + guard + [free] * 10)
        self.assertEqual((total, n['contacts'], n['opened']), (0.5 * focus.PRESS_CONTACT, 1, 0))
        total, n = self.play([free] * 3 + guard + guard + [free] * 10)  # the guard touched again
        self.assertEqual((total, n['contacts']), (2 * 0.5 * focus.PRESS_CONTACT, 2))
        total, n = self.play([free] * 3 + guard + [free] * 10 + [hit] * 5)
        self.assertEqual((total, n['opened']), (0.5 * focus.PRESS_CONTACT + 0.5, 1))
        total, n = self.play([free] * 3 + guard + [hit] * 5)            # opened out of the guard
        self.assertEqual((total, n['opened']), (0.5 * focus.PRESS_CONTACT + 0.5, 1))
        total, n = self.play([free] * 3 + guard + [self.view(0x64)] * 5)  # thrown out of it
        self.assertEqual(n['opened'], 1)

    def test_a_hit_with_no_guard_before_it_or_long_after_one_is_not_the_pressure(self):
        free, hit = self.view(0), self.view(0x3b)
        guard = [self.view(0x97, k) for k in range(8)]
        total, n = self.play([free] * 3 + [hit] * 5)
        self.assertEqual((total, n['opened']), (0.0, 0))
        total, n = self.play([free] * 3 + guard + [free] * (focus.PRESS_WINDOW + 1) + [hit] * 5)
        self.assertEqual((total, n['opened']), (0.5 * focus.PRESS_CONTACT, 0))
        total, n = self.play([free] * 3 + [self.view(0xa8, k) for k in range(8)] + [free] * 5)
        self.assertEqual((total, n['contacts']), (0.0, 0))             # a recoil guard: not held


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

    def test_what_a_stay_is_made_of(self):
        """corner_hold(): the opponent's guard and hit steps, where the player stands, the
        player's moves, and the opponent's jumps there with what became of them."""
        import evaluate
        import tactics
        T = 200
        c = np.zeros((T, len(tactics.OBS)), np.float32)
        c[:, 14], c[:, 15] = 1.0, 1.0
        c[:, 18] = 100 / 640
        x = np.zeros((T, 2), np.float32)
        x[:, 0] = 0.5
        x[20:140, 1] = 0.9                            # the stay: 120 steps
        x[140:, 1], x[140:, 0] = 0.3, 0.6
        c[30:40, 1] = 0x97                            # it guards ten steps,
        c[50:55, 0] = 0xc8                            # (a move of the player's on the ground
        c[95:100, 0], c[95:100, 6] = 0xd0, 1.0        #  and one in the air)
        c[60:80, 5] = 1.0                             # is in a hit twenty,
        c[100:110, 7] = 1.0                           # jumps and is hit in the air (caught),
        c[104:110, 5] = 1.0
        c[136:150, 7] = 1.0                           # jumps again and is out
        n = dict(zip(evaluate.HOLD, evaluate.corner_hold(c, x)))
        self.assertEqual((n['steps'], n['guard'], n['hit']), (120, 10, 26))
        self.assertEqual((n['<60'], n['<110'], n['<170'], n['further']), (0, 76, 0, 0))
        self.assertEqual((n['moves'], n['air moves']), (2, 1))
        self.assertEqual((n['jumps'], n['caught'], n['out'], n['stayed in'], n['player hit']),
                         (2, 1, 1, 0, 0))
        c[101:103, 4] = 1.0                           # the player hit first: not a catch
        n = dict(zip(evaluate.HOLD, evaluate.corner_hold(c, x)))
        self.assertEqual((n['caught'], n['player hit']), (0, 1))
        e = evaluate.Events('ayu')
        e.n['corner_list'] = evaluate.corner(c, x)
        e.n['corner_steps'] = T
        e.n['corner_hold'] = evaluate.corner_hold(c, x)
        e.n['frames'] = T
        hold = e.report()['corner']['hold']
        self.assertEqual((hold['jumps'], hold['jump']['out'], hold['moves'], hold['air_moves']),
                         (2.0, 0.5, 2.0, 0.5))


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

    def test_an_empty_jump_and_a_low_as_it_lands(self):
        """low: the jump-in on the agent's rising with nothing in the air, and the
        character's fastest low normal from its landing."""
        self.assertEqual(advantages.parse('jumpin=0.9,low=0.6')['low'], 0.6)
        self.assertEqual(advantages.low_normal('kano'), 'B')     # (her 2A is no low)
        self.assertEqual(advantages.low_normal('sayuri'), 'A')
        for low, last in ((1.0, (2, 'B')), (0.0, (5, 'A'))):
            logic = advantages.Advantages('kano', 1, jumpin=1.0, low=low, learner='ayu')
            plan = max(logic.plans, key=lambda p: p['contact'])
            seq = []
            for t in range(160):                                 # the agent knocked down, lying
                v = np.zeros(168, np.float32)
                v[advantages.OPP_ACT] = 0x62
                v[advantages.DX] = plan['distance'] / 640
                seq.append(logic.step(0, v))
            start = seq.index((9, ''))                           # (it waits at its distance; the same jump)
            played = [a for a in seq[start:] if a is not None]
            pressed = [a for a in played if a[1]]
            self.assertEqual(pressed[0], last)
            self.assertEqual(logic.counts['lowins'], int(low))
            if low:  # nothing pressed in the air; the low thrice from the landing
                air = logic.jump['prejump'] + logic.jump['air']
                self.assertFalse(any(a[1] for a in played[:air]))
                self.assertEqual(played[air:air + 6], [(2, 'B'), (2, '')] * 3)

    POKES = ('2A', {'2A': (55, 0xcc, 4), '5A': (63, 0xc8, 4), '5B': (65, 0xc9, 6),
                    '2B': (101, 0xcd, 7)},
             {'2A': ['5A', '5B', '2B'], '5A': ['5B', '2A', '2B'], '5B': ['2B'], '2B': []})

    def pressing(self, **more):
        with mock.patch.object(advantages, 'pokes', return_value=self.POKES):
            logic = advantages.Advantages('mai', 1, press=1.0, **more)
        logic.clear(0)
        return logic

    def near(self, dx, act=0, opp=0, frame=0):
        v = self.view(act)
        v[advantages.DX] = dx / 640
        v[advantages.OPP_ACT], v[advantages.OPP_ACT_FRAME] = opp, frame
        v[advantages.OPP_GUARDING] = float(opp in advantages.GUARDS)
        return v

    def test_it_goes_in_and_chains_its_normals_on_a_guard(self):
        """press: a run in, its 2A from inside its reach, and on each guard the next normal
        the game cancels into that still reaches, pressed every other step."""
        self.assertEqual(advantages.parse('press=0.6')['press'], 0.6)
        logic = self.pressing()
        got = [logic.step(0, self.near(200)) for _ in range(4)]
        self.assertEqual(got, [(6, ''), (5, ''), (6, ''), (6, '')])     # 66: the run
        self.assertEqual(logic.step(0, self.near(52)), (6, ''))          # not inside its reach yet
        self.assertEqual(logic.step(0, self.near(40)), (2, 'A'))
        self.assertEqual(logic.step(0, self.near(40, 0xcc)), (1, ''))    # out, nothing touched
        self.assertEqual(logic.step(0, self.near(40, 0xcc, 0x99, 0)), (5, 'A'))   # guarded: its 5A
        self.assertEqual(logic.step(0, self.near(40, 0xcc, 0x99, 1)), (5, ''))
        self.assertEqual(logic.step(0, self.near(40, 0xcc, 0x99, 2)), (5, 'A'))
        self.assertEqual(logic.step(0, self.near(42, 0xc8, 0x99, 3)), (1, ''))    # it started
        # the guard touched again (its frame back): the 5B is out of reach by then (65 less
        # the push), the 2B is not
        self.assertEqual(logic.step(0, self.near(50, 0xc8, 0x99, 0)), (2, 'B'))
        self.assertEqual(logic.step(0, self.near(60, 0xcd, 0x99, 1)), (1, ''))
        self.assertEqual(logic.step(0, self.near(70, 0xcd, 0x99, 0)), (1, ''))    # nothing left to chain
        counts = logic.counts
        self.assertEqual((counts['presses'], counts['press_pokes'], counts['press_guarded']), (1, 1, 3))
        # its string over: a crouching guard at the most, and it goes in again
        got = [logic.step(0, self.near(70)) for _ in range(40)]
        self.assertIn((6, ''), got)
        self.assertTrue(set(got[:got.index((6, ''))]) <= {(1, ''), None})
        self.assertEqual(logic.counts['presses'], 2)

    def test_it_lets_go_into_a_move_and_when_it_hits(self):
        logic = self.pressing()
        logic.step(0, self.near(200))
        self.assertEqual(logic.step(0, self.near(200, opp=advantages.FIRST_OWN + 3)), (5, ''))  # far: on it goes
        self.assertIsNone(logic.step(0, self.near(120, opp=advantages.FIRST_OWN + 3)))
        self.assertEqual(logic.counts['press_let_go'], 1)
        self.assertIsNone(logic.step(0, self.near(120)))                 # no chance for a while
        logic = self.pressing()
        self.assertEqual(logic.step(0, self.near(40)), (2, 'A'))
        logic.step(0, self.near(40, 0xcc))
        hit = self.near(40, 0xcc, 0x32)
        hit[advantages.OPP_HITSTUN] = 1.0
        self.assertIsNone(logic.step(0, hit))                            # the combo is its own play's
        self.assertEqual(logic.counts['press_hit'], 1)
        logic = self.pressing()
        up = self.near(40)
        up[advantages.OPP_AIRBORNE] = 1.0
        self.assertIsNone(logic.step(0, up))                             # the agent in the air: no chance
        self.assertEqual(logic.counts['press_chances'], 0)

    def test_a_guarded_normal_of_its_own_play_is_gone_on_from(self):
        logic = self.pressing()
        self.assertIsNone(logic.step(0, self.near(40, 0xc9)))            # its own play's 5B
        self.assertEqual(logic.step(0, self.near(40, 0xc9, 0x99, 0)), (2, 'B'))
        self.assertEqual(logic.counts['press_joined'], 1)
        logic = advantages.Advantages('mai', 1)                          # none of it at zero
        logic.clear(0)
        self.assertIsNone(logic.step(0, self.near(40, 0xc9, 0x99, 0)))

    def meaty(self, **more):
        lying = {0x63: [40 - k for k in range(40)]}
        with mock.patch.object(advantages, 'pokes', return_value=self.POKES), \
                mock.patch.object(advantages, 'knockdown_left', return_value=lying):
            logic = advantages.Advantages('mai', 1, meaty=1.0, **more)
        logic.clear(0)
        return logic

    def test_a_meaty_on_the_agents_knockdown(self):
        """meaty: by the agent lying, into its reach, and its 2A pressed so that it touches
        MEATY_LATE steps after the agent's first free one; a guard, and the string goes on."""
        self.assertEqual(advantages.parse('meaty=0.5')['meaty'], 0.5)
        logic = self.meaty()
        # 40 steps to lie, the 2A touches 4 steps after its press: pressed with 2 left
        got = [logic.step(0, self.near(90, opp=0x63)) for _ in range(3)]
        self.assertEqual(got, [(6, '')] * 3)                             # a walk into its reach
        got = [logic.step(0, self.near(45, opp=0x63)) for _ in range(35)]
        self.assertEqual(set(got), {(5, '')})                            # there: it waits
        self.assertEqual(logic.step(0, self.near(45, opp=0x63)), (2, 'A'))
        self.assertEqual(logic.step(0, self.near(45, 0xcc, 0x60)), (1, ''))
        self.assertEqual(logic.step(0, self.near(45, 0xcc, 0x99, 0)), (5, 'A'))   # guarded: its 5A
        counts = logic.counts
        self.assertEqual((counts['meaty_chances'], counts['meaties'], counts['meaty_pokes'],
                          counts['meaty_guarded']), (1, 1, 1, 1))
        # once a knockdown; from too far it runs (forward let go first) and lets go in time
        logic = self.meaty()
        got = [logic.step(0, self.near(140, opp=0x63)) for _ in range(38)]
        self.assertEqual(got[:5], [(5, ''), (6, ''), (5, ''), (6, ''), (6, '')])
        self.assertIsNone(logic.step(0, self.near(120, opp=0x63)))
        self.assertIsNone(logic.step(0, self.near(40, opp=0x63)))
        self.assertEqual((logic.counts['meaty_far'], logic.counts['meaty_chances']), (1, 1))
        # further than it covers in the time left (2.5 pixels a step until it has covered
        # more): no chance, the knockdown is its own play's
        logic = self.meaty()
        self.assertIsNone(logic.step(0, self.near(200, opp=0x63)))
        self.assertEqual((logic.counts['meaty_apart'], logic.counts['meaty_chances']), (1, 0))
        logic.pace = 5.0
        logic.step(0, self.near(200))
        self.assertEqual(logic.step(0, self.near(200, opp=0x63)), (5, ''))
        # the agent up before its time: let go; and in the open nothing without press
        logic = self.meaty()
        logic.step(0, self.near(45, opp=0x63))
        self.assertIsNone(logic.step(0, self.near(45)))
        self.assertEqual(logic.counts['meaty_late'], 1)
        self.assertTrue(all(logic.step(0, self.near(45)) is None for _ in range(40)))
        with mock.patch.object(advantages, 'pokes', return_value=(None, {}, {})):
            none = advantages.Advantages('mai', 1, meaty=1.0)            # a character with no normal for it
        self.assertEqual((none.meaty, 'meaty' in none.off), (0.0, True))

    def antiair(self, **more):
        # 80-95 pixels away, 96-119 up, falling: with nothing out its 623A, at an air B out its 5A
        table = {(5, 4, 1, 0): [([6, 2, 3], 'A', 0xcc), ([2], 'C', 0xce)],
                 (5, 4, 1, 0xd0): [([5], 'A', 0xc8)]}
        with mock.patch.object(advantages, 'antiairs', return_value=((16, 24), table)):
            logic = advantages.Advantages('mai', 1, antiair=1.0, **more)
        logic.clear(0)
        return logic

    def up(self, dx, height, act=0, opp=0):
        v = self.near(dx, act, opp)
        v[advantages.OPP_AIRBORNE], v[advantages.OPP_Y] = 1.0, -height / 480
        return v

    def test_an_anti_air_at_a_jump_from_a_sure_place(self):
        """antiair: once a jump, the move that is sure from where the agent is, after the
        steps a person needs to see a jump and by the move the agent has out; none at an
        agent moving away."""
        self.assertEqual(advantages.parse('antiair=0.7')['antiair'], 0.7)
        logic = self.antiair()
        rising = [logic.step(0, self.up(150 - 2 * k, 20 + 10 * k)) for k in range(12)]
        self.assertEqual(set(rising), {None})
        got = [logic.step(0, self.up(90, 100)), logic.step(0, self.up(88, 90)),
               logic.step(0, self.up(86, 80))]
        self.assertEqual(got, [(6, ''), (2, ''), (3, 'A')])              # its 623A
        self.assertIsNone(logic.step(0, self.up(90, 100)))               # once a jump
        hit = self.up(84, 70)
        hit[advantages.OPP_HITSTUN] = 1.0
        logic.step(0, hit)
        counts = logic.counts
        self.assertEqual((counts['antiair_chances'], counts['antiairs'], counts['antiair_hit']), (1, 1, 1))
        # seen for 5 steps only: not yet; and not at an agent going away
        logic = self.antiair()
        for k in range(5):
            logic.step(0, self.up(150 - 2 * k, 120 + 5 * k))
        self.assertIsNone(logic.step(0, self.up(90, 100)))
        logic = self.antiair()
        for k in range(12):
            logic.step(0, self.up(60 + 2 * k, 20 + 10 * k))
        self.assertIsNone(logic.step(0, self.up(90, 100)))
        self.assertEqual(logic.counts['antiair_chances'], 0)
        # with an air move out: the move that is sure against that one, or none
        for act, want in ((0xd0, (5, 'A')), (0xd1, None)):
            logic = self.antiair()
            for k in range(12):
                logic.step(0, self.up(150 - 2 * k, 20 + 10 * k))
            self.assertEqual(logic.step(0, self.up(90, 100, opp=act)), want)

    def test_a_button_after_a_guard(self):
        """mash: on the first step it is free after a guard, its fastest normal that
        reaches, three presses every other step, whatever the agent does; none from too
        far; and who was hit first is counted."""
        self.assertEqual(advantages.parse('mash=0.4')['mash'], 0.4)
        with mock.patch.object(advantages, 'pokes', return_value=self.POKES):
            logic = advantages.Advantages('mai', 1, mash=1.0)
        logic.clear(0)
        for k in range(6):
            self.assertIsNone(logic.step(0, self.near(60, 0x97, 0xc9)))    # guarding the agent's 5B
        got = [logic.step(0, self.near(60, 0, 0xca)) for _ in range(7)]   # free: the agent's 5C starting
        self.assertEqual(got, [(5, 'A'), (5, ''), (5, 'A'), (5, ''), (5, 'A'), (5, ''), None])  # 5A reaches 63; 2A 55 does not
        hit = self.near(60, 0xc8)
        hit[advantages.OPP_HITSTUN] = 1.0
        logic.step(0, hit)
        counts = logic.counts
        self.assertEqual((counts['mash_chances'], counts['mashes'], counts['mash_hit']), (1, 1, 1))
        for k in range(6):
            logic.step(0, self.near(120, 0x97, 0xc9))
        self.assertIsNone(logic.step(0, self.near(120, 0, 0)))             # nothing reaches
        self.assertEqual((counts['mash_chances'], counts['mashes'], counts['mash_far']), (2, 1, 1))

    def gapping(self):
        with mock.patch.object(advantages, 'pokes', return_value=self.POKES), \
                mock.patch.object(advantages, 'startups',
                                  return_value={0xc8: (4, 12), 0xc9: (5, 19), 0xce: (14, 34)}):
            logic = advantages.Advantages('mai', 1, gap=1.0)
        logic.clear(0)
        for k in range(6):
            self.assertIsNone(logic.step(0, self.near(60, 0x97, 0xc9)))    # guarding the agent's 5B
        return logic

    def test_a_button_into_a_gap_of_the_agents_pressure(self):
        """gap: after a guard, its fastest normal that reaches where the agent cannot hit
        it first: into a slow move's start, a move's recovery and a walk back in; not into
        a move that comes out first or is out; once a move."""
        self.assertEqual(advantages.parse('gap=0.5')['gap'], 0.5)
        logic = self.gapping()                                             # the agent's 2C next: 14 steps to come out
        got = [logic.step(0, self.near(60, 0, 0xce)) for _ in range(5)]
        self.assertEqual(got, [(5, 'A'), (5, ''), (5, 'A'), (5, ''), None])
        self.assertEqual((logic.counts['gap_chances'], logic.counts['gaps']), (1, 1))
        logic = self.gapping()                                             # its 5A next: out in 4, as fast as the button
        got = [logic.step(0, self.near(60, 0, 0xc8)) for _ in range(7)]    # ... and then out
        self.assertEqual(set(got), {None})
        self.assertEqual(logic.step(0, self.near(60, 0, 0xc8)), (5, 'A'))  # its recovery
        logic = self.gapping()                                             # the agent walks back in
        self.assertEqual(logic.step(0, self.near(60, 0, 0x1)), (5, 'A'))
        logic = self.gapping()                                             # out of reach: nothing
        self.assertIsNone(logic.step(0, self.near(120, 0, 0x1)))
        self.assertEqual(logic.counts['gap_chances'], 0)
        logic = self.gapping()                                             # long after the guard: its own play's
        for k in range(advantages.GAP_AFTER):
            logic.step(0, self.near(120, 0, 0x1))
        self.assertIsNone(logic.step(0, self.near(60, 0, 0xce)))

    def test_an_anti_air_that_loses_in_the_game_is_left_out(self):
        """antiair: a move hit first more than half as often as it hits against a kind of
        jump is left out there after ANTIAIR_PROVE tries (the place's next sure move
        instead), and tried again once ANTIAIR_AGAIN such chances have gone by."""
        logic = self.antiair()

        def jump(came):  # one jump at it: the first step of its answer, then who is hit
            for k in range(12):
                logic.step(0, self.up(150 - 2 * k, 20 + 10 * k))
            first = logic.step(0, self.up(90, 100))
            for k in range(1, 4):
                logic.step(0, self.up(90 - k, 100 - 3 * k))
            v = self.up(84, 60)
            v[advantages.OPP_HITSTUN if came == 'hit' else advantages.SELF_HITSTUN] = 1.0
            logic.step(0, v)
            logic.step(0, self.near(84))  # the agent landed
            return first

        firsts = [jump('back') for _ in range(advantages.ANTIAIR_PROVE)]
        self.assertEqual(set(firsts), {(6, '')})                          # its 623A, hit back each time
        self.assertEqual(jump('hit'), (2, 'C'))                           # then the next sure move, its 2C
        self.assertEqual(logic.counts['antiair_left_out'], 1)
        self.assertEqual(logic.counts['antiair_hit_back'], advantages.ANTIAIR_PROVE)
        for _ in range(advantages.ANTIAIR_AGAIN - 2):
            self.assertEqual(jump('hit'), (2, 'C'))
        jump('hit')                                                       # the 40th: half the record forgotten
        self.assertEqual(jump('hit'), (6, ''))                            # the 623A again
        with mock.patch.object(advantages, 'antiairs', return_value=((16, 24), {})):
            none = advantages.Advantages('mai', 1, antiair=1.0)
        self.assertEqual((none.antiair, 'antiair' in none.off), (0.0, True))

    def objects(self, **more):
        moves = [([2, 3, 6], 'C', 'rf', 0xfc, 45), ([2, 3, 6], 'B', None, 0xfb, 38),
                 ([2, 1, 4], 'A', None, 0x101, 90)]
        with mock.patch.object(advantages, 'object_moves', return_value=moves), \
                mock.patch.object(advantages, 'knockdown_left', return_value={0x62: [60 - k for k in range(60)]}):
            logic = advantages.Advantages('mai', 1, object=1.0, **more)
        logic.clear(0)
        return logic

    def test_an_object_put_out_in_the_open_and_on_a_knockdown(self):
        """object: the move with the most cover its gauges allow, the agent far and in no
        move, or lying for long enough; none with an object of its own out."""
        self.assertEqual(advantages.parse('object=0.5')['object'], 0.5)
        logic = self.objects()
        self.assertIsNone(logic.step(0, self.near(120)))                 # too near
        got = [logic.step(0, self.near(200)) for _ in range(4)]          # no RF: the 236B
        self.assertEqual(got, [(2, ''), (3, ''), (6, 'B'), (6, '')])
        logic.step(0, self.near(200, 0xfb))
        self.assertEqual((logic.counts['objects'], logic.counts['objects_started']), (1, 1))
        out = self.near(200)
        out[advantages.SELF_OBJECTS[2]] = 1.0                            # its object out: none
        self.assertTrue(all(logic.step(0, out) is None for _ in range(60)))
        rf = self.near(200)
        rf[advantages.SELF_RF] = 1.0
        self.assertEqual([logic.step(0, rf) for _ in range(3)][-1], (6, 'C'))   # with RF: the 236C
        # the agent knocked down beside it, lying for 60 steps: the 236B again (38 steps),
        # once; with 20 left, nothing fits
        logic = self.objects()
        logic.step(0, self.near(60, act=0xd0, opp=0x62))                 # (in a move of its own)
        self.assertEqual(logic.step(0, self.near(60, opp=0x62)), (2, ''))
        logic = self.objects()
        for _ in range(42):
            logic.step(0, self.near(60, act=0xd0, opp=0x62))
        self.assertIsNone(logic.step(0, self.near(60, opp=0x62)))
        self.assertEqual(logic.counts['objects'], 0)
        with mock.patch.object(advantages, 'object_moves', return_value=[]):
            none = advantages.Advantages('mai', 1, object=1.0)           # a character with no such move
        self.assertEqual((none.object, 'object' in none.off), (0.0, True))

    def test_none_of_it_at_zero(self):
        logic = advantages.Advantages('mai', 1)
        logic.clear(0)
        self.assertIsNone(logic.step(0, self.view(0x3b, air=True)))
