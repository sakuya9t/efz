// The game state (EfzGame.h).
#include "stdafx.h"
#include "EfzGame.h"
#include "Log.h"
#include "Config.h"
#include "../DDRAW/EfzRender.h"
#include <comdef.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "EfzRevival.h"

// FUNCTION: 0x1006d5a0
static BOOL countDevice(LPCDIDEVICEINSTANCE instance, LPVOID count)
{
    ++*(int *)count;
    return TRUE;
}

// FUNCTION: 0x1006d480
// (The FILETIME and joystickCount_ are cleared last: the zero ZeroMemory leaves in eax
// is then used only for them, and the other members get immediates.)
Game::Game()
{
    unknown0 = 0;
    initialized_ = false;
    replay_.name = L"NONE.rep";
    writeReplay_ = true;
    readReplay_ = true;
    muteBGM_ = false;
    recording_ = false;
    saveReplays_ = true;
    pendingReplay_ = 0;
    timer = 0;
    render_ = 0;
    rendering_ = true;
    unknown16_ = false;
    graphics_ = 0;
    input_ = 0;
    sound_ = 0;
    game_ = 0;
    ZeroMemory(&keyIniTime_, sizeof(keyIniTime_));
    joystickCount_ = 0;
}

// FUNCTION: 0x1006d390
void Game::init()
{
    if (!initialized_) {
        Config config(L"./EfzRevival.ini");
        muteBGM_ = config.muteBGM != 0;
        saveReplays_ = config.saveAllReplays != 0;
        timer = getEfzTimer();
        render_ = getEfzRender();
        render_->initTextRender();
        initialized_ = true;
        rendering_ = true;
        unknown16_ = false;
        graphics_ = EFZ_GRAPHICS;
        input_ = EFZ_INPUT;
        sound_ = EFZ_SOUND;
        game_ = EFZ_GAME;
    }
}

// FUNCTION: 0x1006d350
Game::~Game()
{
}

// FUNCTION: 0x1006d340
int Game::sceneId()
{
    return EFZ_SCENE;
}

// Player 1's keys for player 2's (the practice session's switch).
// FUNCTION: 0x1006d320
void Game::swapBindings()
{
    KeyBindings *keys = bindings();
    std::swap(keys[0], keys[1]);
}

// FUNCTION: 0x1006d310
void Game::setRandomState(unsigned int state)
{
    g_rng.seed(state);
}

// FUNCTION: 0x1006d280
int Game::newRandomSeed()
{
    std::stringstream stream;
    stream << g_rng;
    return atoi(stream.str().data());
}

// g_rng's state from an extended replay.
// FUNCTION: 0x1006d210
void Game::loadRandomState(int state)
{
    std::stringstream stream;
    stream << state;
    stream >> g_rng;
}

// The game's CSound::Play, but the music stays silent with MuteBGM.
// FUNCTION: 0x1006d190
int Game::playSound(WORD id, int loop)
{
    int result = id;
    IDirectSoundBuffer **buffers = sound_->buffers;
    if (isMusic(id) && muteBGM_)
        return buffers[id]->Stop();
    if (id < 0x96 && buffers[id]) {
        buffers[id]->Stop();
        buffers[id]->SetCurrentPosition(0);
        result = buffers[id]->Play(0, 0, loop);
    }
    return result;
}

// FUNCTION: 0x1006d150
int Game::stopSound(WORD id)
{
    int result = id;
    IDirectSoundBuffer **buffers = sound_->buffers;
    if (id < 0x96 && buffers[id])
        result = buffers[id]->Stop();
    return result;
}

// FUNCTION: 0x1006d110
void Game::setSoundVolume(WORD id, int volume)
{
    IDirectSoundBuffer **buffers = sound_->buffers;
    if (id < 0x96 && buffers[id])
        buffers[id]->SetVolume(volume);
}

// FUNCTION: 0x1006d0f0
bool Game::isMusic(WORD id)
{
    return id == g_game.musicId();
}

// FUNCTION: 0x1006d0d0
char Game::efzInput(int player)
{
    return getEfzInput(player != 0);
}

// FUNCTION: 0x1006d0b0
void Game::runFrame()
{
    *(BYTE *)&EFZ_SCENE = EFZ_SCENES[EFZ_SCENE]->Update();
}

