#ifndef USEREVENTARGS_H
#define USEREVENTARGS_H

#include "SdlDotNetCompat/Core/SdlEventArgs.h"

namespace SdlDotNetCompat {
namespace Core {

class UserEventArgs : public SdlDotNetCompat::Core::SdlEventArgs
{
public:
   UserEventArgs();

   UserEventArgs(const SDL_Event &event);

   int UserCode() const;
};

} // namespace Core
} // namespace SdlDotNetCompat

#endif // USEREVENTARGS_H
