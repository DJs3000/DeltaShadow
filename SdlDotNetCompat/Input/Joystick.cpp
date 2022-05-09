#include "Joystick.h"

namespace SdlDotNetCompat {
namespace Input {

Joystick::Joystick()
{

}

int Joystick::NumberOfButtons() const
{
   return 0;
}

ButtonKeyState Joystick::GetButtonState(int button)
{
   return ButtonKeyState::NotPressed;
}

float Joystick::GetAxisPosition(JoystickAxis axis)
{
   return 0.0;
}

} // namespace Input
} // namespace SdlDotNetCompat
