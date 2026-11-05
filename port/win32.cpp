// The Win32 file functions the game code calls, on the C library. (MessageBox,
// PostMessage and timeGetTime are the platform's: port/main.cpp, port/headless/.)
//
// Files: the game opens paths like "system\effect\effect.dat" relative to its folder.
// Here they resolve against the data folder (efz::SetDataDir), whatever the case of the
// names on disk, and what the game writes (key.ini, records, replays, screenshots) goes
// to the save folder, which is read first. Both are the current folder by default.
//
// Several games can run at once in a headless build, so the table of open files is
// shared under a lock, and doesn't allocate (operator new would take from the arena of
// whichever game opened a file first).
#include <mutex>
#include <string>

#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <dirent.h>
#include <strings.h>
#endif

#include "efz.h"
#include "platform.h"
#include "log.h"

namespace efz {

// Set by netplay (port/netplay/) in the game; empty elsewhere (efz_native.h).
NetplayHooks g_netplay;

namespace {

std::string g_dataDir = ".";
std::string g_saveDir = ".";
const size_t kFiles = 4096;
FILE* g_files[kFiles]; // handle n is g_files[n - 1]
std::mutex g_filesLock;
thread_local const char* t_replayFile = nullptr; // SetReplayFile's

// "replay\data<page>-<slot>.rep", as CScene2 names a replay slot's file.
bool IsReplaySlot(const char* name)
{
    size_t n = strlen(name);
    return n > 11 && strncmp(name, "replay", 6) == 0 && (name[6] == '\\' || name[6] == '/') &&
           strncmp(name + 7, "data", 4) == 0 && strcmp(name + n - 4, ".rep") == 0;
}

bool Exists(const std::string& path)
{
    FILE* f = fopen(path.c_str(), "rb");
    if (f)
        fclose(f);
    return f != nullptr;
}

bool IsDir(const std::string& path)
{
#ifdef _WIN32
    struct _stat st;
    return _stat(path.c_str(), &st) == 0 && (st.st_mode & _S_IFDIR);
#else
    struct stat st;
    return stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
#endif
}

// `name` under `dir`, matching each component of the name regardless of case. Missing
// components are kept as written, so that a file can be created.
std::string Resolve(const std::string& dir, const char* name)
{
    std::string path = dir;
    std::string part;
    for (const char* p = name;; p++) {
        if (*p && *p != '\\' && *p != '/') {
            part += *p;
            continue;
        }
        if (!part.empty()) {
            std::string exact = path + "/" + part;
#ifndef _WIN32
            if (!Exists(exact) && !IsDir(exact)) {
                if (DIR* d = opendir(path.c_str())) {
                    while (struct dirent* e = readdir(d)) {
                        if (strcasecmp(e->d_name, part.c_str()) == 0) {
                            exact = path + "/" + e->d_name;
                            break;
                        }
                    }
                    closedir(d);
                }
            }
#endif
            path = exact;
            part.clear();
        }
        if (!*p)
            return path;
    }
}

void MakeParents(const std::string& path)
{
    for (size_t i = 1; i < path.size(); i++) {
        if (path[i] != '/')
            continue;
        std::string dir = path.substr(0, i);
        if (!IsDir(dir)) {
#ifdef _WIN32
            _mkdir(dir.c_str());
#else
            mkdir(dir.c_str(), 0777);
#endif
        }
    }
}

FILE* FileOf(HANDLE h)
{
    if (h == 0 || h == INVALID_HANDLE_VALUE || h > kFiles)
        return nullptr;
    return g_files[h - 1];
}

} // namespace

void SetDataDir(const char* data, const char* save)
{
    g_dataDir = data;
    g_saveDir = save ? save : data;
}

void SetReplayFile(const char* path)
{
    t_replayFile = path;
}

FILE* OpenPath(const char* path, const char* mode)
{
#ifdef _WIN32
    // UTF-8 to UTF-16 (no windows.h here: the game's own Win32 types are).
    std::wstring wide, wmode(mode, mode + strlen(mode));
    for (const unsigned char* p = (const unsigned char*)path; *p;) {
        uint32_t c = *p++;
        int more = c >= 0xf0 ? 3 : c >= 0xe0 ? 2 : c >= 0xc0 ? 1 : 0;
        c &= more == 3 ? 0x07 : more == 2 ? 0x0f : more == 1 ? 0x1f : 0x7f;
        for (; more > 0 && (*p & 0xc0) == 0x80; more--)
            c = c << 6 | (*p++ & 0x3f);
        if (c >= 0x10000) {
            c -= 0x10000;
            wide += (wchar_t)(0xd800 + (c >> 10));
            wide += (wchar_t)(0xdc00 + (c & 0x3ff));
        } else {
            wide += (wchar_t)c;
        }
    }
    return _wfopen(wide.c_str(), wmode.c_str());
#else
    return fopen(path, mode);
#endif
}

FILE* OpenGameFile(const char* name, const char* mode)
{
    bool write = strchr(mode, 'w') || strchr(mode, 'a') || strchr(mode, '+');
    std::string saved = Resolve(g_saveDir, name);
    if (write) {
        MakeParents(saved);
        return fopen(saved.c_str(), mode);
    }
    if (FILE* f = fopen(saved.c_str(), mode))
        return f;
    return fopen(Resolve(g_dataDir, name).c_str(), mode);
}

} // namespace efz

