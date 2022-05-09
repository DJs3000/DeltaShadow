#ifndef MOUSE_H
#define MOUSE_H

#include <SDL_mouse.h>

namespace SdlDotNetCompat {
namespace Input {

// TODO: https://github.com/AlteredCarrot71/SdlDotNetCompat/blob/master/Input/Mouse.cs
// using Sdl.SDL_RELEASED, Sdl.SDL_PRESSED:
enum ButtonKeyState
{
   NotPressed
 , Pressed
};

enum MouseButton
{
   /// <summary>
   /// None
   /// </summary>
   None = 0,
   /// <summary>
   /// Primary button. Typically the left button
   /// </summary>
   PrimaryButton = SDL_BUTTON_LEFT,
   /// <summary>
   /// Secondary button. typically the right button
   /// </summary>
   SecondaryButton = SDL_BUTTON_RIGHT,
   /// <summary>
   /// Middle button
   /// </summary>
   MiddleButton = SDL_BUTTON_MIDDLE,
   /// <summary>
   /// Wheel up
   /// </summary>
   WheelUp = SDL_BUTTON_WHEELUP,
   /// <summary>
   /// Wheel down
   /// </summary>
   WheelDown = SDL_BUTTON_WHEELDOWN
};

class Mouse
{
public:
   Mouse();

   static bool ShowCursor;
};

} // namespace Input
} // namespace SdlDotNetCompat

#endif // MOUSE_H
