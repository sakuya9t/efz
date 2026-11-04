// Crash reports and the watchdog. See crash.h and docs/logging.md.
//
// The report is written with the log's raw file functions and fixed buffers: after a
// crash the heap may be what broke. It goes to crash.txt in the session folder; the
// lines that say what and where also go to stderr and efz.log.
#include <atomic>
#include <chrono>
#include <exception>
#include <thread>

#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601 // SetThreadStackGuarantee, GetErrorMode: older MinGW's default lacks them
#endif
#include <windows.h>
#include <dbghelp.h>
#else
#include <dlfcn.h>
#include <unistd.h>
#if defined(__has_include)
#if __has_include(<execinfo.h>)
#include <execinfo.h>
#define EFZ_HAVE_BACKTRACE 1
#endif
#endif
#endif

#include "crash.h"
#include "log.h"

namespace efz {

namespace {

std::atomic<int> g_crashing{0};
void (*g_describe)(char* out, size_t size);
void (*g_onCrash)();
bool g_dialog = true;
volatile int g_zero = 0;

// The report being written, and its buffers.
intptr_t g_report = -1;
bool g_echo; // the part of the report stderr gets too
char g_line[4096];
char g_game[16384];

void Out(const char* text)
{
    size_t n = strlen(text);
    if (g_report >= 0)
        RawWrite(g_report, text, n);
    if (g_echo || g_report < 0)
        fwrite(text, 1, n, stderr);
}

void Printf(const char* format, ...) EFZ_PRINTF(1, 2);
void Printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(g_line, sizeof(g_line), format, args);
    va_end(args);
    Out(g_line);
}

void OutLine(void*, const char* line)
{
    Out("  ");
    Out(line);
}

const char* Basename(const char* path)
{
    const char* base = path;
    for (const char* p = path; *p; p++) {
        if (*p == '/' || *p == '\\')
            base = p + 1;
    }
    return base;
}

bool Headless()
{
    const char* video = getenv("SDL_VIDEO_DRIVER");
    return video && (strcmp(video, "offscreen") == 0 || strcmp(video, "dummy") == 0);
}

// The report: `what` happened; `stack` writes the stack trace. `file` is crash.txt or
// hang.txt.
void WriteReport(const char* file, const char* title, const char* what,
                 void (*stack)(void* context), void* context)
{
    char path[1100];
    char time[48];
    g_report = SessionPath(file, path, sizeof(path)) ? RawOpen(path, false) : -1;
    IsoTime(time, sizeof(time));
    g_echo = true;
    Printf("efz %s\n\n", title);
    Printf("what:    %s\n", what);
    Printf("session: %s\n", SessionId()[0] ? SessionId() : "(none)");
    Printf("build:   %s\n", BuildDescription());
    Printf("time:    %s, %.1f s after the start\n\n", time, Uptime());
    Printf("stack, innermost first:\n");
    if (stack)
        stack(context);
    else
        Printf("  (no stack trace on this system)\n");
    g_echo = false;
    Printf("\ngame:\n");
    if (g_describe) {
        g_describe(g_game, sizeof(g_game));
        Out(g_game);
    } else {
        Out("  (not started)\n");
    }
    Printf("\nlog, the last lines (debug included), oldest first:\n");
    ForEachRecentLine(OutLine, nullptr);
    if (g_report >= 0) {
        RawClose(g_report);
        g_report = -1;
        fprintf(stderr, "efz: the report is in %s\n", path);
    }
}

// The log's last line about it.
void LogCrash(const char* what, const char* file)
{
    char line[768];
    snprintf(line, sizeof(line), "%s; see %s", what, file);
    LogFromCrash("crash", line);
}

void TerminateHandler()
{
    const char* what = "no exception";
    if (std::exception_ptr e = std::current_exception()) {
        try {
            std::rethrow_exception(e);
        } catch (const std::exception& x) {
            what = x.what();
        } catch (...) {
            what = "not a std::exception";
        }
    }
    Fatal("crash", "an exception nobody caught: %s", what);
}

#ifdef _WIN32

HANDLE g_mainThread;
bool g_symbols;

void InitSymbols()
{
    if (g_symbols)
        return;
    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES);
    g_symbols = SymInitialize(GetCurrentProcess(), nullptr, TRUE) != FALSE;
}

struct StackContext {
    HANDLE thread;
    CONTEXT context;
};

