#include "VideoResizeEventArgs.h"

namespace SdlDotNetCompat {
namespace Graphics {

VideoResizeEventArgs::VideoResizeEventArgs(const SDL_Event &event)
   :SdlEventArgs(event)
{

}

int VideoResizeEventArgs::Width() const
{
   return eventStruct.resize.w;
}

int VideoResizeEventArgs::Height() const
{
   return eventStruct.resize.h;
}

} // namespace Graphics
} // namespace SdlDotNetCompat
