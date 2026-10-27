// The record of a frame that both sides of a netplay match (and its spectators) compare:
// makeSyncBlock, in the object after OnlineSpectatorSession.cpp's (0x10075680-0x100757e0;
// its file name is unknown, but it sorts between that and PracticeSession.cpp). The
// object also has two functions nothing calls: 0x10075680 only returns its object (an
// empty constructor) and 0x10075690 does nothing (an empty destructor). Link-time code
// generation keeps a function only when something refers to it, so something did before
// it removed the calls to them as doing nothing: here, an object makeSyncBlock makes
// and destroys (which matches). Their class and the object's use are guesses.
#include "stdafx.h"
#include "EfzGame.h"
#include "Log.h"

// The unknown class of 0x10075680 and 0x10075690.
class SyncScope {
public:
    SyncScope();
    ~SyncScope();
};

// FUNCTION: 0x10075690
SyncScope::~SyncScope()
{
}

// FUNCTION: 0x10075680
SyncScope::SyncScope()
{
}

// FUNCTION: 0x100756a0
SyncBlock makeSyncBlock(int frame, const FrameInput &inputP1, const FrameInput &inputP2)
{
    SyncScope scope;
    SyncBlock sync;
    sync.frame = frame;
    sync.state = g_game.sceneId();
    sync.inputP1 = inputP1;
    sync.inputP2 = inputP2;
    unsigned int control = 0;
    _controlfp_s(&control, 0, 0);
    sync.fpuCW = control;
    sync.rng = g_game.newRandomSeed();
    if (g_game.sceneId() == 3) {
        CScene *fight = EFZ_SCENES[3];
        CPlayer *p1 = *fight->players[0];
        CPlayer *p2 = *fight->players[1];
        sync.stateP1 = g_game.playerAction(0);
        sync.stateP2 = g_game.playerAction(1);
        sync.p1x = p1->x;
        sync.p1y = p1->y;
        sync.p2x = p2->x;
        sync.p2y = p2->y;
    } else {
        sync.stateP1 = 0;
        sync.stateP2 = 0;
        sync.p1x = 0;
        sync.p1y = 0;
        sync.p2x = 0;
        sync.p2y = 0;
    }
    g_log << "Sync " << sync.toString();
    g_log.flush();
    return sync;
}
