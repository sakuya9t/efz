// Fifth object of efz.exe (0x406070-0x4081ff): CGame, the state shared by the scenes.
// The inline methods it uses first follow it (0x408200-0x4083af): EffectAnim's, CFile's
// constructor and destructor, and these compiler-generated helpers:
// FUNCTION: 0x408200 ??_EEffectAnim@@QAEPAXI@Z
//   EffectAnim's vector deleting destructor, for `delete[] m_effectAnims`
// FUNCTION: 0x4082a0 ??_I@YGXPAXIHP6EX0@Z@Z
//   `vector destructor iterator'
// FUNCTION: 0x408380 ??_H@YGXPAXIHP6EPAX0@Z@Z
//   `vector constructor iterator', for `new EffectAnim[count]`
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

#define PI 3.141592

CGame::CGame(CGraphics* graphics, CInput* input, CSound* sound)
{
    int i;

    m_graphics = graphics;
    m_input = input;
    m_sound = sound;
    m_stage = 0;
    m_effectTail = 0;
    m_effectHead = 0;
    for (i = 0; i < 0x41; i++)
        m_sounds[i] = 0x96;
    m_music = 0x96;
    m_objectSurface = NULL;
    m_stageSurface = NULL;
    m_stageNegative = NULL;
    for (i = 0; i < 0x398; i++)
        m_surfaces[i] = NULL;
    m_background = NULL;
    m_effectAnims = NULL;
    m_hasConfig = ReadConfigByte(0x21) > 0;
    if (m_hasConfig) {
        m_cpuLevel = ReadConfigByte(0x21);
        m_drawEveryFrame = ReadConfigByte(0x22) - 1;
        m_fullEffects = ReadConfigByte(0x23) - 1;
        m_damageLevel = ReadConfigByte(0x24);
        m_roundsSetting = ReadConfigByte(0x26);
        unk1345 = 0;
    } else {
        m_cpuLevel = 2;
        m_drawEveryFrame = 1;
        m_fullEffects = 1;
        m_damageLevel = 2;
        m_roundsSetting = 2;
        unk1345 = 0;
    }
    CheckExtraChars();
    Reset();
}

CGame::~CGame()
{
    int i;

    for (i = 0; i < 0x398; i++) {
        if (m_surfaces[i]) {
            m_surfaces[i]->Release();
            m_surfaces[i] = NULL;
        }
    }
    if (m_stageSurface) {
        m_stageSurface->Release();
        m_stageSurface = NULL;
    }
    if (m_stageNegative) {
        m_stageNegative->Release();
        m_stageNegative = NULL;
    }
    if (m_objectSurface) {
        m_objectSurface->Release();
        m_objectSurface = NULL;
    }
    for (i = 0; i < 0x41; i++) {
        if (m_sounds[i] != 0x96)
            m_sound->Release(m_sounds[i]);
    }
    if (m_music != 0x96)
        m_sound->Release(m_music);
    if (m_effectAnims)
        delete[] m_effectAnims;
    if (m_background) {
        delete m_background;
        m_background = NULL;
    }
}

void CGame::Reset()
{
    m_effectTail = 0;
    m_effectHead = 0;
    ClearEffects();
    m_shake = 0.0;
    m_shakeHold = 0;
    m_shakeX = 0;
    m_shakeY = 0;
    m_shakeAngleX = 0.0;
    m_shakeAngleY = 0.0;
    m_speedRequested = 0;
    m_dummyStance = 0;
    m_dummyGuard = 0;
    m_fade = 0.0;
    m_fadeHold = 0;
    m_fadeIn = 0;
    m_fadeOut = 0;
    m_fadeDir = 0;
    m_negativeTime = 0;
    m_hideObjectsTime = 0;
    m_hideHudTime = 0;
    m_musicStep = 0;
    m_musicVolume = 0;
    m_round = 1;
    m_intro = 1;
    m_roundOver = 0;
}

