#ifndef QUITEVENTARGS_H
#define QUITEVENTARGS_H

#include "SdlDotNetCompat/Core/SdlEventArgs.h"

namespace SdlDotNetCompat {
namespace Core {

class QuitEventArgs : public SdlDotNetCompat::Core::SdlEventArgs
{
public:
   QuitEventArgs();
   QuitEventArgs(const SDL_Event &event);
};

} // namespace Core
} // namespace SdlDotNetCompat

#endif // QUITEVENTARGS_H
