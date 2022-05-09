#include "ActiveEventArgs.h"

namespace SdlDotNetCompat {
namespace Input {

ActiveEventArgs::ActiveEventArgs(const SDL_Event &event)
 : SdlEventArgs(event)
{

}

bool ActiveEventArgs::GainedFocus() const
{
   return (eventStruct.active.gain != 0);
}

Focus::Enum ActiveEventArgs::State() const
{
   return static_cast<Focus::Enum>(eventStruct.active.state);
}

} // namespace Input
} // namespace SdlDotNetCompat
