# Ayu against Sayuri's throws

An eight-frame jump back on a visible walk-in won 64 of 96 simulated matches against three Sayuri policies. Round 25 won 58 on the same seeds. Waiting until a confirmed ground throw before using the response won 45 of 60, compared with 42 for round 25 on that subset. The independent human replay sample contained zero ground throws following this cue. Both responses are implemented in the headless evaluator. Round 25 remains the community file.

The November 23 tester session contains two complete Sayuri matches against round 25, fights 011 and 012. The original analysis counted 21 transitions into Ayu's thrown poses. Sayuri's action on each transition distinguishes the punish. Both fights were reproduced from their original controls and checked against the stored observation at every frame.

| Sayuri action when Ayu entered a thrown pose | Entries | Distinct activations |
|---|---:|---:|
| Ground throw, horizontal direction + C | 6 | 6 |
| Air throw | 2 | 2 |
| 214 parry counter | 6 | 6 |
| 41236 running grab | 4 | 4 |
| 21436 super | 3 | 2 |

All six normal ground throws occurred in fight 012. The two level-two super entries 39 frames apart came from the same activation. The parry puts Ayu in a thrown pose 40 frames after the counter has triggered. The stance was visible for 5–12 frames before triggering, shorter than Ayu's 11-frame sight delay in five cases. For four of the six running-grab or super activations, Ayu was already in hitstun when Sayuri began the move. The opening hits were 2A, 5A, jumping B and jumping C. They landed 3, 4, 8 and 9 frames after the attacks began. [Sayuri's actions](../src/efz.h)

## Same-position trials

For both source fights the simulator branched at every cue from Ayu's 11-frame-delayed view. Each branch tried eight frames of walking back, jumping back, crouch-jabbing then guarding, or low guarding. After eight frames both players continued with their original relative inputs. Payoff was net HP over 120 frames or until the round ended. Every unmodified branch matched the recorded observation at every step. This measures what changing the input could have done against the recorded opponent sequence. Full games below let the opponent react.

| Delayed cue | Occurrences | Original thrown-pose entries within the scoring horizon | Result |
|---|---:|---|---|
| Sayuri walking forward within 42 pixels, both grounded and Ayu free | 5 | 4 normal ground throws | Jumping back left 1 ground throw and gained 572 net HP per cue. Jab left 3 and gained 231. Retreat and guard left all 4. |
| Running grab or 21436 super visible | 16 | 8 entries across the windows | Each of the four responses averaged −48 HP and counted 9 entries. |
| Parry stance visible | 10 | 6 parry counters | Guarding left all 6 and averaged +13 HP. |

Cues fire on entry and have a 32-frame cooldown per type. Windows can overlap, so the table counts outcomes per opportunity. Additional diagnostic branches started 12, 24, 48 or 64 frames before each of the 21 recorded entries. Jumping back exactly 12 frames before contact removed five of six ordinary ground throws from a ±12-frame window. Guarding exactly 48 frames before the parry victim pose removed all six parry entries from that window. The second result uses foreknowledge of timing. The observable parry cue failed to prevent any of the six.

The walk-and-jump response was frozen before a separate replay check on the seven Sayuri matches in the previous human holdout and the November 25 OCI Sayuri match. Twelve eligible walks occurred in the seven human matches and zero in the OCI match. On those 12 walks the original inputs led to zero ground throws in the scoring windows, and jumping lost 99 HP per decision on average. The seven human matches contained two normal ground throws elsewhere.

## What preceded the running grabs and supers

Four distinct carries began while Ayu was already in hitstun. Replacing eight frames of inputs with standing back immediately before the opening hit still led to a carry in all four. Repeating the substitution at the input that started Ayu's preceding move gave a different result.

| Ayu's move | Frames from substituted input to opening hit | Did Sayuri still finish with the carry? | Net HP change |
|---|---:|---|---:|
| 236C | 78 | No | +438 |
| Jump A | 2 | Yes, later | +1,082 |
| 214B | 77 | No | +2,298 |
| Level-one 641236A | 79 | No | +1,850 |

These four positions were selected because the carry happened. To measure the cost of avoiding successful specials as well, a separate check tried standing back at **every** 236C, 214B and level-one 641236A in the same two matches and the separate OCI game. Over a fixed 240-frame horizon this lost 74 HP per use in fight 011 (9 uses), gained 934 in fight 012 (6 uses), and lost 16 in the OCI game (1 use). These are offline experiments using the recorded move onset. A playable selector would need to identify the proposed command from Ayu's own inputs and recognize the risk before committing.

## Full matches

Both agents saw the game 11 frames late. Round 25's opponent was a live Sayuri policy with combos. The throw-heavy profile also gave its scripted opponent an 80% chance of attempting a throw on a close-range opportunity. The two profiles use different policy generations, so the causal comparison is between candidates on identical seeds within each profile. Sets contained three matches, with fresh opponent memory for each set. The conditional response activates only after the delayed observations show Sayuri completing a normal ground throw against Ayu. That memory carries between matches in a set.

