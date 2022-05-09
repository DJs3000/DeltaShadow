#include "QuitEventArgs.h"

namespace SdlDotNetCompat {
namespace Core {

QuitEventArgs::QuitEventArgs()
{

}

QuitEventArgs::QuitEventArgs(const SDL_Event &event)
   : SdlEventArgs(event)
{

}

} // namespace Core
} // namespace SdlDotNetCompat
