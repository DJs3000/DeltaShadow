#ifndef POINT_H
#define POINT_H

#include <cstdint>

namespace SdlDotNetCompat {
namespace Drawing {

class Point
{
public:
   Point(int32_t x, int32_t y)
    : X(x)
    , Y(y)
   {}

   int32_t X;
   int32_t Y;
};

} // namespace Drawing
} // namespace System

#endif // POINT_H
