// Crash reports and the watchdog (docs/logging.md).
#ifndef EFZ_CRASH_H
#define EFZ_CRASH_H

#include <stddef.h>

namespace efz {

// Installs the handlers for crashes: access violations and the like, abort() (which
// Fatal and the arena's checks end in), an uncaught exception, and on Windows the C
// library's invalid parameter and pure call errors. A crash writes crash.txt to the
// session folder (to stderr without one): what crashed and where (a stack trace), the
// game as the recorder last saw it, and the last lines of the log; on Windows also
// crash.dmp, a minidump for a debugger. Then the game ends as the system would end it.
void InstallCrashHandler();
// What the report says of the game, written into `out` at crash time without
// allocating; and what the recorder does on a crash (ends the fight's record).
void SetCrashContext(void (*describe)(char* out, size_t size), void (*onCrash)());
// Whether a crash also shows a message box (Windows; never without a display).
void SetCrashDialog(bool show);
// Crashes on purpose, to test the handler: "segv", "abort" or "fatal"; or "hang", to
// test the watchdog: the main thread stops for 4 s, and the game exits with 5.
[[noreturn]] void CrashTest(const char* kind);

// The watchdog: a thread that reports the main loop not advancing for `seconds`, a
// hang, with the game's state and, on Windows, the main thread's stack (hang.txt) and a
// minidump (hang.dmp). It reports each hang once, and when the loop goes on again.
void StartWatchdog(double seconds);
void StopWatchdog();
// Each frame, and from the game's own waiting loops.
void Heartbeat();
// Around waits that may take long by design (a message box).
void PauseWatchdog(bool paused);

} // namespace efz

#endif
