# Netplay

The native game has EfzRevival 1.02h's rollback netplay built in: no launcher, no DLL
injected, no DirectX. The title menu's NET PLAY hosts or joins a match, which then runs
as VS HUMAN with one player at this computer and the other over the network.

It is Revival's own code, recovered in [revival.md](revival.md), made native: the
launcher's network side (`revival/EfzRevivalLauncher/`: the protocol's states, the
messages) and EfzRevival.dll's online session (`revival/EfzRevival/OnlineSession.cpp`:
rollback, input delay, the sync records), in the game's process, with the game's own
objects where Revival patches `efz.exe`'s addresses. It speaks Revival's protocol,
version 1.02 (`0x66`), and plays by its rules (its `rand()`, its patches), so that a
match against EfzRevival 1.02h is meant to work too ("Against EfzRevival 1.02h" below).

| Source | What it is |
|---|---|
| `port/netplay/net.cpp` | UDP sockets (IPv4 and IPv6), addresses, protobuf's wire format, zlib's inflate |
| `port/netplay/protocol.cpp` | The launcher's `ProtocolContext` and its states: host, join, measuring the delay, play, end; a thread that answers pings |
| `port/netplay/session.cpp` | EfzRevival.dll's `OnlineSession`: running the frames, rollback, save states, sounds, sync records, the replay |
| `port/netplay/titleitem.cpp` | The title menu's NET PLAY row, made from the menu's own letters |
| `port/netplay/netplay.cpp` | The NET PLAY screens, and the protocol and the session tied to the game's loop |
| `port/netplay.h`, `efz_native.h` (`NetplayHooks`) | What the rest of the game calls |
| `tests/netplay_test.cpp` | zlib, protobuf, Revival's `rand()` and sockets, checked without game data (`ctest -R netplay`) |

## Playing

On the title, NET PLAY (after VS HUMAN) opens netplay's screen over the title:

| Row | |
|---|---|
| MODE | HOST: wait for the other player. JOIN: connect to a host |
| ADDRESS | To join: the host's address, `192.168.1.5`, `example.org:10800`, `[2001:db8::1]:10800` (Ctrl+V pastes) |
| PORT | The UDP port: the host's to listen on, or the joiner's default for an address without one. 10800, as Revival's |
| NAME | What the other player sees, up to 20 characters |
| YOUR SIDE | The host's: P1, P2 or at random. The joiner gets the other |
| START | Host or join |

The arrow keys move and change, typing edits, Enter starts, Esc goes back; P1's controls
work too (A to start, B to go back). The settings are kept in `netplay.ini` in the save
folder.

Hosting shows this computer's addresses for the other player. Over the internet the host
needs the UDP port forwarded to it on their router (Revival's hole-punching server isn't
used); Windows asks, the first time, whether to let the game through its firewall. Once the two are connected, both games measure the round trip for about four
seconds and suggest an input delay, which each player confirms with Enter (or changes
with left and right). Then both games start from the title, as Revival starts `efz.exe`:
P1's first inputs pick VS HUMAN, and the two players are at character select.

In a match:

- **Each player plays with P1's controls**, whichever side they are on.
- **Esc** in a fight goes back to character select, for both. Esc anywhere else, or in a
  fight when the other side has stopped answering for three seconds, leaves the match.
- **The input delay** changes in a fight with the keypad's + and - (Revival's keys), or
  F10 and F9.
- **The screen** shows both names and wins at the top, the delay and the ping at the
  bottom, "Waiting for ..." when the other side's inputs are late, and a warning if the
  two games ever disagree (below).
- **Replays** of every match are saved, as Revival saves them, to `replay/netplay/` in the
  save folder: `<date-time> <P1> (<character>) vs <P2> (<character>).rep`, Revival's
  extended format (the game's words, then the random state and both players' inputs).
- **Rounds, damage, effects**: two rounds, 100% damage, normal effects and every frame
  drawn, whatever either side's `key.ini` says (Revival's `setSpectating`).
- When the match ends, for whatever reason, the game starts over at the title and the
  screen says why.

From the command line, without the menus (the game quits when the match ends):

```sh
efz --data DIR --host [--port 10800] [--name NAME] [--delay N]
efz --data DIR --join HOST[:PORT] [--name NAME] [--delay N]
```

## How it works

### The protocol