// Opens a file the game may write: from the save folder, copied there from the data
// folder first if only that has it, or created if `create`.
FILE* efz::OpenForUpdate(const char* name, bool create)
{
    std::string saved = Resolve(g_saveDir, name);
    if (FILE* f = fopen(saved.c_str(), "r+b"))
        return f;
    FILE* src = fopen(Resolve(g_dataDir, name).c_str(), "rb");
    if (!src && !create)
        return nullptr;
    MakeParents(saved);
    FILE* f = fopen(saved.c_str(), "w+b");
    if (src) {
        char buf[4096];
        size_t n;
        while (f && (n = fread(buf, 1, sizeof(buf), src)) > 0)
            fwrite(buf, 1, n, f);
        fclose(src);
        if (f)
            fseek(f, 0, SEEK_SET);
    }
    return f;
}

uint32_t efz::AdoptFile(FILE* f)
{
    std::lock_guard<std::mutex> lock(g_filesLock);
    for (size_t i = 0; i < kFiles; i++) {
        if (!g_files[i]) {
            g_files[i] = f;
            return (uint32_t)(i + 1);
        }
    }
    fclose(f);
    return INVALID_HANDLE_VALUE;
}

HANDLE CreateFileA(LPCSTR name, DWORD access, DWORD, SECURITY_ATTRIBUTES*, DWORD disposition,
                   DWORD, HANDLE)
{
    using namespace efz;
    bool write = (access & GENERIC_WRITE) != 0;
    FILE* f = nullptr;
    if (t_replayFile && !write && IsReplaySlot(name)) {
        f = OpenPath(t_replayFile, "rb");
        if (!f) {
            efz::LogDebug("file", "cannot open %s for reading", t_replayFile);
            return INVALID_HANDLE_VALUE;
        }
        return AdoptFile(f);
    }
    switch (disposition) {
    case CREATE_ALWAYS:
        f = OpenGameFile(name, "w+b");
        break;
    case OPEN_EXISTING:
        f = write ? OpenForUpdate(name, false) : OpenGameFile(name, "rb");
        break;
    case OPEN_ALWAYS:
        f = write ? OpenForUpdate(name, true) : OpenGameFile(name, "rb");
        break;
    case TRUNCATE_EXISTING:
        if ((f = OpenGameFile(name, "rb")) != nullptr) {
            fclose(f);
            f = OpenGameFile(name, "w+b");
        }
        break;
    }
    if (!f) {
        // Often expected (key.ini, records and replays not made yet), so at debug level:
        // it shows in a crash report's last lines all the same.
        efz::LogDebug("file", "cannot open %s for %s", name, write ? "writing" : "reading");
        return INVALID_HANDLE_VALUE;
    }
    return AdoptFile(f);
}

BOOL ReadFile(HANDLE h, LPVOID buffer, DWORD size, LPDWORD read, void*)
{
    FILE* f = efz::FileOf(h);
    if (read)
        *read = 0;
    if (!f)
        return FALSE;
    size_t n = fread(buffer, 1, size, f);
    if (read)
        *read = (DWORD)n;
    return TRUE;
}

BOOL WriteFile(HANDLE h, const void* buffer, DWORD size, LPDWORD written, void*)
{
    FILE* f = efz::FileOf(h);
    if (written)
        *written = 0;
    if (!f)
        return FALSE;
    fseek(f, 0, SEEK_CUR); // switching from reading to writing
    size_t n = fwrite(buffer, 1, size, f);
    if (written)
        *written = (DWORD)n;
    return TRUE;
}

DWORD SetFilePointer(HANDLE h, LONG offset, LONG*, DWORD method)
{
    FILE* f = efz::FileOf(h);
    if (!f)
        return 0xffffffffu;
    int whence = method == FILE_BEGIN ? SEEK_SET : method == FILE_END ? SEEK_END : SEEK_CUR;
    if (fseek(f, offset, whence) != 0)
        return 0xffffffffu;
    return (DWORD)ftell(f);
}

DWORD GetFileSize(HANDLE h, LPDWORD high)
{
    FILE* f = efz::FileOf(h);
    if (high)
        *high = 0;
    if (!f)
        return INVALID_FILE_SIZE;
    long pos = ftell(f);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, pos, SEEK_SET);
    return (DWORD)size;
}

BOOL CloseHandle(HANDLE h)
{
    FILE* f = efz::FileOf(h);
    if (!f)
        return FALSE;
    fclose(f);
    std::lock_guard<std::mutex> lock(efz::g_filesLock);
    efz::g_files[h - 1] = nullptr;
    return TRUE;
}

#ifndef _WIN32
// Windows's C library has these, the original's own.
char* _itoa(int value, char* buffer, int radix)
{
    char digits[34];
    int n = 0;
    unsigned u = value;
    char* p = buffer;
    if (radix == 10 && value < 0) {
        *p++ = '-';
        u = 0u - (unsigned)value;
    }
    do {
        digits[n++] = "0123456789abcdefghijklmnopqrstuvwxyz"[u % radix];
        u /= radix;
    } while (u);
    while (n)
        *p++ = digits[--n];
    *p = '\0';
    return buffer;
}

char* _strnset(char* str, int c, size_t count)
{
    for (size_t i = 0; i < count && str[i]; i++)
        str[i] = (char)c;
    return str;
}
#endif
