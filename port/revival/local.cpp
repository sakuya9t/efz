// EfzRevival's local play (local.h): the sessions' switching (EfzRevival.cpp), the game
// as they see it (EfzGame.cpp) and the overlay they draw (DDRAW.dll's EfzRender).
#include "local_internal.h"
#include "local.h"

#include <SDL3/SDL.h>

#include "../record.h"
#include "../netplay.h"

namespace efz {
namespace revival {

namespace {

struct Text {
    std::string text;
    int x, y, align;
};

struct State {
    bool on = false;
    bool tournament = false;
    std::unique_ptr<Session> session;
    int lastScene = 0; // switchSession's
    // The overlay
    std::vector<Text> texts;
    bool textOn = false;
    std::vector<std::pair<int, int>> boxes; // player, kind
    double fps = kDefaultFps;
    bool swapped = false;
    // The frame being run (RunFrame's)
    void (*run)(void*) = nullptr;
    void* scene = nullptr;
    bool ran = false;
    long frames = 0;     // RunFrame's calls
    long keysFrame = -1; // the frame FightKeys last decided for, and what it decided
    unsigned char keys[0x100];
};
State g;

// A record played or converted from the REPLAY menu, or the replay tool: not the
// sessions' (record.cpp plays those itself).
bool RecordsBusy()
{
    return RecordTasksRunning() || ViewingRecord() != nullptr;
}

// Whether the session runs the game's frames now: not in a network match, nor a record's,
// and only as OPTIONS has it (the tournament, asked for, whatever it says).
bool Active()
{
    return g.on && !RecordsBusy() && !g_netplay.active && g.session &&
           (g.tournament || (RevivalFeatures() && g.session->Enabled()));
}

// switchSession: on leaving the title, REPLAY's menu brings the replay session, VS PLAYER's
// or PRACTICE's character select the practice session; the tournament keeps its own.
void SwitchSession()
{
    int scene = SceneId();
    if (scene == g.lastScene)
        return;
    if (g.lastScene == 0 && !g.tournament) {
        Session* next = nullptr;
        if (scene == 8 && MenuChoice() == 4)
            next = NewReplaySession();
        else if (scene == 1 && (MenuChoice() == 3 || MenuChoice() == 2))
            next = NewPracticeSession();
        if (next) {
            g.session.reset(next);
            g.session->Start();
        }
    }
    g.lastScene = scene;
}

} // namespace

// --- local.h

void InitLocal(bool tournament)
{
    g.on = true;
    g.tournament = tournament;
    g.session.reset(tournament ? NewTournamentSession() : NewPracticeSession());
    g.session->Start();
    LogInfo("revival", "EfzRevival's %s on", tournament ? "tournament" : "local play");
}

bool LocalOn()
{
    return g.on;
}

bool WillRunFrame()
{
    if (!g.on || RecordsBusy() || g_netplay.active)
        return true;
    SwitchSession();
    if (!Active())
        return true;
    int keys[64];
    int n = PressedKeys(keys, 64);
    for (int i = 0; i < n; i++)
        g.session->KeyPressed(keys[i]);
    return !g.session->Holds();
}

void RunFrame(void (*run)(void* scene), void* scene)
{
    if (!Active()) {
        run(scene);
        return;
    }
    g.run = run;
    g.scene = scene;
    g.frames++;
    g.session->Update();
    g.run = nullptr;
}

double FramesPerSecond()
{
    return Active() ? g.fps : kDefaultFps;
}

void Input(int player, unsigned char* input)
{
    if (Active() && player >= 0 && player < 2)
        g.session->Input(input, player);
}

void FightKeys(unsigned char* keys, size_t size)
{
    if (!Active() || size < 0x100 || SceneId() != 3)
        return;
    // The fight reads the keyboard more than once a frame (CScene3::HandleKeys first, then
    // CInput::GetInput's reads): the session decides once a frame, as Revival's
    // fightUpdate is called once, and every read of the frame gets its function keys and Esc.
    if (g.keysFrame != g.frames) {
        g.keysFrame = g.frames;
        memcpy(g.keys, keys, 0x100);
        g.session->FightKeys(g.keys);
    }
    keys[0x01] = g.keys[0x01];
    for (int k = 0x3b; k <= 0x58; k++)
        keys[k] = g.keys[k];
}

// --- The game

int SceneId()
{
    unsigned char* scene = Objects().scene;
    return scene ? *scene : -1;
}

CScene* SceneAt(int index)
{
    return index >= 0 && index < 9 ? Objects().scenes[index] : nullptr;
}

CGame* GameObject()
{
    return Objects().game;
}

int MenuChoice()
{
    CScene0* title = (CScene0*)SceneAt(0);
    return title ? title->m_cursor : 0;
}

CPlayer* PlayerOf(int index)
{
    if (SceneId() != 3)
        return nullptr;
    CScene* fight = SceneAt(3);
    PTR32(CPlayer)* ref = index == 0 ? (PTR32(CPlayer)*)fight->m_player1Ref
                                     : (PTR32(CPlayer)*)fight->m_player2Ref;
    return ref ? (CPlayer*)*ref : nullptr;
}

int Character(int player)
{
    int scene = SceneId();
    if (scene == 2 || scene == 3) {
        CScene* s = SceneAt(scene);
        PTR32(CPlayer)* ref = player == 0 ? (PTR32(CPlayer)*)s->m_player1Ref
                                          : (PTR32(CPlayer)*)s->m_player2Ref;
        CPlayer* p = ref ? (CPlayer*)*ref : nullptr;
        return p ? p->m_charId : -1;
    }
    if (scene == 1)
        return ((CScene1*)SceneAt(1))->m_charId[player];
    return -1;
}

int HumanPlayer()
{
    return GameObject()->m_isCpu[0];
}

void RunGameFrame()
{
    if (g.run) {
        g.run(g.scene);
        g.ran = true;
    }
}

void SwapBindings()
{
    CInput* input = Objects().input;
    if (!input)
        return;
    for (int i = 0; i < 8; i++)
        std::swap(input->m_bindings[0][i], input->m_bindings[1][i]);
    g.swapped = !g.swapped;
}

bool SwappedBindings()
{
    return g.swapped;
}

void UnswapBindings()
{
    if (g.swapped)
        SwapBindings();
}

bool IsWakingUp(int player)
{
    CPlayer* p = PlayerOf(player);
    return p && p->pattern == kLyingDown && p->timer >= 3;
}

bool IsTeching(int player)
{
    CPlayer* p = PlayerOf(player);
    if (!p)
        return false;
    int action = p->pattern;
    return action >= kFirstHitReaction && action < kFirstGuard && p->m_guardGauge <= 0.0 &&
           p->m_untechTime == 0 && p->y < 0.0 && p->m_noAirRecovery == 0;
}

bool IsGuarding(int player)
{
    CPlayer* p = PlayerOf(player);
    if (!p)
        return false;
    int action = p->pattern;
    return action == kGuardStandMedium || action == kGuardCrouchLight || action == kGuardAir;
}

bool IsRecoilGuarding(int player)
{
    CPlayer* p = PlayerOf(player);
    if (!p)
        return false;
    int action = p->pattern;
    return action == kRecoilGuardStand || action == kRecoilGuardCrouch || action == kRecoilGuardAir;
}

int ReplayMode()
{
    int scene = SceneId();
    if (scene != 2 && scene != 3)
        return -1;
    return GameObject()->m_replayMode;
}

bool IsRoundOver()
{
    if (SceneId() != 3)
        return false;
    int leave = ((CScene3*)SceneAt(3))->m_leave;
    return leave == 1 || leave == 2;
}

bool IsMatchOver()
{
    return SceneId() == 3 && ((CScene3*)SceneAt(3))->m_leave == 2;
}

unsigned char FunctionKeys()
{
    const unsigned char* keys = KeyboardState();
    unsigned char result = 0;
    for (int i = 0; i < 5; i++)
        if (keys[0x3e + i] & 0x80)
            result |= 1 << i;
    if (keys[0x01] & 0x80)
        result |= 0x20;
    return result;
}

unsigned char CleanInput(unsigned char input)
{
    if ((input & kInputLeft) && (input & kInputRight))
        return input & ~kInputRight;
    return input;
}

unsigned char ControlsOf(int player)
{
    CInput* input = Objects().input;
    if (!input)
        return 0;
    // CInput::GetInput's reading, without its hooks: P1's bindings are LocalControls'.
    if (player == 0)
        return LocalControls();
    // P2's: read with the bindings swapped, so that LocalControls reads them
    for (int i = 0; i < 8; i++)
        std::swap(input->m_bindings[0][i], input->m_bindings[1][i]);
    unsigned char result = LocalControls();
    for (int i = 0; i < 8; i++)
        std::swap(input->m_bindings[0][i], input->m_bindings[1][i]);
    return result;
}

const char* CharacterName(int c)
{
    static const char* const names[] = {
        "Rumi",    "Ayu",  "Mai",    "Makoto",  "Akane",   "Mayu",  "Nagamori",
        "Misaki",  "Shiori", "Sayuri", "NayukiS", "Mio",   "Doppel", "Kaori",
        "Ikumi",   "Mishio", "Akiko", "NayukiA", "Unknown", "Kanna", "Kano",
        "Minagi",  "AltNayukiS", "Misuzu", "BossUnknown"};
    return c >= 0 && c < 25 ? names[c] : "error";
}

void CheckDevices()
{
    static int frames = 1;
    static Sint64 seen = 0;
    if (frames++ % 32 != 0)
        return;
    if (!(SDL_GetWindowFlags(Window()) & SDL_WINDOW_INPUT_FOCUS))
        return;
    std::string path = std::string(SaveDir()) + "/key.ini";
    SDL_PathInfo info;
    if (!SDL_GetPathInfo(path.c_str(), &info)) {
        path = std::string(DataDir()) + "/key.ini";
        if (!SDL_GetPathInfo(path.c_str(), &info))
            return;
    }
    if (seen == 0)
        seen = info.modify_time;
    if (info.modify_time > seen) {
        seen = info.modify_time;
        bool swapped = g.swapped;
        Objects().input->LoadBindings();
        g.swapped = false;
        if (swapped)
            SwapBindings();
        LogInfo("revival", "key.ini written: its keys read again");
    }
}

// --- The overlay

void ClearText()
{
    g.texts.clear();
}

void AddText(const std::string& text, int x, int y, int align)
{
    g.texts.push_back(Text{text, x, y, align});
}

void SetTextRender(bool on)
{
    g.textOn = on;
}

void ClearBoxes()
{
    g.boxes.clear();
}

void ShowBoxes(int player, int kind)
{
    g.boxes.push_back({player, kind});
}

std::string InputText(unsigned char input)
{
    bool up = input & kInputUp, down = input & kInputDown;
    bool left = input & kInputLeft, right = input & kInputRight;
    char dir = up ? (left ? '7' : right ? '9' : '8') : down ? (left ? '1' : right ? '3' : '2')
                                                            : left ? '4' : right ? '6' : '5';
    std::string text(1, dir);
    text += ' ';
    text += input & kInputA ? 'A' : ' ';
    text += input & kInputB ? 'B' : ' ';
    text += input & kInputC ? 'C' : ' ';
    text += input & kInputD ? 'D' : ' ';
    return text;
}

void DrawInputs(const std::vector<char>& inputs, int y, int x, int divisor)
{
    if (inputs.empty())
        return;
    int line = 0;
    size_t at = inputs.size() - 1;
    char last = inputs[at];
    while (at > 0 && line <= 14) {
        int frames = 0;
        while (at > 0 && inputs[at] == last) {
            frames++;
            at--;
            if (frames > divisor * 999)
                frames = divisor * 999;
        }
        char count[8];
        snprintf(count, sizeof(count), "%3d", frames / divisor);
        AddText(std::string(count) + " " + InputText((unsigned char)last), x, y + line * 14);
        last = inputs[at];
        line++;
    }
}

void SetFps(double fps)
{
    g.fps = fps;
}

namespace {

struct Rect {
    int left, top, right, bottom;
    uint32_t color;
    bool stippled;
};

// One player's boxes of a kind, and its objects' (Game::drawBoxRequest), in the
// overlay's 640x480.
void CollectBoxes(int index, int kind, std::vector<Rect>* out)
{
    CPlayer* p = PlayerOf(index);
    CScene3* fight = (CScene3*)SceneAt(3);
    if (!p || !fight || !p->m_patterns || !p->anims)
        return;
    const PatternFrame& frame = p->m_patterns[p->pattern].frames[p->frame];
    const EffectFrame& sprite = p->anims[p->pattern].frames[p->frame];
    CollisionInfo info;
    memset(&info, 0, sizeof(info));
    info.frame = frame;
    info.anim = sprite;
    info.x = p->x;
    info.y = p->y;
    info.facing = p->facing;
    bool vulnerable = (frame.flagsB0 & kStateInvulnerable) == 0 && p->m_invulTime == 0;
    bool solid = p->m_hitsLeft != 0 || (frame.flagsAA & kAttackThrow) != 0;
    const RECT* boxes = nullptr;
    int count = 0;
    uint32_t color = 0;
    bool stippled = false;
    switch (kind) {
    case kBoxHit:
        boxes = frame.attackBoxes;
        color = 0xffff0000;
        count = 4;
        stippled = !solid;
        break;
    case kBoxHurt:
        if (vulnerable) {
            boxes = frame.boxes;
            color = 0xff0000ff;
            count = 5;
        }
        break;
    case kBoxCollision:
        boxes = &frame.pushBox;
        color = 0xffffff00;
        count = 1;
        break;
    }
    int cameraX = fight->m_drawX, cameraY = fight->m_drawY;
    for (int i = 0; i < count; i++) {
        RECT box = boxes[i];
        RECT r = fight->InfoBoxOnStage(&info, &box);
        int width = box.right - box.left;
        int height = box.bottom - box.top;
        if (width == 0 || height == 0)
            continue;
        Rect s;
        s.left = (r.left + cameraX) * 2;
        s.right = s.left + width * 2;
        s.top = (int)((cameraY + box.top + info.y + 210.0 - (info.y < 0.0) - sprite.y) * 2.0);
        s.bottom = s.top + height * 2;
        s.color = color;
        s.stippled = stippled;
        out->push_back(s);
        if (kind == kBoxCollision) {
            // The crossup midline: through the player's x, twice the box's height, centred
            // on its top.
            int top = (int)(box.top - height / 2.0);
            Rect line;
            line.left = line.right = ((int)p->x + cameraX) * 2;
            line.top = (int)((cameraY + top + info.y + 210.0 - (info.y < 0.0) - sprite.y) * 2.0);
            line.bottom = line.top + height * 4;
            line.color = color;
            line.stippled = stippled;
            out->push_back(line);
        }
    }
    for (int i = p->m_objectTail; i != p->m_objectHead; i = (i + 1) % 64) {
        if (p->m_objectActive[i] == 0)
            continue;
        PlayerObject* object = &p->m_objects[i];
        const PatternFrame& of = p->m_patterns[object->pattern].frames[object->frame];
        bool objectVulnerable = (of.flagsB0 & kStateInvulnerable) == 0;
        bool active = object->hitsLeft != 0 && objectVulnerable;
        boxes = nullptr;
        count = 0;
        stippled = false;
        switch (kind) {
        case kBoxHit:
            boxes = of.attackBoxes;
            color = 0xffff0000;
            count = 4;
            stippled = !active || object->attackResult != 0;
            break;
        case kBoxHurt:
            if (objectVulnerable) {
                boxes = of.boxes;
                color = 0xff0000ff;
                count = 5;
                break;
            }
            // not vulnerable: its collision box, in blue
            boxes = &of.pushBox;
            color = 0xff0000ff;
            count = 1;
            break;
        case kBoxCollision:
            boxes = &of.pushBox;
            color = objectVulnerable ? 0xffffff00 : 0xff0000ff;
            count = 1;
            break;
        }
        for (int j = 0; j < count; j++) {
            RECT box = boxes[j];
            RECT r = fight->BoxOnStage(object, &box);
            int width = box.right - box.left;
            int height = box.bottom - box.top;
            if (width == 0 || height == 0)
                continue;
            Rect s;
            s.left = (r.left + cameraX) * 2;
            s.right = s.left + width * 2;
            s.top = (r.top + cameraY) * 2 + 420;
            s.bottom = s.top + height * 2;
            s.color = color;
            s.stippled = stippled;
            out->push_back(s);
        }
    }
}

// A closed line two pixels wide; stippled: every other 4 pixels.
void DrawRect(SDL_Renderer* r, const Rect& b)
{
    SDL_SetRenderDrawColor(r, (b.color >> 16) & 0xff, (b.color >> 8) & 0xff, b.color & 0xff, 255);
    auto line = [&](float x0, float y0, float x1, float y1) {
        float length = std::max(fabsf(x1 - x0), fabsf(y1 - y0));
        if (!b.stippled || length < 1) {
            SDL_FRect f = {std::min(x0, x1), std::min(y0, y1), std::max(2.0f, fabsf(x1 - x0) + 2),
                           std::max(2.0f, fabsf(y1 - y0) + 2)};
            SDL_RenderFillRect(r, &f);
            return;
        }
        for (float t = 0; t < length; t += 8) {
            float t1 = std::min(length, t + 4);
            float ax = x0 + (x1 - x0) * t / length, ay = y0 + (y1 - y0) * t / length;
            float bx = x0 + (x1 - x0) * t1 / length, by = y0 + (y1 - y0) * t1 / length;
            SDL_FRect f = {std::min(ax, bx), std::min(ay, by), std::max(2.0f, fabsf(bx - ax)),
                           std::max(2.0f, fabsf(by - ay))};
            SDL_RenderFillRect(r, &f);
        }
    };
    float l = (float)b.left, t = (float)b.top, rr = (float)b.right, bb = (float)b.bottom;
    if (b.left == b.right) {
        line(l, t, l, bb);
        return;
    }
    line(l, t, rr, t);
    line(rr, t, rr, bb);
    line(l, bb, rr, bb);
    line(l, t, l, bb);
}

void DrawText(SDL_Renderer* r, const Text& t)
{
    float width = (float)t.text.size() * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    float x = t.align == kAlignRight ? t.x - width : (float)t.x;
    float y = (float)t.y + 3;
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
            if (dx || dy)
                SDL_RenderDebugText(r, x + dx, y + dy, t.text.c_str());
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderDebugText(r, x, y, t.text.c_str());
}

} // namespace

void DrawLocal(SDL_Renderer* renderer)
{
    if (!Active())
        return;
    if (SceneId() == 3 && !g.boxes.empty()) {
        std::vector<Rect> rects;
        for (const auto& b : g.boxes)
            CollectBoxes(b.first, b.second, &rects);
        for (const Rect& rect : rects)
            DrawRect(renderer, rect);
    }
    if (g.textOn) {
        for (const Text& t : g.texts)
            DrawText(renderer, t);
    }
}

} // namespace revival
} // namespace efz
