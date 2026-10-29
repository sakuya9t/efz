// Second object of efz.exe (0x4019b0-0x40540f): CGame's per-frame effect update, plus a
// leftover developer tool. The inline helpers this object uses first are placed after
// it: <math.h>'s fabs(float)/sin(float) and EffectDesc's constructor (0x405410-0x4054af).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

#define PI 3.141592

// FUNCTION: 0x4019b0
// Developer tool, never called: re-encodes system0\object.bmp as system\object.dat by
// dropping the first 10 bytes and XORing the rest with 0x64. It also builds numbered
// ayu0\NNN.bmp / ayu\NNN.dat names but then opens the fixed names instead. The shipped
// .dat files are not in this format.
void EncodeObjectDat()
{
    int j;
    int writesize;
    BYTE* data;
    DWORD dwRead;
    int size;
    BYTE* pOut;
    BOOL success;
    int i;
    HANDLE hfile2;
    HANDLE hRead;
    char cnum[10];
    char fname[30];

    for (i = 0; i <= 0; i++) {
        _strnset(fname, 0, 30);
        strcat(fname, "ayu0\\");
        if (i < 100)
            strcat(fname, "0");
        if (i < 10)
            strcat(fname, "0");
        _itoa(i, cnum, 10);
        strcat(fname, cnum);
        strcat(fname, ".bmp");
        hRead = CreateFile("system0\\object.bmp", GENERIC_READ, 0, NULL, OPEN_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL, NULL);

        _strnset(fname, 0, 30);
        strcat(fname, "ayu\\");
        if (i < 100)
            strcat(fname, "0");
        if (i < 10)
            strcat(fname, "0");
        _itoa(i, cnum, 10);
        strcat(fname, cnum);
        strcat(fname, ".dat");
        hfile2 = CreateFile("system\\object.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL,
                            OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        size = GetFileSize(hRead, NULL);
        data = new BYTE[size];
        success = ReadFile(hRead, data, size, &dwRead, NULL);
        pOut = new BYTE[size - 10];
        for (j = 0; j < size - 10; j++)
            pOut[j] = data[j + 10] ^ 0x64;
        writesize = size - 10;
        success = WriteFile(hfile2, pOut, writesize, &dwRead, NULL);
        CloseHandle(hRead);
        CloseHandle(hfile2);
        delete data;
        delete pOut;
    }
}

// count times, spawn effect `type` twice at this effect's position, the second time
// on layer 1.
#define SPAWN_PAIRS(count, effectType)                      \
    for (i = 0; i < (count); i++) {                         \
        d.x = (int)m_effects[index].x;                      \
        d.y = (int)m_effects[index].y;                      \
        d.side = m_effects[index].side;                     \
        d.scale = 2;                                        \
        d.layer = 0;                                        \
        d.type = (effectType);                              \
        CreateEffect(&d);                                   \
        d.layer = 1;                                        \
        CreateEffect(&d);                                   \
    }

// count times, spawn effect `type` once at this effect's position.
#define SPAWN_EACH(count, effectType)                       \
    for (i = 0; i < (count); i++) {                         \
        d.x = (int)m_effects[index].x;                      \
        d.y = (int)m_effects[index].y;                      \
        d.side = m_effects[index].side;                     \
        d.scale = 2;                                        \
        d.layer = 0;                                        \
        d.type = (effectType);                              \
        CreateEffect(&d);                                   \
    }

#define FIRST_FRAME (m_effects[index].frame == 0 && m_effects[index].timer == 0)

// Advances the animation; the effect is removed after its last frame.
#define ANIMATION_DONE \
    (m_effects[index].timer >= m_effectAnims[m_effects[index].type].frames[m_effects[index].frame].duration)
#define LAST_FRAME_PASSED \
    (m_effects[index].frame >= m_effectAnims[m_effects[index].type].frameCount)

void CGame::UpdateEffect(short index)
{
    double tx;
    EffectDesc d;
    int i;
    double ty;

    d.unk0 = 0;
    d.screen = 0;
    d.unk2c = 0xff;

    switch (m_effects[index].type) {
    case 0:
        if (FIRST_FRAME && unk1366) {
            SPAWN_PAIRS(3, 0xa)
            SPAWN_PAIRS(3, 0x23)
            SPAWN_PAIRS(8, 0x24)
            SPAWN_PAIRS(2, 0x2f)
        }
        break;
    case 2:
        if (FIRST_FRAME && unk1366) {
            SPAWN_PAIRS(8, 0x27)
        }
        break;
    case 5:
        m_effects[index].timer++;
        if (ANIMATION_DONE) {
            m_effects[index].timer = 0;
            m_effects[index].frame++;
            if (m_effects[index].frame == 10) {
                d.unk0 = 0;
                d.x = 160;
                d.y = 120;
                d.side = 0;
                d.scale = 0;
                d.layer = 2;
                d.screen = 1;
                d.type = 0x15;
                d.unk2c = 0xff;
                CreateEffect(&d);
                d.x = 160;
                d.y = 120;
                d.side = 0;
                d.scale = 0;
                d.layer = 2;
                d.screen = 1;
                d.type = unk134d + 0x38;
                d.unk2c = 0xff;
                CreateEffect(&d);
            }
            if (m_effects[index].frame == 15) {
                d.unk0 = 0;
                d.x = 160;
                d.y = 120;
                d.side = 0;
                d.scale = 2;
                d.layer = 1;
                d.screen = 1;
                d.type = 0x1a;
                d.unk2c = 0xff;
                CreateEffect(&d);
            }
            if (LAST_FRAME_PASSED)
                RemoveEffect(index);
        }
        return;
    case 10:
        if (FIRST_FRAME) {
            double angle = rand() * PI * 2 / 32768.0;
            double speed = rand() / 2000;
            m_effects[index].vx = cos(angle) * speed;
            m_effects[index].vy = sin(angle) * speed;
        }
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0xb:
        if (FIRST_FRAME && unk1366) {
            SPAWN_PAIRS(5, 0x22)
        }
        break;
    case 0xc:
        if (FIRST_FRAME && unk1366) {
            SPAWN_PAIRS(8, 0x22)
        }
        break;
    case 0xd:
        if (FIRST_FRAME && unk1366) {
            SPAWN_PAIRS(8, 0x25)
            SPAWN_PAIRS(5, 0x22)
        }
        break;
    case 0xe:
        if (FIRST_FRAME && unk1366) {
            SPAWN_PAIRS(16, 0x2a)
        }
        break;
    case 0xf:
        if (FIRST_FRAME && unk1366) {
            SPAWN_PAIRS(8, 0x2c)
        }
        break;
    case 0x10:
        if (FIRST_FRAME && unk1366) {
            SPAWN_PAIRS(8, 0x2b)
        }
        break;
    case 0x15:
        m_effects[index].timer++;
        if (ANIMATION_DONE) {
            m_effects[index].timer = 0;
            m_effects[index].frame++;
            if (LAST_FRAME_PASSED) {
                RemoveEffect(index);
                d.unk0 = 0;
                d.x = 160;
                d.y = 120;
                d.side = 0;
                d.scale = 2;
                d.layer = 3;
                d.screen = 1;
                d.type = 6;
                d.unk2c = 0xff;
                CreateEffect(&d);
                d.unk0 = 0;
                d.x = 160;
                d.y = 120;
                d.side = 0;
                d.scale = 0;
                d.layer = 2;
                d.screen = 1;
                d.type = 0x16;
                d.unk2c = 0x17;
                CreateEffect(&d);
            }
        }
        return;
    case 0x16:
        m_effects[index].timer++;
        if (ANIMATION_DONE) {
            m_effects[index].timer = 0;
            m_effects[index].frame++;
            if (LAST_FRAME_PASSED) {
                RemoveEffect(index);
                d.unk0 = 0;
                d.x = 160;
                d.y = 120;
                d.side = 0;
                d.scale = 0;
                d.layer = 2;
                d.screen = 1;
                d.type = 0x17;
                d.unk2c = 0xff;
                CreateEffect(&d);
            }
        }
        return;
    case 0x17:
        m_effects[index].timer++;
        if (ANIMATION_DONE) {
            m_effects[index].timer = 0;
            m_effects[index].frame++;
            if (LAST_FRAME_PASSED) {
                RemoveEffect(index);
                d.unk0 = 0;
                d.x = 160;
                d.y = 120;
                d.side = 0;
                d.scale = 2;
                d.layer = 2;
                d.screen = 1;
                d.type = 7;
                d.unk2c = 0xff;
                CreateEffect(&d);
                d.unk0 = 0;
                d.x = 160;
                d.y = 120;
                d.side = 0;
                d.scale = 0;
                d.layer = 2;
                d.screen = 1;
                d.type = 0x18;
                d.unk2c = 0x18;
                CreateEffect(&d);
            }
        }
        return;
    case 0x18:
        m_effects[index].timer++;
        if (ANIMATION_DONE) {
            m_effects[index].timer = 0;
            m_effects[index].frame++;
            if (LAST_FRAME_PASSED) {
                RemoveEffect(index);
                d.unk0 = 0;
                d.x = 160;
                d.y = 120;
                d.side = 0;
                d.scale = 0;
                d.layer = 2;
                d.screen = 1;
                d.type = 0x19;
                d.unk2c = 0xff;
                CreateEffect(&d);
            }
        }
        return;
    case 0x19:
        m_effects[index].timer++;
        if (ANIMATION_DONE) {
            m_effects[index].timer = 0;
            m_effects[index].frame++;
            if (LAST_FRAME_PASSED) {
                RemoveEffect(index);
                d.unk0 = 0;
                d.x = 160;
                d.y = 120;
                d.side = 0;
                d.scale = 2;
                d.layer = 2;
                d.screen = 1;
                d.type = 0x12;
                d.unk2c = 0xff;
                CreateEffect(&d);
                unk1350 = 0;
            }
        }
        return;
    case 0x1a:
        unk142a0 = m_effects[index].frame;
        unk142a4 = m_effects[index].timer;
        break;
    case 0x1b:
        m_effects[index].timer++;
        if (ANIMATION_DONE) {
            m_effects[index].timer = 0;
            m_effects[index].frame++;
            if (m_effects[index].frame == 0x1a) {
                d.unk0 = 0;
                d.x = 160;
                d.y = 120;
                d.side = 0;
                d.scale = 2;
                d.layer = 2;
                d.screen = 1;
                d.type = 5;
                d.unk2c = unk134d + 0xb;
                CreateEffect(&d);
            }
            if (LAST_FRAME_PASSED)
                RemoveEffect(index);
        }
        return;
    case 0x21:
        if (FIRST_FRAME) {
            unk14294 = 0;
            SPAWN_EACH(40, 0x26)
        }
        break;
    case 0x22:
        if (FIRST_FRAME) {
            double angle = rand() * PI * 2 / 32768.0;
            double speed = rand() / 20000.0;
            m_effects[index].vx = cos(angle) * speed;
            m_effects[index].vy = sin(angle) * speed;
        }
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x23:
        if (FIRST_FRAME) {
            double angle = rand() * PI * 2 / 32768.0;
            double speed = rand() / 20000.0;
            m_effects[index].vx = cos(angle) * speed;
            m_effects[index].vy = sin(angle) * speed;
        }
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x24:
        if (FIRST_FRAME) {
            double angle = rand() * PI * 2 / 32768.0;
            double speed = rand() / 13000.0;
            m_effects[index].vx = cos(angle) * speed;
            m_effects[index].vy = sin(angle) * speed;
        }
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x25:
        if (FIRST_FRAME) {
            double angle = rand() * PI * 2 / 32768.0;
            double speed = rand() / 13000.0;
            m_effects[index].vx = cos(angle) * speed;
            m_effects[index].vy = sin(angle) * speed;
        }
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x26:
        // Points on a flattened ellipse, rotated by -25 degrees.
        if (FIRST_FRAME) {
            double theta = unk14294 * 9 * PI / 180.0;
            double r = 3.0;
            tx = cos(theta) * r;
            ty = sin(theta) * r / 3.0;
            m_effects[index].vx = cos(-25 * PI / 180) * tx - sin(-25 * PI / 180) * ty;
            m_effects[index].vy = (m_effects[index].side * 2 - 1) *
                                  (cos(-25 * PI / 180) * ty + sin(-25 * PI / 180) * tx);
            unk14294++;
        }
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x27:
        if (FIRST_FRAME) {
            double angle = rand() * PI * 2 / 32768.0;
            double speed = rand() / 13000.0;
            m_effects[index].vx = (m_effects[index].side * 2 - 1) * cos(angle / 2 - PI / 2) * speed;
            m_effects[index].vy = sin(angle) * speed;
        }
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x2a:
        if (FIRST_FRAME) {
            double angle = (rand() * 20 / 32768 + (rand() < 0x4000) * 180 + 35) * (PI / 180);
            double speed = rand() / 13000.0;
            m_effects[index].vx = (m_effects[index].side * 2 - 1) * cos(angle) * speed;
            m_effects[index].vy = sin(angle) * speed;
        }
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x2b:
        if (FIRST_FRAME) {
            double angle = (rand() * 40 / 32768 + (rand() < 0x4000) * 180 + 25) * (PI / 180);
            double speed = rand() / 13000.0;
            m_effects[index].vx = (m_effects[index].side * 2 - 1) * cos(angle) * speed;
            m_effects[index].vy = sin(angle) * speed;
        }
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x2c:
        if (FIRST_FRAME) {
            double angle = (rand() * 20 / 32768 + (rand() < 0x4000) * 180 - 10) * (PI / 180);
            double speed = rand() / 13000.0;
            m_effects[index].vx = (m_effects[index].side * 2 - 1) * cos(angle) * speed;
            m_effects[index].vy = sin(angle) * speed;
        }
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x2d:
        if (FIRST_FRAME) {
            double angle = (rand() * 40 / 32768 + (rand() < 0x4000) * 180 - 20) * (PI / 180);
            double speed = rand() / 13000.0;
            m_effects[index].vx = (m_effects[index].side * 2 - 1) * cos(angle) * speed;
            m_effects[index].vy = sin(angle) * speed;
        }
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x2e:
        // Debris: thrown up, falls under gravity and bounces on y = 0 with random damping.
        if (FIRST_FRAME) {
            m_effects[index].vx = sin((float)rand()) * 6.0f;
            m_effects[index].vy = -(double)rand() / 4000.0 - 2.0;
        }
        m_effects[index].vy += 0.2;
        if (rand() < 0x4000)
            m_effects[index].timer++;
        if (m_effects[index].y + m_effects[index].vy >= 0.0)
            m_effects[index].vy = -m_effects[index].vy * (0.9 - rand() / 32768.0 * 0.3);
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x2f:
        if (FIRST_FRAME) {
            m_effects[index].vx = (m_effects[index].side * 2 - 1) * -fabs(sin((float)rand()) * 4.0f);
            m_effects[index].vy = -(double)rand() / 7000.0 - 2.0;
        }
        m_effects[index].vy += 0.2;
        if (rand() < 0x4000)
            m_effects[index].timer++;
        if (m_effects[index].y + m_effects[index].vy >= 0.0)
            m_effects[index].vy = -m_effects[index].vy * (0.9 - rand() / 32768.0 * 0.3);
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x34:
        if (FIRST_FRAME && unk1366) {
            SPAWN_PAIRS(16, 0x2e)
            unk14294 = 0;
            unk14298 = (short)(rand() / 91.02);
            unk1429c = unk14298 + 30 + (short)(rand() / 273.07);
            SPAWN_EACH(40, 0x35)
            SPAWN_EACH(40, 0x36)
        }
        break;
    case 0x35:
        if (FIRST_FRAME) {
            double theta = unk14294 * 9 * PI / 180.0;
            double r = 3.0;
            tx = cos(theta) * r * 5.0;
            ty = sin(theta) * r / 3.0 * 5.0;
            m_effects[index].vx = cos(unk14298 * PI / 180.0) * tx - sin(unk14298 * PI / 180.0) * ty;
            m_effects[index].vy = (m_effects[index].side * 2 - 1) *
                                  (cos(unk14298 * PI / 180.0) * ty + sin(unk14298 * PI / 180.0) * tx);
            unk14294++;
        }
        m_effects[index].vx *= 0.94;
        m_effects[index].vy *= 0.94;
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    case 0x36:
        if (FIRST_FRAME) {
            double theta = unk14294 * 9 * PI / 180.0;
            double r = 3.0;
            tx = cos(theta) * r * 5.0;
            ty = sin(theta) * r / 3.0 * 5.0;
            m_effects[index].vx = cos(unk1429c * PI / 180.0) * tx - sin(unk1429c * PI / 180.0) * ty;
            m_effects[index].vy = (m_effects[index].side * 2 - 1) *
                                  (cos(unk1429c * PI / 180.0) * ty + sin(unk1429c * PI / 180.0) * tx);
            unk14294++;
        }
        m_effects[index].vx *= 0.94;
        m_effects[index].vy *= 0.94;
        m_effects[index].x += m_effects[index].vx;
        m_effects[index].y += m_effects[index].vy;
        break;
    }

    m_effects[index].timer++;
    if (ANIMATION_DONE) {
        m_effects[index].timer = 0;
        m_effects[index].frame++;
        if (LAST_FRAME_PASSED)
            RemoveEffect(index);
    }
}

// Inline helpers emitted after this object's code (COMDATs first used here).
// FUNCTION: 0x405410 ?fabs@@YAMM@Z
// FUNCTION: 0x405430 _fabsf
// FUNCTION: 0x405450 ?sin@@YAMM@Z
// FUNCTION: 0x405470 _sinf
