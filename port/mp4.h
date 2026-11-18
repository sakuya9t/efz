// Video files of fights (docs/logging.md): the frames the game shows and the sound it
// plays, in an MP4 that video sites and players take as it is. Pictures are H.264
// (baseline profile, from minih264's encoder, port/minih264.c), tagged BT.709; sound is
// Opus at 48 kHz, stereo (libopus); the boxes are written here. The game's 64 frames a
// second are kept: 750 samples of sound go with each frame.
#ifndef EFZ_MP4_H
#define EFZ_MP4_H

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>

struct OpusEncoder; // libopus's

namespace efz {

class Mp4Writer {
public:
    static const int kFps = 64;
    static const int kRate = 48000;
    static const int kSamplesPerFrame = kRate / kFps; // 750

    ~Mp4Writer();
    // A file of width x height pictures (multiples of 16), written to path (through a
    // temporary file beside it until Close). False (and Error()) if it can't be.
    bool Open(const std::string& path, int width, int height);
    // A frame as the game shows it (0x00RRGGBB), scaled to the video's size, nearest
    // pixel; and its sound, kSamplesPerFrame stereo samples (left, right) at kRate.
    bool AddFrame(const uint32_t* pixels, int width, int height, const float* sound);
    // Finishes the file; false, the file removed, if it couldn't be.
    bool Close();
    void Abandon();
    const std::string& Error() const { return error_; }
    long Frames() const { return (long)video_.sizes.size(); }

private:
    struct Track {
        std::vector<uint32_t> sizes;
        std::vector<uint64_t> offsets;
        std::vector<uint32_t> keys; // video: sync samples, from 1
    };
    bool Fail(const std::string& what);
    bool Write(const void* data, size_t size, Track* track);
    bool EncodePicture(const uint32_t* pixels, int width, int height);
    bool EncodeSound(bool flush);
    std::vector<uint8_t> Moov() const;

    FILE* file_ = nullptr;
    std::string path_, temp_, error_;
    uint64_t at_ = 0;           // the file's length so far
    uint64_t mdatStart_ = 0;    // where mdat's header is
    int width_ = 0, height_ = 0;
    // H.264
    void* encoder_ = nullptr;   // minih264's persistent memory
    void* scratch_ = nullptr;
    std::vector<uint8_t> yuv_;
    std::vector<uint8_t> sps_, pps_;
    Track video_;
    // Opus
    ::OpusEncoder* opus_ = nullptr;
    int preSkip_ = 0;
    std::vector<float> pcm_;    // samples waiting for a packet of 960
    uint64_t samples_ = 0;      // the sound's samples given
    Track audio_;
};

} // namespace efz

#endif
