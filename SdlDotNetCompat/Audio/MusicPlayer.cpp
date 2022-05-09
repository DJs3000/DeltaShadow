#include "MusicPlayer.h"

#include "SDL_mixer.h"

namespace SdlDotNetCompat {
namespace Audio {

SdlDotNetCompat::Audio::Music MusicPlayer::m_music;

void MusicPlayer::SetCurrentMusic(const SdlDotNetCompat::Audio::Music &music)
{
   m_music = music;
}

void *MusicPlayer::CurrentMusic()
{
   return m_music.Handle();
}

void MusicPlayer::Play(int numberOfTimes)
{
   if (Mix_Music *hMusic = static_cast<Mix_Music*>(m_music.Handle()))
   {
      Mix_PlayMusic(hMusic, numberOfTimes);
   }
}

void MusicPlayer::Stop()
{
   Mix_HaltMusic();
}

void MusicPlayer::Pause()
{
   Mix_PauseMusic();
}

void MusicPlayer::Resume()
{
   Mix_ResumeMusic();
}

} // namespace Audio
} // namespace sdlDotNetCompat
