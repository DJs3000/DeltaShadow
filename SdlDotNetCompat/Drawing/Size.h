#ifndef SIZE_H
#define SIZE_H

#include <cstdint>
#include "Point.h"

namespace SdlDotNetCompat {
namespace Drawing {

class Size
{
public:
   Size()
      : Width(0)
      , Height(0)
   {}

   Size(int32_t width, int32_t height)
      : Width(width)
      , Height(height)
   {}

   Size(const Point &point)
      : Width(point.X)
      , Height(point.Y)
   {}

   int32_t Width;

   int32_t Height;
};

}}

#endif // SIZE_H
