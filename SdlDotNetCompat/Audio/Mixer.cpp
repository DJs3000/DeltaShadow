#include "Mixer.h"

#include "SdlDotNetCompat/Graphics/Video.h"

#include <SDL.h>
#include <SDL_mixer.h>

namespace SdlDotNetCompat {
namespace Audio {

bool Mixer::isOpen = false;
bool Mixer::isInitialized = Mixer::Initialize();

bool Mixer::Initialize()
{
   SdlDotNetCompat::Graphics::Video::Initialize();

   if (SDL_Init(SDL_INIT_AUDIO) != 0)
   {
      return false;
   }
   else
   {
      Mixer::OpenInternal();
      return true;
   }
}

Mix_Chunk *Mixer::Load(const std::string &file)
{
   SDL_RWops *f = SDL_RWFromFile(file.c_str(), "rb");
   Mix_Chunk *chunk = Mix_LoadWAV_RW(f, 0);

   return chunk;
}

Mix_Music *Mixer::LoadMusic(const std::string &fileName)
{
   Mix_Music *h = Mix_LoadMUS(fileName.c_str());

   return h;
}

bool Mixer::OpenInternal()
{
   if (!isOpen)
   {
      Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

      isOpen = true;
   }

   return isOpen;
}

int Mixer::FindAvailableChannel()
{
   return Mix_GroupAvailable(-1);
}

} // namespace Audio
} // namespace SdlDotNetCompat
