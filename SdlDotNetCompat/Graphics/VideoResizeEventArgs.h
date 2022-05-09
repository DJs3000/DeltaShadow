#ifndef VIDEORESIZEEVENTARGS_H
#define VIDEORESIZEEVENTARGS_H

#include "SdlDotNetCompat/Core/SdlEventArgs.h"


namespace SdlDotNetCompat {
namespace Graphics {

class VideoResizeEventArgs : public SdlDotNetCompat::Core::SdlEventArgs
{
public:
   VideoResizeEventArgs(const SDL_Event &event);

   int Width() const;

   int Height() const;
};

} // namespace Graphics
} // namespace SdlDotNetCompat

#endif // VIDEORESIZEEVENTARGS_H
