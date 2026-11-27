# Round 25 neutral decisions

This experiment asks whether another entry from a position before contact earns more HP than round 25, whether Ayu can identify that entry with 11-frame sight, and whether the improvement survives a whole set. Round 25 is the reference for every comparison.

Round 25 remains the community file after 492 simulated matches. Learning which ground entry to use reduced held-out wins. The closest candidate sampled a fresh input when Ayu first proposed a jump. It tied round 25 at 15 wins in 36 held-out games and gained an estimated 2,097 net HP per game, with a 95% interval from −1,448 to +5,569. All human-match evidence comes from existing replays.

## Paired decisions

Development uses 21 in-sync community replays against Kano, Ikumi and Mishio. The held-out sample uses 17 against Sayuri, Mizuka B and EX-Nanase. Both players in each held-out replay are absent from the development replays, as identified in the archive. Three separate OCI replays supply positions actually reached by round 25. After restoring a position, a live frozen policy plays the opposing character. These measurements describe counterfactual play against those policies.

Up to six opportunities per replay are sampled, at least 160 frames apart. From Ayu's delayed view she is grounded, free, and 65–260 pixels away, with neither side in a combo. The sampler includes opportunities where she has already committed to a different action in the intervening 11 frames. Each branch restores the same simulator state and replays the preceding 40 frames of actual inputs for both players. The harness checks the resulting observation against the recording. The players begin with fresh long-term opponent accounts. The first baseline in each replay is also repeated at identical seeds.

Each candidate starts from round 25, takes control for up to 24 frames, then hands control back to its native policy and planners. The old teacher is the policy from league11-r7's best checkpoint at delay 11. The other choices are walking 12 frames then guarding, walking ten frames then pressing 2B, a three-frame 236C when the delayed gauge permits, guarding low for 16 frames, and replaying the closest of 193 human ground-entry clips. Those clips come from 20 development games. Retrieval excludes the current replay and uses delayed visible cues. All forced inputs go into the native player's actual input history.

The defender is its character's exploiter18 with combos in development and exploiter19 on the held-out and OCI positions. About half of the positions also face the scripted anti-air. Two independent pairs of policy seeds play every option. The score is net HP through 160 frames, extended through an ongoing combo up to frame 320, or until the round ends. This horizon can miss a later return from a knockdown or expenditure of meter.

## What the paired decisions earned

Values are mean net HP differences from keeping round 25 at the same decision. Each replay has equal weight. Parentheses give a 95% bootstrap interval over source replays. The three OCI files describe three specific games. Intervals over those files have little resolution.

| How the choice was made | Development, 125 positions | Held-out, 100 positions | OCI, 18 positions |
|---|---:|---:|---:|
| Highest payoff on the draw being scored, hindsight | +1,244 | +1,393 | +1,536 |
| Highest payoff on the other independent policy draw | +121 (−23 to +270) | +256 (−1 to +500) | +403 (+45 to +772) |
| Learned from observable cues, including known inputs | +104 (−37 to +231) | +14 (−146 to +162) | +224 (−23 to +414) |

Every fixed intervention had a negative mean in development, so the fitted fixed choice kept round 25. Across the 17 held-out source games the chooser gained 51 HP per decision against Mizuka B, gained 39 against EX-Nanase and lost 34 against Sayuri, with seven, three and seven source games respectively. These observations motivate measuring complete sets.

The larger hindsight gains depend on knowing the outcome of the draw being scored. A repeatability check took three positions from each of three held-out games and each of three OCI games. All options played ten policy draws per position. Each draw in turn was reserved for scoring while the other draws ranked the options. With one ranking draw, the selected entry lost 37 HP per held-out decision and 59 per OCI decision. With three, five and nine ranking draws, the held-out gains were 87, 74 and 86 HP. The corresponding OCI gains were 8, 86 and 23 HP. At nine draws the intervals were −94 to +250 and −151 to +167 HP. This smaller sample gives little support to the size of the single-draw hindsight estimate.

