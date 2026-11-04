// The native game's log (docs/logging.md). Each run of the game is a session with a
// folder of its own under the logs folder (by default the save folder's `logs`), named
// for when it started (20261103-182001-4f2a):
//   efz.log        what happened, one line each: the time, the game's frame and scene,
//                  a level and a category
//   session.json   the run's facts (build, system, options, seed) and how it ended
//   fight-NNN.*    each fight's record (port/record.cpp)
//   crash.txt      after a crash, what and where (port/crash.cpp); crash.dmp on Windows
// The newest sessions are kept (--log-keep). The last lines of every level, debug
// included, are also kept in memory for the crash report.
//
// Nothing here allocates once the session has started, so that logging leaves the
// game's arena alone, and the crash handler can use what it needs of it.
//
// All of it is the SDL3 game's (port/log.cpp), except LogV and FatalV, which every
// platform defines, so that the parts every build shares (arena.cpp, win32.cpp) can log:
// the headless library's (port/headless/platform.cpp) write warnings and worse to
// stderr, with no session, files or crash reports.
#ifndef EFZ_LOG_H
#define EFZ_LOG_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#if defined(__GNUC__) || defined(__clang__)
#define EFZ_PRINTF(f, a) __attribute__((format(printf, f, a)))
#else
#define EFZ_PRINTF(f, a)
#endif

namespace efz {

enum LogLevel { kLogDebug, kLogInfo, kLogWarn, kLogError, kLogFatal };

struct LogOptions {
    const char* dir = nullptr;       // the logs folder; null or empty: no files
    LogLevel fileLevel = kLogInfo;   // efz.log gets this level and above
    LogLevel stderrLevel = kLogWarn; // and stderr
    int keep = 20;                   // session folders kept, the newest; 0 keeps all
    // and no more of them than this many bytes, the newest kept; 0: any size
    unsigned long long maxBytes = 2048ull << 20;
};

// "debug", "info", "warn" or "error".
bool ParseLogLevel(const char* name, LogLevel* level);

// Starts the session: makes its folder, removes the oldest beyond options.keep, notes a
// previous session that never recorded its end, writes session.json and the lines
// logged so far. Returns false without a folder: the log then goes to stderr only.
bool StartLog(const LogOptions& options);
// Ends it: session.json records the exit code.
void EndLog(int exitCode);

// Every platform's: a line of the log; and a fatal error's, which stops the game through
// abort() (the crash handler reports it).
void LogV(LogLevel level, const char* category, const char* format, va_list args);
[[noreturn]] void FatalV(const char* category, const char* format, va_list args);

inline void Log(LogLevel level, const char* category, const char* format, ...)
    EFZ_PRINTF(3, 4);
inline void LogDebug(const char* category, const char* format, ...) EFZ_PRINTF(2, 3);
inline void LogInfo(const char* category, const char* format, ...) EFZ_PRINTF(2, 3);
inline void LogWarn(const char* category, const char* format, ...) EFZ_PRINTF(2, 3);
inline void LogError(const char* category, const char* format, ...) EFZ_PRINTF(2, 3);
[[noreturn]] inline void Fatal(const char* category, const char* format, ...) EFZ_PRINTF(2, 3);

#define EFZ_LOG_AT(level)                                                                  \
    va_list args;                                                                          \
    va_start(args, format);                                                                \
    LogV(level, category, format, args);                                                   \
    va_end(args);
inline void Log(LogLevel level, const char* category, const char* format, ...)
{
    EFZ_LOG_AT(level)
}
inline void LogDebug(const char* category, const char* format, ...) { EFZ_LOG_AT(kLogDebug) }
inline void LogInfo(const char* category, const char* format, ...) { EFZ_LOG_AT(kLogInfo) }
inline void LogWarn(const char* category, const char* format, ...) { EFZ_LOG_AT(kLogWarn) }
inline void LogError(const char* category, const char* format, ...) { EFZ_LOG_AT(kLogError) }
#undef EFZ_LOG_AT

inline void Fatal(const char* category, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    FatalV(category, format, args);
}

// The main loop's frame and scene, which each line notes.
void SetLogFrame(long frame, int scene);

// session.json's facts: a JSON value by key (SetSessionValue("seed", "1234")), or a
// string, escaped here. A key set again is replaced. Written out at once.
void SetSessionValue(const char* key, const char* json);
void SetSessionString(const char* key, const char* value);
// Adds to one of session.json's counts ("fights", "anomalies"...).
void CountSession(const char* key, int n = 1);

const char* SessionId();  // "" before StartLog
const char* SessionDir(); // "" without a folder
// `name` in the session folder, in out. False without a folder or if it doesn't fit.
bool SessionPath(const char* name, char* out, size_t size);
// Seconds since the game started.
double Uptime();
// The build in a line: revision, compiler, configuration, system and processor.
const char* BuildDescription();
// The same as JSON members ("revision": "...", ...), for the fight records' headers.
const char* BuildJson();

// For the crash handler, which mustn't take locks or allocate: session.json's status
// becomes "crashed"; and each line kept in memory, oldest first.
void MarkSessionCrashed();
// Fatal's last message ("arena: the arena has no room..."), or "".
const char* FatalMessage();
// A FATAL line for efz.log and stderr, written without the log's lock.
void LogFromCrash(const char* category, const char* text);
void ForEachRecentLine(void (*fn)(void* context, const char* line), void* context);

// Files by UTF-8 path without stdio: written straight through, so that nothing is lost
// in a buffer when the game crashes. RawOpen returns -1 on failure.
intptr_t RawOpen(const char* path, bool append);
bool RawWrite(intptr_t file, const void* data, size_t size);
void RawClose(intptr_t file);
// fopen by UTF-8 path, on Windows too.
FILE* OpenUtf8(const char* path, const char* mode);

// `in` as a JSON string, quotes included, in out (truncated to fit). Returns its length.
size_t JsonString(const char* in, char* out, size_t size);
// The local time as 2026-11-03T18:20:01.123+09:00.
void IsoTime(char* out, size_t size);

} // namespace efz

#endif
