#ifndef ACTIVEEVENTARGS_H
#define ACTIVEEVENTARGS_H

#include "SdlDotNetCompat/Core/SdlEventArgs.h"
#include "SdlDotNetCompat/Input/Keyboard.h"

namespace SdlDotNetCompat {
namespace Input {

class ActiveEventArgs : public SdlDotNetCompat::Core::SdlEventArgs
{
public:
   ActiveEventArgs(const SDL_Event &event);

   bool GainedFocus() const;

   Focus::Enum State() const;
};

} // namespace Input
} // namespace SdlDotNetCompat

#endif // ACTIVEEVENTARGS_H
