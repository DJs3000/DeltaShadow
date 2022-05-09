#ifndef VIDEOINFO_H
#define VIDEOINFO_H

#include <cstdint>

namespace SdlDotNetCompat {
namespace Graphics {

class VideoInfo
{
public:

   static uint8_t BitsPerPixel();

   static uint8_t BytesPerPixel();


   static uint32_t AlphaMask();

   static uint32_t RedMask();

   static uint32_t GreenMask();

   static uint32_t BlueMask();


   static uint8_t AlphaShift();

   static uint8_t RedShift();

   static uint8_t GreenShift();

   static uint8_t BlueShift();


   static uint8_t AlphaLoss();

   static uint8_t RedLoss();

   static uint8_t GreenLoss();

   static uint8_t BlueLoss();


   static bool HasHardwareSurfaces();

   static bool HasWindowManager();

   static bool HasHardwareBlits();

   static bool HasHardwareColorKeyBlits();

   static bool HasHardwareAlphaBlits();

   static bool HasSoftwareBlits();

   static bool HasSoftwareColorKeyBlits();

   static bool HasSoftwareAlphaBlits();

   static bool HasColorFills();


   static uint32_t VideoMemory();

   static int ScreenHeight();

   static int ScreenWidth();

};

} // namespace Graphics
} // namespace SdlDotNetCompat

#endif // VIDEOINFO_H
