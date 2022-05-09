#include "Color.h"

namespace SdlDotNetCompat {
namespace Drawing {

const Color Color::White = Color::FromArgb(0xFFFFFFFF);
const Color Color::Black = Color::FromArgb(0xFF000000);
const Color Color::Blue  = Color::FromArgb(0xFF0000FF);

Color Color::FromArgb(int32_t argb)
{
   Color res;

   res.argb = argb;

   return res;
}

Color Color::FromArgb(int32_t alpha, const Color &color)
{
   Color res;

   res.argb = ((alpha & 0xFF) << 24)
            | ( color.ToArgb() & 0x00FFFFFF );

   return res;
}

Color Color::FromArgb(int32_t r, int32_t g, int32_t b)
{
   return FromArgb(255, r, g, b);
}

Color Color::FromArgb(int32_t a, int32_t r, int32_t g, int32_t b)
{
   Color res;

   res.argb = ( (a & 0xFF) << 24 )
            | ( (r & 0xFF) << 16 )
            | ( (g & 0xFF) << 8  )
            | ( (b & 0xFF)       );

   return res;
}

uint8_t Color::A() const
{
   return (argb >> 24) & 0xFF;
}

uint8_t Color::R() const
{
   return (argb >> 16) & 0xFF;
}

uint8_t Color::G() const
{
   return (argb >> 8) & 0xFF;
}

uint8_t Color::B() const
{
   return argb & 0xFF;
}

}}
