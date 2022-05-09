#ifndef SURFACE_H
#define SURFACE_H

#include "SdlDotNetCompat/Core/BaseSdlResource.h"

#include "SdlDotNetCompat/Drawing/Point.h"
#include "SdlDotNetCompat/Drawing/Color.h"
#include "SdlDotNetCompat/Drawing/Rectangle.h"

#include <memory>
#include <vector>

struct SDL_Surface;
struct SDL_PixelFormat;

namespace SdlDotNetCompat {
namespace Graphics {

class Surface : public SdlDotNetCompat::Core::BaseSdlResource
{
public:
   Surface(SDL_Surface *handle);

   Surface(const std::string &file);

   Surface(const SdlDotNetCompat::Drawing::Size &size);

   Surface(const SdlDotNetCompat::Drawing::Rectangle &rectangle);

   Surface(int width, int height);

   Surface(int width, int height, int bitsPerPixel);

   Surface(int width, int height, int bitsPerPixel, uint32_t redMask, uint32_t greenMask, uint32_t blueMask, uint32_t alphaMask);

   Surface(int width, int height, int bitsPerPixel, bool alphaChannel);

   void Dispose();

   Surface CreateScaledSurface(double zoomX, double zoomY, bool antiAlias) const;

   Surface CreateScaledSurface(double zoomX, double zoomY) const;

   Surface CreateScaledSurface(double zoom) const;

   Surface CreateScaledSurface(double zoom, bool antiAlias) const;

   SdlDotNetCompat::Drawing::Rectangle Blit(const Surface &sourceSurface, const SdlDotNetCompat::Drawing::Point &destinationPosition);

   SdlDotNetCompat::Drawing::Rectangle Blit(const SdlDotNetCompat::Graphics::Surface &sourceSurface, const SdlDotNetCompat::Drawing::Rectangle &destinationRectangle);

   SdlDotNetCompat::Drawing::Rectangle Blit(const SdlDotNetCompat::Graphics::Surface &sourceSurface, const SdlDotNetCompat::Drawing::Rectangle &destinationRectangle, const SdlDotNetCompat::Drawing::Rectangle &sourceRectangle);

   SdlDotNetCompat::Drawing::Rectangle Blit(const SdlDotNetCompat::Graphics::Surface &sourceSurface, const SdlDotNetCompat::Drawing::Point &destinationPosition, const SdlDotNetCompat::Drawing::Rectangle &sourceRectangle);

   void Draw(const SdlDotNetCompat::Drawing::Point &point, uint32_t color);

   void Draw(const SdlDotNetCompat::Drawing::Point &point, const SdlDotNetCompat::Drawing::Color &color);

   SdlDotNetCompat::Drawing::Rectangle Fill(const SdlDotNetCompat::Drawing::Color &color);

   SdlDotNetCompat::Drawing::Rectangle Fill(const SdlDotNetCompat::Drawing::Rectangle &rectangle, const SdlDotNetCompat::Drawing::Color &color);

   void SetClipRectangle(const SdlDotNetCompat::Drawing::Rectangle &rect);

   uint32_t GetColorValue(const SdlDotNetCompat::Drawing::Color &color) const;

   int Width() const;

   int Height() const;

   void CopyPixels(const SdlDotNetCompat::Drawing::Point &dst, const SdlDotNetCompat::Drawing::Rectangle &source);

   void Update();

   // BaseSdlResource interface
protected:
   virtual void CloseHandle() override;

   SDL_Surface *SurfaceStruct() const;

private:   
   SdlDotNetCompat::Drawing::Color m_transparentColor;
   uint8_t m_alpha;
   bool m_alphaBlending;   
   bool m_transparentInitialized;
   bool m_transparent;

   std::vector<uint8_t> m_buffer;

};

} // namespace Graphics
} // namespace SdlDotNetCompat

#endif // SURFACE_H