// Without rendering, CGraphics' blits and fills return at once (a jump to their end):
// the frames a rollback or a fast replay runs aren't drawn.
// FUNCTION: 0x1006cf90
void Game::setRendering(bool enable)
{
    if (rendering_ != enable) {
        rendering_ = enable;
        if (enable) {
            patches_.restoreAll();
            return;
        }
        BYTE blit[5] = { 0xe9, 0x17, 0x03, 0x00, 0x00 };
        patches_.patch((void *)0x409a90, 5, blit);
        BYTE blitEx[5] = { 0xe9, 0x79, 0x03, 0x00, 0x00 };
        patches_.patch((void *)0x40a0b0, 5, blitEx);
        BYTE blitTint[5] = { 0xe9, 0x59, 0x03, 0x00, 0x00 };
        patches_.patch((void *)0x40a440, 5, blitTint);
        BYTE blitShadow[5] = { 0xe9, 0x1e, 0x03, 0x00, 0x00 };
        patches_.patch((void *)0x40a7b0, 5, blitShadow);
        BYTE fillRect[5] = { 0xe9, 0x2c, 0x01, 0x00, 0x00 };
        patches_.patch((void *)0x40b300, 5, fillRect);
        BYTE upscale[5] = { 0xe9, 0x76, 0x01, 0x00, 0x00 };
        patches_.patch((void *)0x40b44c, 5, upscale);
        BYTE blitSmear[5] = { 0xe9, 0x20, 0x03, 0x00, 0x00 };
        patches_.patch((void *)0x40aae0, 5, blitSmear);
    }
}

// Called by CScene3::Draw in place of CScene3::Unk7631f0 (hookCall at 0x76479c): the
// boxes asked for, the kept ones, then the call it replaced.
// FUNCTION: 0x1006ce40
void Game::drawBoxes()
{
    if (rendering_ && sceneId() == 3) {
        std::list<BoxRequest>::iterator it = boxes_.begin();
        std::list<BoxRequest>::iterator end = boxes_.end();
        for (; it != end; ++it) {
            BoxRequest request = *it;
            drawBoxRequest(&request);
        }
        std::vector<HitRect>::iterator rect = rects_.begin();
        std::vector<HitRect>::iterator last = rects_.end();
        for (; rect != last; ++rect) {
            HitRect copy = *rect;
            toScreen(&copy.rect);
            render_->addRectRender(copy.rect, copy.color, copy.flags);
        }
        EFZ_DRAW_FIGHT((CScene3 *)EFZ_SCENES[3]);
    }
}

// FUNCTION: 0x1006ce00
void Game::readKeyboard(BYTE *keys)
{
    memset(keys, 0, 0x100);
    IDirectInputDevice7 *keyboard = device(0);
    if (keyboard) {
        keyboard->Acquire();
        keyboard->GetDeviceState(0x100, keys);
    }
}

// F4-F8 and Esc as bits 0-5.
// FUNCTION: 0x1006cd90
BYTE Game::functionKeys()
{
    BYTE keys[0x100];
    readKeyboard(keys);
    BYTE result = 0;
    if (keys[DIK_F4] & 0x80)
        result = 1;
    if (keys[DIK_F5] & 0x80)
        result |= 2;
    if (keys[DIK_F6] & 0x80)
        result |= 4;
    if (keys[DIK_F7] & 0x80)
        result |= 8;
    if (keys[DIK_F8] & 0x80)
        result |= 0x10;
    if (keys[DIK_ESCAPE] & 0x80)
        result |= 0x20;
    return result;
}

// The names the game's files use, by character number.
// FUNCTION: 0x1006cab0
std::string Game::characterName(int character)
{
    switch (character) {
    case 0:
        return "Rumi";
    case 1:
        return "Ayu";
    case 2:
        return "Mai";
    case 3:
        return "Makoto";
    case 4:
        return "Akane";
    case 5:
        return "Mayu";
    case 6:
        return "Nagamori";
    case 7:
        return "Misaki";
    case 8:
        return "Shiori";
    case 9:
        return "Sayuri";
    case 10:
        return "NayukiS";
    case 11:
        return "Mio";
    case 12:
        return "Doppel";
    case 13:
        return "Kaori";
    case 14:
        return "Ikumi";
    case 15:
        return "Mishio";
    case 16:
        return "Akiko";
    case 17:
        return "NayukiA";
    case 18:
        return "Unknown";
    case 19:
        return "Kanna";
    case 20:
        return "Kano";
    case 21:
        return "Minagi";
    case 22:
        return "AltNayukiS";
    case 23:
        return "Misuzu";
    case 24:
        return "BossUnknown";
    default:
        return "error";
    }
}

// FUNCTION: 0x1006ca30
std::wstring Game::characterNameW(int character)
{
    std::string name = characterName(character);
    return std::wstring(name.begin(), name.end());
}

// FUNCTION: 0x1006c9e0
int Game::character(int player)
{
    int id = sceneId();
    if (id == 2 || id == 3)
        return (*currentScene()->players[player])->character;
    if (id == 1)
        return ((CScene1 *)currentScene())->character[player];
    return -1;
}

