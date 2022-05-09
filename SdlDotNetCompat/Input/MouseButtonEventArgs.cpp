#include "MouseButtonEventArgs.h"

namespace SdlDotNetCompat {
namespace Input {

MouseButtonEventArgs::MouseButtonEventArgs(const SDL_Event &event)
  : SdlEventArgs(event)
{

}

MouseButton MouseButtonEventArgs::Button() const
{
   return static_cast<MouseButton>(eventStruct.button.button);
}

} // namespace Input
} // namespace SdlDotNetCompat
