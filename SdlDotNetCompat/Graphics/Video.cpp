#include "Video.h"

#include "VideoInfo.h"

#include "SDL.h"

namespace SdlDotNetCompat {
namespace Graphics {

namespace
{
   enum VideoModes
   {
      None             = SDL_SWSURFACE
    , HardwareSurface  = SDL_HWSURFACE
    , AsynchronousBlit = SDL_ASYNCBLIT
    , HardwarePalette  = SDL_HWPALETTE
    , DoubleBuffering  = SDL_DOUBLEBUF
    , FullScreen       = SDL_FULLSCREEN
    , OpenGL           = SDL_OPENGL
    , Resizable        = SDL_RESIZABLE
    , NoFrame          = SDL_NOFRAME
   };

   const int USE_CURRENT_BPP = 0;
}

bool Video::Initialize()
{
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
   {
      return false;
   }
   else
   {
      return true;
   }
}

bool Video::IsVideoModeOk(int width, int height, bool fullScreen, int bitsPerPixel)
{
   VideoModes flags = VideoModes::None;

   if (fullScreen)
   {
      flags = VideoModes::FullScreen;
   }

   const int result = SDL_VideoModeOK(width, height, bitsPerPixel, flags);

   return result == bitsPerPixel;
}

int Video::BestBitsPerPixel(int width, int height, bool fullScreen)
{
   VideoModes flags = VideoModes::None;

   if (fullScreen)
   {
      flags = VideoModes::FullScreen;
   }

   return SDL_VideoModeOK(width, height, VideoInfo::BitsPerPixel(), static_cast<Uint32>(flags));
}

Surface Video::SetVideoMode()
{
   return Video::SetVideoMode(0, 0, USE_CURRENT_BPP, false, false, false, false, true);
}

Surface Video::SetVideoMode(int width, int height)
{
   return SetVideoMode(width, height, USE_CURRENT_BPP, false, false, false, false, true);
}

Surface Video::SetVideoMode(int width, int height, int bitsPerPixel)
{
   return SetVideoMode(width, height, bitsPerPixel, false, false, false, false, true);
}

Surface Video::SetVideoMode(int width, int height, bool resizable)
{
   return SetVideoMode(width, height, USE_CURRENT_BPP, resizable, false, false, false, true);
}

Surface Video::SetVideoMode(int width, int height, int bitsPerPixel, bool resizable)
{
   return SetVideoMode(width, height, bitsPerPixel, resizable, false, false, false, true);
}

Surface Video::SetVideoMode(int width, int height, bool resizable, bool openGL)
{
   return SetVideoMode(width, height, USE_CURRENT_BPP, resizable, openGL, false, false, true);
}

Surface Video::SetVideoMode(int width, int height, int bitsPerPixel, bool resizable, bool openGL)
{
   return SetVideoMode(width, height, bitsPerPixel, resizable, openGL, false, false, true);
}

Surface Video::SetVideoMode(int width, int height, bool resizable, bool openGL, bool fullScreen)
{
   return SetVideoMode(width, height, USE_CURRENT_BPP, resizable, openGL, fullScreen, false, true);
}

Surface Video::SetVideoMode(int width, int height, int bitsPerPixel, bool resizable, bool openGL, bool fullScreen)
{
   return SetVideoMode(width, height, bitsPerPixel, resizable, openGL, fullScreen, false, true);
}

Surface Video::SetVideoMode(int width, int height, bool resizable, bool openGL, bool fullScreen, bool hardwareSurface)
{
   return SetVideoMode(width, height, USE_CURRENT_BPP, resizable, openGL, fullScreen, hardwareSurface, true);
}

Surface Video::SetVideoMode(int width, int height, int bitsPerPixel, bool resizable, bool openGL, bool fullScreen, bool hardwareSurface)
{
   return SetVideoMode(width, height, bitsPerPixel, resizable, openGL, fullScreen, hardwareSurface, true);
}

Surface Video::SetVideoMode(int width, int height, bool resizable, bool openGL, bool fullScreen, bool hardwareSurface, bool frame)
{
   return SetVideoMode(width, height, USE_CURRENT_BPP, resizable, openGL, fullScreen, hardwareSurface, frame);
}

Surface Video::SetVideoMode(int width, int height, int bitsPerPixel, bool resizable, bool openGL, bool fullScreen, bool hardwareSurface, bool frame)
{
   Uint32 flags = VideoModes::None;

   if (hardwareSurface)
   {
      flags |= VideoModes::HardwareSurface;
      flags |= VideoModes::DoubleBuffering;
   }
   if (fullScreen)
   {
      flags |= VideoModes::FullScreen;
   }
   if (openGL)
   {
      flags |= VideoModes::OpenGL;
   }
   if (resizable)
   {
      flags |= VideoModes::Resizable;
   }
   if (!frame)
   {
      flags |= VideoModes::NoFrame;
   }

   // https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlsetvideomode.html

   SDL_Surface *surface = SDL_SetVideoMode(width, height, bitsPerPixel, static_cast<Uint32>(flags));

   return Surface(surface);
}

void Video::SetWindowCaption(const std::string &caption)
{
   SDL_WM_SetCaption(caption.c_str(), "");
}

Surface Video::Screen()
{
   return Surface(SDL_GetVideoSurface());
}

} // namespace Graphics
} // namespace SdlDotNetCompat
