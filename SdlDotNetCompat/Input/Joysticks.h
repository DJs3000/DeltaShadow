#ifndef JOYSTICKS_H
#define JOYSTICKS_H

#include "Joystick.h"

namespace SdlDotNetCompat {
namespace Input {

// https://github.com/AlteredCarrot71/SdlDotNetCompat/blob/master/Input/Joysticks.cs

class Joysticks
{
public:
   Joysticks();

   static bool IsInitialized() { return false; }

   static bool Initialize() { return false; }

   static bool IsJoystickInitialized(int index) { return false; }

   static void Close() {}

   static bool IsValidJoystickNumber(int index) { return false; }

   static Joystick OpenJoystick(int index)
   {
      return Joystick();
   }
};

} // namespace Input
} // namespace SdlDotNetCompat

#endif // JOYSTICKS_H
