# Round 28 human test

Round 28 is a single native Ayu agent for testing against Sayuri. It changes Ayu's decision when Sayuri walks into throw range. Install [ayu-round28.efzagent](../tmp/round28/distribution/ayu-round28.efzagent) in the game's or save folder's `agents/` directory. Choose **VS HUMAN**, press **F5** on character select until P1 shows **Ayu round28**, and play Sayuri on P2. Round 25 is the community reference. [Agent controls](agents.md)

## What changed

The November 23 tester beat round 25 with Sayuri twice. Analysis of the input tapes found six ordinary ground throws, all in the second match. Four followed a recognizable walk-in. An eight-frame jump-back intervention in the simulator prevented three of the four, and won six additional matches over 96 against three live Sayuri policies. That earlier test overrode the controller in Python. [Original replay analysis](sayuri-throws.md)

Round 28 learns this response inside the policy that the game already plays. The trigger uses Ayu's 11-frame-delayed observation of both characters on the ground, Ayu free to act, and Sayuri walking forward. It gives up-back additional probability inside 42 pixels, tapering to zero at 44. A fit to 67 eligible frames from seven community matches and two tester matches estimated a logit increase of 9.836. The actor samples a direction every frame it controls. This lets it jump on the first actionable frame but also lets it decline. The combo, okizeme, air-recovery, rising-defense and raw-special modules come from round 25. The file keeps the 16-input history and includes a trainable checkpoint.

Across 35 other community games covering 22 opposing characters, the native policies returned bit-identical action probabilities on all 7,699 sampled observations outside the trigger. On 77 eligible observations, round 28 assigned up-back 65% probability on average. Those frames can cluster within one approach. The exported actor agreed with the reconstructed PyTorch model to within 0.000046 in log probability.

A second build, round 28b, also learned starting values for three raw specials. For every eligible start in 12 tester matches, the simulator compared the recorded buttons with eight frames of button release. Across 39 uses, the estimated prior for 214B became −74 HP, for 236C +58 HP, and for the level-one 641236A super −250 HP. The smaller estimates each came from four uses. Changing these priors affects every matchup.

## Replaying the human decisions

At each eligible walk-in the simulator restored the game state 48 frames earlier. It replayed the actual controls through the cue while warming the native agent, checked that the observations matched, and then let each build play Ayu. Sayuri continued the original inputs. The agents used eight paired sampling seeds at each position. Ground throws count over the first 32 frames, net HP over 120 frames or until the round ends. A replay branch starts with fresh opponent memory. The human cannot respond to what happens inside the branch.

| Source | Opportunities | Ground throws, round 25 | Ground throws, round 28 | Mean change in net HP |
|---|---:|---:|---:|---:|
| Original tester, two games | 5 × 8 | 31/40 | 12/40 | +524 |
| Earlier holdout, seven community games | 12 × 8 | 0/96 | 0/96 | −48 |

Three of the tester's four dangerous positions improved. At the fourth, all eight draws still took the throw. The seven earlier holdout games contained no recorded ground throw after this cue, and the additional OCI Sayuri replay contained no eligible walk-in. Across the seven community games, four had at least one cue.

## Wider community archive

The archive contained 199 in-sync Ayu–Sayuri records. Excluding the fitting and earlier holdout games and deduplicating by Ayu's inputs left 174 matches. Eighty-four contained an eligible walk-in. Eighteen of those games included at least one ordinary ground throw within 32 frames after a walk-in. We played both frozen agents from **all 133 eligible positions**, including the walks that led to a jab, a guard, a retreat or another outcome. Every selected position and original throw label agreed between the stored dataset and the re-simulated game.

| What happened in the original human game | Walks | Paired draws | Round 25 ground throws taken | Round 28 ground throws taken | Change in net HP per walk |
|---|---:|---:|---:|---:|---:|
| A ground throw followed | 24 | 192 | 166 | 76 | +413 |
| Other outcome | 109 | 872 | 1 | 3 | −104 |
| All walks | 133 | 1,064 | 167 | 79 | −11 |

Round 28 avoided 88 throws across the repeated draws. Resampling whole games gives a 95% interval of 3.8 to 12.8 percentage points fewer throws, and −85 to +60 net HP per eligible walk. The throw reduction occurred across several players. One Sayuri player supplied 90 of the 133 walks and accounts for 42 of the 88 prevented throws. A session against a player who regularly walks in for a strike could favor round 25.

The earlier throw-conditioned rule also suggests which human opponents to recruit. At 13 walks, Ayu's delayed view had already shown a normal ground throw against her earlier in that recorded game. At those positions round 25 took 48 throws in 104 draws, round 28 took 11, and round 28 gained 312 net HP per walk. At the other 120 positions it lost 46 HP per walk on average. This retrospective grouping uses the original tape's history. The distributed round 28 file responds from the first walk and has no new memory module.

## Live matches and compatibility

Each set comprised three full matches. Ayu and the base Sayuri policy both played with 11 frames of sight delay and carried opponent memory through the set. Where indicated, the benchmark also supplied Sayuri with scripted throw or anti-air inputs. The comparison uses the same seeds, opponent builds and settings for each Ayu.

| Live Sayuri test | Matches per build | 22d wins | 25 wins | 27a wins | 28 wins | 28b wins |
|---|---:|---:|---:|---:|---:|---:|
| Ordinary, generation 19, seeds 310–315 | 18 | 9 | 10 | 12 | 10 | 3 |
| 80% throw, generation 18, seeds 310–315 | 18 | 14 | 15 | 14 | 16 | 14 |
| 35% throw, generation 17, seeds 410–417 | 24 | 20 | 21 | 22 | 20 | 17 |
| 50% throw, generation 16, seeds 410–417 | 24 | 19 | 20 | 19 | 19 | 15 |
| 65% throw plus anti-air, generation 15, seeds 610–617 | 24 | 13 | 16 | — | 18 | 18 |

