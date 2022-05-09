#ifndef MUSIC_H
#define MUSIC_H

#include "SdlDotNetCompat/Core/BaseSdlResource.h"

#include <string>

namespace SdlDotNetCompat {
namespace Audio {

class Music : public SdlDotNetCompat::Core::BaseSdlResource
{
public:
   Music();

   Music(const std::string &fileName);

   Music(const char* data, int length);

   // BaseSdlResource interface
protected:
   virtual void CloseHandle() override;
};

} // namespace Audio
} // namespace SdlDotNetCompat

#endif // MUSIC_H
