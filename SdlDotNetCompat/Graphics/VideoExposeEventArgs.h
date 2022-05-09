#ifndef VIDEOEXPOSEEVENTARGS_H
#define VIDEOEXPOSEEVENTARGS_H

#include "SdlDotNetCompat/Core/SdlEventArgs.h"

namespace SdlDotNetCompat {
namespace Graphics {

class VideoExposeEventArgs : public SdlDotNetCompat::Core::SdlEventArgs
{
public:
   VideoExposeEventArgs(const SDL_Event &event);
};

} // namespace Graphics
} // namespace SdlDotNetCompat

#endif // VIDEOEXPOSEEVENTARGS_H