// FUNCTION: 0x1006c980
void Game::setNetplay(bool netplay)
{
    if (scene(2)) {
        if (netplay) {
            game_->unk1364 = 5;
            game_->unk1365 = 1;
            game_->replayMode = 2;
            return;
        }
        game_->unk1364 = 4;
        game_->unk1365 = 4;
        game_->replayMode = 0;
    }
}

// FUNCTION: 0x1006c960
void Game::setReplayMode(char mode)
{
    game_->replayMode = mode;
}

// FUNCTION: 0x1006c940
CScene *Game::scene(int index)
{
    return EFZ_SCENES[index];
}

// FUNCTION: 0x1006c930
CScene *Game::currentScene()
{
    return scene(sceneId());
}

// FUNCTION: 0x1006c8d0
void Game::addText(std::wstring text, int x, int y, DWORD color)
{
    render_->addTextRender(text, x, y, color);
}

// FUNCTION: 0x1006c8c0
void Game::clearText()
{
    render_->clearTextRender();
}

// FUNCTION: 0x1006c890
void Game::setSpectating()
{
    CGame *game = game_;
    game->unk1366 = 1;
    game->unk1368 = 0;
    game->unk136c = 1;
    game->unk1370 = 2;
    game->unk134f = 2;
}

// FUNCTION: 0x1006c880
void Game::setTextRender(bool enable)
{
    render_->setRenderText(enable);
}

// FUNCTION: 0x1006c860
char Game::menuChoice()
{
    CScene0 *title = (CScene0 *)scene(0);
    if (title)
        return title->menuChoice;
    return 0;
}

// FUNCTION: 0x1006c850
int Game::humanPlayer()
{
    return game_->unk1343;
}

// FUNCTION: 0x1006c800
int Game::paletteNumber(int player)
{
    switch (sceneId()) {
    case 1:
    case 2:
        return ((CScene1 *)scene(1))->palette[player];
    case 3:
        return (*currentScene()->players[player])->palette;
    }
    return 0;
}

// FUNCTION: 0x1006c7d0
bool Game::hasPalette(int player)
{
    int id = sceneId();
    if (id >= 1 && id <= 3)
        return *(bool *)&scene(1)->game->hasPalette[player];
    return false;
}

// FUNCTION: 0x1006c790
bool Game::canChoosePalette(int player)
{
    CScene1 *select = (CScene1 *)currentScene();
    switch (sceneId()) {
    case 1:
        return select->unk49e[player] == 6;
    case 2:
    case 3:
        return true;
    }
    return false;
}

// FUNCTION: 0x1006c730
void Game::setPalette(int player, const ColorPalette &palette)
{
    if (sceneId() == 3) {
        CGame *game = (*currentScene()->players[player])->game;
        memcpy(&game->palette[95 + player * 40], palette.data + 4, 0xa0);
        EFZ_BUILD_BLEND_TABLES(EFZ_GRAPHICS, game->palette);
    }
}

// FUNCTION: 0x1006c6d0
POINT Game::getCamera()
{
    CPlayer *p1 = player(0);
    CScene3 *fight = (CScene3 *)currentScene();
    short shake = isHit(p1) * (p1->unk14a * 2 % 2);
    POINT camera;
    camera.x = shake + fight->camera.x;
    camera.y = fight->camera.y;
    return camera;
}

// FUNCTION: 0x1006c6a0
void Game::showBoxes(int player, int kind)
{
    boxes_.push_back(BoxRequest(player, kind));
}

