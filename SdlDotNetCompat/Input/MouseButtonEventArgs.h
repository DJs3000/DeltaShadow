#ifndef MOUSEBUTTONEVENTARGS_H
#define MOUSEBUTTONEVENTARGS_H

#include "SdlDotNetCompat/Core/SdlEventArgs.h"
#include "SdlDotNetCompat/Input/Mouse.h"

namespace SdlDotNetCompat {
namespace Input {

class MouseButtonEventArgs : public SdlDotNetCompat::Core::SdlEventArgs
{
public:
   MouseButtonEventArgs(const SDL_Event &event);

   MouseButton Button() const;

};

} // namespace Input
} // namespace SdlDotNetCompat

#endif // MOUSEBUTTONEVENTARGS_H
