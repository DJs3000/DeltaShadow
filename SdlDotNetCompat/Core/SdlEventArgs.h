#ifndef SDLEVENTARGS_H
#define SDLEVENTARGS_H

#include "SDL_events.h"

namespace SdlDotNetCompat {
namespace Core {

class SdlEventArgs
{
public:
   SdlEventArgs();
   SdlEventArgs(const SDL_Event &event);
   virtual ~SdlEventArgs() = default;

   Uint8 Type() const { return eventStruct.type; }

protected:
   SDL_Event eventStruct;
};

} // namespace Core
} // namespace SdlDotNetCompat

#endif // SDLEVENTARGS_H