void WalkStack(void* p)
{
    StackContext* sc = (StackContext*)p;
    HANDLE process = GetCurrentProcess();
    CONTEXT c = sc->context;
    STACKFRAME64 frame;
    memset(&frame, 0, sizeof(frame));
    DWORD machine;
#if defined(_M_X64) || defined(__x86_64__)
    machine = IMAGE_FILE_MACHINE_AMD64;
    frame.AddrPC.Offset = c.Rip;
    frame.AddrFrame.Offset = c.Rbp;
    frame.AddrStack.Offset = c.Rsp;
#elif defined(_M_ARM64) || defined(__aarch64__)
    machine = IMAGE_FILE_MACHINE_ARM64;
    frame.AddrPC.Offset = c.Pc;
    frame.AddrFrame.Offset = c.Fp;
    frame.AddrStack.Offset = c.Sp;
#else
    machine = IMAGE_FILE_MACHINE_I386;
    frame.AddrPC.Offset = c.Eip;
    frame.AddrFrame.Offset = c.Ebp;
    frame.AddrStack.Offset = c.Esp;
#endif
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrFrame.Mode = AddrModeFlat;
    frame.AddrStack.Mode = AddrModeFlat;
    InitSymbols();
    for (int i = 0; i < 64; i++) {
        if (!StackWalk64(machine, process, sc->thread, &frame, &c, nullptr,
                         SymFunctionTableAccess64, SymGetModuleBase64, nullptr))
            break;
        DWORD64 pc = frame.AddrPC.Offset;
        if (!pc)
            break;
        char module[MAX_PATH] = "?";
        DWORD64 base = SymGetModuleBase64(process, pc);
        if (base)
            GetModuleFileNameA((HMODULE)base, module, sizeof(module));
        alignas(SYMBOL_INFO) char buffer[sizeof(SYMBOL_INFO) + 256];
        SYMBOL_INFO* symbol = (SYMBOL_INFO*)buffer;
        memset(buffer, 0, sizeof(buffer));
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = 255;
        DWORD64 offset = 0;
        IMAGEHLP_LINE64 line;
        memset(&line, 0, sizeof(line));
        line.SizeOfStruct = sizeof(line);
        DWORD lineOffset = 0;
        bool named = g_symbols && SymFromAddr(process, pc, &offset, symbol);
        bool lined = g_symbols && SymGetLineFromAddr64(process, pc, &lineOffset, &line);
        if (named && lined)
            Printf("  %2d %s!%s+0x%llx (%s:%lu)\n", i, Basename(module), symbol->Name,
                   (unsigned long long)offset, Basename(line.FileName), line.LineNumber);
        else if (named)
            Printf("  %2d %s!%s+0x%llx\n", i, Basename(module), symbol->Name,
                   (unsigned long long)offset);
        else
            Printf("  %2d %s+0x%llx [0x%llx]\n", i, Basename(module),
                   (unsigned long long)(pc - base), (unsigned long long)pc);
    }
}

void WriteDump(const char* file, EXCEPTION_POINTERS* info, DWORD threadId)
{
    char path[1100];
    wchar_t wide[1100];
    if (!SessionPath(file, path, sizeof(path)) ||
        !MultiByteToWideChar(CP_UTF8, 0, path, -1, wide, 1100))
        return;
    HANDLE f = CreateFileW(wide, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL, nullptr);
    if (f == INVALID_HANDLE_VALUE)
        return;
    MINIDUMP_EXCEPTION_INFORMATION exception;
    exception.ThreadId = threadId;
    exception.ExceptionPointers = info;
    exception.ClientPointers = FALSE;
    MINIDUMP_TYPE type = (MINIDUMP_TYPE)(MiniDumpWithDataSegs | MiniDumpWithHandleData |
                                         MiniDumpWithIndirectlyReferencedMemory |
                                         MiniDumpWithThreadInfo | MiniDumpWithUnloadedModules);
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), f, type,
                      info ? &exception : nullptr, nullptr, nullptr);
    CloseHandle(f);
}