// One player's boxes of one kind, then those of its objects. Each box goes through the
// fight's own transform (CScene3::Unk7677a0), doubled for the 640x480 overlay; the
// height is recomputed from the player's position. Hitboxes are stippled once the
// attack has hit (CPlayer+0x16c clear) unless the frame may hit again (flag 0x40); a
// collision box also gets a vertical line through the player's x, twice its height,
// centred on its top edge: the crossup midline.
// FUNCTION: 0x1006c1d0
// TODO: differs: register allocation of boxes/color/count and of the camera across
// the box loop; the original also keeps a store of (int)p->x into r->left that this
// build drops as dead. The calls, constants and control flow are the same.
void Game::drawBoxRequest(BoxRequest *request)
{
    if (sceneId() != 3)
        return;
    CPlayer *p = player(request->player);
    if (p == 0)
        return;
    CollisionInfo info;
    RECT result;
    RECT objectResult;
    RECT *boxes = 0;
    int count = 0;
    DWORD color = 0;
    getCollisionInfo(request->player, &info);
    bool vulnerable = (info.frame.flagsB0 & 0x20) == 0 && p->unk13c == 0;
    bool solid = (p->unk16c != 0) | (info.frame.flagsAA >> 6 & 1);
    unsigned int flags = 0xffffffff;
    switch (request->kind) {
    case BOX_HIT:
        if (!solid)
            flags = 0xf0f0f0f0;
        boxes = info.frame.hitBoxes;
        color = 0xffff0000;
        count = 4;
        break;
    case BOX_HURT:
        if (vulnerable) {
            boxes = info.frame.hurtBoxes;
            color = 0xff0000ff;
            count = 5;
        }
        break;
    case BOX_COLLISION:
        boxes = &info.frame.collisionBox;
        color = 0xffffff00;
        count = 1;
        break;
    }
    POINT camera = getCamera();
    for (int i = 0; i < count; i++) {
        RECT box = boxes[i];
        RECT *r = EFZ_INFO_BOX(&result, &info, &box);
        int width = box.right - box.left;
        int height = box.bottom - box.top;
        r->left = (r->left + camera.x) * 2;
        r->right = r->left + width * 2;
        r->top = (int)((camera.y + box.top + info.y + 210.0 - (info.y < 0.0) - info.sprite.rect.y)
                       * 2.0);
        r->bottom = r->top + height * 2;
        if (width != 0 && height != 0) {
            render_->addRectRender(*r, color, flags);
            if (request->kind == BOX_COLLISION) {
                box.top = (int)(box.top - height / 2.0);
                r->left = (int)p->x;
                r->left = (r->left + camera.x) * 2;
                r->right = r->left;
                r->top = (int)((camera.y + box.top + info.y + 210.0 - (info.y < 0.0)
                                - info.sprite.rect.y) * 2.0);
                r->bottom = r->top + height * 2 * 2;
                render_->addRectRender(*r, color, flags);
            }
        }
    }
    short end = p->objectEnd;
    for (int i = p->objectStart; i != end; i = (i + 1) % 64) {
        PlayerObject *object = &p->objects[i];
        if (p->objectActive[i] == 0)
            continue;
        getPatternFrame(request->player, object->pattern, object->frame, &info.frame);
        bool vulnerable = (info.frame.flagsB0 & 0x20) == 0;
        bool active = object->unk84 != 0 && vulnerable;
        unsigned int objectFlags = 0xffffffff;
        switch (request->kind) {
        case BOX_HIT:
            boxes = info.frame.hitBoxes;
            color = 0xffff0000;
            count = 4;
            if (!active || object->unk80 != 0)
                objectFlags = 0xf0f0f0f0;
            break;
        case BOX_HURT:
            if (vulnerable) {
                boxes = info.frame.hurtBoxes;
                color = 0xff0000ff;
                count = 5;
            } else {
                boxes = &info.frame.collisionBox;
                color = 0xff0000ff;
                count = 1;
            }
            break;
        case BOX_COLLISION:
            if (!vulnerable) {
                boxes = &info.frame.collisionBox;
                color = 0xff0000ff;
                count = 1;
            }
            break;
        default:
            count = 0;
            break;
        }
        for (int j = 0; j < count; j++) {
            RECT box = boxes[j];
            RECT *r = EFZ_OBJECT_BOX(&objectResult, object, &box);
            int width = box.right - box.left;
            int height = box.bottom - box.top;
            if (width != 0 && height != 0) {
                r->left = (r->left + camera.x) * 2;
                r->right = r->left + width * 2;
                r->top = (r->top + camera.y) * 2 + 420;
                r->bottom = r->top + height * 2;
                render_->addRectRender(*r, color, objectFlags);
            }
        }
    }
}

