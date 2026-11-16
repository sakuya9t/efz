# Backward compatibility

The modern fork has to play the same game as the original 4.02 `efz.exe`. This document
records how that is tested, in two layers: replays and CPU fights against a fixed
reference (decided 28 October 2026; the whole game state and a fixed reference since
31 October 2026), and, once the fork has netplay of its own, a netplay match against the
original game with EfzRevival (decided 3 November 2026). It also records what the
original's replays can and cannot reproduce, and the rules a change has to follow so the
tests keep working.

Statements about the game are **observed** (read from the matched source) or **inferred**.

## Decisions

- **The test is a suite of fights** (`tests/compat/suite.txt`): replays, and fights of
  the game's CPU (which never plays in a replay). Each must play in the fork exactly as
  it plays in the original, tick by tick. If P1 takes a heavy attack at frame 144 and
  loses 432 HP, and P2 takes a full combo at frame 3400 and loses 5529 HP in all, the
  fork shows the same frames and the same numbers.
- **The original is fixed: the git tag `compat-reference`.** Since 31 October 2026 the
  source no longer has to build `efz.exe` byte for byte: names, types and structure may
  change. The reference is the last source that did (`make check` there), built with
  the test's harness and run under wine; `tests/compat/reference.txt` holds the digest
  of its log for every case. A change passes when every case's log is the reference's,
  byte for byte.
- **Both ways the fork runs the game: with a window and headless** (decided 4 November
  2026). Every case runs in the native game and in the headless runner `efz-headless`
  ([headless.md](headless.md)), which moves its game every 97 frames into a copy on a
  new thread, as the training library's restarts and workers do. Each log must be the
  reference's, and the two must be the same: on a machine where a build doesn't give
  the reference's logs, that the two agree still holds (`--no-reference`).
- **Three layers: replays, the old version's trails, and the network.** The suite (the
  replay layer) checks the fork's simulation against the reference. The recorded layer
  ("The recorded layer" below, decided 4 November 2026) checks it against the old
  version as players have it (`efz.exe` 4.02 with EfzRevival 1.02h), from matches that
  version played and recorded on the owner's machine, in CI. A version with built-in
  netplay must also pass the network layer ("The network layer" below): a match over
  the network against that old version itself, where the state recorded on both ends
  must be the same. No layer replaces another.
- **Compare the whole game state.** After every tick the harness hashes both players
  (all of CPlayer and the character class, the 64 objects of each), the fight scene, the
  game object and the effects, pointers left out. Visual effects are compared too: they
  follow the same code and the same `rand()`, and a change to them is a change.
- **The status is the report.** The log also prints each player's action, frame,
  position, velocity, HP, combo and gauge. The first tick on which a block's hash
  differs is where the bug is; `tools/compat.py explain` names the members that differ.
- A change that touches the simulation sits behind a negotiated ruleset, as netplay with
  EfzRevival 1.02h already requires. With the ruleset off, the suite must pass
  unchanged.

## Running it

```sh
tools/native.sh                      # build/native/efz and efz-headless
tools/compat.py check                # every case in the native game and headless (about 4 minutes, -j 16)
tools/compat.py check fuzz5- cpu-03  # some: by name, or a prefix ending in -
tools/compat.py check --mode game    # one of the two only (game or headless)
tools/compat.py check --no-reference # only that the two agree with each other
tools/compat.py check --windows      # build/windows/efz.exe and efz-headless.exe, under 64-bit wine
tools/compat.py check --exe build/trace/efz.exe   # any 32-bit build with the harness, under wine
tools/compat.py explain cpu-03       # where and how a failing case parts from the reference
tools/compat.py explain cpu-03 --mode headless    # the same for the headless runner
tools/compat.py coverage             # what the suite runs: lines of src/, actions per character
```

`EFZ_DIR` names the original game's folder (its data; the suite has none of it). Work
folders, wine prefixes and the reference's logs are in `$EFZ_COMPAT` (default
`~/.local/share/efz-decomp/compat2`). A check needs only the data and the builds to
test, and runs on Windows as well (Visual Studio's `build/native/RelWithDebInfo/efz.exe`
is found); `explain` also runs the reference (below), so it needs the toolchain's docker
images. When the game and the headless runner part, `check` prints where; their logs
are in `$EFZ_COMPAT/logs/game` and `logs/headless`, for `tools/compat.py diff`.

