#ifndef MOUSEMOTIONEVENTARGS_H
#define MOUSEMOTIONEVENTARGS_H

#include "SdlDotNetCompat/Input/Mouse.h"
#include "SdlDotNetCompat/Core/SdlEventArgs.h"

namespace SdlDotNetCompat {
namespace Input {

class MouseMotionEventArgs : public SdlDotNetCompat::Core::SdlEventArgs
{
public:
   MouseMotionEventArgs();
   MouseMotionEventArgs(const SDL_Event &event);

   bool ButtonPressed() const;

   MouseButton Button() const;
};

} // namespace Input
} // namespace SdlDotNetCompat

#endif // MOUSEMOTIONEVENTARGS_H