void CGame::UpdateInput()
{
    int j;
    BYTE input[2];

    for (j = 0; j < 2; j++) {
        input[j] = m_input->GetInput(j);
        m_inputX[j] = 0;
        m_inputY[j] = 0;
        m_pressA[j] = 0;
        m_pressB[j] = 0;
        m_pressC[j] = 0;
        m_pressD[j] = 0;
        if ((input[j] & 8) > 0)
            m_inputY[j] = -1;
        else if ((input[j] & 4) > 0)
            m_inputY[j] = 1;
        if ((input[j] & 2) > 0)
            m_inputX[j] = -1;
        else if ((input[j] & 1) > 0)
            m_inputX[j] = 1;
        if ((input[j] & 0x10) > 0) {
            m_pressA[j] = m_holdA[j] == 0;
            m_holdA[j] = 1;
        } else {
            m_holdA[j] = 0;
        }
        if ((input[j] & 0x20) > 0) {
            m_pressB[j] = m_holdB[j] == 0;
            m_holdB[j] = 1;
        } else {
            m_holdB[j] = 0;
        }
        if ((input[j] & 0x40) > 0) {
            m_pressC[j] = m_holdC[j] == 0;
            m_holdC[j] = 1;
        } else {
            m_holdC[j] = 0;
        }
        if ((input[j] & 0x80) > 0) {
            m_pressD[j] = m_holdD[j] == 0;
            m_holdD[j] = 1;
        } else {
            m_holdD[j] = 0;
        }
    }
}

void CGame::LoadSounds()
{
    int j;
    char path[32];
    char num[8];

    for (j = 0; j < 0x41; j++) {
        strcpy(path, "wave\\se\\");
        if (j < 10)
            strcat(path, "0");
        _itoa(j, num, 10);
        strcat(path, num);
        strcat(path, ".wav");
        m_sounds[j] = m_sound->Load(path);
        m_sound->SetVolume(m_sounds[j], -500);
    }
}

void CGame::PlaySE(WORD index)
{
    if (m_sounds[index] != 0x96)
        m_sound->Play(m_sounds[index], FALSE);
}

void CGame::PlayMusic(WORD track)
{
    char path[32];
    char num[8];

    strcpy(path, "wave\\bgm\\bgm");
    if (track < 10)
        strcat(path, "0");
    _itoa(track, num, 10);
    strcat(path, num);
    strcat(path, ".wav");
    if (m_music != 0x96) {
        m_sound->Stop(m_music);
        m_sound->Release(m_music);
        m_music = 0x96;
    }
    m_music = m_sound->Load(path);
    m_sound->LoadLoop(path);
    if (m_music != 0x96)
        m_sound->Play(m_music, 1 - (track == 2 || track == 3 || track == 4 || track == 9));
}

void CGame::StopMusic()
{
    if (m_music != 0x96) {
        m_sound->Stop(m_music);
        m_sound->Release(m_music);
        m_music = 0x96;
    }
}

void CGame::FadeMusic(int volume, short step)
{
    m_musicTarget = volume;
    m_musicStep = step;
}

void CGame::LoadEffects()
{
    int m;
    int j;
    char str[100];
    BYTE* data;
    DWORD dwRead;
    int size;
    int offset;
    int len;
    HANDLE hFile;
    char name[32];
    char num[8];

    if (1) {
        offset = 0;
        hFile = CreateFile("system\\effect\\effect.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING,
                           FILE_ATTRIBUTE_NORMAL, NULL);
        size = GetFileSize(hFile, NULL);
        data = new BYTE[size];
        ReadFile(hFile, data, size, &dwRead, NULL);
        offset = data[0] * 3 + 1;
        for (j = 0; j <= 0x397; j++) {
            len = m_graphics->LoadSurface(&m_surfaces[j], data + offset, 0x51, 0xaf);
            if (len == 0) {
                _itoa(j, str, 10);
                MessageBox(NULL, str, NULL, MB_OK);
            } else {
                offset += len;
            }
        }
        CloseHandle(hFile);
        delete data;
        LoadDat(&m_objectSurface, "system\\object.dat", 0, 0xaf);
        m_graphics->LoadPaletteDat(m_palette, "system\\object.dat", 0, 0xaf, 0x50);
    } else {
        // The development name: one bitmap per sprite.
        for (m = 0; m <= 0x397; m++) {
            if (m >= 100)
                strcpy(name, "system\\effect\\efe");
            else if (m >= 10)
                strcpy(name, "system\\effect\\efe0");
            else
                strcpy(name, "system\\effect\\efe00");
            _itoa(m, num, 10);
            strcat(name, num);
            strcat(name, ".bmp");
            m_graphics->LoadBmp(&m_surfaces[m], name, 0xaf);
        }
        m_graphics->LoadBmp(&m_objectSurface, "system\\object.bmp", 0xaf);
        m_graphics->LoadPaletteBmp(m_palette, "system\\object.bmp", 0, 0xaf, 0x50);
    }
    m_colorKey = m_graphics->GetColorKey(m_objectSurface);
}