At the moment control actually changed, Ayu was already airborne in 16 of 100 held-out positions and 10 of 18 OCI positions. She appeared grounded in every delayed view used to select those positions. Two additional controls test the choice of timing and the source of the suggested inputs.

- On the human holdout, play the human's actual next 24 inputs with the same interruption rules as a retrieved clip. This uses future recorded inputs strictly for diagnosis. The defender still plays live and can respond differently.
- On the three round 25 OCI replays, branch when Ayu proposes her first up input after 11 frames without one, while the delayed view meets the same eligibility rules. The reference issues that exact one-frame input, then resumes the native policy. The same alternative prefixes and previously fitted chooser can instead cancel it; choosing round 25 lets the proposed input through. Six independent draws score each sampled takeoff.

On the 100 held-out human positions, playing the original human prefix gained 191 HP per decision over round 25 (−38 to +423). The retrieved clip gained 71 (−180 to +330). The paired difference between the two was +120 (−149 to +411). Even giving Ayu those original inputs leaves substantial uncertainty about the return against a different defender.

At all 20 proposed takeoffs Ayu was still grounded. Letting the restored round 25 policy sample its own action gained 232 HP per decision over issuing the recorded up input, with gains of 166, 377 and 152 in the EX-Nanase, Sayuri and Mishio replays. Forcing walk-and-guard lost 294 HP on average. Walking into 2B gained 374 against Sayuri, lost 657 against Mishio and broke even (−3) against EX-Nanase. The fitted chooser gained 11. Each character here has just one source game. The immediate-choice result is measured against live simulated defenders, and the restored policy has a different random draw and shorter history than in the source game.

### Which command came out

