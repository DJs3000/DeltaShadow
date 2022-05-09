#include "KeyboardEventArgs.h"

namespace SdlDotNetCompat {
namespace Input {

KeyboardEventArgs::KeyboardEventArgs(const SDL_Event &event)
  : SdlEventArgs(event)
{

}

SdlDotNetCompat::Input::Key KeyboardEventArgs::Key() const
{
   return static_cast<SdlDotNetCompat::Input::Key>(eventStruct.key.keysym.sym);
}

int KeyboardEventArgs::Mod() const
{
   return 0;
}

} // namespace Input
} // namespace SdlDotNetCompat
