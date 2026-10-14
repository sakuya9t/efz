// Eighth object of efz.exe (0x40d810-0x40e62f): CSound, the DirectSound layer.
#include <string.h>
#include "efz.h"

CSound::CSound()
{
    int i;

    m_loopEnd = 0;
    m_loopLength = 0;
    for (i = 0; i < 0x96; i++) {
        m_data[i] = NULL;
        m_buffers[i] = NULL;
    }
}

CSound::~CSound()
{
    WORD i;

    for (i = 0; i < 0x96; i++) {
        if (m_buffers[i]) {
            ReleaseBuffer(i);
            if (m_data[i]) {
                delete m_data[i];
                m_data[i] = NULL;
            }
            m_buffers[i] = NULL;
        }
    }
    if (m_ds) {
        m_ds->Release();
        m_ds = NULL;
    }
}

void CSound::Shutdown()
{
    WORD i;

    for (i = 0; i < 0x96; i++) {
        if (m_buffers[i]) {
            ReleaseBuffer(i);
            if (m_data[i]) {
                delete m_data[i];
                m_data[i] = NULL;
            }
            m_buffers[i] = NULL;
        }
    }
    if (m_ds) {
        m_ds->Release();
        m_ds = NULL;
    }
}

void CSound::Init(HWND hWnd)
{
    WORD i;
    HRESULT hr;

    m_hwnd = hWnd;
    for (i = 0; i < 0x96; i++)
        m_buffers[i] = NULL;
    hr = DirectSoundCreate(NULL, &m_ds, NULL);
    if (hr != DS_OK) {
        MessageBox(m_hwnd, "DirectSoundオブジェクトが生成できません", "DS", MB_OK);
        return;
    }
    hr = m_ds->SetCooperativeLevel(m_hwnd, DSSCL_EXCLUSIVE);
    if (hr != DS_OK)
        MessageBox(m_hwnd, "協調レベルを設定できません", "DS", MB_OK);
}

void CSound::Fill(WORD id)
{
    HRESULT result;
    LPVOID ptr2;
    DWORD size1;
    DWORD size2;
    LPVOID ptr1;

    if (m_buffers[id]) {
        result = m_buffers[id]->Lock(0, m_size[id], &ptr1, &size1, &ptr2, &size2, 0);
        if (result == DSERR_BUFFERLOST) {
            m_buffers[id]->Restore();
            result = m_buffers[id]->Lock(0, m_size[id], &ptr1, &size1, &ptr2, &size2, 0);
        }
        if (result != DS_OK)
            MessageBox(m_hwnd, "Lockに失敗しました", "DS", MB_OK);
        memcpy(ptr1, m_data[id], size1);
        if (ptr2)
            memcpy(ptr2, m_data[id] + size1, size2);
        result = m_buffers[id]->Unlock(ptr1, size1, ptr2, size2);
        if (result != DS_OK)
            MessageBox(m_hwnd, "Unlockに失敗しました", "DS", MB_OK);
    }
}

void CSound::ReleaseBuffer(WORD id)
{
    HRESULT hr;

    if (m_buffers[id]) {
        hr = m_buffers[id]->Release();
        if (hr != DS_OK)
            MessageBox(m_hwnd, "バッファの解放に失敗しました", "DS", MB_OK);
        m_buffers[id] = NULL;
    }
}

void CSound::CreateBuffer(WORD id, WAVEFORMATEX* format)
{
    HRESULT hr;
    PCMWAVEFORMAT wf;
    DSBUFFERDESC dsbd;

    memset(&wf, 0, sizeof(wf));
    wf.wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.wf.nChannels = format->nChannels;
    wf.wf.nSamplesPerSec = format->nSamplesPerSec;
    wf.wf.nBlockAlign = format->nBlockAlign;
    wf.wf.nAvgBytesPerSec = wf.wf.nBlockAlign * wf.wf.nSamplesPerSec;
    wf.wBitsPerSample = format->nBlockAlign * 8 / format->nChannels;
    memset(&dsbd, 0, sizeof(dsbd));
    dsbd.dwSize = sizeof(dsbd);
    dsbd.dwFlags = DSBCAPS_CTRLVOLUME;
    dsbd.dwBufferBytes = m_size[id];
    dsbd.lpwfxFormat = (WAVEFORMATEX*)&wf;
    hr = m_ds->CreateSoundBuffer(&dsbd, &m_buffers[id], NULL);
    if (hr != DS_OK)
        MessageBox(m_hwnd, "バッファが作成できませんでした", "DS", MB_OK);
}

WORD CSound::FindFreeSlot()
{
    WORD i;

    for (i = 0; i < 0x96; i++) {
        if (!m_buffers[i])
            break;
    }
    if (i == 0x96)
        MessageBox(m_hwnd, "使用できるチャンネルがありません", "DS使用できるチャンネルがありません", MB_OK);
    return i;
}

void CSound::Stop(WORD id)
{
    if (m_buffers[id])
        m_buffers[id]->Stop();
}

void CSound::Play(WORD id, BOOL loop)
{
    HRESULT hr;

    if (m_buffers[id] && id != 0x96) {
        m_buffers[id]->Stop();
        m_buffers[id]->SetCurrentPosition(0);
        hr = m_buffers[id]->Play(0, 0, loop == 1);
        if (hr != DS_OK)
            MessageBox(m_hwnd, "再生できません", "DS再生できません", MB_OK);
    }
}