**In CI.** On every push CI (`.github/workflows/native.yml`) builds both on every
platform and runs what needs none of the game's data: the headless library's own tests
(`ctest -L headless`: the arena's copies, the sprite loader without drawing, the C and
Python API). The suite itself needs the data, which the repository mustn't hold, but
not much of it: the frame data (`.pat`), the palettes, each picture's size and first
pixel, the sound files' headers and `key.ini` are all the game's state depends on.
`tools/compatpack.py` makes a **compatibility pack** of just that from an install
(1.3 MB as a `.tar.gz`, a 750 MB install's worth of pictures and sounds left out)
that `EFZ_DIR` can name:

```sh
tools/compatpack.py build efz-pack --efz "$EFZ_DIR"
EFZ_DIR=efz-pack tools/compat.py check
```

**The encrypted pack** (decided 4 November 2026). The pack is still the game's data
(its moves and palettes), so the repository holds it only encrypted:
`tests/compat/pack.tar.gz.enc` (openssl's AES-256, the key derived by PBKDF2), with
the SHA-256 of what it holds in `tests/compat/pack.sha256`. The key is in no file of
the repository: its owner keeps it, and gives it to CI as the secret
`EFZ_COMPAT_PACK_KEY`.

```sh
EFZ_COMPAT_PACK_KEY=... tools/compatpack.py encrypt --efz "$EFZ_DIR"   # or --key-file
EFZ_COMPAT_PACK_KEY=... tools/compatpack.py unpack efz-pack
```

`encrypt` remakes the pack, and rewrites the encrypted file only when it doesn't
already hold that pack under that key (the archive is the same bytes for the same
files); `unpack` checks the digest, so a wrong key is told as one.

**Keeping the key.** It lives in two places, and in no file of the repository
(`.gitignore` refuses `*.key`):

- the owner's: a file outside the checkout (`--key-file`), and a copy in a password
  manager. GitHub never shows a secret again, so that copy is the only way back to it.
- CI's: the repository secret `EFZ_COMPAT_PACK_KEY` (Settings, Secrets and variables,
  Actions; or `gh secret set EFZ_COMPAT_PACK_KEY < compat-pack.key`).

Nobody else needs it: anyone with the game checks with their own install
(`EFZ_DIR`), and the pack only stands in for it where there is none. A maintainer who
remakes the pack gets the key from the password manager, not over chat or e-mail. The
secret reaches every workflow run of the repository's own branches, so whoever can
push a branch could read it: write access to the repository is access to the key.

**Changing it**, when it may have got out or someone who had it no longer should:

```sh
openssl rand -base64 48 > new.key        # outside the checkout
tools/compatpack.py encrypt --efz "$EFZ_DIR" --key-file new.key   # re-encrypts: the key changed
tools/compatpack.py unpack /tmp/pack-check --key-file new.key      # opens with it
```

then set the secret to the new key and push the new `pack.tar.gz.enc` together (until
both have changed, CI can't open the pack), and replace the copy in the password
manager. The old key still opens the old file in the history, which stays public: a
new key protects the pack from then on, not what was already out.

**Remaking the pack** (a change to what `compatpack.py` keeps, or a new install):
`tools/compatpack.py encrypt` with the current key, and commit the two files.

The `compat` job runs the suite on every push, on GitHub's Linux runners (whose GCC
builds give the reference's logs): it unpacks `tests/compat/pack.tar.gz.enc` with
`EFZ_COMPAT_PACK_KEY`, outside the checkout, builds the game and `efz-headless`, and
runs `tools/compat.py check`. Without the secret (a fork, a pull request from one) it
says so and stops; only its two steps that need the key see it. The repository
variable `EFZ_COMPAT_ARGS` adds options to the check (`--no-reference` on runners whose
builds don't give the reference's logs).

**Measured** (4 November 2026, Windows 11, MSVC): a pack made from a 753 MB install
(1.3 MB as a `.tar.gz`) gives the install's logs, byte for byte, in all 254 cases, in
the game and in the headless runner. The encrypted one unpacks into the same files.

**Measured** (4 November 2026; Windows 11, MSVC 17.14, an EFZ 4.02 install with its own
`key.ini`; `-j 10`, 7 minutes): the game and the headless runner write the same log in
all 254 cases, and each gives the reference's in all 254. Before the order of
`src/effect.cpp`'s draws was fixed that day ([native.md](native.md), "Evaluation
order") both gave it in 146: the other 108 parted at the first hit spark whose
particles Visual C++ drew the other way round. GCC on the same machine (MinGW-w64
16.2) gives it in all 254, before the fix and after. On GitHub's runners, Linux with
GCC gives it in all 254 too, with the same `key.ini` (from the compatibility pack).

## The suite

`tests/compat/suite.txt`, one case per line:

| Kind | Cases | What |
|---|---|---|
| `NAME replay` | 204 | `tests/compat/replays/NAME.rep` played back, both players human. 154 random fights from before the readable source (114 the original recorded, 40 the native game), 3,000 to 6,000 ticks; 50 the reference recorded with the harness's newer scripted input (more motions: supers, dashes, double motions), 4,000 ticks |
| `NAME cpu SPEC TICKS` | 50 | A fight nothing records: characters, stage, palettes and seed (`P1:P2:STAGE:PAL1:PAL2:SEED:C1:C2`), each side the game's CPU (`1`) or the harness's scripted input (`0`). `cpu-NN`: character NN's CPU against another CPU; `bot-NN`: against scripted input |

In all 254 cases, 1,223,436 ticks (about 5.3 hours of fighting). Adding cases:

```sh
tools/compat.py add-fuzz 20 fuzz6- --seed 6 --ticks 4000   # the reference records 20 replays
tools/compat.py add-cpu cpu-ayu-mai 1:2:5:0:0:77:1:1 6000   # a CPU fight
tools/compat.py reference --update fuzz6- cpu-ayu-mai        # their digests
```

then commit the new replays, `suite.txt` and `reference.txt`.

## The reference

`tools/compat.py build-reference` extracts the tag `compat-reference` and runs
`make trace check` in it: `make check` proves its `efz.exe` is the original byte for
byte, and `build/reference/efz.exe` is that code with the harness (`src/trace.cpp`,
hooked into `WinMain`, `CScene3::Update` and `CInput::GetInput`; every other function
is the original's code). `tools/compat.py reference` plays every case in it under wine
(16 at a time, about 4 minutes) and checks each log's digest against `reference.txt`.

To make two runs of the original comparable on every byte, the harness changes four
things in the reference, and the native game does the same:

| | The original | The reference and the native game | Why it is the same game |
|---|---|---|---|
| Memory from `new` | The heap's garbage | Zeroed (the native game's arena always was) | Initialised members are the same; an uninitialised one, `CPlayer::m_hitsLeft`, decided a few hits by the garbage (see "Answered"): zero is one of the original's outcomes |
| `sin`, `cos`, `atan2` | The CPU's `fsin`, `fcos`, `fpatan`, whose last bits differ between CPUs | Correctly rounded to the x87's 64 bits: `port/x87.cpp`, which MinGW builds into the reference (`tools/x87ref.cpp`) | One of the CPUs' results; the same on every machine |
| `rand()` | Seeded from the clock | Seeded with the case's seed (replays: 1) | Only effects and the CPU use it (see below) |
| The rectangle a throw's hit spark is placed at (`CScene3::WillRecoilCounter`, `ResolvePlayerAttack`, `ResolveObjectAttack`) | Read from stack memory the code never set | Zeroed | Only the spark's position |

While a replay plays, the harness also has the controls read as untouched, so what the
menus and `CGame`'s polling see is the same everywhere.

## What is compared

The log (`src/trace.cpp`) starts with a line naming its format; then each line is one
tick: the tick, the replay's read position, each player's status (below), and an
FNV-1a hash of each block of state:

| Block | What |
|---|---|
| `p1`, `p2` | The player's `CPlayer` (`0x3138` bytes), without its object table |
| `p1obj`, `p2obj` | Its 64 objects (`PlayerObject`, `0x98` bytes each) |
| `p1char`, `p2char` | The character class's own members (from `CPlayer`'s end to its size) |
| `scene` | The fight scene's (`CScene3`) members |
| `game` | `CGame`, without the effects |
| `fx` | The effects' ring buffer: 640 `Effect`s and their bookkeeping |

Left out: pointers (the vtable, `m_game`, sprite tables..., Nanase's and Ikumi's second
pattern tables), which differ between builds; `CScene3`'s frames-per-second count and
`lastMessage`, which follow the clock and the window system. Everything else is
compared bit for bit, padding included. The hashes rely on the original's layout,
which the native build keeps (`port/layout.cpp`): a change of layout needs the harness
to hash the members it moved by name.

With `EFZ_TRACE_DUMP` the harness writes every block's bytes, which `explain` diffs
between the reference and the build and maps to members through `tools/members.py
fields` (needs the libclang Python package):

```
cpu-01: FAILED
  tick 2015: first difference
    tick 2015: state differs in fx
  tick 2015, block fx: 2 bytes differ
    effect 258: reference active 1 type 0x38 frame 0 timer 0 x 41.0 y -63.0 ...
    effect 258: build     active 1 type 0x38 frame 0 timer 0 x 57.0 y -61.0 ...
```

## Coverage

`tools/compat.py coverage` builds the native game with gcov (`tools/native.sh
coverage`), plays every case in it, and prints for each source file the share of its
lines the suite runs and how many of its functions it never runs, then the actions each
character reached. `build/coverage/gcov/*.gcov` has each line with its count. A change
to code the suite never runs is not tested by it: add a case that runs it.

## The network layer

**Decided 3 November 2026. Not run yet.** The fork has had netplay built in since November
2026 ([netplay.md](netplay.md)): EfzRevival 1.02h's protocol and rules, checked native
against native (both games' sync records the same on every frame, with and without
latency). Against end (b) it hasn't been run: that needs EfzRevival 1.02h's binaries,
which the machine it was written on doesn't have. Every version with netplay has to pass
this test. The
two ends of the match:

| End | What runs |
|---|---|
| (a) | The version under test, with its own netplay |
| (b) | The original game, as players have it: `$EFZ_DIR/efz.exe` 4.02 (SHA-256 `3a1616d6…6dd66481`) and EfzRevival 1.02h's `EfzRevival.exe`, `EfzRevival.dll` and `DDRAW.dll` from `$REVIVAL_DIR`, all unchanged. Not the reference and not the rebuilt Revival: this layer is there to check the fork against what people actually play on |

The test:

1. The two ends connect over the local network (one machine, or two on one LAN): one
   hosts and the other joins, through EfzRevival's protocol ([revival.md](revival.md),
   "The launcher's protocol").