// Mishio's 0x199 objects: their boxes are kept in rects, one per object and box.
// FUNCTION: 0x1006bf20
// TODO: differs: the original keeps p in esi across getCollisionInfo (and the object's
// pattern in esi across character()); this build reloads p from its stack slot, and
// the register allocation of the whole loop diverges from there.
void Game::collectRects(BoxRequest *request, std::vector<HitRect> &rects)
{
    if (sceneId() != 3)
        return;
    CPlayer *p = player(request->player);
    if (p == 0)
        return;
    CollisionInfo info;
    RECT result;
    RECT *boxes = 0;
    int count = 0;
    DWORD color = 0;
    getCollisionInfo(request->player, &info);
    short end = p->objectEnd;
    for (int i = p->objectStart; i != end; i = (i + 1) % 64) {
        PlayerObject *object = &p->objects[i];
        if (p->objectActive[i] == 0)
            continue;
        short pattern = object->pattern;
        if (character(request->player) != 15 || pattern != 0x199)
            continue;
        getPatternFrame(request->player, 0x199, object->frame, &info.frame);
        bool vulnerable = !((info.frame.flagsB0 & 0x20) > 0);
        switch (request->kind) {
        case BOX_HIT:
            boxes = info.frame.hitBoxes;
            color = 0xffff0000;
            count = 4;
            break;
        case BOX_HURT:
            if (vulnerable) {
                boxes = info.frame.hurtBoxes;
                color = 0xff0000ff;
                count = 5;
            } else {
                boxes = &info.frame.collisionBox;
                color = 0xff0000ff;
                count = 1;
            }
            break;
        case BOX_COLLISION:
            if (!vulnerable) {
                boxes = &info.frame.collisionBox;
                color = 0xff0000ff;
                count = 1;
            }
            break;
        default:
            count = 0;
            break;
        }
        for (int j = 0; j < count; j++) {
            RECT box = boxes[j];
            RECT *r = EFZ_OBJECT_BOX(&result, object, &box);
            int width = box.right - box.left;
            int height = box.bottom - box.top;
            if (width == 0 || height == 0)
                continue;
            r->left = r->left * 2;
            r->right = r->left + width * 2;
            r->top = r->top * 2;
            r->bottom = r->top + height * 2;
            bool found = false;
            std::vector<HitRect>::iterator it = rects.begin();
            std::vector<HitRect>::iterator last = rects.end();
            for (; it != last; ++it) {
                if (it->object == i && it->box == j) {
                    it->rect = *r;
                    found = true;
                    break;
                }
            }
            if (!found)
                rects.push_back(HitRect(*r, color, 0xffffffff, i, j));
        }
    }
}

// FUNCTION: 0x1006be90
void Game::updateRects()
{
    if (sceneId() == 3) {
        std::list<BoxRequest>::iterator it = boxes_.begin();
        std::list<BoxRequest>::iterator end = boxes_.end();
        for (; it != end; ++it) {
            BoxRequest request = *it;
            collectRects(&request, rects_);
        }
    }
}

// FUNCTION: 0x1006be80
void Game::clearRects()
{
    rects_.clear();
}

// From collectRects' coordinates to the overlay's.
// FUNCTION: 0x1006be20
void Game::toScreen(RECT *rect)
{
    if (sceneId() == 3) {
        CScene3 *fight = (CScene3 *)currentScene();
        int width = rect->right - rect->left;
        int height = rect->bottom - rect->top;
        rect->left = rect->left + fight->camera.x * 2;
        rect->right = rect->left + width;
        rect->top = rect->top + (fight->camera.y + 210) * 2;
        rect->bottom = rect->top + height;
    }
}

// FUNCTION: 0x1006bdf0
CPlayer *Game::player(int index)
{
    if (sceneId() != 3)
        return 0;
    return *currentScene()->players[index];
}

// FUNCTION: 0x1006bdd0
void Game::clearBoxes()
{
    render_->clearBoxRender();
    boxes_.clear();
}

// FUNCTION: 0x1006bd70
bool Game::isHit(CPlayer *p)
{
    if (sceneId() != 3)
        return false;
    short action = p->pattern;
    short opponent = *p->unk78[2];
    return action >= 50 && action < 150 && opponent != 0x60 && opponent != 0x61
        && opponent != 0x62 && opponent != 0x63;
}

// FUNCTION: 0x1006bd20
void Game::getPatternFrame(int index, short pattern, short frame, PatternFrame *out)
{
    if (sceneId() == 3 && out != 0) {
        PatternFrame *frames = player(index)->patterns[pattern].frames;
        *out = frames[frame];
    }
}

// FUNCTION: 0x1006bc70
// TODO: differs: the original tests info in memory, keeps p in index's stack slot and
// reloads info after the PatternFrame copy; this build holds info in a register from
// the start, so the registers and the order of the loads differ.
void Game::getCollisionInfo(int index, CollisionInfo *info)
{
    if (sceneId() == 3 && info != 0) {
        CPlayer *p = player(index);
        short frame = p->frame;
        short pattern = p->pattern;
        PatternFrame *frames = p->patterns[pattern].frames;
        SpriteFrame *sprites = p->anims[pattern].frames;
        info->frame = frames[frame];
        info->sprite.rect = sprites[frame].rect;
        info->x = p->x;
        info->y = p->y;
        info->facing = p->facing;
    }
}