void CGame::LoadDat(PTR32(IDirectDrawSurface)* surface, const char* name, BYTE rle, BYTE offset)
{
    BYTE* data;
    DWORD dwRead;
    DWORD size;
    HANDLE hFile;

    hFile = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    size = GetFileSize(hFile, NULL);
    data = new BYTE[size];
    ReadFile(hFile, data, size, &dwRead, NULL);
    m_graphics->LoadSurface(surface, data + data[0] * 3 + 1, rle, offset);
    CloseHandle(hFile);
    delete data;
}

void CGame::LoadEffectAnims()
{
    int m;
    int j;
    int k;
    int frameCount;
    int size;
    CFile file("system\\effect\\effect.pat", 1);
    int animCount;
    int skip[4];

    animCount = file.ReadInt();
    m_effectAnims = new EffectAnim[animCount];
    for (k = 0; k < animCount; k++) {
        size = file.ReadInt();
        file.ReadInt();
        file.ReadInt();
        m_effectAnims[k].frameCount = file.ReadInt();
        frameCount = m_effectAnims[k].frameCount;
        m_effectAnims[k].Alloc(frameCount);
        for (j = 0; j < frameCount; j++) {
            m_effectAnims[k].frames[j].duration = file.ReadInt();
            m_effectAnims[k].frames[j].surface = file.ReadInt();
            m_effectAnims[k].frames[j].width = file.ReadInt();
            m_effectAnims[k].frames[j].height = file.ReadInt();
            m_effectAnims[k].frames[j].x = file.ReadInt();
            m_effectAnims[k].frames[j].y = file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            for (m = 0; m < 10; m++)
                file.Read(skip, 16);
        }
    }
}

void CGame::CreateEffect(EffectDesc* desc)
{
    m_effectActive[m_effectHead] = 1;
    m_effectKeep[m_effectHead] = desc->keep;
    m_effectUnk2784[m_effectHead] = 0;
    m_effects[m_effectHead].type = desc->type;
    m_effects[m_effectHead].frame = 0;
    m_effects[m_effectHead].timer = 0;
    m_effects[m_effectHead].x = desc->x;
    m_effects[m_effectHead].y = desc->y;
    m_effects[m_effectHead].facing = desc->facing;
    m_effects[m_effectHead].side = desc->side;
    m_effects[m_effectHead].scale = desc->scale;
    m_effects[m_effectHead].sound = desc->sound;
    m_effects[m_effectHead].screen = desc->screen;
    m_effects[m_effectHead].layer = desc->layer;
    AdvanceEffectHead();
}

void CGame::RemoveEffect(short index)
{
    m_effectActive[index] = 0;
    m_effectKeep[index] = 0;
    if (index == m_effectTail) {
        while (m_effectTail != m_effectHead && !m_effectActive[m_effectTail]) {
            m_effectKeep[m_effectTail] = 0;
            m_effectTail++;
            if (m_effectTail >= 0x280)
                m_effectTail = 0;
        }
    }
}

