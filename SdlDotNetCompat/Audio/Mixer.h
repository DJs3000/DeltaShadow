#ifndef MIXER_H
#define MIXER_H

#include <string>

#include "SDL_mixer.h"

namespace SdlDotNetCompat {
namespace Audio {

class Mixer
{
public:

   static bool Initialize();

   static Mix_Chunk *Load(const std::string &file);

   static Mix_Music *LoadMusic(const std::string &fileName);

   static bool OpenInternal();

   static int FindAvailableChannel();

private:
   static bool isOpen;
   static bool isInitialized;
};

} // namespace Audio
} // namespace SdlDotNetCompat

#endif // MIXER_H
