#ifndef SOUND_H
#define SOUND_H

#include "SdlDotNetCompat/Core/BaseSdlResource.h"
#include <string>

namespace SdlDotNetCompat {
namespace Audio {

class Sound : public SdlDotNetCompat::Core::BaseSdlResource
{
public:
   Sound(const std::string &file);

   void Dispose();

   void Play();

   void Play(int loops);

   void Play(int loops, int milliseconds);

   void Play(bool loopIndefinitely);

   // BaseSdlResource interface
protected:
   virtual void CloseHandle() override;
};

} // namespace Audio
} // namespace SdlDotNetCompat

#endif // SOUND_H
