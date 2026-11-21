// Video files of fights: see mp4.h. The MP4 is ISO/IEC 14496-12 and -15 (H.264 in
// 'avc1' with its 'avcC'), with Opus as "Encapsulation of Opus in ISO Base Media File
// Format" puts it ('Opus' with 'dOps', the encoder's lookahead skipped by an edit list).
// Samples go into one 'mdat' as they come, the tables of where they are into 'moov' at
// the end.
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <string.h>

#include <opus.h>

// As port/minih264.c builds the encoder.
#define H264E_SVC_API 0
#define H264E_MAX_THREADS 0
#include "minih264e.h"

#include "log.h"
#include "mp4.h"

namespace efz {

namespace {

// Pictures: a fixed quantizer, so every frame has the same quality; a key frame every 2 s;
// the encoder's fast setting, which looks as its middle one and makes smaller files. The
// stages' dithered pictures take bits: about 5-6 Mbit/s at 640x480, 10 at 1280x960 (what
// YouTube asks of an upload between 720p and 1080p at 60 frames a second).
const int kQp = 28;
const int kGop = 128;
const int kSpeed = 8;
const int kOpusBitrate = 160000;
const int kOpusFrame = 960; // 20 ms at 48 kHz

// A box being built: sizes filled in as each closes.
struct Boxes {
    std::vector<uint8_t> b;
    std::vector<size_t> open;

