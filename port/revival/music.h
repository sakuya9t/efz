// EfzRevival's music (revival/EfzRevival/Music.cpp, MusicList.cpp): the files of
// EfzRevival.ini's [Global] BGMFolder (.wav, .mp3, .ogg, .flac; Revival also plays .wma,
// through DirectShow, which this can't) in random order in place of the game's music on
// match setup and in the fight, a new one each match; MuteBGM, and ToggleBGM to turn the
// music off and on. The game's music calls come here first (sound.cpp's CSound::Play,
// SetVolume and Stop); the files play through sound.cpp's mixer.
#ifndef EFZ_REVIVAL_MUSIC_H
#define EFZ_REVIVAL_MUSIC_H

namespace efz {
namespace revival {

// main.cpp, out of the compatibility harness: the playlist read, and the hooks set.
// tournament: Revival's tournament has no custom music (MuteBGM still holds).
void InitMusic(bool tournament);
// Each real frame, before the game's: a new file on match setup, the file again once it
// has played to its end in a fight, ToggleBGM.
void MusicFrame();
// OPTIONS changed MuteBGM or EfzRevival's features: the music on or off as they now say.
void ApplyMusicSettings();
// sound.cpp: the game playing, changing the volume of, or stopping sound `id`. True when
// this did it instead (or chose that it isn't heard).
bool MusicPlay(unsigned short id, int loop);
bool MusicSetVolume(unsigned short id, int volume);
bool MusicStop(unsigned short id);
// sound.cpp's mixer: the music's samples added to out (stereo), at `rate`. Called with
// the audio locked.
void MixMusic(float* out, int frames, int rate);

} // namespace revival
} // namespace efz

#endif