const char* ExceptionName(DWORD code)
{
    switch (code) {
    case EXCEPTION_ACCESS_VIOLATION: return "access violation";
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: return "array bounds exceeded";
    case EXCEPTION_DATATYPE_MISALIGNMENT: return "misaligned data";
    case EXCEPTION_FLT_DIVIDE_BY_ZERO: return "floating-point division by zero";
    case EXCEPTION_FLT_INVALID_OPERATION: return "invalid floating-point operation";
    case EXCEPTION_ILLEGAL_INSTRUCTION: return "illegal instruction";
    case EXCEPTION_IN_PAGE_ERROR: return "page error";
    case EXCEPTION_INT_DIVIDE_BY_ZERO: return "integer division by zero";
    case EXCEPTION_INT_OVERFLOW: return "integer overflow";
    case EXCEPTION_PRIV_INSTRUCTION: return "privileged instruction";
    case EXCEPTION_STACK_OVERFLOW: return "stack overflow";
    case 0xc0000409: return "stack buffer overrun or fail-fast";
    default: return "exception";
    }
}

// What the crashed thread hands the thread that reports it: the report has a stack of
// its own then, which a stack overflow leaves the crashed thread without.
struct Crash {
    EXCEPTION_POINTERS* info;
    DWORD threadId;
    StackContext stack;
    char what[512];
};

DWORD WINAPI ReportThread(void* p)
{
    Crash* crash = (Crash*)p;
    if (g_onCrash)
        g_onCrash();
    WriteReport("crash.txt", "crash report", crash->what, WalkStack, &crash->stack);
    WriteDump("crash.dmp", crash->info, crash->threadId);
    MarkSessionCrashed();
    LogCrash(crash->what, "crash.txt");
    return 0;
}

void Report(Crash* crash)
{
    HANDLE thread = CreateThread(nullptr, 1 << 20, ReportThread, crash, 0, nullptr);
    if (thread) {
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
    } else {
        ReportThread(crash);
    }
    if (g_dialog && !Headless()) {
        wchar_t dir[1100] = L"";
        MultiByteToWideChar(CP_UTF8, 0, SessionDir(), -1, dir, 1100);
        wchar_t text[1400];
        _snwprintf(text, 1400, L"EFZ crashed.\n\nA report was saved in\n%ls",
                   dir[0] ? dir : L"(no log folder)");
        text[1399] = 0;
        MessageBoxW(nullptr, text, L"EFZ", MB_OK | MB_ICONERROR | MB_TOPMOST);
    }
}

Crash g_crash;

LONG WINAPI ExceptionFilter(EXCEPTION_POINTERS* info)
{
    if (g_crashing.exchange(1))
        return EXCEPTION_CONTINUE_SEARCH;
    EXCEPTION_RECORD* r = info->ExceptionRecord;
    char where[MAX_PATH + 64] = "";
    HMODULE module = nullptr;
    if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                               GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           (LPCSTR)r->ExceptionAddress, &module)) {
        char name[MAX_PATH];
        GetModuleFileNameA(module, name, sizeof(name));
        snprintf(where, sizeof(where), " (%s+0x%llx)", Basename(name),
                 (unsigned long long)((char*)r->ExceptionAddress - (char*)module));
    }
    if (r->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && r->NumberParameters >= 2) {
        const char* how = r->ExceptionInformation[0] == 0   ? "reading"
                          : r->ExceptionInformation[0] == 1 ? "writing"
                                                            : "executing";
        snprintf(g_crash.what, sizeof(g_crash.what), "%s (0x%08lx) %s 0x%llx at %p%s",
                 ExceptionName(r->ExceptionCode), (unsigned long)r->ExceptionCode, how,
                 (unsigned long long)r->ExceptionInformation[1], r->ExceptionAddress, where);
    } else {
        snprintf(g_crash.what, sizeof(g_crash.what), "%s (0x%08lx) at %p%s",
                 ExceptionName(r->ExceptionCode), (unsigned long)r->ExceptionCode,
                 r->ExceptionAddress, where);
    }
    g_crash.info = info;
    g_crash.threadId = GetCurrentThreadId();
    g_crash.stack.context = *info->ContextRecord;
    DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(),
                    &g_crash.stack.thread, 0, FALSE, DUPLICATE_SAME_ACCESS);
    Report(&g_crash);
    return EXCEPTION_EXECUTE_HANDLER;
}