2. They play a match, both players human (no CPU). A player is either a person or, for
   an unattended run, scripted input. On end (b) the scripted input arrives as key
   presses, so the game reads its keyboard as it always does.
3. Both ends record both players' inputs and the game's state for every confirmed frame
   (a frame whose inputs both ends have).
4. When the match is over, the two records must be the same, frame for frame.

The test runs each way round: (a) hosts and (b) joins, then the reverse. That way each
end has played P1 and P2, and each end's seed has been used. It also runs with latency
added to the link (50-100 ms each way). On a local network the remote input nearly
always arrives before a frame needs it, so the rollback would hardly run.

**What is recorded.** End (b) can't be rebuilt with the harness, so its state is read
without changing anything the game or Revival computes:

- **Revival's sync records.** Each record holds the frame, the scene, the FPU control
  word, both players' actions, inputs and positions, and Revival's random state.
  **Observed:** EfzRevival.dll makes one for every confirmed frame, just before the
  frame runs (`OnlineSession::runFrame`, DLL `0x10070e70`). With `Debug=1` in
  `EfzRevival.ini`, the 1.02h launcher asks the other end for its records, compares
  them with its own, and logs `Checked <frame>` or `ERROR:` with both records to
  `logNet.txt` (`ProtocolStatePlay::handleResendTimer`, `ProtocolContext::checkSync`).
  End (a) therefore has to make and answer these records exactly as Revival does
  (`MessageSync`), and end (b)'s log must show no `ERROR:`.
