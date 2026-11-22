// The tournament session (local.h): revival/EfzRevival/TournamentSession.cpp.
//
// The game walks its title to VS PLAYER by itself (P1's inputs, as netplay's start). The
// two players are EfzRevival.ini's [Tournament] P1_Name and P2_Name, read again on
// character select (new names: a new set, its score from 0). Each match is recorded as a
// network match is (the game's replay mode 2) into TournamentFolder\<time> <P1>
// (<character>) vs <P2> (<character>).rep, and each set's results go to
// TournamentFolder\tournament_results.txt (SaveBattleLog = 1): a line for the set, then
// one a match. In a fight the function keys do nothing, and Esc leaves only once held 80
// frames; back on the title the program ends.
//
// Otherwise than Revival: the replays are saved whatever SaveAllReplays says (Revival
// keeps them for a SavePreviousReplay that the tournament doesn't have); its own
// controller check every 32 frames is the game's (controllers are opened as plugged in).
#include "local_internal.h"


namespace efz {
namespace revival {

namespace {

std::string TimeText(time_t t, const char* format)
{
    tm local;
#ifdef _WIN32
    localtime_s(&local, &t);
#else
    localtime_r(&t, &local);
#endif
    char text[64];
    strftime(text, sizeof(text), format, &local);
    return text;
}

// An iostream's width: to `width` characters (a wide stream's, as Revival's lines are
// made), the text on the left or the right.
std::string Pad(const std::string& s, size_t width, bool left)
{
    size_t n = 0;
    for (unsigned char c : s)
        if ((c & 0xc0) != 0x80)
            n++;
    if (n >= width)
        return s;
    std::string padding(width - n, ' ');
    return left ? s + padding : padding + s;
}

std::string FileSafe(const std::string& s)
{
    std::string out;
    for (char c : s)
        out.push_back((unsigned char)c < 0x20 || strchr("\\/:*?\"<>|", c) ? '_' : c);
    return out;
}

std::string Folder(const std::string& folder)
{
    if (folder.empty() || folder.back() == '/' || folder.back() == '\\')
        return folder;
    return folder + "/";
}

class TournamentSession : public Session {
public:
    TournamentSession()
    {
        // P1 on the title menu: down, down, A (VS PLAYER).
        static const char start[22] = {0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0,
                                       4, 0, 0, 0, 0, 0x10, 0, 0, 0, 0, 0};
        for (char c : start)
            menuInputs_.push_back(c);
    }

    ~TournamentSession() override
    {
        g_revival.tournament = false;
        g_revival.matchLeft = nullptr;
        g_revival.replayOpen = nullptr;
        g_revival.replayWrite = nullptr;
        g_revival.replayClose = nullptr;
    }

    void Start() override
    {
        self_ = this;
        g_revival.tournament = true;
        g_revival.matchLeft = [] { self_->MatchLeft(); };
        g_revival.replayOpen = [] { self_->replay_.clear(); self_->recording_ = true; };
        g_revival.replayWrite = [](short v) {
            if (self_->recording_)
                self_->replay_.push_back(v);
        };
        g_revival.replayClose = [] { self_->WriteReplay(); };
        const Config& ini = GetConfig();
        p1Name_ = ini.p1Name;
        p2Name_ = ini.p2Name;
        LogInfo("revival", "tournament: %s vs %s, folder %s", p1Name_.c_str(), p2Name_.c_str(),
                ini.tournamentFolder.c_str());
    }

    void Update() override
    {
        int scene = SceneId();
        if (lastScene_ != scene)
            SceneChanged();
        if (scene == 3 || scene == 1 || scene == 5)
            DrawInfo();
        lastScene_ = scene;
        switch (scene) {
        case 0:
            // Back on the title once the menu inputs ran out: the tournament is over.
            if (menuInputs_.empty()) {
                LogInfo("revival", "tournament: back on the title; the end");
                RequestQuit();
            }
            RunGameFrame();
            return;
        case 1:
            CheckDevices();
            SelectFrame();
            return;
        case 3:
            for (int i = 0; i < 2; i++)
                if (CPlayer* p = PlayerOf(i))
                    rounds_[i] = p->m_roundsWon;
            RunGameFrame();
            return;
        default:
            RunGameFrame();
        }
    }

    void Input(unsigned char* input, int player) override
    {
        if (!menuInputs_.empty()) {
            if (player == 1) {
                *input = 0;
                return;
            }
            *input = (unsigned char)menuInputs_.front();
            menuInputs_.pop_front();
        }
    }

    // No function keys in a fight, and Esc only once held.
    void FightKeys(unsigned char* keys) override
    {
        memset(keys + 0x3b, 0, 15); // F1 to F10, and on
        if (keys[0x01] & 0x80) {
            escFrames_++;
            if (!escHeld_ || escFrames_ < kEscHoldFrames) {
                keys[0x01] = 0;
                escHeld_ = true;
            }
        } else {
            escHeld_ = false;
            escFrames_ = 0;
        }
    }

private:
    static const int kEscHoldFrames = 80;

    // Every 64 frames of character select: the ini again (new names: a new set).
    void SelectFrame()
    {
        if (selectFrames_ % 64 == 0) {
            selectFrames_ = 0;
            std::string p1 = GetConfig().p1Name, p2 = GetConfig().p2Name;
            ReloadConfig();
            if (p1 != GetConfig().p1Name || p2 != GetConfig().p2Name) {
                wins_[0] = wins_[1] = 0;
                setNumber_++;
                LogInfo("revival", "tournament: a new set, %s vs %s", GetConfig().p1Name.c_str(),
                        GetConfig().p2Name.c_str());
            }
        }
        selectFrames_++;
        RunGameFrame();
    }

