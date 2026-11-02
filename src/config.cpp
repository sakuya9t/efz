// Fourth object of efz.exe (0x405a20-0x406065): key.ini access, the per-character
// record files and the replay stream.
#include <string.h>
#include "efz.h"

BYTE ReadConfigByte(BYTE offset)
{
    BYTE* data;
    DWORD dwRead;
    DWORD size;
    HANDLE hFile = NULL;
    BYTE value = 0;

    hFile = CreateFile("key.ini", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE && GetFileSize(hFile, NULL) >= 0x20) {
        size = GetFileSize(hFile, NULL);
        data = new BYTE[size];
        ReadFile(hFile, data, size, &dwRead, NULL);
        value = data[offset];
        delete data;
    }
    CloseHandle(hFile);
    return value;
}

// Always returns 0.
BYTE WriteConfigByte(BYTE offset, BYTE newValue)
{
    BYTE* data;
    DWORD dwRead;
    DWORD size;
    HANDLE hFile = NULL;
    BYTE value = 0;

    hFile = CreateFile("key.ini", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE && GetFileSize(hFile, NULL) >= 0x20) {
        size = GetFileSize(hFile, NULL);
        data = new BYTE[size];
        ReadFile(hFile, data, size, &dwRead, NULL);
        CloseHandle(hFile);
        data[offset] = newValue;
        hFile = CreateFile("key.ini", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL, NULL);
        WriteFile(hFile, data, size, &dwRead, NULL);
        delete data;
    }
    CloseHandle(hFile);
    return value;
}

void CharRecord::Save(const char* name)
{
    DWORD buffer[9];
    char path[32];
    DWORD dwWrite;
    HANDLE hFile;

    hFile = NULL;
    strcpy(path, "system\\");
    strcat(path, name);
    strcat(path, "\\");
    strcat(path, name);
    strcat(path, ".rec");
    hFile = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        buffer[0] = uses;
        buffer[1] = vsWins;
        buffer[2] = vsLosses;
        buffer[3] = bestScore;
        buffer[4] = bestScoreHigh;
        buffer[5] = unk14;
        buffer[6] = maxCombo;
        buffer[7] = maxDamage;
        buffer[8] = 0;
        WriteFile(hFile, buffer, sizeof(buffer), &dwWrite, NULL);
    }
    CloseHandle(hFile);
}

void CharRecord::Load(const char* name)
{
    DWORD buffer[9];
    char path[32];
    DWORD dwRead;
    DWORD size;
    HANDLE hFile;

    hFile = NULL;
    strcpy(path, "system\\");
    strcat(path, name);
    strcat(path, "\\");
    strcat(path, name);
    strcat(path, ".rec");
    uses = 0;
    vsWins = 0;
    vsLosses = 0;
    bestScore = 0;
    bestScoreHigh = 0;
    unk14 = 0;
    maxCombo = 0;
    maxDamage = 0;
    hFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        size = GetFileSize(hFile, NULL);
        ReadFile(hFile, buffer, size, &dwRead, NULL);
        uses = buffer[0];
        vsWins = buffer[1];
        vsLosses = buffer[2];
        bestScore = buffer[3];
        bestScoreHigh = buffer[4];
        unk14 = buffer[5];
        maxCombo = buffer[6];
        maxDamage = buffer[7];
    }
    CloseHandle(hFile);
}

CReplayFile::CReplayFile()
{
    m_eof = FALSE;
    m_handle = NULL;
}

DWORD CReplayFile::OpenRead(const char* name)
{
    m_handle = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (m_handle == INVALID_HANDLE_VALUE)
        return 0;
    m_remaining = GetFileSize(m_handle, NULL);
    m_read = 0;
    m_eof = FALSE;
    return m_remaining;
}

void CReplayFile::OpenWrite(const char* name)
{
    m_handle = CreateFile(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
                          NULL);
    if (m_handle == INVALID_HANDLE_VALUE)
        return;
    m_eof = FALSE;
}

void CReplayFile::Close()
{
    if (m_handle) {
        CloseHandle(m_handle);
        m_handle = NULL;
    }
}

CReplayFile::~CReplayFile()
{
    if (m_handle)
        CloseHandle(m_handle);
}

short CReplayFile::Read()
{
    short value;

    if (m_remaining <= 0) {
        m_eof = TRUE;
        return 0;
    }
    if (!ReadFile(m_handle, &value, 2, &m_read, NULL)) {
        MessageBox(NULL, "リプレイファイルの読み込みに失敗しました。", "確認", MB_OK);
        return 0;
    }
    m_remaining -= 2;
    return value;
}

void CReplayFile::Write(short value)
{
    short data = value;
    DWORD written;

    if (!WriteFile(m_handle, &data, 2, &written, NULL))
        MessageBox(NULL, "リプレイファイルの書き込みに失敗しました。", "ReplaySave ERROR", MB_OK);
}