- **The whole state.** These are the blocks of "What is compared", hashed at that same
  point of every confirmed frame. On end (b) a reader loaded into the game beside
  Revival does the hashing, hooked where Revival makes the sync record. The reader only
  reads. On end (a) the harness does the same.

**What end (b) computes differently from the reference.** **Observed** in Revival's
source, and what each difference means for the comparison and for end (a):

| What | On end (b) | So |
|---|---|---|
| `rand()` | Revival replaces the CRT's (`0x777d61`) with `std::uniform_int_distribution<int>(0, 0x7fff)` over a `std::minstd_rand` seeded with the host's seed (MessageInit field 6), saved and restored with each save state | In netplay, end (a) draws its random numbers the same way, including Visual C++ 2012's distribution |
| `sin`, `cos`, `atan2` | The CPU's `fsin`, `fcos`, `fpatan` | End (a) takes them from the CPU too (`EFZ_HOST_X87`, [native.md](native.md)). Both ends run on one machine, or on CPUs that agree: two copies of the original game on different CPUs part as well ("Answered") |
| Memory from `new` | The heap's garbage | Bytes the original reads before ever setting them are left out of the comparison: the bytes on which two runs of the original game disagree when playing the same replay, such as `m_comboDamage` before the first combo. Where the garbage decides a hit (`m_hitsLeft`, "Answered"), the match parts for real. The original parts from itself the same way, so such a run is reported as that and played again, not counted as a failure of the fork |
| The rectangle a throw's hit spark is placed at | Stack garbage | The spark's position is left out of `fx` |
| x87 precision | 53 bits, as in the original: Revival's `DDRAW.dll` creates its Direct3D 9 device with `D3DCREATE_FPU_PRESERVE` | Nothing to change |

