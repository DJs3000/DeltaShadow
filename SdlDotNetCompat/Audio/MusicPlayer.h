#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "SdlDotNetCompat/Audio/Music.h"

namespace SdlDotNetCompat {
namespace Audio {

class Music;

class MusicPlayer
{
public:
   static void SetCurrentMusic(const SdlDotNetCompat::Audio::Music &music);

   static void *CurrentMusic();

   static void Play(bool continuous)
   {
      if (continuous)
      {
         Play(-1);
      }
      else
      {
         Play(1);
      }
   }

   static void Play(int numberOfTimes);

   static void Stop();

   static void Pause();

   static void Resume();

private:
   static SdlDotNetCompat::Audio::Music m_music;

   MusicPlayer() = delete;
};


} // namespace Audio
} // namespace SdlDotNetCompat

#endif // MUSICPLAYER_H
