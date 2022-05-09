#include "VideoInfo.h"

#include "SdlDotNetCompat/Core/SdlException.h"
#include "SDL.h"

namespace SdlDotNetCompat {
namespace Graphics {

const SDL_VideoInfo *VideoInfoStruct()
{
   const SDL_VideoInfo *ptr = SDL_GetVideoInfo();
   if (ptr == nullptr)
   {
      throw Core::SdlException(SDL_GetError());
   }
   return ptr;
}

const SDL_PixelFormat *PixelFormat()
{
   const SDL_VideoInfo *ptr = SDL_GetVideoInfo();
   return ptr->vfmt;
}

uint8_t VideoInfo::BitsPerPixel()
{
   return PixelFormat()->BitsPerPixel;
}

uint8_t VideoInfo::BytesPerPixel()
{
   return PixelFormat()->BytesPerPixel;
}

uint32_t VideoInfo::AlphaMask()
{
   return PixelFormat()->Amask;
}

uint32_t VideoInfo::RedMask()
{
   return PixelFormat()->Rmask;
}

uint32_t VideoInfo::GreenMask()
{
   return PixelFormat()->Gmask;
}

uint32_t VideoInfo::BlueMask()
{
   return PixelFormat()->Bmask;
}

uint8_t VideoInfo::AlphaShift()
{
   return PixelFormat()->Ashift;
}

uint8_t VideoInfo::RedShift()
{
   return PixelFormat()->Rshift;
}

uint8_t VideoInfo::GreenShift()
{
   return PixelFormat()->Gshift;
}

uint8_t VideoInfo::BlueShift()
{
   return PixelFormat()->Bshift;
}

uint8_t VideoInfo::AlphaLoss()
{
   return PixelFormat()->Aloss;
}

uint8_t VideoInfo::RedLoss()
{
   return PixelFormat()->Rloss;
}

uint8_t VideoInfo::GreenLoss()
{
   return PixelFormat()->Gloss;
}

uint8_t VideoInfo::BlueLoss()
{
   return PixelFormat()->Bloss;
}

bool VideoInfo::HasHardwareSurfaces()
{
   return (VideoInfoStruct()->hw_available == 1);
}

bool VideoInfo::HasWindowManager()
{
   return (VideoInfoStruct()->wm_available == 1);
}

bool VideoInfo::HasHardwareBlits()
{
   return (VideoInfoStruct()->blit_hw == 1);
}

bool VideoInfo::HasHardwareColorKeyBlits()
{
   return (VideoInfoStruct()->blit_hw_CC == 1);
}

bool VideoInfo::HasHardwareAlphaBlits()
{
   return (VideoInfoStruct()->blit_hw_A == 1);
}

bool VideoInfo::HasSoftwareBlits()
{
   return (VideoInfoStruct()->blit_sw == 1);
}

bool VideoInfo::HasSoftwareColorKeyBlits()
{
   return (VideoInfoStruct()->blit_sw_CC == 1);
}

bool VideoInfo::HasSoftwareAlphaBlits()
{
   return (VideoInfoStruct()->blit_sw_A == 1);
}

bool VideoInfo::HasColorFills()
{
   return (VideoInfoStruct()->blit_fill == 1);
}

uint32_t VideoInfo::VideoMemory()
{
   return VideoInfoStruct()->video_mem;
}

int VideoInfo::ScreenHeight()
{
   return VideoInfoStruct()->current_h;
}

int VideoInfo::ScreenWidth()
{
   return VideoInfoStruct()->current_w;
}


} // namespace Graphics
} // namespace SdlDotNetCompat