Pointers are left out as in the first layer. Anything else that is left out has to be
named here with its reason.

**When the records differ,** the first frame on which they part is where to look. If
the two ends disagree on that frame's inputs, the fault is in the netplay. If the inputs
agree and the state differs, the fault is in the simulation. End (a) also writes the
match as a replay: added to the suite, it shows whether the fork parts from the
reference on those inputs alone, or only in netplay.

**Where it runs** (decided 4 November 2026). Not on GitHub's runners: end (b) is the
original program and EfzRevival's, which the repository can't hold in any form (the
compatibility pack is data only, and EfzRevival has a licence of its own); Revival
draws through Direct3D 9, which a runner without a desktop may not give it; and two
programs exchanging packets with real timing and added latency make a slow and
flaky check for every push. It runs on a self-hosted Windows runner of the owner's
that has the game and Revival, nightly or by hand, never for pull requests (their
code mustn't run on that machine). Every push gets the recorded layer instead, which
checks the same old version's game without its programs.

## The recorded layer: the old version's trails

**Decided 4 November 2026. Not runnable yet:** it needs the fork's Revival rules and a
reader of Revival's replays (below), and the recorder. It checks the fork against the
game people play, `efz.exe` 4.02 with EfzRevival 1.02h unchanged, where the replay
layer checks it against the reference (the rebuilt `efz.exe`, with the four changes of
"The reference", without Revival). What it doesn't check is the network: the protocol,
live timing and rollback under latency stay the network layer's. The old version plays
on the owner's machine once; CI checks the fork against what it recorded, on every
push.

**A case** is a file in `tests/compat/revival/`, all computed values and no game data,
so the repository holds it as it is (player names left out):

| What | From |
|---|---|
| The match: both characters, the stage, the palettes, Revival's random seed | Revival's replay |
| Both players' inputs, every confirmed frame | Revival's replay |
| The trail: for every confirmed frame, Revival's sync record (frame, scene, FPU control word, both players' actions and inputs, the random state, both positions, the doubles bit for bit) | Revival's `logNet.txt` |