`Protocol` is the launcher's `ProtocolContext` with its states (HostConnect,
ClientConnect, TestDelay, Play, End) as one class, from `ProtocolContext.cpp` and the
`ProtocolState*.cpp` files ([revival.md](revival.md), "The launcher's protocol" and
"The network messages"). Its timers (ping, resend, timeout) are times checked each
frame; its console is the NET PLAY screen; the shared-memory queues between the
launcher and EfzRevival.dll are members the session reads and writes.

Each datagram is a 2-byte header (compressed or not, the message's type) and a protobuf
2.6.1 message, written and read by hand (`net::Writer`, `net::Reader`): ten messages of
varints and bytes need nothing more. Revival compresses Init, Input, Sync and Palette
with zlib but reads the header byte to decide, so this side sends everything
uncompressed and inflates what comes compressed (`net::Inflate`, RFC 1950 and 1951 as
Mark Adler's puff.c reads them; checked against zlib's own output in the test).

The launcher is a process of its own, so it answers a ping at once, whatever the game
is doing. Here a thread of the socket's does that, takes in the other datagrams with the
time they came, and leaves them for the frame loop. Without it the round trips counted
the game's frame (up to 16 ms each way) and its fades and loads, which hold the game's
thread for half a second at a time: on one machine they measured 15 ms, and up to 280
ms after a fade, and the menus' input delay, which follows the worst ping, rose to 9
frames. With it they measure 0-1 ms.

Left out: spectating (a spectator is answered as a host with `AllowSpectating = false`
answers), the hole-punching server and NAT traversal, custom palettes over the network
(received ones are ignored, none are sent), Revival's custom BGM folder and its battle
log. Sync records, which Revival asks for only with `Debug = 1`, are always asked for and
compared: a desync is logged with both records and shown on screen.

### The session

`Session` is `OnlineSession` ([revival.md](revival.md), "Rollback"), line for line where
it decides anything: which frames run, when the game waits, when it saves and loads,
which frames get a sync record, which sounds play. Each real frame (64 a second) it runs
the game from its last confirmed frame (the newest with both players' inputs) up to the
newest local input less the input delay, with the drawing off but for the last frame; a
remote input not yet received repeats the last one. Each frame confirmed on the way is
saved before it runs, and its sync record made; then the last confirmed frame's state is
loaded, so that the next update runs the unconfirmed frames again with what has arrived.
Out of a fight there is no rollback: the menus wait for the remote inputs. The first 20
frames of a fight, and from 120 frames after the match is decided, run without rollback
too.

**Save states** copy what Revival's do (`GameState.cpp`), by the native game's types
instead of `efz.exe`'s addresses: the F-key word (`g_fkeyHeld`), the fight scene
(`CScene3`), `CGame` (which holds the effects), both players (by their character's
class), the screen's palette and back buffer, the stage's animation, and `rand()`'s
state. In the native game these are the same bytes as in the original
([native.md](native.md), "Memory"), and their pointers are 32-bit handles into the
arena that don't move during a fight, so copying them back is all a load needs. About
400 KB a state; a ring of 60.

**Drawing off** (`efz::g_skipDrawing`, Revival's `setRendering(false)`): the blitters,
the fills and the upscale do nothing, and `Flip` shows nothing.

**Sounds** a frame plays are counted, so that running it again doesn't play them twice,
and sounds started on inputs that turned out wrong are stopped (`countSounds`).

### Revival's rules

What EfzRevival changes in `efz.exe` for a network match, and where the native game
does the same (`efz::NetplayHooks`, set only while a match runs, so that every other
game is the original's; `tools/compat.py check` passes unchanged):

| EfzRevival 1.02h | What it does | Native |
|---|---|---|
| The CRT's `rand` (`0x777d61`) replaced | `std::uniform_int_distribution<int>(0, 0x7fff)` over a `std::minstd_rand` seeded with the host's seed, saved with each state | `port/x87.cpp`'s `Rand` under `SetRevivalRand` |
| `CInput::GetInput`'s end (`0x40d131`) | Left and right together become left; the frame's input for that player | `port/input.cpp` |
| `CScene3::HandleKeys` (`0x7656a7`) | F4-F8 and Esc as either player pressed them on the frame, in place of the keyboard's | `src/scene3.cpp` |
| `CScene3::Update` (`0x763e50`, `0x763f04`) | Leaving the fight closes the replay; the mode is VS HUMAN again | `src/scene3.cpp` |
| `CReplayFile`'s methods (`0x405e90`-`0x406020`) | The match's replay kept in memory, written only on confirmed frames | `src/config.cpp` |
| `CSound::Play` (`0x40de80`) | Counted per frame (above) | `port/sound.cpp` |
| `0x776053` | The title's idle demo never starts | `src/scene0.cpp` |
| `0x754c1a` | B on character select doesn't go back to the title | `src/scene1.cpp` |
| `0x7599ed` | Each side's colour is kept from one character select to the next | `src/scene1.cpp` |
| `setSpectating`, `setNetplay` | Normal effects, every frame drawn, 100% damage, two rounds; from match setup on the mode is 5 (a replay being recorded) | `session.cpp` |
| `applyPalette` | Both players' palettes set as the fight starts: a missing EDIT COLOR palette is the colour's own, not black | `session.cpp` |

The last one shows why each matters: the game loads an EDIT COLOR palette
(`<name>\<name>N.pal`) without looking at whether the file is there, and in a game just
started the colours it leaves are zeros: the character was black until the session
applied the palette at the fight's start, as Revival does.

**Revival's `rand()`.** Visual C++ 2012's `uniform_int_distribution`, read from the
machine code of Revival's DLL (the installed 1.02a's, built with the same compiler):
the distribution draws 30 bits at a time, each the engine's next value less its minimum
(1), drawn again while above 2^30 - 1, and keeps the low 15. `tests/netplay_test.cpp`
has its first values from seed 1.

### Starting where efz.exe starts

Revival starts `efz.exe` for each match, so both sides begin on the title as a game just
started. The native game does the same without a new process: it deletes the game and
its scenes and makes them anew (`efz::RestartGame`), then runs the 22 scripted inputs
Revival gives P1. When the match ends it does it again, so that nothing of the match is
left in the game the player goes back to. The fight records ([logging.md](logging.md))
are off during a match: rollback runs frames again, which a record can't follow; the
match's replay stands in for them.

## Checking it

- `ctest -R netplay` (`tests/netplay_test.cpp`): inflating zlib's own streams (fixed,
  dynamic and stored blocks, and damaged ones), protobuf's wire format, Revival's
  `rand()`, a socket over the loopback (IPv4 to a dual-stack socket and back). CI runs it.
- Two games on one machine, with `--host` and `--join 127.0.0.1` and scripted input
  (`--keys`), compare their sync records frame by frame and log the result: "frames
  0-N: both sides' sync records agree", and at the end "sync records: ... all the same".
  `EFZ_NET_LAG=MS[:JITTER]` delays every datagram one side sends (a slow link on one
  machine, for the rollback), and `EFZ_DUMP_WINDOW=DIR` saves the window as shown,
  screens included, every `EFZ_DUMP_WINDOW_EVERY` frames.

What was run (Windows, MSVC, November 2026), each a match from the title through
character select into a fight with both players' input random:

| Link | Delay | Frames | Rollback | Sync records |
|---|---|---|---|---|
| Loopback | 0 | 2,280 | every frame, 1-2 at a time | all the same |
| Loopback, 60 ± 20 ms each way (144 ms round trip) | 2 and 3 | 2,834 | up to 5 frames at a time, 3,300 and 4,900 frames run again | all the same |
| Loopback, the host through the menus | 0 and 2 | 459 (left with Esc) | none | all the same |

Both sides' replays of a match are byte for byte the same, up to the frame where one
side stopped first.

## Against EfzRevival 1.02h

The protocol and the rules are Revival 1.02h's as recovered, so a native game and an
`efz.exe` with EfzRevival 1.02h are meant to play each other. That hasn't been tried:
the machine this was written on has EfzRevival 1.02a, whose protocol differs. It is the
network layer of [compat.md](compat.md), which can now be run. What to expect there:

- **The x87.** Revival's `sin`, `cos` and `atan2` are the CPU's, the native game's are
  correctly rounded ([compat.md](compat.md), "Answered"); a velocity set from an angle can
  then differ in its last bit. A build with `EFZ_HOST_X87` takes them from the CPU.
- **Uninitialised memory.** `efz.exe`'s heap holds garbage where the native game's holds
  zeros, which decides a few first hits (`m_hitsLeft`, [compat.md](compat.md)).
- **The FPU control word** in the sync records is sent as `0x9001f` (53-bit precision,
  rounding to nearest, every exception masked), what `_controlfp_s` should give in
  `efz.exe` under Revival; it is assumed, not read from a running game. The records are
  compared only on request, which Revival makes only with `Debug = 1`.
- **Palettes.** A custom (EDIT COLOR) palette isn't sent, so the other side shows that
  player's colour as the character's own. Colours don't change the game.

Two native games have none of these differences: they compute the same game on every
machine the compatibility suite passes on.
