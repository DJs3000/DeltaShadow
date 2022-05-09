#include "SdlEventArgs.h"

namespace SdlDotNetCompat {
namespace Core {

SdlEventArgs::SdlEventArgs()
{
}

SdlEventArgs::SdlEventArgs(const SDL_Event &event)
 : eventStruct(event)
{
}

} // namespace Core
} // namespace SdlDotNetCompat