| Live Sayuri defender | Round 25 wins | Always respond to the walk | Respond after an observed ground throw |
|---|---:|---:|---:|
| Ordinary, seeds 240–245 | 5/18 | 6/18 | — |
| Throw-heavy, seeds 240–245 | 11/18 | 12/18 | — |
| Ordinary, seeds 260–265 | 10/18 | 11/18 | 10/18 |
| Throw-heavy, seeds 260–265 | 13/18 | 14/18 | 14/18 |
| Third policy, 50% throw habit, seeds 280–287 | 19/24 | 21/24 | 21/24 |

Against throw-heavy Sayuri on seeds 260–265, the conditional rule activated on 43 walks and gained 1,847 net HP per match. The paired 95% bootstrap interval over the six sets ran from −180 to +3,985 HP. Ground throws taken fell from 47 to 42. Adjusting for match length gives 1.10 and 1.08 per minute. Against ordinary Sayuri, the unconditional response gained a win in both seed groups despite zero ground throws in either baseline. The conditional rule never activated on the fresh ordinary seeds and exactly reproduced the reference matches.

The third policy used fresh seeds, a different generation and a 50% throw habit. Both candidates won all eight sets to round 25's seven. Ground throws taken fell from 45 to 42 for both candidates. Mean net HP per game changed by −155 for the unconditional response and −49 for the conditional response, with both intervals spanning losses and gains. Press rates on this defender were 1.69 and 1.67 per second overall and 0.63 and 0.65 under pressure. Across all three policies the study played 252 full games, including the shared controls.

## Reproduction

Use the Release headless library and training environment from the [neutral decision study](neutral-trials.md). In the following Bash commands, set `PY` to the training Python executable, `DATA` to the installed EFZ game, `BASE` to the round 25 file, and `SESSION` to the extracted November 23 session folder. The output directory should be new.

```bash
export OPENBLAS_NUM_THREADS=1 OMP_NUM_THREADS=1
OUT=tmp/sayuri-study
mkdir -p "$OUT"
"$PY" runs/human-ayu/from_record.py "$OUT/recordings" "$SESSION/fight-011.jsonl" "$SESSION/fight-012.jsonl" --data "$DATA"
for fight in 11 12; do
  "$PY" runs/human-ayu/sayuri_throws.py replay --data "$DATA" --session "$SESSION" \
    --recordings "$OUT/recordings" --fight "$fight" --out "$OUT/replay-$fight.jsonl"
  "$PY" runs/human-ayu/sayuri_throws.py replay --data "$DATA" --session "$SESSION" \
    --recordings "$OUT/recordings" --fight "$fight" --openings --out "$OUT/commit-$fight.jsonl"
  "$PY" runs/human-ayu/sayuri_throws.py replay --data "$DATA" --session "$SESSION" \
    --recordings "$OUT/recordings" --fight "$fight" --all-commits --out "$OUT/allcast-$fight.jsonl"
done
```

For the external replay check, pass `validate --rep FILE --side AYU_SIDE --frames FRAME_COUNT --winner WINNER_SIDE --data "$DATA" --out FILE.jsonl` to the same script. Use archive IDs 35712, 12048, 12050, 19767, 12703, 12046 and 20462 with the side, frame count and winner from the archive manifest. For OCI, use 20261125-200057, Ayu side 0, 8,260 frames and winner 0. Name these output files `valid-ID.jsonl`.
Repeat the OCI command with `--all-commits --out "$OUT/allcast-oci.jsonl"` for the special-move comparison.

```bash
for profile in ordinary grabs; do
  generation=exploiter19
  habit=0
  if [[ "$profile" == grabs ]]; then generation=exploiter18; habit=0.8; fi
  for first in 240 260; do
    modes=(base jump)
    if [[ "$first" == 260 ]]; then modes+=(conditioned); fi
    for label in "${modes[@]}"; do
      extra=()
      if [[ "$label" != base ]]; then
        extra=(--rules '{"walk":"jump"}')
        if [[ "$label" == conditioned ]]; then extra+=(--after-ground); fi
      fi
      "$PY" runs/human-ayu/sayuri_throws.py sets --data "$DATA" --agent "$BASE" \
        --generation "$generation" --throw "$habit" --seed "$first" --count 6 "${extra[@]}" \
        --out "$OUT/$label-$profile-$first.jsonl"
    done
  done
done
for label in base jump conditioned; do
  extra=()
  if [[ "$label" != base ]]; then extra=(--rules '{"walk":"jump"}'); fi
  if [[ "$label" == conditioned ]]; then extra+=(--after-ground); fi
  "$PY" runs/human-ayu/sayuri_throws.py sets --data "$DATA" --agent "$BASE" \
    --generation exploiter16 --throw 0.5 --seed 280 --count 8 "${extra[@]}" \
    --out "$OUT/$label-transfer-280.jsonl"
done
"$PY" runs/human-ayu/sayuri_report.py "$OUT"
```