    void U8(uint32_t v) { b.push_back((uint8_t)v); }
    void U16(uint32_t v)
    {
        U8(v >> 8);
        U8(v);
    }
    void U32(uint32_t v)
    {
        U16(v >> 16);
        U16(v & 0xffff);
    }
    void U64(uint64_t v)
    {
        U32((uint32_t)(v >> 32));
        U32((uint32_t)v);
    }
    void Four(const char* s) { b.insert(b.end(), s, s + 4); }
    void Bytes(const void* p, size_t n)
    {
        b.insert(b.end(), (const uint8_t*)p, (const uint8_t*)p + n);
    }
    void Zeros(size_t n) { b.insert(b.end(), n, 0); }
    void Begin(const char* type)
    {
        open.push_back(b.size());
        U32(0);
        Four(type);
    }
    void Full(const char* type, int version, uint32_t flags)
    {
        Begin(type);
        U32((uint32_t)version << 24 | flags);
    }
    void End()
    {
        size_t at = open.back();
        open.pop_back();
        uint32_t size = (uint32_t)(b.size() - at);
        b[at] = (uint8_t)(size >> 24);
        b[at + 1] = (uint8_t)(size >> 16);
        b[at + 2] = (uint8_t)(size >> 8);
        b[at + 3] = (uint8_t)size;
    }
    void Matrix()
    {
        static const uint32_t m[9] = {0x10000, 0, 0, 0, 0x10000, 0, 0, 0, 0x40000000};
        for (uint32_t v : m)
            U32(v);
    }
};

// H.264's level for the picture size at 64 frames a second (Table A-1): the macroblocks
// a second and a frame's.
int Level(int width, int height)
{
    long frame = (long)(width / 16) * (height / 16);
    long second = frame * Mp4Writer::kFps;
    static const struct {
        int level;
        long perSecond, perFrame;
    } levels[] = {{30, 40500, 1620},   {31, 108000, 3600},  {32, 216000, 5120},
                  {40, 245760, 8192},  {42, 522240, 8704},  {50, 589824, 22080},
                  {51, 983040, 36864}, {52, 2073600, 36864}};
    for (const auto& l : levels) {
        if (second <= l.perSecond && frame <= l.perFrame)
            return l.level;
    }
    return 52;
}

} // namespace

Mp4Writer::~Mp4Writer()
{
    Abandon();
}

bool Mp4Writer::Fail(const std::string& what)
{
    if (error_.empty())
        error_ = what;
    return false;
}

void Mp4Writer::Abandon()
{
    if (file_) {
        fclose(file_);
        file_ = nullptr;
        SDL_RemovePath(temp_.c_str());
    }
    free(encoder_);
    free(scratch_);
    encoder_ = scratch_ = nullptr;
    if (opus_)
        opus_encoder_destroy(opus_);
    opus_ = nullptr;
}

bool Mp4Writer::Open(const std::string& path, int width, int height)
{
    path_ = path;
    temp_ = path + ".part";
    width_ = width;
    height_ = height;
    if (width % 16 || height % 16)
        return Fail("the picture's size isn't a multiple of 16");
    file_ = OpenUtf8(temp_.c_str(), "wb");
    if (!file_)
        return Fail("can't write " + temp_);
    Boxes head;
    head.Begin("ftyp");
    head.Four("isom");
    head.U32(0x200);
    head.Four("isom");
    head.Four("iso2");
    head.Four("avc1");
    head.Four("mp41");
    head.End();
    mdatStart_ = head.b.size();
    head.U32(1); // the size is the 64-bit one that follows, filled in by Close
    head.Four("mdat");
    head.U64(0);
    if (!Write(head.b.data(), head.b.size(), nullptr))
        return false;

    H264E_create_param_t create;
    memset(&create, 0, sizeof(create));
    create.width = width;
    create.height = height;
    create.gop = kGop;
    create.const_input_flag = 1;
    create.enableNEON = 1;
    int persist = 0, scratch = 0;
    if (H264E_sizeof(&create, &persist, &scratch) != H264E_STATUS_SUCCESS)
        return Fail("the H.264 encoder won't take that size");
    encoder_ = malloc(persist);
    scratch_ = malloc(scratch);
    if (!encoder_ || !scratch_ ||
        H264E_init((H264E_persist_t*)encoder_, &create) != H264E_STATUS_SUCCESS)
        return Fail("the H.264 encoder can't start");
    yuv_.resize((size_t)width * height * 3 / 2);

    int err = 0;
    opus_ = opus_encoder_create(kRate, 2, OPUS_APPLICATION_AUDIO, &err);
    if (!opus_ || err != OPUS_OK)
        return Fail("the Opus encoder can't start");
    opus_encoder_ctl(opus_, OPUS_SET_BITRATE(kOpusBitrate));
    opus_int32 lookahead = 0;
    opus_encoder_ctl(opus_, OPUS_GET_LOOKAHEAD(&lookahead));
    preSkip_ = lookahead;
    return true;
}

bool Mp4Writer::Write(const void* data, size_t size, Track* track)
{
    if (!file_)
        return Fail("the file isn't open");
    if (fwrite(data, 1, size, file_) != size)
        return Fail("can't write " + temp_ + " (is the disk full?)");
    if (track) {
        track->sizes.push_back((uint32_t)size);
        track->offsets.push_back(at_);
    }
    at_ += size;
    return true;
}

bool Mp4Writer::EncodePicture(const uint32_t* pixels, int w, int h)
{
    // Nearest pixel to the video's size, then BT.709's YCbCr, limited range; the colour
    // a 2x2 block's average.
    uint8_t* Y = yuv_.data();
    uint8_t* U = Y + (size_t)width_ * height_;
    uint8_t* V = U + (size_t)width_ * height_ / 4;
    std::vector<int> xs(width_);
    for (int x = 0; x < width_; x++)
        xs[x] = x * w / width_;
    for (int y = 0; y < height_; y += 2) {
        const uint32_t* rows[2] = {pixels + (size_t)(y * h / height_) * w,
                                   pixels + (size_t)((y + 1) * h / height_) * w};
        for (int x = 0; x < width_; x += 2) {
            int r = 0, g = 0, b = 0;
            for (int dy = 0; dy < 2; dy++) {
                for (int dx = 0; dx < 2; dx++) {
                    uint32_t p = rows[dy][xs[x + dx]];
                    int pr = (p >> 16) & 0xff, pg = (p >> 8) & 0xff, pb = p & 0xff;
                    Y[(size_t)(y + dy) * width_ + x + dx] =
                        (uint8_t)(16 + ((47 * pr + 157 * pg + 16 * pb + 128) >> 8));
                    r += pr;
                    g += pg;
                    b += pb;
                }
            }
            size_t c = (size_t)(y / 2) * (width_ / 2) + x / 2;
            U[c] = (uint8_t)(128 + ((-26 * r - 87 * g + 112 * b + 512) >> 10));
            V[c] = (uint8_t)(128 + ((112 * r - 102 * g - 10 * b + 512) >> 10));
        }
    }
    H264E_io_yuv_t io;
    io.yuv[0] = Y;
    io.yuv[1] = U;
    io.yuv[2] = V;
    io.stride[0] = width_;
    io.stride[1] = io.stride[2] = width_ / 2;
    H264E_run_param_t run;
    memset(&run, 0, sizeof(run));
    run.encode_speed = kSpeed;
    run.qp_min = run.qp_max = kQp;
    unsigned char* coded = nullptr;
    int size = 0;
    if (H264E_encode((H264E_persist_t*)encoder_, (H264E_scratch_t*)scratch_, &run, &io, &coded,
                     &size) != H264E_STATUS_SUCCESS)
        return Fail("the H.264 encoder failed on frame " + std::to_string(Frames() + 1));
    // Annex B's start codes to the lengths MP4 has; the parameter sets go to 'avcC'.
    std::vector<uint8_t> sample;
    bool key = false;
    int level = Level(width_, height_);
    for (int i = 0; i + 3 <= size;) {
        if (!(coded[i] == 0 && coded[i + 1] == 0 && coded[i + 2] == 1)) {
            i++;
            continue;
        }
        int start = i + 3, end = start;
        while (end + 3 <= size &&
               !(coded[end] == 0 && coded[end + 1] == 0 &&
                 (coded[end + 2] == 1 || (coded[end + 2] == 0 && end + 3 < size &&
                                          coded[end + 3] == 1))))
            end++;
        if (end + 3 > size)
            end = size;
        int type = coded[start] & 0x1f;
        if (type == 7 && sps_.empty()) {
            sps_.assign(coded + start, coded + end);
            if (sps_.size() > 3)
                sps_[3] = (uint8_t)level;
        } else if (type == 8 && pps_.empty()) {
            pps_.assign(coded + start, coded + end);
        } else if (type != 7 && type != 8 && type != 9) {
            uint32_t n = (uint32_t)(end - start);
            uint8_t len[4] = {(uint8_t)(n >> 24), (uint8_t)(n >> 16), (uint8_t)(n >> 8),
                              (uint8_t)n};
            sample.insert(sample.end(), len, len + 4);
            sample.insert(sample.end(), coded + start, coded + end);
            key |= type == 5;
        }
        i = end;
    }
    if (sample.empty())
        return Fail("the H.264 encoder gave no picture for frame " +
                    std::to_string(Frames() + 1));
    if (!Write(sample.data(), sample.size(), &video_))
        return false;
    if (key)
        video_.keys.push_back((uint32_t)video_.sizes.size());
    return true;
}

bool Mp4Writer::EncodeSound(bool flush)
{
    // At the end, silence up to a whole packet, and until the lookahead is played out.
    if (flush) {
        uint64_t encoded = (uint64_t)audio_.sizes.size() * kOpusFrame + pcm_.size() / 2;
        uint64_t need = samples_ + preSkip_;
        while (encoded < need || pcm_.size() % (2 * kOpusFrame)) {
            pcm_.push_back(0);
            pcm_.push_back(0);
            encoded++;
        }
    }
    unsigned char packet[4000];
    size_t used = 0;
    while (pcm_.size() - used >= 2 * (size_t)kOpusFrame) {
        int n = opus_encode_float(opus_, pcm_.data() + used, kOpusFrame, packet, sizeof(packet));
        if (n < 0)
            return Fail("the Opus encoder failed");
        if (!Write(packet, (size_t)n, &audio_))
            return false;
        used += 2 * kOpusFrame;
    }
    pcm_.erase(pcm_.begin(), pcm_.begin() + used);
    return true;
}

bool Mp4Writer::AddFrame(const uint32_t* pixels, int w, int h, const float* sound)
{
    if (!file_ || !error_.empty())
        return false;
    if (!EncodePicture(pixels, w, h))
        return false;
    pcm_.insert(pcm_.end(), sound, sound + 2 * kSamplesPerFrame);
    samples_ += kSamplesPerFrame;
    return EncodeSound(false);
}

std::vector<uint8_t> Mp4Writer::Moov() const
{
    const uint32_t videoScale = kFps * 1000; // a frame: 1000
    uint64_t videoMs = (uint64_t)video_.sizes.size() * 1000 / kFps;
    uint64_t audioMs = samples_ * 1000 / kRate;
    auto stbl = [](Boxes& m, const Track& t, uint32_t delta, bool keys) {
        m.Full("stts", 0, 0);
        m.U32(1);
        m.U32((uint32_t)t.sizes.size());
        m.U32(delta);
        m.End();
        if (keys) {
            m.Full("stss", 0, 0);
            m.U32((uint32_t)t.keys.size());
            for (uint32_t k : t.keys)
                m.U32(k);
            m.End();
        }
        m.Full("stsc", 0, 0);
        m.U32(1);
        m.U32(1);
        m.U32(1);
        m.U32(1);
        m.End();
        m.Full("stsz", 0, 0);
        m.U32(0);
        m.U32((uint32_t)t.sizes.size());
        for (uint32_t s : t.sizes)
            m.U32(s);
        m.End();
        bool wide = !t.offsets.empty() && t.offsets.back() > 0xffffffffull;
        m.Full(wide ? "co64" : "stco", 0, 0);
        m.U32((uint32_t)t.offsets.size());
        for (uint64_t o : t.offsets) {
            if (wide)
                m.U64(o);
            else
                m.U32((uint32_t)o);
        }
        m.End();
    };
    auto dinf = [](Boxes& m) {
        m.Begin("dinf");
        m.Full("dref", 0, 0);
        m.U32(1);
        m.Full("url ", 0, 1);
        m.End();
        m.End();
        m.End();
    };
    auto tkhd = [](Boxes& m, int id, uint64_t ms, bool audio, int w, int h) {
        m.Full("tkhd", 0, 3);
        m.U32(0);
        m.U32(0);
        m.U32((uint32_t)id);
        m.U32(0);
        m.U32((uint32_t)ms);
        m.Zeros(8);
        m.U16(0);
        m.U16(0);
        m.U16(audio ? 0x100 : 0);
        m.U16(0);
        m.Matrix();
        m.U32((uint32_t)w << 16);
        m.U32((uint32_t)h << 16);
        m.End();
    };
    auto mdhd = [](Boxes& m, uint32_t scale, uint64_t duration) {
        m.Full("mdhd", 0, 0);
        m.U32(0);
        m.U32(0);
        m.U32(scale);
        m.U32((uint32_t)duration);
        m.U16(0x55c4); // "und"
        m.U16(0);
        m.End();
    };
    auto hdlr = [](Boxes& m, const char* type, const char* name) {
        m.Full("hdlr", 0, 0);
        m.U32(0);
        m.Four(type);
        m.Zeros(12);
        m.Bytes(name, strlen(name) + 1);
        m.End();
    };

    Boxes m;
    m.Begin("moov");
    m.Full("mvhd", 0, 0);
    m.U32(0);
    m.U32(0);
    m.U32(1000);
    m.U32((uint32_t)(videoMs > audioMs ? videoMs : audioMs));
    m.U32(0x10000);
    m.U16(0x100);
    m.Zeros(10);
    m.Matrix();
    m.Zeros(24);
    m.U32(3);
    m.End();

    // The pictures.
    m.Begin("trak");
    tkhd(m, 1, videoMs, false, width_, height_);
    m.Begin("mdia");
    mdhd(m, videoScale, (uint64_t)video_.sizes.size() * 1000);
    hdlr(m, "vide", "VideoHandler");
    m.Begin("minf");
    m.Full("vmhd", 0, 1);
    m.Zeros(8);
    m.End();
    dinf(m);
    m.Begin("stbl");
    m.Full("stsd", 0, 0);
    m.U32(1);
    m.Begin("avc1");
    m.Zeros(6);
    m.U16(1);
    m.Zeros(16);
    m.U16((uint32_t)width_);
    m.U16((uint32_t)height_);
    m.U32(0x480000);
    m.U32(0x480000);
    m.U32(0);
    m.U16(1);
    m.Zeros(32);
    m.U16(0x18);
    m.U16(0xffff);
    m.Begin("avcC");
    m.U8(1);
    m.U8(sps_.size() > 3 ? sps_[1] : 66);
    m.U8(sps_.size() > 3 ? sps_[2] : 0);
    m.U8(sps_.size() > 3 ? sps_[3] : 30);
    m.U8(0xff);
    m.U8(0xe1);
    m.U16((uint32_t)sps_.size());
    m.Bytes(sps_.data(), sps_.size());
    m.U8(1);
    m.U16((uint32_t)pps_.size());
    m.Bytes(pps_.data(), pps_.size());
    m.End();
    m.Begin("colr"); // BT.709, limited range
    m.Four("nclx");
    m.U16(1);
    m.U16(1);
    m.U16(1);
    m.U8(0);
    m.End();
    m.End();
    m.End();
    stbl(m, video_, 1000, true);
    m.End();
    m.End();
    m.End();
    m.End();

    // The sound.
    m.Begin("trak");
    tkhd(m, 2, audioMs, true, 0, 0);
    m.Begin("edts"); // from after the encoder's lookahead, as long as the sound given
    m.Full("elst", 0, 0);
    m.U32(1);
    m.U32((uint32_t)audioMs);
    m.U32((uint32_t)preSkip_);
    m.U32(0x10000);
    m.End();
    m.End();
    m.Begin("mdia");
    mdhd(m, kRate, (uint64_t)audio_.sizes.size() * kOpusFrame);
    hdlr(m, "soun", "SoundHandler");
    m.Begin("minf");
    m.Full("smhd", 0, 0);
    m.U32(0);
    m.End();
    dinf(m);
    m.Begin("stbl");
    m.Full("stsd", 0, 0);
    m.U32(1);
    m.Begin("Opus");
    m.Zeros(6);
    m.U16(1);
    m.Zeros(8);
    m.U16(2);
    m.U16(16);
    m.U16(0);
    m.U16(0);
    m.U32((uint32_t)kRate << 16);
    m.Begin("dOps");
    m.U8(0);
    m.U8(2);
    m.U16((uint32_t)preSkip_);
    m.U32(kRate);
    m.U16(0);
    m.U8(0);
    m.End();
    m.End();
    m.End();
    stbl(m, audio_, kOpusFrame, false);
    m.End();
    m.End();
    m.End();
    m.End();
    m.End();
    return m.b;
}

bool Mp4Writer::Close()
{
    if (!file_)
        return Fail("the file isn't open");
    if (!error_.empty() || video_.sizes.empty() || !EncodeSound(true)) {
        Abandon();
        return Fail("no frames");
    }
    std::vector<uint8_t> moov = Moov();
    uint64_t mdatSize = at_ - mdatStart_;
    bool ok = Write(moov.data(), moov.size(), nullptr);
    uint8_t size[8];
    for (int i = 0; i < 8; i++)
        size[i] = (uint8_t)(mdatSize >> (56 - 8 * i));
    ok = ok && fseek(file_, (long)(mdatStart_ + 8), SEEK_SET) == 0 &&
         fwrite(size, 1, 8, file_) == 8;
    ok = fclose(file_) == 0 && ok;
    file_ = nullptr;
    if (ok) {
        SDL_RemovePath(path_.c_str());
        ok = SDL_RenamePath(temp_.c_str(), path_.c_str());
    }
    if (!ok) {
        SDL_RemovePath(temp_.c_str());
        Abandon();
        return Fail("can't write " + path_);
    }
    Abandon();
    return true;
}

} // namespace efz
