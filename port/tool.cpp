// The replay tool: see tool.h. Drawn as netplay's screens are, with SDL's 8x8 font over
// the 640x480 screen, and worked with the mouse: buttons are drawn each frame and the
// clicks of the next frames found in what was drawn.
#include <SDL3/SDL.h>
#include <algorithm>
#include <string>
#include <vector>

#include "efz.h"
#include "platform.h"
#include "log.h"
#include "record.h"
#include "tool.h"

namespace efz {

namespace {

struct Color {
    Uint8 r, g, b, a;
};
const Color kWhite = {255, 255, 255, 255};
const Color kGrey = {160, 160, 160, 255};
const Color kDim = {95, 95, 95, 255};
const Color kTeal = {80, 210, 190, 255};
const Color kYellow = {255, 220, 110, 255};
const Color kRed = {255, 110, 100, 255};
const Color kBack = {12, 22, 34, 255};

// A file in the list, and how its last conversion went.
struct Row {
    std::string path;
    bool replay = false; // a .rep; else a record
    int status = -1;     // -1 nothing done, 0 done, 3 played otherwise, 4 not converted
    std::string said;
};

enum Button {
    kNone,
    kAdd,
    kClear,
    kFolder,
    kOpen,
    kSmall,
    kLarge,
    kToRep,
    kToRecord,
    kToVideo,
    kCancel,
    kRemove, // + the row
};

struct Hit {
    SDL_FRect rect;
    int id;
};

bool g_on;
std::vector<Row> g_rows;
std::string g_out;      // where what is made goes
int g_scale = 2;        // videos: 640x480 times this
int g_top = 0;          // the list's first row shown
int g_hover = -1;       // the row under the mouse
float g_mouseX = -1, g_mouseY = -1;
std::vector<Hit> g_hits;  // the last frame's buttons
int g_clicked = kNone;
std::string g_message;
// The conversion going: the rows its jobs are of.
bool g_batch = false;
std::vector<int> g_batchRows;
// What the system's dialogs picked, from whichever thread they answer on.
SDL_Mutex* g_picked;

struct Lock {
    Lock() { SDL_LockMutex(g_picked); }
    ~Lock() { SDL_UnlockMutex(g_picked); }
};
std::vector<std::string> g_pickedFiles;
std::string g_pickedFolder;

const int kRows = 15;
const float kListX = 20, kListY = 70, kRowH = 16;

bool Ends(const std::string& s, const char* ext)
{
    size_t n = strlen(ext);
    if (s.size() < n)
        return false;
    for (size_t i = 0; i < n; i++) {
        if (tolower((unsigned char)s[s.size() - n + i]) != ext[i])
            return false;
    }
    return true;
}

std::string FileName(const std::string& path)
{
    size_t slash = path.find_last_of("/\\");
    return slash == std::string::npos ? path : path.substr(slash + 1);
}

// What the list calls a file: a record with its session's folder (they are all
// fight-NNN), a replay by its name.
std::string Label(const Row& row)
{
    if (row.replay)
        return FileName(row.path);
    size_t slash = row.path.find_last_of("/\\");
    if (slash == std::string::npos || slash == 0)
        return row.path;
    size_t before = row.path.find_last_of("/\\", slash - 1);
    return row.path.substr(before == std::string::npos ? 0 : before + 1);
}

// A file, or the records and replays in a folder dropped (a session's folder).
SDL_EnumerationResult AddEntry(void* context, const char* dirname, const char* fname);

void Add(const std::string& path)
{
    SDL_PathInfo info;
    if (SDL_GetPathInfo(path.c_str(), &info) && info.type == SDL_PATHTYPE_DIRECTORY) {
        SDL_EnumerateDirectory(path.c_str(), AddEntry, nullptr);
        return;
    }
    bool replay = Ends(path, ".rep");
    if (!replay && !Ends(path, ".jsonl")) {
        g_message = FileName(path) + " is neither a record (.jsonl) nor a replay (.rep).";
        return;
    }
    for (const Row& row : g_rows) {
        if (row.path == path)
            return;
    }
    Row row;
    row.path = path;
    row.replay = replay;
    g_rows.push_back(row);
}

SDL_EnumerationResult AddEntry(void*, const char* dirname, const char* fname)
{
    std::string path = std::string(dirname) + fname;
    if (Ends(path, ".rep") || Ends(path, ".jsonl"))
        Add(path);
    return SDL_ENUM_CONTINUE;
}

void SDLCALL Picked(void*, const char* const* files, int)
{
    Lock lock;
    for (int i = 0; files && files[i]; i++)
        g_pickedFiles.push_back(files[i]);
}

void SDLCALL PickedFolder(void*, const char* const* files, int)
{
    Lock lock;
    if (files && files[0])
        g_pickedFolder = files[0];
}

std::string LogsFolder()
{
    std::string session = SessionDir();
    size_t slash = session.find_last_of("/\\");
    return slash == std::string::npos ? std::string(SaveDir()) : session.substr(0, slash);
}

void OpenFolder(const std::string& path)
{
    std::string url = path;
    std::replace(url.begin(), url.end(), '\\', '/');
    url = (url.size() > 0 && url[0] == '/' ? "file://" : "file:///") + url;
    if (!SDL_OpenURL(url.c_str()))
        g_message = std::string("Can't open the folder: ") + SDL_GetError();
}

// The rows a job of this kind is for.
bool Takes(const Row& row, Conversion::Kind kind)
{
    return kind == Conversion::kToVideo || (kind == Conversion::kToRep) == !row.replay;
}

void Start(Conversion::Kind kind, unsigned char* scene)
{
    std::vector<Conversion> list;
    g_batchRows.clear();
    for (size_t i = 0; i < g_rows.size(); i++) {
        if (!Takes(g_rows[i], kind))
            continue;
        Conversion c;
        c.kind = kind;
        c.in = g_rows[i].path;
        c.outDir = g_out;
        c.videoScale = g_scale;
        list.push_back(c);
        g_batchRows.push_back((int)i);
        g_rows[i].status = -1;
        g_rows[i].said = "waiting";
    }
    if (list.empty()) {
        g_message = kind == Conversion::kToRep    ? "No records to make replays of."
                    : kind == Conversion::kToRecord ? "No replays to make records of."
                                                    : "Nothing to make videos of.";
        return;
    }
    SDL_CreateDirectory(g_out.c_str());
    g_message.clear();
    g_batch = true;
    LogInfo("tool", "%d file(s) to %s, in %s", (int)list.size(),
            kind == Conversion::kToRep      ? "replays"
            : kind == Conversion::kToRecord ? "records"
                                            : "videos",
            g_out.c_str());
    StartConversions(list, scene, true);
}

// The conversion's states in its rows.
void Update()
{
    if (!g_batch)
        return;
    std::vector<ConversionState> states = Conversions();
    for (size_t j = 0; j < states.size() && j < g_batchRows.size(); j++) {
        if (g_batchRows[j] >= (int)g_rows.size())
            continue;
        Row& row = g_rows[g_batchRows[j]];
        if (states[j].status >= 0) {
            row.status = states[j].status;
            row.said = states[j].said;
        }
    }
    if (!RecordTasksRunning()) {
        g_batch = false;
        int done = 0, failed = 0;
        for (const ConversionState& s : states)
            (s.status == 0 ? done : failed)++;
        g_message = std::to_string(done) + " made" +
                    (failed ? ", " + std::to_string(failed) +
                                  " not (the mouse over a file says why)"
                            : "") +
                    ". Open shows them.";
    }
}

// --- Drawing

void Text(SDL_Renderer* r, float x, float y, const std::string& text, float scale, Color c)
{
    std::string s;
    for (char ch : text)
        s.push_back((unsigned char)ch < 0x80 ? ch : '?'); // the font has ASCII only
    SDL_SetRenderScale(r, scale, scale);
    SDL_SetRenderDrawColor(r, 0, 0, 0, (Uint8)(c.a * 3 / 4));
    SDL_RenderDebugText(r, x / scale + 1, y / scale + 1, s.c_str());
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    SDL_RenderDebugText(r, x / scale, y / scale, s.c_str());
    SDL_SetRenderScale(r, 1, 1);
}

float Width(const std::string& s, float scale)
{
    return (float)s.size() * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * scale;
}

void Box(SDL_Renderer* r, float x, float y, float w, float h, Color c)
{
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(r, &rect);
}

// At most `width` letters: the end of a path, the start of anything else.
std::string Fit(const std::string& s, size_t width, bool tail)
{
    if (s.size() <= width)
        return s;
    return tail ? "..." + s.substr(s.size() - (width - 3)) : s.substr(0, width - 3) + "...";
}

bool Inside(const SDL_FRect& rect)
{
    return g_mouseX >= rect.x && g_mouseX < rect.x + rect.w && g_mouseY >= rect.y &&
           g_mouseY < rect.y + rect.h;
}

// A button: its label centred, lit under the mouse; recorded for the clicks.
void Push(SDL_Renderer* r, int id, float x, float y, float w, const std::string& label,
          bool enabled, bool chosen = false)
{
    SDL_FRect rect = {x, y, w, 20};
    bool over = enabled && Inside(rect);
    Box(r, x, y, w, 20,
        chosen ? Color{40, 110, 100, 255} : over ? Color{50, 70, 90, 255} : Color{30, 44, 60, 255});
    Box(r, x, y + 19, w, 1, enabled ? kTeal : kDim);
    Text(r, x + (w - Width(label, 1)) / 2, y + 6, label, 1, enabled ? kWhite : kDim);
    if (enabled)
        g_hits.push_back(Hit{rect, id});
}

void DrawRows(SDL_Renderer* r, bool idle)
{
    Box(r, kListX, kListY, 600, kRows * kRowH + 8, Color{6, 14, 24, 255});
    if (g_rows.empty()) {
        std::string a = "Drop records (.jsonl) and replays (.rep) here,";
        std::string b = "or a session's folder, or pick them with Add files.";
        Text(r, 320 - Width(a, 1) / 2, kListY + 100, a, 1, kGrey);
        Text(r, 320 - Width(b, 1) / 2, kListY + 114, b, 1, kGrey);
        return;
    }
    g_top = std::max(0, std::min(g_top, (int)g_rows.size() - kRows));
    for (int i = 0; i < kRows && g_top + i < (int)g_rows.size(); i++) {
        int at = g_top + i;
        const Row& row = g_rows[at];
        float y = kListY + 4 + i * kRowH;
        if (at == g_hover)
            Box(r, kListX + 2, y - 3, 596, kRowH - 1, Color{30, 50, 66, 255});
        Text(r, kListX + 8, y + 1, row.replay ? "REP" : "REC", 1, row.replay ? kYellow : kTeal);
        Text(r, kListX + 44, y + 1, Fit(Label(row), 38, false), 1, kWhite);
        std::string status = row.status == 0   ? "done"
                             : row.status > 0 ? (row.status == 3 ? "differs" : "not made")
                                               : row.said;
        Color c = row.status == 0 ? kTeal : row.status > 0 ? kRed : kGrey;
        Text(r, kListX + 360, y + 1, Fit(status, 26, false), 1, c);
        if (idle) {
            SDL_FRect x = {kListX + 578, y - 2, 16, 14};
            bool over = Inside(x);
            Text(r, x.x + 4, y + 1, "x", 1, over ? kRed : kDim);
            g_hits.push_back(Hit{x, kRemove + at});
        }
    }
    if ((int)g_rows.size() > kRows) {
        float h = kRows * kRowH;
        float bar = std::max(12.0f, h * kRows / g_rows.size());
        float at = (h - bar) * g_top / (float)(g_rows.size() - kRows);
        Box(r, kListX + 596, kListY + 4 + at, 3, bar, kGrey);
    }
}

void DrawFull(SDL_Renderer* r, const ConversionProgress& p)
{
    bool idle = !p.running;
    Box(r, 0, 0, 640, 480, kBack);
    Text(r, 20, 14, "EFZ REPLAY TOOL", 2, kWhite);
    std::string what = "records and replays; videos";
    Text(r, 620 - Width(what, 1), 20, what, 1, kGrey);
    Push(r, kAdd, 20, 42, 120, "Add files...", idle);
    Push(r, kClear, 148, 42, 80, "Clear", idle && !g_rows.empty());
    std::string count = std::to_string(g_rows.size()) + " file(s)";
    Text(r, 620 - Width(count, 1), 48, count, 1, kGrey);
    DrawRows(r, idle);

    // The row under the mouse, at length.
    float y = kListY + kRows * kRowH + 14;
    if (g_hover >= 0 && g_hover < (int)g_rows.size()) {
        const Row& row = g_rows[g_hover];
        Text(r, 20, y, Fit(row.path, 76, true), 1, kGrey);
        if (!row.said.empty() && row.said != "waiting")
            Text(r, 20, y + 12, Fit(row.said, 76, false), 1, row.status == 0 ? kTeal : kRed);
    }

    y = 352;
    Text(r, 20, y + 6, "Save to", 1, kGrey);
    Text(r, 84, y + 6, Fit(g_out, 50, true), 1, kWhite);
    Push(r, kFolder, 500, y, 64, "Change", idle);
    Push(r, kOpen, 568, y, 52, "Open", true);
    y += 28;
    Text(r, 20, y + 6, "Videos", 1, kGrey);
    Push(r, kSmall, 84, y, 90, "640x480", idle, g_scale == 1);
    Push(r, kLarge, 178, y, 90, "1280x960", idle, g_scale == 2);
    Text(r, 272, y + 6, "(S)", 1, kDim);
    Text(r, 304, y + 6, "MP4: H.264 and Opus sound, 64 fps", 1, kDim);
    y += 34;
    bool records = false, replays = false;
    for (const Row& row : g_rows) {
        records |= !row.replay;
        replays |= row.replay;
    }
    Push(r, kToRep, 20, y, 192, "1  Records to replays", idle && records);
    Push(r, kToRecord, 224, y, 192, "2  Replays to records", idle && replays);
    Push(r, kToVideo, 428, y, 192, "3  Videos of them", idle && !g_rows.empty());
    y += 32;
    if (p.running) {
        std::string doing = (p.checking ? "Checking the replay against the record: "
                                        : p.video ? "Making the video: "
                                                  : "Converting: ") +
                            std::to_string(p.job + 1) + " of " + std::to_string(p.jobs);
        Text(r, 20, y + 2, doing, 1, kWhite);
        Box(r, 20, y + 14, 480, 6, Color{60, 60, 60, 255});
        Box(r, 20, y + 14, 480 * p.done, 6, kTeal);
        Push(r, kCancel, 540, y, 80, "Stop", true);
    } else if (!g_message.empty()) {
        Text(r, 20, y + 6, Fit(g_message, 76, false), 1, kYellow);
    }
}

// A video being made: the fight shows; how far, at the bottom.
void DrawBar(SDL_Renderer* r, const ConversionProgress& p)
{
    Box(r, 0, 440, 640, 40, Color{0, 0, 0, 200});
    std::string name = p.job < g_batchRows.size() && g_batchRows[p.job] < (int)g_rows.size()
                           ? Label(g_rows[g_batchRows[p.job]])
                           : "";
    std::string doing = "Video " + std::to_string(p.job + 1) + " of " +
                        std::to_string(p.jobs) + ": " + Fit(name, 44, false);
    Text(r, 16, 448, doing, 1, kWhite);
    Box(r, 16, 462, 500, 6, Color{60, 60, 60, 255});
    Box(r, 16, 462, 500 * p.done, 6, kTeal);
    Push(r, kCancel, 544, 448, 80, "Stop", true);
}

} // namespace

void InitTool(const std::vector<std::string>& files)
{
    g_on = true;
    g_picked = SDL_CreateMutex();
    g_out = LogsFolder() + "/converted";
    for (const std::string& f : files)
        Add(f);
    SDL_SetWindowTitle(Window(), "EFZ replay tool");
    SDL_ShowCursor();
    LogInfo("tool", "the replay tool: %d file(s), saving to %s", (int)g_rows.size(),
            g_out.c_str());
}

bool ToolOn()
{
    return g_on;
}

bool ToolEvent(const SDL_Event& event)
{
    if (!g_on)
        return false;
    SDL_Event e = event;
    if (SDL_Renderer* r = SDL_GetRenderer(Window()))
        SDL_ConvertEventToRenderCoordinates(r, &e);
    switch (e.type) {
    case SDL_EVENT_MOUSE_MOTION: {
        g_mouseX = e.motion.x;
        g_mouseY = e.motion.y;
        int row = (int)((g_mouseY - kListY - 1) / kRowH);
        g_hover = g_mouseX >= kListX && g_mouseX < kListX + 600 && row >= 0 && row < kRows &&
                          g_mouseY >= kListY
                      ? g_top + row
                      : -1;
        return true;
    }
    case SDL_EVENT_MOUSE_WHEEL:
        g_top -= (int)(e.wheel.y * 3);
        return true;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        if (e.button.button != SDL_BUTTON_LEFT)
            return true;
        g_mouseX = e.button.x;
        g_mouseY = e.button.y;
        for (const Hit& h : g_hits) {
            if (Inside(h.rect)) {
                g_clicked = h.id;
                break;
            }
        }
        return true;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        return true;
    case SDL_EVENT_DROP_FILE:
        if (!RecordTasksRunning() && e.drop.data)
            Add(e.drop.data);
        return true;
    }
    return false;
}

void ToolFrame(unsigned char* scene)
{
    Update();
    {
        Lock lock;
        for (const std::string& f : g_pickedFiles)
            Add(f);
        g_pickedFiles.clear();
        if (!g_pickedFolder.empty())
            g_out = g_pickedFolder;
        g_pickedFolder.clear();
    }
    // The keyboard too: 1, 2, 3 the three conversions, S the videos' size, Delete clears.
    static bool held[5];
    const unsigned char* keys = KeyboardState();
    static const int shortcuts[5][2] = {{0x02, kToRep}, {0x03, kToRecord}, {0x04, kToVideo},
                                        {0x1f, kSmall}, {0xd3, kClear}};
    for (int i = 0; i < 5; i++) {
        bool down = (keys[shortcuts[i][0]] & 0x80) != 0;
        if (down && !held[i] && g_clicked == kNone)
            g_clicked = shortcuts[i][1] == kSmall ? (g_scale == 1 ? kLarge : kSmall)
                                                  : shortcuts[i][1];
        held[i] = down;
    }
    int clicked = g_clicked;
    g_clicked = kNone;
    if (clicked == kNone || RecordTasksRunning())
        return;
    static const SDL_DialogFileFilter filters[] = {{"Records and replays", "jsonl;rep"},
                                                   {"Records", "jsonl"},
                                                   {"Replays", "rep"}};
    static std::string logs;
    switch (clicked) {
    case kAdd:
        logs = LogsFolder();
        SDL_ShowOpenFileDialog(Picked, nullptr, Window(), filters, 3, logs.c_str(), true);
        break;
    case kClear:
        g_rows.clear();
        g_message.clear();
        break;
    case kFolder:
        SDL_CreateDirectory(g_out.c_str());
        SDL_ShowOpenFolderDialog(PickedFolder, nullptr, Window(), g_out.c_str(), false);
        break;
    case kOpen:
        SDL_CreateDirectory(g_out.c_str());
        OpenFolder(g_out);
        break;
    case kSmall:
        g_scale = 1;
        break;
    case kLarge:
        g_scale = 2;
        break;
    case kToRep:
        Start(Conversion::kToRep, scene);
        break;
    case kToRecord:
        Start(Conversion::kToRecord, scene);
        break;
    case kToVideo:
        Start(Conversion::kToVideo, scene);
        break;
    default:
        if (clicked >= kRemove && clicked - kRemove < (int)g_rows.size())
            g_rows.erase(g_rows.begin() + (clicked - kRemove));
        break;
    }
}

void DrawTool(SDL_Renderer* r)
{
    if (!g_on)
        return;
    g_hits.clear();
    ConversionProgress p = Progress();
    // Stop works while a conversion goes on (the frames' clicks come here).
    if (p.running && g_clicked == kCancel) {
        g_clicked = kNone;
        CancelConversions();
    }
    Update();
    if (p.running && p.video)
        DrawBar(r, p);
    else
        DrawFull(r, p);
}

} // namespace efz
