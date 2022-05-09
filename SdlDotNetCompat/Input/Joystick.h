#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "SdlDotNetCompat/Input/Mouse.h"

namespace SdlDotNetCompat {
namespace Input {

enum JoystickAxis
{
   Horizontal = 0
 , Vertical = 1
 , Axis3 = 2
 , Axis4 = 3
 , Axis5 = 4
 , Axis6 = 5
};

class Joystick
{
public:
   Joystick();

   int NumberOfButtons() const;

   ButtonKeyState GetButtonState(int button);

   float GetAxisPosition(JoystickAxis axis);
};

} // namespace Input
} // namespace SdlDotNetCompat

#endif // JOYSTICK_H