void CSound::Release(WORD id)
{
    ReleaseBuffer(id);
    if (m_data[id]) {
        delete m_data[id];
        m_data[id] = NULL;
    }
}

WORD CSound::Load(const char* name)
{
    WORD ch;
    HMMIO hm;
    MMCKINFO parent = {0, 0, 0, 0, 0};
    MMCKINFO child = parent;
    WAVEFORMATEX wfx;

    hm = mmioOpen((LPSTR)name, NULL, MMIO_ALLOCBUF | MMIO_READ);
    if (!hm)
        return 0x96;
    parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    if (mmioDescend(hm, &parent, NULL, MMIO_FINDRIFF)) {
        mmioClose(hm, 0);
        MessageBox(m_hwnd, "WAVEファイルではありません", "DS", MB_OK);
        return 0x96;
    }
    child.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioDescend(hm, &child, &parent, 0)) {
        mmioClose(hm, 0);
        MessageBox(m_hwnd, "ファイルを開くことができません", "DS", MB_OK);
        return 0x96;
    }
    if (mmioRead(hm, (HPSTR)&wfx, sizeof(wfx)) != sizeof(wfx)) {
        mmioClose(hm, 0);
        MessageBox(m_hwnd, "fmtチャンクを読み取ることができません", "DS", MB_OK);
        return 0x96;
    }
    if (wfx.wFormatTag != WAVE_FORMAT_PCM) {
        mmioClose(hm, 0);
        MessageBox(m_hwnd, "WAVEファイルはPCMフォーマットではありません", "DS", MB_OK);
        return 0x96;
    }
    if (mmioAscend(hm, &child, 0)) {
        mmioClose(hm, 0);
        MessageBox(m_hwnd, "アセンドできません", "DS", MB_OK);
        return 0x96;
    }
    child.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioDescend(hm, &child, &parent, MMIO_FINDCHUNK)) {
        mmioClose(hm, 0);
        MessageBox(m_hwnd, "WAVEファイルにdataチャンクがありません", "DS", MB_OK);
        return 0x96;
    }
    ch = FindFreeSlot();
    m_data[ch] = new BYTE[child.cksize];
    m_size[ch] = child.cksize;
    if (!m_data[ch]) {
        MessageBox(m_hwnd, "エラー", "DS", MB_OK);
        return 0x96;
    }
    if (mmioRead(hm, (HPSTR)m_data[ch], child.cksize) != (LONG)child.cksize) {
        mmioClose(hm, 0);
        MessageBox(m_hwnd, "dataチャンクを読み取ることができません", "DS", MB_OK);
        return 0x96;
    }
    mmioClose(hm, 0);
    CreateBuffer(ch, &wfx);
    Fill(ch);
    return ch;
}

void CSound::LoadLoop(const char* name)
{
    int j;
    BYTE* buf = new BYTE[0x140];
    DWORD len;
    DWORD dw;
    DWORD fileSize;
    DWORD cue;
    HANDLE h;

    cue = 0;
    len = 0;
    h = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    fileSize = GetFileSize(h, NULL);
    if (h == INVALID_HANDLE_VALUE || GetFileSize(h, NULL) == 0) {
        m_loopEnd = 0;
        m_loopLength = 0;
        return;
    }
    SetFilePointer(h, -0x140, NULL, FILE_END);
    ReadFile(h, buf, 0x140, &dw, NULL);
    CloseHandle(h);
    for (j = 0; j < 0x140; j++) {
        if (buf[j] == 'c' && buf[j + 1] == 'u' && buf[j + 2] == 'e') {
            cue = buf[j + 0x10] + (buf[j + 0x11] << 8) + (buf[j + 0x12] << 8 << 8) +
                  (buf[j + 0x13] << 8 << 8 << 8);
        } else if (buf[j] == 'a' && buf[j + 1] == 'd' && buf[j + 2] == 't' && buf[j + 3] == 'l') {
            len = buf[j + 0x10] + (buf[j + 0x11] << 8) + (buf[j + 0x12] << 8 << 8) +
                   (buf[j + 0x13] << 8 << 8 << 8);
        }
    }
    if (cue == 0 || len == 0)
        return;
    m_loopEnd = (cue + len) * 4;
    m_loopLength = len * 4;
    delete buf;
}

void CSound::UpdateLoop(WORD id)
{
    DWORD pos;

    if (!m_loopEnd)
        return;
    if (id == 0x96)
        return;
    if (!m_buffers[id])
        return;
    if (!m_data[id])
        return;
    m_buffers[id]->GetCurrentPosition(&pos, NULL);
    if (pos > m_loopEnd) {
        m_buffers[id]->Stop();
        m_buffers[id]->SetCurrentPosition(pos - m_loopLength);
        m_buffers[id]->Play(0, 0, DSBPLAY_LOOPING);
    }
}

void CSound::SetVolume(WORD id, int volume)
{
    if (id == 0x96)
        return;
    if (m_buffers[id])
        m_buffers[id]->SetVolume(volume);
}
