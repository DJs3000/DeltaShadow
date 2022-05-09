#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

namespace SdlDotNetCompat {
namespace Drawing {

// https://docs.microsoft.com/ru-ru/dotnet/api/system.drawing.color?view=net-5.0

class Color
{
public:
   static const Color White;
   static const Color Black;
   static const Color Blue;

   static Color FromArgb(int32_t argb);

   static Color FromArgb(int32_t alpha, const Color &color);

   static Color FromArgb(int32_t r, int32_t g, int32_t b);

   static Color FromArgb(int32_t a, int32_t r, int32_t g, int32_t b);

   inline int32_t ToArgb() const { return argb; }

   uint8_t A() const;

   uint8_t R() const;

   uint8_t G() const;

   uint8_t B() const;

private:
   int32_t argb;
};

}}

#endif // COLOR_H