**Recording**, on the owner's machine, once per case:

1. Two copies of the old version, unchanged, with `Debug=1` in `EfzRevival.ini`: one
   hosts, the other joins it at `127.0.0.1`. Netplay is only what makes Revival write
   its records here; nothing about the network is under test.
2. Scripted input drives both players for a whole match, as key presses into each
   window: held directions, button taps and motions (specials, supers, dashes), as the
   harness's scripted input does.
3. Revival saves the match's replay, and each end logs the sync records of both ends
   (`Checked <frame>`, or `ERROR:` with both records).
4. A match with any `ERROR:` is thrown away: the old version disagreed with itself
   (uninitialised memory deciding a hit, "Answered"). Otherwise the replay and the
   records become the case.

**Checking**, in CI on every push, in the game and headless, with the compatibility
pack for data:

1. The fork starts the case's match under Revival's rules: `rand()` as Revival's
   (`std::uniform_int_distribution<int>(0, 0x7fff)` over a `std::minstd_rand`, as
   "The network layer" describes), seeded with the case's seed, the fight starting
   where Revival's replays start it.
2. It reads the recorded inputs, frame by frame, as a replay plays back.
3. Just before each confirmed frame runs, where Revival makes its sync record, the fork
   makes the same record from its own state.
4. The two trails must be the same, frame by frame and field by field.

**When they differ,** the first frame on which they do, and the field, say where:

| What differs | Where the fault is |
|---|---|
| The inputs | Reading Revival's replay |
| Not the inputs, but the random state | Drawing random numbers: Revival's generator, or one call more or fewer than the original makes |
| Neither, but an action or a position | The simulation |

Two kinds of difference are reported as what they are, not as failures: a position
one unit in its last place apart right after a move that sets a velocity from an angle
(the old version takes `sin`, `cos` and `atan2` from the recording machine's CPU,
"Answered"); and a hit that the old version's uninitialised memory decided (recorded
again).

**What the fork needs first**, which netplay and playing Revival's replays need
anyway: the Revival rules (its `rand()`, and where it starts and saves a fight), and a
reader of Revival's replay format. Then the recorder: starting two copies of the old
version with their settings, key presses into each window, and turning the replays and
logs into cases.

## The replay format

**Observed.** `replay\dataN-M.rep` (N, M = 1-9, 81 slots, `src/scene8.cpp`) is a stream
of 16-bit words. It has no frame markers, checksum, random seed or settings: the game
reads the words back strictly in the order it wrote them.

| Part | Words | Where |
|---|---|---|
| Header | P1 character, P2 character, `0x68`, stage, P1 palette, P2 palette | written `src/scene3.cpp:680-686`, read `src/scene2.cpp:126-137` |
| Each fight frame, not while paused | Two values the F4/F5 keys set; the second is the HP the players are reset to (`src/player.cpp:326`) | `CScene3::HandleKeys`, `src/scene3.cpp:595-611` |
| Each player's input | One word: bits `1` right, `2` left, `4` down, `8` up, `0x10`-`0x80` A-D | `src/player.cpp:1027-1029`, decoded at `:1037-1084` |
| Each random draw through `CPlayer::Random` (`0x4108a0`) | The `rand()` value when recording; on playback the word replaces it | `src/player.cpp:667-680` |

A third header word of 100 or less is the stage and means the replay has no per-frame
F4/F5 words (the game then uses 1000 and 9999). **Inferred:** these are replays from
earlier versions.

## What a replay reproduces

- **Randomness that matters to play.** It goes through `CPlayer::Random`, so it is
  recorded. Ayu's LV4 (A, neutral, A, 4, B, C with the gauge full and HP below 3333;
  state `0x13e`, `src/ayu.cpp:124` and `:449-479`) is the clearest case. During the
  move, whether each attacking feather spawns, its type (fast `0x1a0` or slow `0x1a1`),
  its height, speed, rise and starting animation frame are all drawn through the helper
  (`src/ayu_states.cpp:5021-5033`, `src/ayu.cpp:1868-1915`).
- **Guarding.** A human player's guard comes from input: holding away from the opponent,
  standing or crouching, against the attack's high/low flags (`src/player.cpp:563-570`).

