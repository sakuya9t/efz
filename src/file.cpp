// Third object of efz.exe (0x4054b0-0x405a1f): CFile, a thin wrapper over the Win32 file
// API. The loaders read their data files through it.
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "efz.h"

BOOL CFile::Open(const char* name, DWORD mode)
{
    DWORD dwDesiredAccess;
    DWORD dwCreationDisposition;
    SECURITY_ATTRIBUTES sa;

    Close();
    dwDesiredAccess = 0;
    dwCreationDisposition = 0;
    if (mode & 1)
        dwDesiredAccess |= GENERIC_READ;
    if (mode & 2)
        dwDesiredAccess |= GENERIC_WRITE;
    if (mode & 0x10)
        dwCreationDisposition = TRUNCATE_EXISTING;
    if (mode & 0x20)
        dwCreationDisposition = OPEN_ALWAYS;
    if ((mode & 0x10) && (mode & 0x20))
        dwCreationDisposition = CREATE_ALWAYS;
    if (!(mode & 0x10) && !(mode & 0x20))
        dwCreationDisposition = OPEN_EXISTING;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;
    m_handle = CreateFile(name, dwDesiredAccess, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa,
                          dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);
    if (m_handle == INVALID_HANDLE_VALUE) {
        m_handle = NULL;
        return FALSE;
    }
    return TRUE;
}

BOOL CFile::Close()
{
    if (m_handle) {
        CloseHandle(m_handle);
        m_handle = NULL;
    }
    if (m_data) {
        delete m_data;
        m_data = NULL;
    }
    Reset();
    return TRUE;
}

DWORD CFile::Read(void* buffer, DWORD size)
{
    DWORD read;

    if (!IsOpen())
        return 0;
    ReadFile(m_handle, buffer, size, &read, NULL);
    return read;
}

int CFile::ReadLine(char* line, int size)
{
    int pos;
    BYTE buf[1000];

    for (pos = 0; pos < size - 1; pos++) {
        if (!Read(&buf[pos], 1))
            break;
        if (buf[pos] == '\n')
            break;
    }
    buf[pos] = '\0';
    if (line)
        strcpy(line, (char*)buf);
    return pos - 1;
}

int CFile::ReadInt()
{
    int value;

    Read(&value, 4);
    return value;
}

short CFile::ReadShort()
{
    short value;

    Read(&value, 2);
    return value;
}

float CFile::ReadFloat()
{
    float value;

    Read(&value, 4);
    return value;
}

DWORD CFile::Write(const void* buffer, DWORD size)
{
    DWORD written;

    if (!IsOpen())
        return 0;
    WriteFile(m_handle, buffer, size, &written, NULL);
    return written;
}

void CFile::WriteInt(int value)
{
    Write(&value, 4);
}

void CFile::WriteFloat(float value)
{
    Write(&value, 4);
}

BOOL CFile::Printf(const char* format, ...)
{
    va_list ap;
    char buf[256];

    va_start(ap, format);
    vsprintf(buf, format, ap);
    Write(buf, strlen(buf));
    va_end(ap);
    return TRUE;
}

DWORD CFile::Seek(LONG offset, int origin)
{
    DWORD method;

    if (!IsOpen())
        return 0;
    // Maps SEEK_SET to FILE_CURRENT first, then overrides it with FILE_BEGIN.
    if (origin == 0)
        method = FILE_CURRENT;
    if (origin == 1)
        method = FILE_CURRENT;
    if (origin == 0)
        method = FILE_BEGIN;
    if (origin == 2)
        method = FILE_END;
    return SetFilePointer(m_handle, offset, NULL, method);
}

DWORD CFile::SeekToStart()
{
    if (!IsOpen())
        return 0;
    return SetFilePointer(m_handle, 0, NULL, FILE_BEGIN);
}

DWORD CFile::SeekToEnd()
{
    if (!IsOpen())
        return 0;
    return SetFilePointer(m_handle, 0, NULL, FILE_END);
}

DWORD CFile::GetSize()
{
    if (!IsOpen())
        return 0;
    return GetFileSize(m_handle, NULL);
}

BOOL CFile::IsOpen()
{
    if (m_handle)
        return TRUE;
    return FALSE;
}

BOOL CFile::Reset()
{
    m_handle = NULL;
    m_data = NULL;
    return TRUE;
}

char* CFile::Load(const char* name)
{
    Close();
    if (!Open(name, 1))
        return NULL;
    m_data = new char[GetSize() + 1];
    m_data[GetSize()] = '\0';
    Read(m_data, GetSize());
    return m_data;
}