// 0 stops the fight: the calls that advance it are replaced by nops.
// FUNCTION: 0x1006bb00
void Game::setGameSpeed(char speed)
{
    patches_.restore((void *)0x76425f);
    patches_.restore((void *)0x75e183);
    patches_.restore((void *)0x75dfb5);
    patches_.restore((void *)0x75dfd0);
    patches_.restore((void *)0x75e055);
    patches_.restore((void *)0x75e0da);
    patches_.restore((void *)0x76420a);
    patches_.restore((void *)0x764aeb);
    patches_.restore((void *)0x765e59);
    patches_.restore((void *)0x765e7a);
    if (speed == 0) {
        char nops[5];
        memset(nops, 0x90, sizeof(nops));
        patches_.patch((void *)0x76425f, 5, nops);
        patches_.patch((void *)0x75e183, 3, nops);
        patches_.patch((void *)0x75dfb5, 3, nops);
        patches_.patch((void *)0x75dfd0, 3, nops);
        patches_.patch((void *)0x75e055, 3, nops);
        patches_.patch((void *)0x75e0da, 3, nops);
        patches_.patch((void *)0x76420a, 5, nops);
        patches_.patch((void *)0x764aeb, 3, nops);
        patches_.patch((void *)0x765e59, 5, nops);
        patches_.patch((void *)0x765e7a, 5, nops);
    }
    CScene3 *fight = (CScene3 *)scene(3);
    if (fight)
        fight->speed = speed;
}

// FUNCTION: 0x1006baf0
void Game::setReplayName(const std::wstring &name)
{
    replay_.name = name;
}

// FUNCTION: 0x1006bae0
void Game::setWriteReplay(bool write)
{
    writeReplay_ = write;
}

// Into the replay's own file, the file to save the match under, or memory until
// flushReplay decides.
// FUNCTION: 0x1006b9e0
std::iostream *Game::openReplayWrite(const char *name)
{
    if (pendingReplay_ != 0) {
        g_log << "Delete old replay backup\n";
        closeStream(pendingReplay_);
    }
    g_log << "Create replay write\n";
    g_log.flush();
    inputs_.clear();
    std::iostream *file;
    if (replay_.name.empty())
        file = new std::fstream(name, std::ios::out | std::ios::binary);
    else if (saveReplays_)
        file = new std::fstream(replay_.name, std::ios::out | std::ios::binary);
    else
        file = new std::stringstream();
    recording_ = true;
    return file;
}

// FUNCTION: 0x1006b8e0
std::iostream *Game::openReplayRead(const char *name)
{
    if (pendingReplay_ != 0) {
        g_log << "Delete old replay backup\n";
        closeStream(pendingReplay_);
    }
    std::fstream test;
    test.open(name, std::ios::in | std::ios::binary);
    if (!test.is_open()) {
        g_log << "Read replay does not exist, create\n";
        g_log.flush();
        test.close();
        test.open(name, std::ios::out | std::ios::binary);
    }
    g_log << "Create replay read\n";
    g_log.flush();
    std::iostream *file = new std::fstream(name, std::ios::in | std::ios::out | std::ios::binary);
    recording_ = false;
    return file;
}

// FUNCTION: 0x1006b8b0
int Game::writeInput(std::iostream *file, short input)
{
    if (writeReplay_)
        file->write((char *)&input, 2);
    return 1;
}

// A recording that isn't saved at once is kept for flushReplay.
// FUNCTION: 0x1006b870
void Game::closeReplay(std::iostream *&file)
{
    if (file) {
        if (recording_) {
            if (!saveReplays_) {
                pendingReplay_ = file;
                return;
            }
            writeExtendedReplay(file);
        }
        closeStream(file);
    }
}

// FUNCTION: 0x1006b820
void Game::refreshPalette(int player)
{
    if (sceneId() == 3) {
        int start = player * 40 + 95;
        EFZ_DDPALETTE->SetEntries(0, start, 40,
                                  &(*currentScene()->players[player])->game->palette[start]);
    }
}

// FUNCTION: 0x1006b7f0
int Game::playerAction(int index)
{
    if (sceneId() != 3)
        return 0;
    return player(index)->pattern;
}

// FUNCTION: 0x1006b7c0
short Game::actionFrame(int index)
{
    if (sceneId() != 3)
        return 0;
    return player(index)->unkc;
}

// FUNCTION: 0x1006b7a0
CReplayFile *Game::replayFile()
{
    if (sceneId() == 3)
        return &game_->replay;
    return 0;
}

// FUNCTION: 0x1006b760
short Game::readInput(std::iostream *file)
{
    short input = 0;
    if (readReplay_)
        file->read((char *)&input, 2);
    return input;
}

// FUNCTION: 0x1006b750
void Game::setReadReplay(bool read)
{
    readReplay_ = read;
}

// FUNCTION: 0x1006b650
void Game::writeExtendedReplay(std::iostream *file)
{
    if (file != 0 && recording_) {
        int end[4] = { 9999 << 16, 0, 0, 0 };
        for (int i = 0; i < 30; i++)
            file->write((char *)end, sizeof(end));
        int offset = (int)file->tellp();
        int marker = -1;
        file->write((char *)&rngSeed_, 4);
        int size = inputs_.size();
        file->write((char *)&size, 4);
        file->write((char *)inputs_.data(), inputs_.size() * 2);
        file->write((char *)&offset, 4);
        file->write((char *)&marker, 4);
    }
}