The game checks a forward–down–down-forward input in the last 60 frames before checking a down–down-forward–forward input in the last 45. Starting a 236C input while already advancing can complete 623C. The command probe recorded the first new character move and whether 236C appeared within 32 frames, using the first policy draw for each meter-eligible position. [Ayu's input reader](../src/ayu.cpp)

| Recent exact forward in the 57 frames preceding the three-frame input | Held-out attempts | 236C appeared | First new move was ground or air 623C |
|---|---:|---:|---:|
| Yes | 35 | 8 | 19 |
| No | 35 | 26 | 0 |

A rule that tries 236C only with available RF, no such forward, and no up input since the delayed observation gained 2 HP per held-out decision (−173 to +173) and lost 210 per OCI decision. The input history helps explain what Ayu can execute. It gives little evidence on its own about when spending meter is profitable.

## Learning and sets

The chooser fits a separate ridge regression to the paired HP difference for each option against round 25. Each position's draws share one unit of weight. Inputs describe separation, RF gauge, the opponent's airborne and attack states, projectiles, wall position, relative velocity, and Ayu's known directional and button inputs since the delayed view. The two interactions are distance with airborne and attack state. The ridge penalty is 20 on slopes. Competing options must beat round 25's predicted difference of zero.

Whole sets compare round 25, the highest development-average choice available with current meter, a random mixture at the context chooser's development frequencies, the context chooser, and the same chooser adapting within its set. The adaptive version records actual net HP less expected net HP per option, clips an exchange's residual at 3,000 HP in either direction, and shrinks the average toward zero with 12 prior uses. It updates when the exchange is visible or the round has ended. All arms retain the reference agent's existing adaptation. Each set has one defender with its own private memory. The regular batched anti-air benchmark now stores the response record per opponent slot as well. A new training set clears that slot and a continuing set retains it. Comparisons with earlier pooled-memory benchmark runs require remeasuring both files. Seed parity selects whether that defender anti-airs. Each policy plays the same four seeds and three matches per set per character.

The primary transfer test is match wins and net HP on the three held-out opponent policies. The Kano and Ikumi controls reuse the development opponent policies with fresh whole matches. Their purpose is to detect loss of a profitable air game. A favorable snapshot score alone is insufficient for replacing the community file.

| Policy | Held-out match wins (36) | Held-out sets won (12) | Net HP per match relative to round 25 |
|---|---:|---:|---:|
| Round 25 | 16 | 5 | 0 |
| Best fixed choice in development | 16 | 5 | 0 |
| Random at the chooser's development frequencies | 12 | 3 | −2,306 |
| Chooser using delayed observations and known inputs | 13 | 3 | −1,234 |
| Chooser also updating within the set | 12 | 3 | −1,330 |

The per-character match wins for round 25 and the observable chooser were 4 and 3 against Sayuri, 8 and 6 against Mizuka B, and 4 and 4 against EX-Nanase. Resampling the 12 paired sets gives a 95% interval of roughly −28 to +11 percentage points for the chooser's change in match wins. Its press rate was 1.43 per second overall and 0.65 under pressure, compared with 1.46 and 0.66 for round 25. The adaptive chooser won five first matches, two second matches and five third matches. The sample gives no evidence that learning within this set improved later games.

On the two familiar control defenders, round 25 and the contextual chooser each won 16 of 24 matches. The random mixture won 15. The adaptive chooser won 20 and took all eight sets, compared with seven sets for round 25. Its estimated net HP gain was 2,155 per game (−1,015 to +5,770). Pooling those familiar opponents with the new opponents would mask the reversal in the adaptive result.

### Familiar characters against unseen defenders

A follow-up gives the chooser practice against Sayuri, Mizuka B and EX-Nanase. It samples further human replays with neither participant from the 17 held-out games. The practice defenders alternate between exploiter16 and exploiter18. For each option, character and defender, the fit measures the residual over the original contextual prediction and shrinks its average with 12 prior positions. The chooser takes the lower of the two defender corrections when ranking options. Its confirmation uses exploiter19, seeds 90–93 and three-match sets. This is an exploratory follow-up to the original character holdout.

The restore check excluded frame 4,764 of human replay 12926 from every option because projectile positions and velocities diverged during warm-up. Each run writes rejected positions beside its results.

The extra training covered 42 positions each against Sayuri and EX-Nanase and 41 against Mizuka B. The corrected chooser lost 43 HP per decision on the 100 held-out human positions (−225 to +139). On fresh full games it won 13 of 36 and four of 12 sets. Round 25 won 16 games and seven sets. The difference in net HP per game was −226 (−4,080 to +3,628). Giving the chooser matchup practice did not recover the original transfer loss.

### A second draw before takeoff

The takeoff comparison suggested trying a smaller intervention. A second independently seeded round 25 player sees the same delayed observations, receives the same actual inputs, and runs the same modules. When the first player proposes up at an eligible decision, Ayu uses the second player's current input for that frame. Both players then resume observing what actually happened. The rule requires 11 frames without an up input and allows at most one substitution in 11 frames. Either player can choose to jump. The test uses seeds 110–113, the three held-out defenders and the two controls. The immediate takeoff results informed this rule before those sets were played.

| Fresh comparison | Round 25 | Second draw | Paired net HP per game, 95% interval |
|---|---:|---:|---:|
| Three held-out defenders, 36 games each | 15 wins, 5 sets | 15 wins, 4 sets | +2,097 (−1,448 to +5,569) |
| Two control defenders, 24 games each | 20 wins, 7 sets | 18 wins, 7 sets | +44 (−2,814 to +3,258) |

In the held-out games the second draw supplied a different direction from up on 169 of 269 proposals and selected up again on the other 100. It gained one win against Sayuri, tied against Mizuka B and lost one win against EX-Nanase. Presses per second were 1.52 overall and 0.64 under pressure. The immediate gain at the recorded takeoffs transferred to an uncertain full-game HP advantage and zero additional match wins.

## Reproduction

Use a Release headless library, the existing training Python environment, and generated motions and frame data in `runs/human-ayu`. From the repository root, set `PY` to the Python executable, `DATA` to the installed EFZ data, `ARCHIVE` to the community collection, `BASE` to the round 25 release, and `OCI` to the directory with the three November 25 netplay replays. Run these commands in Bash. The evaluators create new output files and refuse to overwrite an existing run.

```bash
cmake --build build/headless --target efz_env -j 4
export OPENBLAS_NUM_THREADS=1 OMP_NUM_THREADS=1
OUT=tmp/neutral-study
mkdir -p "$OUT/teacher"
ln -s "$PWD/runs/human-ayu/agent-league11-r7/best.zip" "$OUT/teacher/best.zip"
"$PY" -c 'import json,sys; from pathlib import Path; c=json.loads(Path(sys.argv[1]).read_text()); c["delay"]=11; Path(sys.argv[2]).write_text(json.dumps(c))' \
  runs/human-ayu/agent-league11-r7/config.json "$OUT/teacher/config.json"
"$PY" python/examples/export_agent.py "$OUT/teacher/best.zip" --no-train --out "$OUT/teacher.efzagent"

TRIAL=("$PY" runs/human-ayu/neutral_trials.py --data "$DATA" --archive "$ARCHIVE"
       --agent "$BASE" --teacher "$OUT/teacher.efzagent" --oci "$OCI" --games 7 --starts 6)
"${TRIAL[@]}" --harvest --out "$OUT/demo.npz"
for split in dev test oci; do
  "${TRIAL[@]}" --split "$split" --out "$OUT/$split.jsonl"
  "${TRIAL[@]}" --split "$split" --demos "$OUT/demo.npz" --out "$OUT/demo-$split.jsonl"
  "${TRIAL[@]}" --split "$split" --context-only --out "$OUT/context-$split.jsonl"
  "${TRIAL[@]}" --split "$split" --command-probe --out "$OUT/command-$split.jsonl"
done
for split in test oci; do
  "${TRIAL[@]}" --split "$split" --demos "$OUT/demo.npz" --replicate --draws 10 --out "$OUT/replicate-$split.jsonl"
done
for char in sayuri exnanase mishio; do
  "${TRIAL[@]}" --split oci --char "$char" --starts 8 --draws 6 --jump-intent \
    --demos "$OUT/demo.npz" --out "$OUT/jump-$char.jsonl"
done

for char in sayuri mizukab exnanase ikumi kano; do
  generation=exploiter19
  if [[ "$char" == ikumi || "$char" == kano ]]; then generation=exploiter18; fi
  "$PY" runs/human-ayu/neutral_sets.py --char "$char" --generation "$generation" \
    --data "$DATA" --agent "$BASE" --teacher "$OUT/teacher.efzagent" --demos "$OUT/demo.npz" \
    --dev "$OUT/dev.jsonl" --dev-demo "$OUT/demo-dev.jsonl" --dev-context "$OUT/context-dev.jsonl" \
    --out "$OUT/sets-$char.jsonl"
  "$PY" runs/human-ayu/neutral_sets.py --char "$char" --generation "$generation" \
    --modes round25 resample_jump --seed 110 \
    --data "$DATA" --agent "$BASE" --teacher "$OUT/teacher.efzagent" --demos "$OUT/demo.npz" \
    --dev "$OUT/dev.jsonl" --dev-demo "$OUT/demo-dev.jsonl" --dev-context "$OUT/context-dev.jsonl" \
    --out "$OUT/redraw-$char.jsonl"
done
for char in sayuri mizukab exnanase; do
  "${TRIAL[@]}" --split test --char "$char" --recorded-entry --out "$OUT/recorded-$char.jsonl"
  "${TRIAL[@]}" --split matchup --char "$char" --demos "$OUT/demo.npz" --out "$OUT/matchup-$char.jsonl"
  "$PY" runs/human-ayu/neutral_sets.py --char "$char" --modes round25 matchup --seed 90 \
    --data "$DATA" --agent "$BASE" --teacher "$OUT/teacher.efzagent" --demos "$OUT/demo.npz" \
    --dev "$OUT/dev.jsonl" --dev-demo "$OUT/demo-dev.jsonl" --dev-context "$OUT/context-dev.jsonl" \
    --matchup-training "$OUT/matchup-$char.jsonl" --out "$OUT/confirm-$char.jsonl"
done
"$PY" runs/human-ayu/neutral_report.py "$OUT"
```