Round 28b's raw-special priors reduced ordinary Sayuri wins to 3/18 and held-out wins to 32/48. Round 28 is the build selected for the human test.

On the two held-out opponents with 35% and 50% throw habits, round 28 won 39/48 to round 25's 41/48. The difference was −4.2 percentage points, with a paired 95% interval of −14.6 to +4.2 over the eight common seeds. Round 28 lost 1,214 net HP per match relative to round 25 (interval −3,087 to +252), and took 70 ground throws to round 25's 65 over the entire matches. The local throw reduction against human input tapes does not carry over to every scripted opponent. In the separate throw-plus-anti-air test round 28 won 18/24, round 25 won 16/24, and round 22d won 13/24.

In a further test, generation 14 chose its throw, jab or guard before starting a delayed walk. It played its usual policy between approaches and could anti-air. With an 80% throw choice, round 28 won 18/18 and round 25 won 17/18. With a 20% throw choice both won 17/18. The approach frequently broke off. Against round 25 the 80% profile attempted six scripted throws in 100 approaches and landed zero ordinary ground throws. This drill adds little evidence about the human walk-to-throw tactic.

Across the seven Sayuri profiles round 28 pressed 1.49–1.71 buttons per second overall and 0.54–0.68 while hit or guarding. Against Ikumi, Kano and Mishio, all 18 games reproduced round 25's result, net HP, length and button counts exactly. In side-swapped Ayu mirrors round 28 split 6/12 with round 25 and won 4/12 against round 22d. Round 25 also won 4/12 against round 22d on those seeds.

The Linux SDL client loaded the distributed file in VS HUMAN and played a complete match against a Sayuri agent, which won 2–0. Ayu made 15 combo plans, chose routes on six and played all three of its okizeme plans. Round 28b also completed a native match. The headless Python suite ran 232 tests, with one skip. The benchmark played 696 complete headless matches across the five builds, including controls and mirrors. Human opponents have yet to play these builds. [Full results](../tmp/round28/results.txt)

## Test with a player

Use a three-match set per build so that the existing opponent memory has time to work. Alternate which build goes first across players. Have someone else choose the builds out of the player's sight if possible. Start with normal Sayuri play, then deliberately mix walk-up throws, low attacks and anti-airs. Save the replay and fight record for both builds. Record the match result, close walk-ins, normal ground throws after those walks, and damage lost to jumps that Sayuri baited. Use a second Sayuri player with a different approach if available. Distinguish normal ground throws from running grabs, supers, air throws and parries when scoring. [Fight records](logging.md)

## Reproduction

Use the Release headless library and the training Python environment. Set `PY`, `DATA`, `ARCHIVE`, `RECORDINGS`, and `BASE` to the Python executable, game data, community replay archive, extracted November 23 training recordings and native round 25 file. The trainer requires a new output directory. [Recording extraction](sayuri-throws.md)

```bash
export OPENBLAS_NUM_THREADS=1 OMP_NUM_THREADS=1
games=()
for id in 18796 43840 52010 52015 52665 52668 53561; do
  games+=("$ARCHIVE"/datasets/ayu/"$id"-*.npz)
done
games+=("$RECORDINGS"/20261123-195819-18b4-{011,012}.npz)
"$PY" runs/human-ayu/train_walk_response.py --base "$BASE" --games "${games[@]}" --out tmp/rebuild28
MODEL=tmp/rebuild28/ayu-round28.efzagent
"$PY" runs/human-ayu/sayuri_throws.py sets --data "$DATA" --agent "$MODEL" \
  --generation exploiter16 --throw 0.5 --seed 410 --count 8 --out tmp/rebuild28/r28-transfer-410.jsonl
"$PY" runs/human-ayu/sayuri_throws.py replay --data "$DATA" --session "$SESSION" \
  --recordings "$RECORDINGS" --fight 12 --players "$BASE" "$MODEL" --draws 8 --out tmp/rebuild28/tester12.jsonl
```

Set `SESSION` to the folder containing the November 23 fight records. The community archive scan excludes the seven fitting games and the seven earlier replay checks, including copies with matching Ayu inputs. Its seed, selection and strata are in the script.

```bash
"$PY" runs/human-ayu/sayuri_walk_archive.py --archive "$ARCHIVE" \
  --exclude 18796 43840 52010 52015 52665 52668 53561 35712 12048 12050 19767 12703 12046 20462 \
  --out tmp/rebuild28/archive-survey.json
```

For every match in the manifest with a nonempty `walks` list, use `sayuri_throws.py validate --rep PATH --side SIDE --winner WINNER --frames FRAMES` with `--data`, `--players` and a fresh `--out`. Values are in the manifest. To reproduce 28b, use `sayuri_throws.py replay --risk-casts` on fights 2 through 13, then `fit_raw_specials.py --agent "$MODEL" --model tmp/rebuild28/checkpoint/model.zip --trials TRIAL_FILES --out OUTPUT.efzagent`.

The SHA-256 of the round 28 human-test file is `1128e7a934b4cf9bf1be4ebc36a699dddff472e6ca45f98d46cc2cd08533bab7`. A second build from the documented inputs reproduced all 51 tensors exactly. Re-exporting records a new timestamp and checkpoint archive hash.