// FUNCTION: 0x1006b610
void Game::closeStream(std::iostream *&stream)
{
    if (stream) {
        delete stream;
        stream = 0;
        g_log << "delete replay\n";
    }
}

// Writes out the recording kept back by closeReplay.
// FUNCTION: 0x1006b520
bool Game::flushReplay()
{
    if (pendingReplay_ != 0 && !saveReplays_) {
        g_log << "Replay flushed " << "\n";
        writeExtendedReplay(pendingReplay_);
        std::fstream file;
        file.open(replay_.name, std::ios::out | std::ios::binary);
        file << pendingReplay_->rdbuf();
        file.close();
        closeStream(pendingReplay_);
        return true;
    }
    g_log << "Cannot flush, empty replay\n";
    return false;
}

// FUNCTION: 0x1006b4f0
void Game::recordInputs(FrameInput p1, FrameInput p2)
{
    inputs_.push_back(p1);
    inputs_.push_back(p2);
}

// FUNCTION: 0x1006b4e0
void Game::setRandomSeed(int seed)
{
    rngSeed_ = seed;
}

// Reads the random state and both players' inputs that an extended replay keeps after
// the game's own data.
// FUNCTION: 0x1006b2f0
// TODO: differs: the original keeps `this` in edi and the file in esi (here the other
// way round), and pushes one g_log literal that this build propagates into a clone of
// the operator<< instantiation; the calls and control flow are the same.
void Game::readExtendedReplay(std::vector<FrameInput> &inputs)
{
    inputs.clear();
    std::iostream *file = (std::iostream *)replayFile()->handle;
    std::streampos start = file->tellg();
    if (!isExtendedReplay(file)) {
        g_log << "Not Modded\n";
        return;
    }
    g_log << "Modded\n";
    g_log.flush();
    int offset = readExtendedOffset(file);
    file->seekg((unsigned int)offset);
    g_log << "Start offset " << offset << "\n";
    g_log.flush();
    file->read((char *)&rngSeed_, 4);
    g_log << "Rng " << rngSeed_ << "\n";
    g_log.flush();
    if (rngSeed_ == 0) {
        file->seekg(start);
        g_log << "Rng empty, recorded with old bugged version, disabling revival replay features.\n";
        g_log.flush();
        return;
    }
    loadRandomState(rngSeed_);
    int size = 0;
    file->read((char *)&size, 4);
    g_log << "Size " << size << "\n";
    g_log.flush();
    size_t bytes = size * 2;
    FrameInput *buffer = (FrameInput *)malloc(bytes);
    file->read((char *)buffer, bytes);
    inputs.assign(buffer, buffer + size);
    file->seekg(start);
}

// FUNCTION: 0x1006b240
bool Game::isExtendedReplay(std::iostream *file)
{
    std::streampos position = file->tellg();
    int marker = 0;
    file->seekg(-4, std::ios::end);
    file->read((char *)&marker, 4);
    if (marker == -1) {
        file->seekg(position);
        return true;
    }
    file->seekg(position);
    return false;
}

// The extended replay's trailer: its offset, then -1, end the file.
// FUNCTION: 0x1006b1c0
int Game::readExtendedOffset(std::iostream *file)
{
    int offset = 0;
    std::streampos position = file->tellg();
    file->seekg(-8, std::ios::end);
    file->read((char *)&offset, 4);
    file->seekg(position);
    return offset;
}

// FUNCTION: 0x1006b190
char Game::replayMode()
{
    if (sceneId() != 2 && sceneId() != 3)
        return -1;
    return game_->replayMode;
}

// FUNCTION: 0x1006b180
CGame *Game::getGame()
{
    return game_;
}

// FUNCTION: 0x1006b160
bool Game::isMatchOver()
{
    if (sceneId() != 3)
        return false;
    return currentScene()->unk2d == 2;
}

// FUNCTION: 0x1006b0d0
bool Game::isTeching(int index)
{
    if (sceneId() != 3)
        return false;
    CPlayer *p = player(index);
    double y = p->y;
    int action = playerAction(index);
    float unk134 = p->unk134;
    return action >= 50 && action < 150 && unk134 <= 0.0 && p->unk124 == 0 && y < 0.0
        && p->unk128 == 0;
}

// FUNCTION: 0x1006b0c0
KeyBindings *Game::bindings()
{
    return input_->bindings;
}

// FUNCTION: 0x1006b0a0
IDirectInputDevice7 *Game::device(char index)
{
    return input_->devices[index];
}

// FUNCTION: 0x1006b080
int Game::roundWinner()
{
    return g_game.getGame()->unk134c;
}

