#include "Rectangle.h"

namespace SdlDotNetCompat {
namespace Drawing {

Rectangle::Rectangle(int x, int y, int width, int height)
   : m_x(x)
   , m_y(y)
   , m_width(width)
   , m_height(height)
{

}

Rectangle::Rectangle(const Point &location, const Size &size)
   : m_x(location.X)
   , m_y(location.Y)
   , m_width(size.Width)
   , m_height(size.Height)
{

}

} // namespace Drawing
} // namespace System