// abort(), and so Fatal: reported from here, with this thread's own stack.
void AbortHandler(int)
{
    if (g_crashing.exchange(1))
        _exit(3);
    if (FatalMessage()[0])
        snprintf(g_crash.what, sizeof(g_crash.what), "fatal error, %s", FatalMessage());
    else
        snprintf(g_crash.what, sizeof(g_crash.what), "abort() was called");
    g_crash.info = nullptr;
    g_crash.threadId = GetCurrentThreadId();
    RtlCaptureContext(&g_crash.stack.context);
    DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(),
                    &g_crash.stack.thread, 0, FALSE, DUPLICATE_SAME_ACCESS);
    Report(&g_crash);
    _exit(3);
}

#ifdef _MSC_VER
void InvalidParameter(const wchar_t*, const wchar_t*, const wchar_t*, unsigned, uintptr_t)
{
    Fatal("crash", "the C library was passed an invalid parameter");
}

void PureCall()
{
    Fatal("crash", "a pure virtual function was called");
}
#endif

void Install()
{
    SetUnhandledExceptionFilter(ExceptionFilter);
    signal(SIGABRT, AbortHandler);
#ifdef _MSC_VER
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    _set_invalid_parameter_handler(InvalidParameter);
    _set_purecall_handler(PureCall);
#endif
    // Room for the filter to run after a stack overflow.
    ULONG guarantee = 64 << 10;
    SetThreadStackGuarantee(&guarantee);
    // Without Windows's own "stopped working" dialog in its place.
    SetErrorMode(GetErrorMode() | SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
}

void HangReport(double seconds)
{
    char what[128];
    snprintf(what, sizeof(what), "the main loop has not advanced for %.0f s", seconds);
    WriteDump("hang.dmp", nullptr, 0);
    StackContext sc;
    sc.thread = g_mainThread;
    memset(&sc.context, 0, sizeof(sc.context));
    sc.context.ContextFlags = CONTEXT_FULL;
    InitSymbols();
    bool suspended = g_mainThread && SuspendThread(g_mainThread) != (DWORD)-1;
    bool got = suspended && GetThreadContext(g_mainThread, &sc.context);
    WriteReport("hang.txt", "hang report", what, got ? WalkStack : nullptr, &sc);
    if (suspended)
        ResumeThread(g_mainThread);
}

void RememberMainThread()
{
    DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(),
                    &g_mainThread, 0, FALSE, DUPLICATE_SAME_ACCESS);
}

// A debugger stopped at a breakpoint isn't a hang.
bool Debugged()
{
    return IsDebuggerPresent() != FALSE;
}

#else // POSIX

char g_altStack[64 << 10];

#ifdef EFZ_HAVE_BACKTRACE
void Backtrace(void*)
{
    void* frames[64];
    int n = backtrace(frames, 64);
    for (int i = 0; i < n; i++) {
        Dl_info info;
        if (dladdr(frames[i], &info) && info.dli_fname) {
            unsigned long long offset =
                (unsigned long long)((char*)frames[i] - (char*)info.dli_fbase);
            if (info.dli_sname)
                Printf("  %2d %s!%s+0x%llx (%s+0x%llx)\n", i, Basename(info.dli_fname),
                       info.dli_sname,
                       (unsigned long long)((char*)frames[i] - (char*)info.dli_saddr),
                       Basename(info.dli_fname), offset);
            else
                Printf("  %2d %s+0x%llx\n", i, Basename(info.dli_fname), offset);
        } else {
            Printf("  %2d %p\n", i, frames[i]);
        }
    }
    Printf("  (addr2line -f -C -e efz 0xOFFSET names a frame of efz+0xOFFSET)\n");
}
#endif

const char* SignalName(int sig)
{
    switch (sig) {
    case SIGSEGV: return "SIGSEGV, invalid memory access";
    case SIGBUS: return "SIGBUS, bus error";
    case SIGILL: return "SIGILL, illegal instruction";
    case SIGFPE: return "SIGFPE, arithmetic error";
    case SIGABRT: return "SIGABRT, abort() was called";
    default: return "signal";
    }
}