// Left and right together count as left.
// FUNCTION: 0x1006b060
char Game::cleanInput(char input)
{
    if ((input & 2) && (input & 1))
        return input & ~1;
    return input;
}

// FUNCTION: 0x1006b050
void Game::setSaveReplays(bool save)
{
    saveReplays_ = save;
}

// FUNCTION: 0x1006b040
void Game::setGameFlag1366(bool value)
{
    game_->unk1366 = value;
}

// FUNCTION: 0x1006b020
int Game::playerFlagAc(int index)
{
    return player(index)->unkac;
}

// FUNCTION: 0x1006aff0
bool Game::isRoundOver()
{
    if (sceneId() == 3)
        return currentScene()->unk2d == 1 || currentScene()->unk2d == 2;
    return false;
}

// FUNCTION: 0x1006afe0
WORD Game::musicId()
{
    return game_->music;
}

// Reads the devices a player's bindings use, logging each result; false if one fails.
// FUNCTION: 0x1006adf0
bool Game::pollDevices(int player)
{
    char *keys = (char *)&input_->bindings[player];
    int last = 0;
    for (int i = 1; i < 16; i += 2) {
        int device = keys[i];
        if (last <= device)
            last = device;
    }
    if (last > 2)
        return true;
    g_log << "Player " << player + 1 << "\n";
    bool ok = true;
    for (int i = 0; i <= last; i++) {
        IDirectInputDevice7 *device = input_->devices[i];
        HRESULT result;
        if (i == 0) {
            char keys[0x100];
            result = device->GetDeviceState(sizeof(keys), keys);
            ok &= result == DI_OK;
        } else {
            DIJOYSTATE state;
            result = device->GetDeviceState(sizeof(state), &state);
        }
        std::wstring message = _com_error(result).ErrorMessage();
        g_log << "Result device " << i << " " << std::string(message.begin(), message.end())
              << "\n";
        ok &= result == DI_OK;
    }
    if (!ok)
        return false;
    return true;
}

// Whether a joystick was plugged in since the last call.
// FUNCTION: 0x1006ada0
bool Game::joystickAdded()
{
    IDirectInput7 *di = input_->di;
    if (di) {
        int count = 0;
        di->EnumDevices(DIDEVTYPE_JOYSTICK, (LPDIENUMDEVICESCALLBACK)countDevice, &count,
                        DIEDFL_ATTACHEDONLY);
        bool added = count > joystickCount_;
        joystickCount_ = count;
        return added;
    }
    return false;
}

// Releases the joysticks and lets the game enumerate them again.
// FUNCTION: 0x1006ad20
void Game::reacquireJoysticks()
{
    char &count = EFZ_JOYSTICK_COUNT;
    for (int i = 0; i < count; i++) {
        IDirectInputDevice7 *&slot = input_->devices[i + 1];
        if (IDirectInputDevice7 *joystick = slot) {
            joystick->Unacquire();
            joystick->Release();
        }
        slot = 0;
    }
    count = 0;
    IDirectInput7 *di = input_->di;
    if (di)
        di->EnumDevices(DIDEVTYPE_JOYSTICK, EFZ_ENUM_JOYSTICKS, di, DIEDFL_ATTACHEDONLY);
}

// FUNCTION: 0x1006ad10
void Game::reloadKeys()
{
    EFZ_LOAD_BINDINGS(input_);
}

// FUNCTION: 0x1006ace0
bool Game::isWakingUp(int player)
{
    if (playerAction(player) == 99 && actionFrame(player) >= 3)
        return true;
    return false;
}

// FUNCTION: 0x1006acb0
bool Game::isGuarding(int player)
{
    int action = playerAction(player);
    if (action != 0x97 && action != 0x99 && action != 0x9c)
        return false;
    return true;
}

// FUNCTION: 0x1006ac80
bool Game::isRecoilGuarding(int player)
{
    int action = playerAction(player);
    if (action != 0xa8 && action != 0xa9 && action != 0xaa)
        return false;
    return true;
}

// Whether key.ini was written since the last call: CInput::LoadBindings then rereads it.
// FUNCTION: 0x1006abe0
bool Game::keyIniChanged()
{
    HANDLE file = CreateFileA("key.ini", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (file != INVALID_HANDLE_VALUE) {
        if (keyIniTime_.dwHighDateTime == 0 && keyIniTime_.dwLowDateTime == 0)
            GetFileTime(file, 0, 0, &keyIniTime_);
        FILETIME time;
        GetFileTime(file, 0, 0, &time);
        CloseHandle(file);
        if (CompareFileTime(&keyIniTime_, &time) == -1) {
            keyIniTime_ = time;
            return true;
        }
    }
    return false;
}

// FUNCTION: 0x1006abd0
HWND Game::window()
{
    return input_->hwnd;
}