void CGame::AdvanceEffectHead()
{
    int n;

    n = 0;
    do {
        m_effectHead++;
        if (m_effectHead >= 0x280)
            m_effectHead = 0;
        if (m_effectHead == m_effectTail) {
            m_effectTail++;
            if (m_effectTail >= 0x280)
                m_effectTail = 0;
            while (m_effectTail != m_effectHead && !m_effectActive[m_effectTail]) {
                m_effectKeep[m_effectTail] = 0;
                m_effectTail++;
                if (m_effectTail >= 0x280)
                    m_effectTail = 0;
            }
        }
        n++;
    } while (m_effectKeep[m_effectHead] && n < 0x280);
}

void CGame::RemoveEffectsOfType(int type)
{
    int i;

    i = m_effectTail;
    do {
        if (m_effects[i].type == type && m_effectActive[i])
            RemoveEffect(i);
        i++;
        if (i >= 0x280)
            i = 0;
    } while (i != m_effectHead + 1 - (m_effectHead == 0x27f) * 0x280);
}

void CGame::ClearEffects()
{
    int i;

    for (i = 0; i < 0x280; i++) {
        m_effectActive[i] = 0;
        m_effectKeep[i] = 0;
    }
}

void CGame::UpdateEffects()
{
    int i;

    i = m_effectTail;
    while (i != m_effectHead) {
        if (m_effectActive[i])
            UpdateEffect(i);
        i++;
        if (i >= 0x280)
            i = 0;
    }
}

void CGame::DrawEffects(int x, int y, BYTE layer)
{
    RECT src;
    EffectFrame* frame;
    RECT dest;
    int i;

    i = m_effectTail;
    while (i != m_effectHead) {
        if (m_effectActive[i] && layer == m_effects[i].layer) {
            frame = &m_effectAnims[m_effects[i].type].frames[m_effects[i].frame];
            src = MakeRect(0, 0, frame->width, frame->height);
            if (m_effects[i].side) {
                dest.left = (int)m_effects[i].x + (m_effects[i].screen == 0) * x -
                           (frame->width - frame->x);
                dest.top = (m_effects[i].screen == 0) * 210 + (int)m_effects[i].y - frame->y +
                          (m_effects[i].screen == 0) * y;
                dest.right = frame->width + dest.left;
                dest.bottom = frame->height + dest.top;
            } else {
                dest.left = (int)m_effects[i].x + (m_effects[i].screen == 0) * x - frame->x;
                dest.top = (m_effects[i].screen == 0) * 210 + (int)m_effects[i].y - frame->y +
                          (m_effects[i].screen == 0) * y;
                dest.right = frame->width + dest.left;
                dest.bottom = frame->height + dest.top;
            }
            if (m_effects[i].scale > 0)
                m_graphics->BlitEx(dest, m_surfaces[frame->surface], src, m_colorKey,
                                   m_effects[i].side, m_effects[i].scale - 1);
            else
                m_graphics->Blit(dest, m_surfaces[frame->surface], src, m_colorKey,
                                 m_effects[i].side);
        }
        i++;
        if (i >= 0x280)
            i = 0;
    }
}

void CGame::UpdateTimers()
{
    if (m_hideObjectsTime > 0)
        m_hideObjectsTime--;
    if (m_hideObjectsTime < 0)
        m_hideObjectsTime = 0;
    if (m_hideHudTime > 0)
        m_hideHudTime--;
    if (m_hideHudTime < 0)
        m_hideHudTime = 0;
    if (m_musicStep > 0) {
        if (m_musicTarget > m_musicVolume) {
            m_musicVolume += m_musicStep;
            if (m_musicTarget <= m_musicVolume) {
                m_musicVolume = m_musicTarget;
                m_musicStep = 0;
            }
        } else {
            m_musicVolume -= m_musicStep;
            if (m_musicTarget >= m_musicVolume) {
                m_musicVolume = m_musicTarget;
                m_musicStep = 0;
            }
        }
        m_sound->SetVolume(m_music, m_musicVolume);
    }
}

