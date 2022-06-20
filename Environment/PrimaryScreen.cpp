#include "PrimaryScreen.h"
#include "SDL.h"
//#include <stdint.h>

namespace Environment {
namespace PrimaryScreen {

//bool Size(int32_t &width, int32_t &height)
//{
//   bool res = false;
//
//   Display *d = XOpenDisplay(NULL);
//   if (d)
//   {
//      Screen  *s = XDefaultScreenOfDisplay(d);
//      width  = s->width;
//      height = s->height;
//      res = true;
//   }
//   XCloseDisplay(d);
//
//   return res;
//}

bool Size(int32_t &width, int32_t &height)
{
   bool res = false;

    const SDL_VideoInfo* info = SDL_GetVideoInfo();   //<-- calls SDL_GetVideoInfo();
	width = info->current_w;
	height = info->current_h;

   return res;
}

} // namespace Screen
} // namespace Environment