## What it does not reproduce

| What | Why | How the test handles it |
|---|---|---|
| Ayu's dash feathers (`0x191`, `0x192`) on 66, 44 and their air versions (states `0xa3`-`0xa6`) | Plain `rand()` (`src/ayu_states.cpp:2157-2373`, `src/ayu.cpp:1562-1605`) | Visual only; compared, with `rand()` seeded the same in both games |
| The burst of objects `0x1f1`/`0x1f2` every character spawns from its object `0x1f0` (e.g. `src/kano.cpp:3784`) | Plain `rand()` for their lifetimes and speeds (e.g. `src/nayuki.cpp:2425-2460`) | **Inferred** visual; compared, as above |
| The game's effects | Plain `rand()` (`src/effect.cpp`) | Visual; compared, as above |
| The CPU (`CpuInput`, and its random guard, `src/player.cpp:551`) | Plain `rand()` and `CPlayer::Random`, which records nothing a CPU's input could be replayed from | Never runs in a recorded fight: replays are recorded from the title menu's replay item, which makes both players human (`src/scene0.cpp:132-133`). The suite's `cpu` cases play it from a seed instead |
| `key.ini` bytes `0x21`-`0x26` (read into `CGame`, `src/game.cpp:37-43`) | Not stored in the replay | Tests run with one fixed `key.ini` |
| Uninitialised variables | Whatever memory held | Zeroed in the reference and the native game ("The reference"); see "Answered": `CPlayer::m_hitsLeft` decides some hits |
| Menus, character select, results | Only the fight is recorded | Out of scope |

## Rules for changes in the fork

- **Keep every helper call.** The same number of calls to `CPlayer::Random`, in the
  same order, at the same points. One call more or less shifts every later word, and the
  replay goes off the rails from that frame.
- **Random numbers that can affect a hit go through the helper.** Plain `rand()` is only
  for visuals. The original already works this way: Ayu's attacking feathers use the
  helper and her dash feathers use `rand()`.
- **Keep the floating point.** Damage is `(int)(base × three double factors)`
  (`src/player.cpp:626`) and positions are doubles. A different compiler, SSE instead of
  x87, or another FPU precision can flip the truncation and change the HP by one. In
  the shared sources that means: floats through `F32` (computed in double, rounded when
  stored), `F32CAST` for a cast to float inside an expression (the original drops it),
  and `sin`, `cos` and `atan2` only through `x87.h`'s versions in the native build
  ([native.md](native.md)).
- **Keep the order of side effects.** The original evaluates a call's arguments right
  to left; a call with two random draws as arguments needs them drawn in that order
  natively (two do, `#ifdef EFZ_NATIVE`). An operator's operands it evaluates left to
  right, where C++ lets each compiler choose: two draws in one expression are drawn in
  statements of their own, in the original's order (as `src/effect.cpp`'s particles
  are: Visual C++ 2022 drew them the other way round, [native.md](native.md)). New
  code doesn't draw twice in one expression.
- **A change that isn't meant to change the game passes the suite unchanged**
  (`tools/compat.py check`), in the game and headless alike. This covers renames and
  other readability work, SDL3, the headless platform and library, widescreen, input
  rebinding and the like. Code the suite doesn't run (`coverage`) isn't tested by it:
  add a case that does before changing it.
