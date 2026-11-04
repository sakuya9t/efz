// The native game's log: the session folder, efz.log, session.json, and the lines kept in
// memory for the crash report. See log.h and docs/logging.md.
#include <SDL3/SDL.h>
#include <algorithm>
#include <atomic>
#include <mutex>
#include <string>
#include <vector>

#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#else
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#endif

// The revision, from git when the game was built (tools/buildinfo.cmake).
#if defined(__has_include)
#if __has_include("efz_build.h")
#include "efz_build.h"
#endif
#endif
#ifndef EFZ_BUILD_REVISION
#define EFZ_BUILD_REVISION "unknown"
#define EFZ_BUILD_DIRTY 0
#endif
#ifndef EFZ_BUILD_CONFIG
#define EFZ_BUILD_CONFIG "unknown"
#endif

#include "log.h"

namespace efz {

namespace {

#define EFZ_STR2(x) #x
#define EFZ_STR(x) EFZ_STR2(x)

#if defined(__clang__)
const char kCompiler[] = "clang " __clang_version__;
#elif defined(__GNUC__)
const char kCompiler[] = "gcc " __VERSION__;
#elif defined(_MSC_VER)
const char kCompiler[] = "msvc " EFZ_STR(_MSC_FULL_VER);
#else
const char kCompiler[] = "unknown";
#endif

#if defined(_WIN32)
const char kOs[] = "windows";
#elif defined(__APPLE__)
const char kOs[] = "macos";
#elif defined(__linux__)
const char kOs[] = "linux";
#else
const char kOs[] = "unknown";
#endif

#if defined(_M_X64) || defined(__x86_64__)
const char kArch[] = "x64";
#elif defined(_M_ARM64) || defined(__aarch64__)
const char kArch[] = "arm64";
#elif defined(_M_IX86) || defined(__i386__)
const char kArch[] = "x86";
#else
const char kArch[] = "unknown";
#endif

const char* const kLevelNames[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

// The lines kept in memory: the last kRingLines, each cut to kRingWidth.
const unsigned kRingLines = 256;
const size_t kRingWidth = 512;
char g_ring[kRingLines][kRingWidth];
unsigned char g_ringLevel[kRingLines];
std::atomic<unsigned> g_ringNext{0};

std::mutex g_mutex;
LogOptions g_options;
intptr_t g_file = -1; // efz.log
char g_id[32];
char g_dir[1024];
char g_startTime[48];
const Uint64 g_startNs = SDL_GetTicksNS();
std::atomic<long> g_frame{-1};
std::atomic<int> g_scene{-1};
const char* volatile g_status = "running";
int g_exitCode;
char g_endTime[48];

// session.json's facts and counts.
struct Value {
    char key[32];
    char json[2048];
};
Value g_values[24];
int g_valueCount;
struct Count {
    char key[32];
    long n;
};
Count g_counts[12];
int g_countCount;
char g_sessionJson[64 << 10];

// snprintf onto the end of a buffer, which stays terminated and stops filling when full.
struct Writer {
    char* out;
    size_t size;
    size_t n = 0;

    Writer(char* o, size_t s) : out(o), size(s) { out[0] = 0; }
    void Printf(const char* format, ...) EFZ_PRINTF(2, 3)
    {
        if (n + 1 >= size)
            return;
        va_list args;
        va_start(args, format);
        int k = vsnprintf(out + n, size - n, format, args);
        va_end(args);
        if (k > 0)
            n = std::min(size - 1, n + (size_t)k);
    }
};

void DateTime(char* out, size_t size, bool iso)
{
    SDL_Time now;
    SDL_DateTime dt;
    if (!SDL_GetCurrentTime(&now) || !SDL_TimeToDateTime(now, &dt, true)) {
        snprintf(out, size, "unknown");
        return;
    }
    int ms = dt.nanosecond / 1000000;
    if (!iso) {
        snprintf(out, size, "%04d-%02d-%02d %02d:%02d:%02d.%03d", dt.year, dt.month, dt.day,
                 dt.hour, dt.minute, dt.second, ms);
        return;
    }
    int offset = dt.utc_offset / 60;
    char sign = offset < 0 ? '-' : '+';
    offset = offset < 0 ? -offset : offset;
    snprintf(out, size, "%04d-%02d-%02dT%02d:%02d:%02d.%03d%c%02d:%02d", dt.year, dt.month,
             dt.day, dt.hour, dt.minute, dt.second, ms, sign, offset / 60, offset % 60);
}

void AddCount(const char* key, int n)
{
    for (int i = 0; i < g_countCount; i++) {
        if (strcmp(g_counts[i].key, key) == 0) {
            g_counts[i].n += n;
            return;
        }
    }
    if (g_countCount < (int)(sizeof(g_counts) / sizeof(g_counts[0]))) {
        snprintf(g_counts[g_countCount].key, sizeof(g_counts[0].key), "%s", key);
        g_counts[g_countCount++].n = n;
    }
}

bool PathIn(const char* dir, const char* name, char* out, size_t size)
{
    if (!dir[0])
        return false;
    int n = snprintf(out, size, "%s/%s", dir, name);
    return n > 0 && (size_t)n < size;
}

// session.json, through a temporary file so that it is never half written.
void WriteSession()
{
    char path[1100], temp[1100];
    if (!PathIn(g_dir, "session.json", path, sizeof(path)) ||
        !PathIn(g_dir, "session.json.tmp", temp, sizeof(temp)))
        return;
    Writer w(g_sessionJson, sizeof(g_sessionJson));
    w.Printf("{\n  \"format\": \"efz-session\",\n  \"version\": 1,\n");
    w.Printf("  \"id\": \"%s\",\n  \"status\": \"%s\",\n", g_id, (const char*)g_status);
    w.Printf("  \"started\": \"%s\",\n", g_startTime);
    if (g_endTime[0])
        w.Printf("  \"ended\": \"%s\",\n  \"exit_code\": %d,\n", g_endTime, g_exitCode);
    w.Printf("  \"seconds\": %.3f,\n  \"build\": {%s},\n", Uptime(), BuildJson());
    for (int i = 0; i < g_valueCount; i++)
        w.Printf("  \"%s\": %s,\n", g_values[i].key, g_values[i].json);
    w.Printf("  \"counts\": {");
    for (int i = 0; i < g_countCount; i++)
        w.Printf("%s\"%s\": %ld", i ? ", " : "", g_counts[i].key, g_counts[i].n);
    w.Printf("}\n}\n");
    intptr_t f = RawOpen(temp, false);
    if (f < 0)
        return;
    bool ok = RawWrite(f, g_sessionJson, w.n);
    RawClose(f);
    if (!ok)
        return;
#ifdef _WIN32
    wchar_t wtemp[1100], wpath[1100];
    if (MultiByteToWideChar(CP_UTF8, 0, temp, -1, wtemp, 1100) &&
        MultiByteToWideChar(CP_UTF8, 0, path, -1, wpath, 1100))
        MoveFileExW(wtemp, wpath, MOVEFILE_REPLACE_EXISTING);
#else
    rename(temp, path);
#endif
}

bool IsSessionName(const char* s)
{
    if (strlen(s) != 20 || s[8] != '-' || s[15] != '-')
        return false;
    for (int i = 0; i < 20; i++) {
        if (i == 8 || i == 15)
            continue;
        bool hex = i > 15 && ((s[i] >= 'a' && s[i] <= 'f'));
        if (!(s[i] >= '0' && s[i] <= '9') && !hex)
            return false;
    }
    return true;
}

SDL_EnumerationResult SDLCALL CollectAll(void* names, const char*, const char* name)
{
    ((std::vector<std::string>*)names)->push_back(name);
    return SDL_ENUM_CONTINUE;
}

void RemoveTree(const std::string& path)
{
    SDL_PathInfo info;
    if (!SDL_GetPathInfo(path.c_str(), &info))
        return;
    if (info.type == SDL_PATHTYPE_DIRECTORY) {
        std::vector<std::string> names;
        SDL_EnumerateDirectory(path.c_str(), CollectAll, &names);
        for (const std::string& n : names)
            RemoveTree(path + "/" + n);
    }
    SDL_RemovePath(path.c_str());
}

Uint64 TreeSize(const std::string& path)
{
    SDL_PathInfo info;
    if (!SDL_GetPathInfo(path.c_str(), &info))
        return 0;
    if (info.type != SDL_PATHTYPE_DIRECTORY)
        return info.size;
    Uint64 size = 0;
    std::vector<std::string> names;
    SDL_EnumerateDirectory(path.c_str(), CollectAll, &names);
    for (const std::string& n : names)
        size += TreeSize(path + "/" + n);
    return size;
}

bool Exists(const std::string& path)
{
    SDL_PathInfo info;
    return SDL_GetPathInfo(path.c_str(), &info);
}

// The previous session, if it never recorded how it ended: killed, hung, or a crash the
// handler couldn't report.
void CheckPrevious(const std::string& dir, const std::string& name)
{
    std::string path = dir + "/" + name;
    size_t size = 0;
    char* json = (char*)SDL_LoadFile((path + "/session.json").c_str(), &size);
    if (!json)
        return;
    bool running = strstr(json, "\"status\": \"running\"") != nullptr;
    bool crashed = strstr(json, "\"status\": \"crashed\"") != nullptr;
    SDL_free(json);
    if (crashed)
        LogWarn("log", "the previous session, %s, crashed: see its crash.txt", name.c_str());
    else if (running && Exists(path + "/crash.txt"))
        LogWarn("log", "the previous session, %s, crashed: see its crash.txt", name.c_str());
    else if (running)
        LogWarn("log", "the previous session, %s, never recorded its end: it may still be "
                       "running, or it was killed or hung", name.c_str());
}

} // namespace

bool ParseLogLevel(const char* name, LogLevel* level)
{
    for (int i = kLogDebug; i <= kLogError; i++) {
        if (SDL_strcasecmp(name, kLevelNames[i]) == 0) {
            *level = (LogLevel)i;
            return true;
        }
    }
    if (SDL_strcasecmp(name, "warning") == 0) {
        *level = kLogWarn;
        return true;
    }
    return false;
}

double Uptime()
{
    return (double)(SDL_GetTicksNS() - g_startNs) / 1e9;
}

const char* BuildDescription()
{
    static char text[256];
    if (!text[0])
        snprintf(text, sizeof(text), "%s%s (%s, %s, %s %s)", EFZ_BUILD_REVISION,
                 EFZ_BUILD_DIRTY ? "+" : "", kCompiler, EFZ_BUILD_CONFIG, kOs, kArch);
    return text;
}

const char* BuildJson()
{
    static char text[512];
    if (!text[0]) {
        char compiler[160];
        JsonString(kCompiler, compiler, sizeof(compiler));
        snprintf(text, sizeof(text),
                 "\"revision\": \"%s\", \"dirty\": %s, \"compiler\": %s, \"config\": \"%s\", "
                 "\"os\": \"%s\", \"arch\": \"%s\"",
                 EFZ_BUILD_REVISION, EFZ_BUILD_DIRTY ? "true" : "false", compiler,
                 EFZ_BUILD_CONFIG, kOs, kArch);
    }
    return text;
}

bool StartLog(const LogOptions& options)
{
    BuildDescription();
    BuildJson();
    DateTime(g_startTime, sizeof(g_startTime), true);
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_options = options;
    }
    // The id: when it started, and a number to tell apart two started in one second.
    SDL_Time now;
    SDL_DateTime dt;
    if (!SDL_GetCurrentTime(&now) || !SDL_TimeToDateTime(now, &dt, true))
        memset(&dt, 0, sizeof(dt));
    unsigned tag = (unsigned)(SDL_GetPerformanceCounter() ^ (SDL_GetPerformanceCounter() >> 20));
    snprintf(g_id, sizeof(g_id), "%04d%02d%02d-%02d%02d%02d-%04x", dt.year, dt.month, dt.day,
             dt.hour, dt.minute, dt.second, tag & 0xffff);
    if (!options.dir || !options.dir[0]) {
        LogInfo("log", "session %s, no log folder", g_id);
        return false;
    }

