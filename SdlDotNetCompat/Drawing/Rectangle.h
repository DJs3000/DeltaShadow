#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"
#include "Size.h"

namespace SdlDotNetCompat {
namespace Drawing {

class Rectangle
{
public:
   Rectangle(int x, int y, int width, int height);

   Rectangle(const Point &location, const Size &size);

   int X() const { return m_x; }

   int Y() const { return m_y; }

   int Width() const { return m_width; }

   int Height() const { return m_height; }

   Point Location() const { return SdlDotNetCompat::Drawing::Point(m_x, m_y); }

private:
   int m_x, m_y, m_width, m_height;
};

} // namespace Drawing
} // namespace System

#endif // RECTANGLE_H
