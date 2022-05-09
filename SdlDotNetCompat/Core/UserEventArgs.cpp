#include "UserEventArgs.h"

namespace SdlDotNetCompat {
namespace Core {

UserEventArgs::UserEventArgs()
{
   // TODO
}

UserEventArgs::UserEventArgs(const SDL_Event &event)
   : SdlEventArgs(event)
{

}

int UserEventArgs::UserCode() const
{
   return eventStruct.user.code;
}

} // namespace Core
} // namespace SdlDotNetCompat
