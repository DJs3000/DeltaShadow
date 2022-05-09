#include "MouseMotionEventArgs.h"

namespace SdlDotNetCompat {
namespace Input {

MouseMotionEventArgs::MouseMotionEventArgs()
{

}

MouseMotionEventArgs::MouseMotionEventArgs(const SDL_Event &event)
  : SdlEventArgs(event)
{

}

bool MouseMotionEventArgs::ButtonPressed() const
{
   return (eventStruct.motion.state != ButtonKeyState::NotPressed);
}

MouseButton MouseMotionEventArgs::Button() const
{

}

} // namespace Input
} // namespace SdlDotNetCompat