    std::string dir = options.dir;
    while (dir.size() > 1 && (dir.back() == '/' || dir.back() == '\\'))
        dir.pop_back();
    std::vector<std::string> names;
    SDL_CreateDirectory(dir.c_str());
    SDL_EnumerateDirectory(dir.c_str(), CollectAll, &names);
    names.erase(std::remove_if(names.begin(), names.end(),
                               [](const std::string& n) { return !IsSessionName(n.c_str()); }),
                names.end());
    std::sort(names.begin(), names.end());
    for (int tries = 0; tries < 16 && Exists(dir + "/" + g_id); tries++)
        snprintf(g_id + 16, sizeof(g_id) - 16, "%04x", (++tag) & 0xffff);
    std::string session = dir + "/" + g_id;
    if (!SDL_CreateDirectory(session.c_str())) {
        LogError("log", "cannot make the log folder %s: %s", session.c_str(), SDL_GetError());
        return false;
    }
    snprintf(g_dir, sizeof(g_dir), "%s", session.c_str());
    char path[1100];
    PathIn(g_dir, "efz.log", path, sizeof(path));
    intptr_t file = RawOpen(path, true);
    if (file < 0) {
        LogError("log", "cannot write %s", path);
        g_dir[0] = 0;
        return false;
    }
    {
        // The lines logged before there was a file.
        std::lock_guard<std::mutex> lock(g_mutex);
        g_file = file;
        char header[256];
        int n = snprintf(header, sizeof(header), "# efz log, session %s, %s\n", g_id,
                         BuildDescription());
        RawWrite(g_file, header, (size_t)n);
        unsigned next = g_ringNext.load();
        for (unsigned i = next > kRingLines ? next - kRingLines : 0; i < next; i++) {
            const char* line = g_ring[i % kRingLines];
            if (g_ringLevel[i % kRingLines] >= g_options.fileLevel)
                RawWrite(g_file, line, strlen(line));
        }
        WriteSession();
    }
    LogInfo("log", "session %s: %s", g_id, g_dir);
    LogInfo("log", "build %s", BuildDescription());
    if (!names.empty())
        CheckPrevious(dir, names.back());
    // The oldest sessions beyond the number kept, this one counted, and beyond the bytes
    // kept: the newest first, this one not counted.
    size_t remove = 0;
    if (options.keep > 0 && (int)names.size() + 1 > options.keep)
        remove = names.size() + 1 - options.keep;
    if (options.maxBytes > 0) {
        Uint64 total = 0;
        for (size_t i = names.size(); i-- > remove;) {
            total += TreeSize(dir + "/" + names[i]);
            if (total > options.maxBytes) {
                remove = i + 1;
                break;
            }
        }
    }
    for (size_t i = 0; i < remove; i++) {
        RemoveTree(dir + "/" + names[i]);
        LogDebug("log", "removed the old session %s", names[i].c_str());
    }
    return true;
}

void EndLog(int exitCode)
{
    LogInfo("log", "session %s ends with %d after %.1f s", g_id, exitCode, Uptime());
    std::lock_guard<std::mutex> lock(g_mutex);
    g_status = "exited";
    g_exitCode = exitCode;
    DateTime(g_endTime, sizeof(g_endTime), true);
    WriteSession();
    if (g_file >= 0)
        RawClose(g_file);
    g_file = -1;
}

void LogV(LogLevel level, const char* category, const char* format, va_list args)
{
    char stamp[40];
    char line[2 * kRingWidth];
    DateTime(stamp, sizeof(stamp), false);
    int n = snprintf(line, sizeof(line), "%s +%.3f f=%ld s=%d %-5s %s: ", stamp, Uptime(),
                     g_frame.load(), g_scene.load(), kLevelNames[level], category);
    if (n < 0)
        return;
    vsnprintf(line + n, sizeof(line) - n - 1, format, args);
    size_t length = strlen(line);
    for (size_t i = 0; i < length; i++) {
        if (line[i] == '\n' || line[i] == '\r')
            line[i] = ' ';
    }
    line[length++] = '\n';
    line[length] = 0;

    std::lock_guard<std::mutex> lock(g_mutex);
    unsigned slot = g_ringNext.load() % kRingLines;
    size_t kept = std::min(length, kRingWidth - 1);
    memcpy(g_ring[slot], line, kept);
    g_ring[slot][kept] = 0;
    g_ringLevel[slot] = (unsigned char)level;
    if (kept == kRingWidth - 1)
        g_ring[slot][kept - 1] = '\n';
    g_ringNext++;
    if (level == kLogWarn)
        AddCount("warnings", 1);
    else if (level >= kLogError)
        AddCount("errors", 1);
    if (g_file >= 0 && level >= g_options.fileLevel)
        RawWrite(g_file, line, length);
    if (level >= g_options.stderrLevel)
        fwrite(line, 1, length, stderr);
}

// The last fatal error's message, which the crash report puts first.
static char g_fatal[512];

void FatalV(const char* category, const char* format, va_list args)
{
    va_list copy;
    va_copy(copy, args);
    int n = snprintf(g_fatal, sizeof(g_fatal), "%s: ", category);
    if (n > 0 && (size_t)n < sizeof(g_fatal))
        vsnprintf(g_fatal + n, sizeof(g_fatal) - n, format, copy);
    va_end(copy);
    LogV(kLogFatal, category, format, args);
    abort();
}

const char* FatalMessage()
{
    return g_fatal;
}

void SetLogFrame(long frame, int scene)
{
    g_frame = frame;
    g_scene = scene;
}

void SetSessionValue(const char* key, const char* json)
{
    std::lock_guard<std::mutex> lock(g_mutex);
    Value* v = nullptr;
    for (int i = 0; i < g_valueCount && !v; i++) {
        if (strcmp(g_values[i].key, key) == 0)
            v = &g_values[i];
    }
    if (!v) {
        if (g_valueCount == (int)(sizeof(g_values) / sizeof(g_values[0])))
            return;
        v = &g_values[g_valueCount++];
        snprintf(v->key, sizeof(v->key), "%s", key);
    }
    if (strlen(json) >= sizeof(v->json))
        json = "null"; // a cut value would make the file invalid
    snprintf(v->json, sizeof(v->json), "%s", json);
    WriteSession();
}

void SetSessionString(const char* key, const char* value)
{
    char json[2048];
    JsonString(value, json, sizeof(json));
    SetSessionValue(key, json);
}

void CountSession(const char* key, int n)
{
    std::lock_guard<std::mutex> lock(g_mutex);
    AddCount(key, n);
}

const char* SessionId()
{
    return g_id;
}

const char* SessionDir()
{
    return g_dir;
}

bool SessionPath(const char* name, char* out, size_t size)
{
    return PathIn(g_dir, name, out, size);
}

void MarkSessionCrashed()
{
    g_status = "crashed";
    DateTime(g_endTime, sizeof(g_endTime), true);
    g_exitCode = -1;
    WriteSession();
}

void LogFromCrash(const char* category, const char* text)
{
    char stamp[40];
    char line[1024];
    DateTime(stamp, sizeof(stamp), false);
    int n = snprintf(line, sizeof(line), "%s +%.3f f=%ld s=%d FATAL %s: %s\n", stamp,
                     Uptime(), g_frame.load(), g_scene.load(), category, text);
    if (n <= 0)
        return;
    size_t length = std::min((size_t)n, sizeof(line) - 1);
    intptr_t file = g_file;
    if (file >= 0)
        RawWrite(file, line, length);
    fwrite(line, 1, length, stderr);
}

void ForEachRecentLine(void (*fn)(void* context, const char* line), void* context)
{
    unsigned next = g_ringNext.load();
    for (unsigned i = next > kRingLines ? next - kRingLines : 0; i < next; i++)
        fn(context, g_ring[i % kRingLines]);
}

#ifdef _WIN32
intptr_t RawOpen(const char* path, bool append)
{
    wchar_t wide[1100];
    if (!MultiByteToWideChar(CP_UTF8, 0, path, -1, wide, 1100))
        return -1;
    HANDLE h = CreateFileW(wide, append ? FILE_APPEND_DATA : GENERIC_WRITE,
                           FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                           append ? OPEN_ALWAYS : CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    return h == INVALID_HANDLE_VALUE ? -1 : (intptr_t)h;
}

bool RawWrite(intptr_t file, const void* data, size_t size)
{
    const char* p = (const char*)data;
    while (size > 0) {
        DWORD chunk = size > (1u << 30) ? (1u << 30) : (DWORD)size;
        DWORD written = 0;
        if (!WriteFile((HANDLE)file, p, chunk, &written, nullptr) || written == 0)
            return false;
        p += written;
        size -= written;
    }
    return true;
}

void RawClose(intptr_t file)
{
    CloseHandle((HANDLE)file);
}

FILE* OpenUtf8(const char* path, const char* mode)
{
    wchar_t wide[1100], wmode[16];
    if (!MultiByteToWideChar(CP_UTF8, 0, path, -1, wide, 1100) ||
        !MultiByteToWideChar(CP_UTF8, 0, mode, -1, wmode, 16))
        return nullptr;
    return _wfopen(wide, wmode);
}
#else
intptr_t RawOpen(const char* path, bool append)
{
    int fd = open(path, O_WRONLY | O_CREAT | O_CLOEXEC | (append ? O_APPEND : O_TRUNC), 0644);
    return fd;
}

bool RawWrite(intptr_t file, const void* data, size_t size)
{
    const char* p = (const char*)data;
    while (size > 0) {
        ssize_t n = write((int)file, p, size);
        if (n < 0 && errno == EINTR)
            continue;
        if (n <= 0)
            return false;
        p += n;
        size -= (size_t)n;
    }
    return true;
}

void RawClose(intptr_t file)
{
    close((int)file);
}

FILE* OpenUtf8(const char* path, const char* mode)
{
    return fopen(path, mode);
}
#endif

size_t JsonString(const char* in, char* out, size_t size)
{
    size_t n = 0;
    if (size < 3) {
        if (size)
            out[0] = 0;
        return 0;
    }
    out[n++] = '"';
    for (const unsigned char* p = (const unsigned char*)in; *p; p++) {
        char esc[8];
        size_t k;
        if (*p == '"' || *p == '\\') {
            esc[0] = '\\';
            esc[1] = (char)*p;
            k = 2;
        } else if (*p < 0x20) {
            k = (size_t)snprintf(esc, sizeof(esc), "\\u%04x", *p);
        } else {
            esc[0] = (char)*p;
            k = 1;
        }
        if (n + k + 2 > size)
            break;
        memcpy(out + n, esc, k);
        n += k;
    }
    out[n++] = '"';
    out[n] = 0;
    return n;
}

void IsoTime(char* out, size_t size)
{
    DateTime(out, size, true);
}

} // namespace efz
