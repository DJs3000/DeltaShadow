#ifndef KEYBOARDEVENTARGS_H
#define KEYBOARDEVENTARGS_H

#include "SdlDotNetCompat/Core/SdlEventArgs.h"
#include "SdlDotNetCompat/Input/Keyboard.h"

namespace SdlDotNetCompat {
namespace Input {

class KeyboardEventArgs : public SdlDotNetCompat::Core::SdlEventArgs
{
public:
   KeyboardEventArgs(const SDL_Event &event);

   SdlDotNetCompat::Input::Key Key() const;

   int Mod() const;
};

} // namespace Input
} // namespace SdlDotNetCompat

#endif // KEYBOARDEVENTARGS_H