void SignalHandler(int sig, siginfo_t* info, void*)
{
    if (g_crashing.exchange(1)) {
        signal(sig, SIG_DFL);
        raise(sig);
        return;
    }
    char what[256];
    if (sig == SIGABRT && FatalMessage()[0])
        snprintf(what, sizeof(what), "fatal error, %s", FatalMessage());
    else if (sig == SIGABRT)
        snprintf(what, sizeof(what), "signal %d (%s)", sig, SignalName(sig));
    else
        snprintf(what, sizeof(what), "signal %d (%s) at address %p", sig, SignalName(sig),
                 info ? info->si_addr : nullptr);
    if (g_onCrash)
        g_onCrash();
#ifdef EFZ_HAVE_BACKTRACE
    WriteReport("crash.txt", "crash report", what, Backtrace, nullptr);
#else
    WriteReport("crash.txt", "crash report", what, nullptr, nullptr);
#endif
    MarkSessionCrashed();
    LogCrash(what, "crash.txt");
    // The system's own handling: a core dump, and the signal as the exit status.
    signal(sig, SIG_DFL);
    raise(sig);
}

void Install()
{
    stack_t ss;
    memset(&ss, 0, sizeof(ss));
    ss.ss_sp = g_altStack;
    ss.ss_size = sizeof(g_altStack);
    sigaltstack(&ss, nullptr);
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = SignalHandler;
    sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
    sigemptyset(&sa.sa_mask);
    const int signals[] = {SIGSEGV, SIGBUS, SIGILL, SIGFPE, SIGABRT};
    for (int sig : signals)
        sigaction(sig, &sa, nullptr);
#ifdef EFZ_HAVE_BACKTRACE
    // The first call loads what backtrace needs, which a crash is no time for.
    void* frames[4];
    backtrace(frames, 4);
#endif
}

void HangReport(double seconds)
{
    char what[128];
    snprintf(what, sizeof(what), "the main loop has not advanced for %.0f s", seconds);
    WriteReport("hang.txt", "hang report", what, nullptr, nullptr);
}

void RememberMainThread()
{
}

bool Debugged()
{
    return false;
}

#endif

// --- The watchdog.

std::atomic<unsigned long long> g_beats{0};
std::atomic<bool> g_watchPaused{false};
std::atomic<bool> g_watchStop{false};
std::atomic<bool> g_watchRunning{false};

void Watch(double limit)
{
    unsigned long long last = g_beats.load();
    double since = Uptime();
    bool reported = false;
    while (!g_watchStop.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        unsigned long long now = g_beats.load();
        if (now != last || g_watchPaused.load() || Debugged()) {
            if (reported)
                LogWarn("watchdog", "the main loop went on after %.1f s", Uptime() - since);
            last = now;
            since = Uptime();
            reported = false;
            continue;
        }
        if (!reported && Uptime() - since >= limit && !g_crashing.load()) {
            reported = true;
            LogError("watchdog", "the main loop has not advanced for %.0f s: see hang.txt",
                     Uptime() - since);
            HangReport(Uptime() - since);
        }
    }
    g_watchRunning = false;
}

} // namespace

void InstallCrashHandler()
{
    Install();
    RememberMainThread();
    std::set_terminate(TerminateHandler);
}

void SetCrashContext(void (*describe)(char* out, size_t size), void (*onCrash)())
{
    g_describe = describe;
    g_onCrash = onCrash;
}

void SetCrashDialog(bool show)
{
    g_dialog = show;
}

void CrashTest(const char* kind)
{
    LogInfo("crash", "crashing on purpose (--crash-test %s)", kind);
    if (strcmp(kind, "abort") == 0)
        abort();
    if (strcmp(kind, "fatal") == 0)
        Fatal("crash", "a fatal error on purpose");
    if (strcmp(kind, "hang") == 0) {
        // Not a crash: the main loop stops, for longer than a watchdog of 2 s allows.
        StartWatchdog(2);
        double end = Uptime() + 4;
        while (Uptime() < end) {
        }
        StopWatchdog();
        exit(5);
    }
    volatile int* p = (volatile int*)(uintptr_t)g_zero;
    *p = 1;
    abort();
}

void StartWatchdog(double seconds)
{
    if (g_watchRunning.exchange(true))
        return;
    g_watchStop = false;
    std::thread(Watch, seconds).detach();
}

void StopWatchdog()
{
    g_watchStop = true;
    // A watchdog stuck in a report isn't waited for.
    for (int i = 0; i < 40 && g_watchRunning.load(); i++)
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
}

void Heartbeat()
{
    g_beats.fetch_add(1, std::memory_order_relaxed);
}

void PauseWatchdog(bool paused)
{
    g_watchPaused = paused;
    Heartbeat();
}

} // namespace efz
