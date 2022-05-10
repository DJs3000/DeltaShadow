#include "Surface.h"

#include "VideoInfo.h"
#include "SdlDotNetCompat/Core/Events.h"
#include "SdlDotNetCompat/Core/SdlException.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_video.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>

#include <cstring>

namespace SdlDotNetCompat {
namespace Graphics {

namespace
{
   SDL_Rect ConvertRectToSdlRect(const SdlDotNetCompat::Drawing::Rectangle &rect)
   {
      SDL_Rect res;

      res.x = rect.X();
      res.y = rect.Y();
      res.w = rect.Width();
      res.h = rect.Height();

      return res;
   }

   class SurfaceLocker
   {
   public:
      SurfaceLocker(SDL_Surface *s)
         : m_surface(s)
      {
         if (SDL_MUSTLOCK(m_surface) != 0)
         {
            locked = SDL_LockSurface(m_surface);
         }
      }

     ~SurfaceLocker()
      {
         if (locked)
         {
            SDL_UnlockSurface(m_surface);
         }
      }

   private:
      SDL_Surface *m_surface;
      bool locked = false;
   };
}

Surface::Surface(SDL_Surface *handle)
{
   SetHandle(handle);
}

Surface::Surface(const std::string &file)
{
   if (SDL_Surface *h = IMG_Load(file.c_str()))
   {
      SetHandle(h);
   }
   else
   {      
      throw Core::SdlException(SDL_GetError());
   }
}

Surface::Surface(const SdlDotNetCompat::Drawing::Size &size)
   : Surface(size.Width, size.Height)
{ }

Surface::Surface(const SdlDotNetCompat::Drawing::Rectangle &rectangle)
   : Surface(rectangle.Width(), rectangle.Height())
{ }

Surface::Surface(int width, int height)
   : Surface(width, height, VideoInfo::BitsPerPixel())
{ }

Surface::Surface(int width, int height, int bitsPerPixel)
   : Surface(width, height, bitsPerPixel, VideoInfo::RedMask(), VideoInfo::GreenMask(), VideoInfo::BlueMask(), VideoInfo::AlphaMask())
{ }

Surface::Surface(int width, int height, int bitsPerPixel, uint32_t redMask, uint32_t greenMask, uint32_t blueMask, uint32_t alphaMask)
{
   if (SDL_Surface *handle = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, bitsPerPixel, redMask, greenMask, blueMask, alphaMask))
   {
      SetHandle(handle);
   }
   else
   {
      throw Core::SdlException(SDL_GetError());
   }
}

Surface::Surface(int width, int height, int bitsPerPixel, bool alphaChannel)
   : Surface(width, height, bitsPerPixel, VideoInfo::RedMask(), VideoInfo::GreenMask(), VideoInfo::BlueMask(), alphaChannel ? VideoInfo::AlphaMask() : 0)
{ }

void Surface::Dispose()
{
   CloseHandle();
}

Surface Surface::CreateScaledSurface(double zoomX, double zoomY, bool antiAlias) const
{
   int antiAliasParam = antiAlias ? SMOOTHING_ON : SMOOTHING_OFF;

   if (SDL_Surface *surface = zoomSurface(SurfaceStruct(), zoomX, zoomY, antiAliasParam))
   {
      Surface res(surface);
      res.m_transparentColor       = m_transparentColor;
      res.m_transparentInitialized = m_transparentInitialized;
      res.m_transparent            = m_transparent;
      res.m_alpha                  = m_alpha;
      res.m_alphaBlending          = m_alphaBlending;      
      return res;
   }

   throw Core::SdlException(SDL_GetError());
}

Surface Surface::CreateScaledSurface(double zoomX, double zoomY) const
{
   return CreateScaledSurface(zoomX, zoomY, false);
}

Surface Surface::CreateScaledSurface(double zoom) const
{
   return CreateScaledSurface(zoom, zoom);
}

Surface Surface::CreateScaledSurface(double zoom, bool antiAlias) const
{
   return CreateScaledSurface(zoom, zoom, antiAlias);
}

SdlDotNetCompat::Drawing::Rectangle Surface::Blit(const Surface &sourceSurface, const SdlDotNetCompat::Drawing::Point &destinationPosition)
{
   return Blit(sourceSurface, destinationPosition, SdlDotNetCompat::Drawing::Rectangle(0, 0, sourceSurface.Width(), sourceSurface.Height()));
}

SdlDotNetCompat::Drawing::Rectangle Surface::Blit(const Surface &sourceSurface, const SdlDotNetCompat::Drawing::Rectangle &destinationRectangle)
{
   return Blit(sourceSurface, destinationRectangle.Location(), SdlDotNetCompat::Drawing::Rectangle(0, 0, sourceSurface.Width(), sourceSurface.Height()));
}

SdlDotNetCompat::Drawing::Rectangle Surface::Blit(const Surface &sourceSurface, const SdlDotNetCompat::Drawing::Rectangle &destinationRectangle, const SdlDotNetCompat::Drawing::Rectangle &sourceRectangle)
{
   SDL_Rect s = ConvertRectToSdlRect(sourceRectangle);
   SDL_Rect d = ConvertRectToSdlRect(destinationRectangle);
   int result = SDL_BlitSurface(sourceSurface.SurfaceStruct(), &s, this->SurfaceStruct(), &d);
   if (result != Core::SdlFlag::Success)
   {
      throw Core::SdlException(SDL_GetError());
   }
   return SdlDotNetCompat::Drawing::Rectangle(d.x, d.y, d.w, d.h);
}

SdlDotNetCompat::Drawing::Rectangle Surface::Blit(const SdlDotNetCompat::Graphics::Surface &sourceSurface, const SdlDotNetCompat::Drawing::Point &destinationPosition, const SdlDotNetCompat::Drawing::Rectangle &sourceRectangle)
{
   return Blit(sourceSurface, SdlDotNetCompat::Drawing::Rectangle(destinationPosition.X, destinationPosition.Y, 0, 0), sourceRectangle);
}

void Surface::Draw(const SdlDotNetCompat::Drawing::Point &point, uint32_t color)
{
   SDL_Surface *surfaceStruct = SurfaceStruct();

   if (point.X < 0 || point.X >= surfaceStruct->w)
      return;

   if (point.Y < 0 || point.Y >= surfaceStruct->h)
      return;

   SurfaceLocker lock(surfaceStruct);

   const SDL_PixelFormat *const format = surfaceStruct->format;

   Uint8 *pixelPtr = ( reinterpret_cast<Uint8*>(surfaceStruct->pixels)
                                             + point.Y * surfaceStruct->pitch
                                             + point.X * format->BytesPerPixel );

   switch (format->BytesPerPixel)
   {
   case 1:
      *(reinterpret_cast<Uint8*>(pixelPtr)) = static_cast<Uint8>(color);
   break;

   case 2:
      *(reinterpret_cast<Uint16*>(pixelPtr)) = static_cast<Uint16>(color);
   break;

   case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
      {
         pixelPtr[0] = ((color & 0x00FF0000) >> 16);
         pixelPtr[1] = ((color & 0x0000FF00) >> 8 );
         pixelPtr[2] = ((color & 0x000000FF)      );
      }
      else
      {
         pixelPtr[0] = ((color & 0x000000FF)      );
         pixelPtr[1] = ((color & 0x0000FF00) >> 8 );
         pixelPtr[2] = ((color & 0x00FF0000) >> 16);
      }
   break;

   case 4:
      *(reinterpret_cast<Uint32*>(pixelPtr)) = color;
   break;

   }
}

void Surface::Draw(const SdlDotNetCompat::Drawing::Point &point, const SdlDotNetCompat::Drawing::Color &color)
{
   Draw(point, GetColorValue(color));
}

SdlDotNetCompat::Drawing::Rectangle Surface::Fill(const SdlDotNetCompat::Drawing::Color &color)
{
   return Fill(SdlDotNetCompat::Drawing::Rectangle(0, 0, SurfaceStruct()->w, SurfaceStruct()->h), color);
}

SdlDotNetCompat::Drawing::Rectangle Surface::Fill(const SdlDotNetCompat::Drawing::Rectangle &rectangle, const SdlDotNetCompat::Drawing::Color &color)
{
   SDL_Rect sdlrect = ConvertRectToSdlRect(rectangle);

   const int result = SDL_FillRect(SurfaceStruct(), &sdlrect, GetColorValue(color));

   if (result != Core::SdlFlag::Success)
   {
      throw Core::SdlException(SDL_GetError());
   }

   return SdlDotNetCompat::Drawing::Rectangle(sdlrect.x, sdlrect.y, sdlrect.w, sdlrect.h);
}

void Surface::SetClipRectangle(const SdlDotNetCompat::Drawing::Rectangle &rect)
{
   SDL_Rect sdlrect = ConvertRectToSdlRect(rect);
   SDL_SetClipRect(SurfaceStruct(), &sdlrect);
}

uint32_t Surface::GetColorValue(const SdlDotNetCompat::Drawing::Color &color) const
{
   SDL_Surface *surface = SurfaceStruct();

   return (surface && surface->format) ? SDL_MapRGBA(surface->format, color.R(), color.G(), color.B(), color.A())
                                       : 0;
}

int Surface::Width() const
{
   return SurfaceStruct()->w;
}

int Surface::Height() const
{
   return SurfaceStruct()->h;
}

void Surface::CopyPixels(const SdlDotNetCompat::Drawing::Point &dst, const SdlDotNetCompat::Drawing::Rectangle &source)
{
   if (SDL_Surface *surfaceStruct = SurfaceStruct())
   {
      SurfaceLocker lock(surfaceStruct);

      const SDL_PixelFormat *const format = surfaceStruct->format;

      Uint8 *pixels = reinterpret_cast<Uint8*>(surfaceStruct->pixels) + ( source.X() * format->BytesPerPixel );

      const size_t bytesPerRow = source.Width() * format->BytesPerPixel;

      m_buffer.resize(bytesPerRow * source.Height());
      uint8_t *buffer = &m_buffer[0];

      // copy from source region to buffer
      for (int y = 0; y < source.Height(); ++y)
      {
         Uint8 *srcRowPtr = pixels + ( (y + source.Y()) * surfaceStruct->pitch );

         std::memcpy(buffer + (y * bytesPerRow), srcRowPtr, bytesPerRow);
      }

      // copy from buffer to target region
      for (int y = 0; y < source.Height(); ++y)
      {
         Uint8 *targetRowPtr = pixels + ( (y + dst.Y) * surfaceStruct->pitch );

         std::memcpy(targetRowPtr, buffer + (y * bytesPerRow), bytesPerRow);
      }
   }
}

void Surface::Update()
{
   SDL_Flip(SurfaceStruct());
}

} // namespace Graphics
} // namespace SdlDotNetCompat


void SdlDotNetCompat::Graphics::Surface::CloseHandle()
{
   if (SDL_Surface *h = static_cast<SDL_Surface*>(Handle()))
   {
      SDL_FreeSurface(h);
   }

   SetHandle(nullptr);
}

SDL_Surface *SdlDotNetCompat::Graphics::Surface::SurfaceStruct() const
{
   return static_cast<SDL_Surface*>(Handle());
}

