#include "VideoExposeEventArgs.h"

namespace SdlDotNetCompat {
namespace Graphics {

VideoExposeEventArgs::VideoExposeEventArgs(const SDL_Event &event)
  : SdlEventArgs(event)
{

}

} // namespace Graphics
} // namespace SdlDotNetCompat
