#include "Music.h"

#include "Mixer.h"

#include "SDL_mixer.h"

namespace SdlDotNetCompat {
namespace Audio {

} // namespace Audio
} // namespace SdlDotNetCompat


SdlDotNetCompat::Audio::Music::Music()
{
   SetHandle(NULL);
}

SdlDotNetCompat::Audio::Music::Music(const std::string &fileName)
{
   Mix_Music *h = Mixer::LoadMusic(fileName);

   SetHandle(h);
}

SdlDotNetCompat::Audio::Music::Music(const char *data, int length)
{
   Mix_Music *h = Mix_LoadMUS_RW(SDL_RWFromConstMem(data, length));

   SetHandle(h);
}

void SdlDotNetCompat::Audio::Music::CloseHandle()
{
   if (Mix_Music *hMusic = static_cast<Mix_Music*>(Handle()))
   {
      Mix_FreeMusic(hMusic);
      SetHandle(nullptr);
   }
}
