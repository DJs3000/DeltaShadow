#include "PrimaryScreen.h"
#include <X11/Xlib.h>

namespace Environment {
namespace PrimaryScreen {

bool Size(int32_t &width, int32_t &height)
{
   bool res = false;

   Display *d = XOpenDisplay(NULL);
   if (d)
   {
      Screen  *s = XDefaultScreenOfDisplay(d);
      width  = s->width;
      height = s->height;
      res = true;
   }
   XCloseDisplay(d);

   return res;
}


} // namespace Screen
} // namespace Environment
