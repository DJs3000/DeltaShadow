#ifndef EVENTS_H
#define EVENTS_H

#include "EventHandler.h"

#include "SdlDotNetCompat/Input/ActiveEventArgs.h"
#include "SdlDotNetCompat/Input/KeyboardEventArgs.h"
#include "SdlDotNetCompat/Input/MouseButtonEventArgs.h"
#include "SdlDotNetCompat/Input/MouseMotionEventArgs.h"

#include "SdlDotNetCompat/Core/QuitEventArgs.h"
#include "SdlDotNetCompat/Core/TickEventArgs.h"

#include "SdlDotNetCompat/Graphics/VideoResizeEventArgs.h"
#include "SdlDotNetCompat/Graphics/VideoExposeEventArgs.h"

typedef union SDL_Event SDL_Event;

namespace SdlDotNetCompat {
namespace Core {

namespace SdlFlag
{
   enum
   {

      Error = -1,

      Success = 0,

      InfiniteLoop = -1,

      Error2 = 1,

      Success2 = 1,

      None = 0,

      FirstFreeChannel = -1,

      TrueValue = 1,

      FalseValue = 0,
   };
}

class Events
{
public:

   static EventHandler<Input::ActiveEventArgs> AppActive;

   static EventHandler<Input::KeyboardEventArgs> KeyboardDown;

   static EventHandler<Input::KeyboardEventArgs> KeyboardUp;

   static EventHandler<Input::MouseMotionEventArgs> MouseMotion;

   static EventHandler<Input::MouseButtonEventArgs> MouseButtonDown;

   static EventHandler<Input::MouseButtonEventArgs> MouseButtonUp;

   static EventHandler<Graphics::VideoExposeEventArgs> VideoExpose;

   static EventHandler<Graphics::VideoResizeEventArgs> VideoResize;

   static EventHandler<Core::QuitEventArgs> Quit;

   static EventHandler<Core::TickEventArgs> Tick;

   static EventHandler<Core::UserEventArgs> UserEvent;

   static void Close();

   static void CloseVideo();

   static void CloseTimer();

   static void CloseJoysticks();

   static void CloseCDRom();

   static void CloseMixer();

   static void CloseAudio();

   static void QuitApplication();

   static void Run();

   static bool Poll();

   static bool Poll(int numberOfEvents);

   static int GetTargetFps();

   static void SetTargetFps(int value);

private:
   static void ThreadTicker();

   static void ProcessEvent(const SDL_Event &event);

};

} // namespace Core
} // namespace SdlDotNetCompat

#endif // EVENTS_H
