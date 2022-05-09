#include "Sound.h"
#include "SdlDotNetCompat/Audio/Mixer.h"
#include "SdlDotNetCompat/Core/Events.h"
#include <SDL_mixer.h>

namespace SdlDotNetCompat {
namespace Audio {

Sound::Sound(const std::string &file)
{
   Mixer::OpenInternal();

   Mix_Chunk *hSound = Mixer::Load(file);

   SetHandle(hSound);
}

void Sound::Dispose()
{
   CloseHandle();
}

void Sound::Play()
{
   Sound::Play(0);
}

void Sound::Play(int loops)
{
   Sound::Play(loops, SdlDotNetCompat::Core::SdlFlag::InfiniteLoop);
}

void Sound::Play(int loops, int milliseconds)
{
   if (Mix_Chunk *hSound = static_cast<Mix_Chunk*>(Handle()))
   {

   int channel = Mixer::FindAvailableChannel();

   Mix_PlayChannelTimed(channel, hSound, loops, milliseconds);
   }
}

void Sound::Play(bool loopIndefinitely)
{
   if (loopIndefinitely)
   {
      Play(-1, SdlDotNetCompat::Core::SdlFlag::InfiniteLoop);
   }
   else
   {
      Play(0);
   }
}

} // namespace Audio
} // namespace SdlDotNetCompat


void SdlDotNetCompat::Audio::Sound::CloseHandle()
{
   if (Mix_Chunk *hSound = static_cast<Mix_Chunk*>(Handle()))
   {
      Mix_FreeChunk(hSound);
      SetHandle(NULL);
   }
}