void CGame::UpdateShake()
{
    if (m_shake >= 1.0) {
        m_shakeX = (int)(cos(m_shakeAngleX * PI / 180.0) * m_shake);
        m_shakeY = (int)(sin(m_shakeAngleY * PI / 180.0) * m_shake);
        m_shakeAngleX += 83.0;
        if (m_shakeAngleX >= 360.0)
            m_shakeAngleX -= 360.0;
        m_shakeAngleY += 107.0;
        if (m_shakeAngleY >= 360.0)
            m_shakeAngleY -= 360.0;
        if (m_shakeHold > 0)
            m_shakeHold--;
        else
            m_shake *= 0.95;
        if (m_shake < 1.0) {
            m_shake = 0.0;
            m_shakeX = 0;
            m_shakeY = 0;
        }
    }
}

void CGame::SetGameSpeed(BYTE value)
{
    m_speedRequested = 1;
    m_requestedSpeed = value;
}

void CGame::UpdateFade()
{
    if (m_fadeDir == 1) {
        if (m_fadeIn > 0) {
            m_fade = (100.0 - m_fade) / m_fadeIn + m_fade;
            if (m_fade > 100.0)
                m_fade = 100.0;
            if (m_fade > 0.0)
                m_graphics->Brighten(m_palette, 1, 0xff, 100 - (int)m_fade);
            m_fadeIn--;
        } else if (m_fadeHold > 0) {
            m_fadeHold--;
        } else if (m_fade > 0.0) {
            m_fade = m_fade - 100.0 / m_fadeOut;
            if (m_fade <= 0.0)
                m_fade = 0.0;
            m_graphics->Brighten(m_palette, 1, 0xff, 100 - (int)m_fade);
        } else {
            m_fadeDir = 0;
        }
    } else if (m_fadeDir == -1) {
        if (m_fadeIn > 0) {
            m_fade = m_fade - (m_fade + 100.0) / m_fadeIn;
            if (m_fade < -100.0)
                m_fade = -100.0;
            if (m_fade < 0.0)
                m_graphics->Darken(m_palette, 1, 0xff, (int)m_fade + 100);
            m_fadeIn--;
        } else if (m_fadeHold > 0) {
            m_fadeHold--;
        } else if (m_fade < 0.0) {
            m_fade = 100.0 / m_fadeOut + m_fade;
            if (m_fade >= 0.0)
                m_fade = 0.0;
            m_graphics->Darken(m_palette, 1, 0xff, (int)m_fade + 100);
        } else {
            m_fadeDir = 0;
        }
    }
}

void CGame::FlashWhite(int in, int hold, int out)
{
    m_fadeDir = 1;
    m_fadeIn = in;
    m_fadeHold = hold;
    m_fadeOut = out;
}

void CGame::FlashBlack(int in, int hold, int out)
{
    m_fadeDir = -1;
    m_fadeIn = in;
    m_fadeHold = hold;
    m_fadeOut = out;
}

void CGame::FlashNegative(int value)
{
    m_negativeTime = value;
    if (m_drawEveryFrame == 0)
        m_negativeTime = m_negativeTime / 2;
}

void CGame::CheckExtraChars()
{
    HANDLE hFile = NULL;
    const char* chars[3] = {"misuzu\\misuzu.dat", "minagi\\minagi.dat", "kano\\kano.dat"};
    const char* second[3] = {"exnanase\\exnanase.dat", "ikumi\\ikumi.dat", "kaori\\kaori.dat"};
    int m;
    int j;

    m_extraChars = 1;
    for (j = 0; j < 3; j++) {
        hFile = CreateFile(chars[j], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
                           NULL);
        if (hFile == INVALID_HANDLE_VALUE)
            m_extraChars = 0;
        CloseHandle(hFile);
    }
    for (m = 0; m < 3; m++) {
        hFile = CreateFile(second[m], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
                           NULL);
        if (hFile == INVALID_HANDLE_VALUE)
            m_extraChars = -1;
        CloseHandle(hFile);
    }
}