- **Netplay keeps EfzRevival 1.02h's protocol and its rules.** Against a 1.02h peer, the
  fork speaks that peer's protocol (version `0x66`, the messages of `EfzPackets.proto`).
  It also computes what the original game with Revival computes (the table in "The
  network layer"). A version with netplay passes both layers.

## The status line

What the log prints for each player on each tick, besides the hashes. Offsets are in
`CPlayer`.

| Field | Member and offset | Notes |
|---|---|---|
| HP | `m_hp`, `+0x108` | 9999 full (`src/player.cpp:216`) |
| HP when the current combo began | `m_comboStartHp`, `+0x10c` | `src/player.cpp:624` |
| The combo's damage so far | `m_comboDamage`, `+0x100` | `src/player.cpp:635`. **Observed:** uninitialised until a combo starts: garbage, different on every run of the original. Compared while the hit count is above 0 |
| Hits in the current combo | `m_comboHits`, `+0x174` | `src/player.cpp:632` |
| Position | `x`, `y`, `+0x20`, `+0x28` | Doubles; y is negative in the air. Compared bit for bit |
| Velocity | `vx`, `vy`, `+0x30`, `+0x38` | Doubles, compared bit for bit |
| Frame of the action | `frame`, `+0xa` | |
| Facing | `facing`, `+0x50` | 1 or -1 |
| Action | `pattern`, `+0x8` | e.g. Ayu's forward dash is `0xa3` |
| Gauge | `m_gauge`, `+0x148` | A level per 1000, 3000 full: moves test `>= 0x3e8`, `0x7d0` and `0xbb8` |

The replay word offset is logged with each tick too: if the fork and the original read
different words first, the bug is in what the fork consumes; if the words agree and
the state differs, it is game logic.

## Answered

- **Does the original play each replay the same way every time?** Nearly always, not
  always. **Observed:** of 154 replays (114 it recorded, 40 the native game recorded;
  [native.md](native.md)), it played 5 differently from run to run: an attack that
  hits in some runs misses in others, the rest of the match then parting. The cause is
  `CPlayer::m_hitsLeft` (`+0x16c`), the hits the current attack can still land: each
  attack's code sets it during the attack and each hit takes one off, but nothing sets
  it before a player's first attack, and the hit test (`CScene3::ResolvePlayerAttack`,
  `src/scene3.cpp:1052`) requires it above 0. The frame an attack's box first appears
  is tested once before its code sets the field (Mizuka's state `0xc8` sets it on
  frame 2, at the update after the one that starts that frame; Kaori's `0xcd` on frame
  3). So a player's first attack hits there when the heap's garbage is positive as a
  short. Memory dumps of a run that hits and one that misses show it on all five: the
  attacker's field holds 27022, 20255, 19239, 19272 and 7196 in the one and -23847,
  -27669, -6235, -17603 and -13365 in the other. The native game's memory starts
  zeroed, so such an attack never hits there, which is one of the original's two
  outcomes; on all 5 the native game plays exactly as one of the original's runs.
  EfzRevival 1.02h doesn't initialise the field either (it only reads it to draw
  hitboxes), so two players on it could part the same way. The reference zeroes the
  heap as the native game does, so the suite has one outcome.
- **Is the original the same on every CPU?** No, though rarely does it show. `sin`,
  `cos` and `atan2` are the x87's `fsin`, `fcos` and `fpatan`, whose last bits are
  each CPU's own: this AMD Zen 4's differ from the correctly rounded value on a third
  of inputs, which changes a velocity set from an angle (`ObjBase::SetVelocity`) by one
  unit in the last place about once in a thousand calls. Intel's microcode differs again. The native game uses the
  correctly rounded value on every machine; `EFZ_HOST_X87` builds it with the
  machine's own instead ([native.md](native.md)). Effects show it often: with them in
  the comparison, 3 of the first 3 cases parted on this machine until the reference
  took the correctly rounded values too.
- **Does `<math.h>`'s float `sin` round to float?** No. Visual C++ .NET 2003 drops the
  cast in its inline `sinf`, so `sin((float)rand()) * 6.0f` (effect `0x2e`) is the
  64-bit result times 6, rounded to double. `fabs` of a float expression does round: its
  argument is passed as a float (effect `0x2f`, `FABSF` in `src/efz.h`).

## Open questions

- Feathers share the 64-slot object table with projectiles. When it is full the oldest
  object stops being updated (`CPlayer::AdvanceObjectHead`, `src/playerobj.cpp`), so a
  random number of feathers could drop a projectile in one playback only. Whether Ayu
  can reach 64 objects depends on feather lifetimes in `ayu.pat`.
- Which of `key.ini` bytes `0x21`-`0x26` change the fight.
- EfzRevival's replays are a format of their own (it replaces `CReplayFile`'s methods;
  see [revival.md](revival.md)). Playing them is later work.
