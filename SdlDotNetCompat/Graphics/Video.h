#ifndef VIDEO_H
#define VIDEO_H

#include "SdlDotNetCompat/Graphics/Surface.h"

namespace SdlDotNetCompat {
namespace Graphics {

class Video
{
public:

   static bool Initialize();

   static bool IsVideoModeOk(int width, int height, bool fullScreen, int bitsPerPixel);

   static bool IsActive () { return false; }

   static int BestBitsPerPixel(int width, int height, bool fullScreen );

   static Surface SetVideoMode();

   static Surface SetVideoMode(int width, int height);

   static Surface SetVideoMode(int width, int height, int bitsPerPixel);

   static Surface SetVideoMode(int width, int height, bool resizable);

   static Surface SetVideoMode(int width, int height, int bitsPerPixel, bool resizable);

   static Surface SetVideoMode(int width, int height, bool resizable, bool openGL);

   static Surface SetVideoMode(int width, int height, int bitsPerPixel, bool resizable, bool openGL);

   static Surface SetVideoMode(int width, int height, bool resizable, bool openGL, bool fullScreen);

   static Surface SetVideoMode(int width, int height, int bitsPerPixel, bool resizable, bool openGL, bool fullScreen);

   static Surface SetVideoMode(int width, int height, bool resizable, bool openGL, bool fullScreen, bool hardwareSurface);

   static Surface SetVideoMode(int width, int height, int bitsPerPixel, bool resizable, bool openGL, bool fullScreen, bool hardwareSurface);

   static Surface SetVideoMode(int width, int height, bool resizable, bool openGL, bool fullScreen, bool hardwareSurface, bool frame);

   static Surface SetVideoMode(int width, int height, int bitsPerPixel, bool resizable, bool openGL, bool fullScreen, bool hardwareSurface, bool frame);

   static void SetWindowCaption(const std::string &caption);

   static Surface Screen();

private:

};

} // namespace Graphics
} // namespace SdlDotNetCompat

#endif // VIDEO_H