    void SceneChanged()
    {
        int scene = SceneId();
        CGame* game = GameObject();
        if (scene == 3) {
            SetTextRender(true);
            seed_ = RandState();
            fightStart_ = time(nullptr);
            characters_[0] = Character(0);
            characters_[1] = Character(1);
            return;
        }
        if (scene == 1) {
            SetTextRender(true);
            return;
        }
        if (scene == 2) {
            p1Name_ = GetConfig().p1Name;
            p2Name_ = GetConfig().p2Name;
            // Game::setNetplay: the match recorded as a replay.
            game->m_gameMode = 5;
            game->m_cpuLevel = 1;
            game->m_replayMode = 2;
            replayName_ = Folder(GetConfig().tournamentFolder) +
                          TimeText(time(nullptr), "%Y%m%d-%H%M%S") + " " + FileSafe(p1Name_) +
                          " (" + CharacterName(Character(0)) + ") vs " + FileSafe(p2Name_) +
                          " (" + CharacterName(Character(1)) + ").rep";
            SetTextRender(false);
            if (wins_[0] != 0 || wins_[1] != 0)
                return;
            // A new set: its header.
            Results("\n" + Pad(TimeText(time(nullptr), "%Y/%m/%d %H:%M:%S"), 19, true) +
                    Pad(Pad(p1Name_, 21, false) + " VS " + Pad(p2Name_, 21, true), 46, true) +
                    "\n");
            return;
        }
        if (scene == 5) {
            if (game->m_winner == 0 || game->m_winner == 1)
                wins_[(int)game->m_winner]++;
            long elapsed = std::max(0L, (long)difftime(time(nullptr), fightStart_));
            char seconds[8];
            snprintf(seconds, sizeof(seconds), "%02ld", elapsed % 60);
            std::string duration = Pad(std::to_string(elapsed / 60), 3, false) + ":" + seconds;
            Results(Pad(TimeText(fightStart_, "%Y/%m/%d %H:%M:%S"), 19, true) +
                    Pad(Pad(CharacterName(characters_[0]), 21, false) + " VS " +
                            Pad(CharacterName(characters_[1]), 21, true),
                        46, true) +
                    Pad("Rounds: " + std::to_string(rounds_[0]) + " " + std::to_string(rounds_[1]),
                        15, true) +
                    Pad("Duration: " + duration, 20, true) +
                    Pad("Score: " + Pad(std::to_string(wins_[0]), 3, false) + " " +
                            std::to_string(wins_[1]),
                        15, true) +
                    "\n");
            rounds_[0] = rounds_[1] = 0;
        }
    }

    // onReplayDone: the match's replay closed, and the game VS HUMAN again.
    void MatchLeft()
    {
        GameObject()->m_replay.Close();
        CGame* game = GameObject();
        game->m_gameMode = 4;
        game->m_cpuLevel = 4;
        game->m_replayMode = 0;
    }

    // The match's replay, with Revival's extended part: the random state the fight began
    // with, and no inputs (the tournament keeps none).
    void WriteReplay()
    {
        if (!recording_)
            return;
        recording_ = false;
        FILE* f = OpenGameFile(replayName_.c_str(), "wb");
        if (!f) {
            LogWarn("revival", "tournament: can't write the replay %s", replayName_.c_str());
            return;
        }
        fwrite(replay_.data(), 2, replay_.size(), f);
        int32_t end[4] = {9999 << 16, 0, 0, 0};
        for (int i = 0; i < 30; i++)
            fwrite(end, sizeof(end), 1, f);
        int32_t offset = (int32_t)ftell(f);
        int32_t seed = (int32_t)seed_, count = 0, marker = -1;
        fwrite(&seed, 4, 1, f);
        fwrite(&count, 4, 1, f);
        fwrite(&offset, 4, 1, f);
        fwrite(&marker, 4, 1, f);
        fclose(f);
        LogInfo("revival", "tournament: replay saved: %s", replayName_.c_str());
    }

    void Results(const std::string& text)
    {
        const Config& ini = GetConfig();
        if (!ini.saveBattleLog)
            return;
        std::string path = Folder(ini.tournamentFolder) + "tournament_results.txt";
        FILE* f = OpenGameFile(path.c_str(), "ab");
        if (!f) {
            LogWarn("revival", "tournament: can't write %s", path.c_str());
            return;
        }
        fwrite(text.data(), 1, text.size(), f);
        fclose(f);
    }

    void DrawInfo()
    {
        ClearText();
        const Config& ini = GetConfig();
        AddText("Wins: " + std::to_string(wins_[0]), 10, 5);
        AddText(ini.p1Name, 80, 5);
        int right = 630;
        if (ini.displayScore) {
            AddText("Wins: " + std::to_string(wins_[1]) + "   ", 630, 5, kAlignRight);
            right = 560;
        }
        AddText(ini.p2Name, right, 5, kAlignRight);
    }

    static TournamentSession* self_;
    std::deque<char> menuInputs_; // P1's, from the title to VS PLAYER
    int lastScene_ = 0;
    int selectFrames_ = 0;
    int setNumber_ = 0;
    int wins_[2] = {0, 0}; // in this set
    int rounds_[2] = {0, 0};
    int characters_[2] = {-1, -1};
    time_t fightStart_ = 0;
    uint32_t seed_ = 0;
    std::string p1Name_, p2Name_;
    bool escHeld_ = false;
    int escFrames_ = 0;
    std::string replayName_;
    bool recording_ = false;
    std::vector<short> replay_;
};

TournamentSession* TournamentSession::self_ = nullptr;

} // namespace

Session* NewTournamentSession()
{
    return new TournamentSession();
}

} // namespace revival
} // namespace efz
