#include "Events.h"

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_mixer.h>

#include <thread>

namespace SdlDotNetCompat {
namespace Core {

namespace
{
   static Events *const instance = new Events();

   static int targetFps = 60;
   static int fps = 60;
   static int lastTick;
   static float ticksPerFrame = (1000.0f / float(targetFps));
   static bool quitFlag = false;

   inline void closeSubsystem(uint32_t subsystem)
   {
      if (SDL_WasInit(subsystem))
      {
         SDL_QuitSubSystem(subsystem);
      }
   }
}

EventHandler<Input::ActiveEventArgs>         Events::AppActive;
EventHandler<Input::KeyboardEventArgs>       Events::KeyboardDown;
EventHandler<Input::KeyboardEventArgs>       Events::KeyboardUp;
EventHandler<Input::MouseMotionEventArgs>    Events::MouseMotion;
EventHandler<Input::MouseButtonEventArgs>    Events::MouseButtonDown;
EventHandler<Input::MouseButtonEventArgs>    Events::MouseButtonUp;
EventHandler<Graphics::VideoExposeEventArgs> Events::VideoExpose;
EventHandler<Graphics::VideoResizeEventArgs> Events::VideoResize;
EventHandler<Core::QuitEventArgs>            Events::Quit;
EventHandler<Core::TickEventArgs>            Events::Tick;
EventHandler<Core::UserEventArgs>            Events::UserEvent;

void Events::Close()
{
   Events::CloseJoysticks();
   Events::CloseCDRom();   
   Events::CloseAudio();
   Events::CloseTimer();
   Events::CloseVideo();
}

void Events::CloseVideo()
{
   closeSubsystem(SDL_INIT_VIDEO);
}

void Events::CloseTimer()
{
   closeSubsystem(SDL_INIT_TIMER);
}

void Events::CloseJoysticks()
{
   closeSubsystem(SDL_INIT_JOYSTICK);
}

void Events::CloseCDRom()
{
   closeSubsystem(SDL_INIT_CDROM);
}

void Events::CloseMixer()
{   
   Mix_CloseAudio();
   closeSubsystem(SDL_INIT_AUDIO);
}

void Events::CloseAudio()
{
   SDL_CloseAudio();

   Events::CloseMixer();
}

void Events::QuitApplication()
{
   quitFlag = true;
}

void Events::Run()
{
   lastTick = 0;
   quitFlag = false;

   ///Timer::Initialize();
   SDL_Init(SDL_INIT_TIMER);

   ThreadTicker();

   Events::Close();

   SDL_Quit();
}

bool Events::Poll()
{
   try
   {
      SDL_Event event;
      int ret = SDL_PollEvent(&event);
      if (ret == SdlFlag::Error)
      {
         // TODO
      }
      if (ret == SdlFlag::None)
      {
         return false;
      }
      else
      {
         ProcessEvent(event);
         return true;
      }
   }
   catch (...)
   {
      return false;
   }
}

bool Events::Poll(int numberOfEvents)
{
   SDL_Event event;
   for (int i = 0; i <= numberOfEvents; ++i) // TODO: check loop condition (<=)
   {
      int ret = SDL_PollEvent(&event);
      if (ret == SdlFlag::Error)
      {
         // TODO
      }
      if (ret == SdlFlag::None)
      {
         break;
      }
      else
      {
         ProcessEvent(event);
      }
   }
   return false;
}

int Events::GetTargetFps()
{
   return targetFps;
}

void Events::SetTargetFps(int value)
{
   if (value == 0)
   {
      targetFps = 1;
   }
   else if (value > 100000 || value == -1)
   {
      targetFps = 100000;
   }
   else
   {
      targetFps = value;
   }
   ticksPerFrame = (1000.0f / float(targetFps));
}

void Events::ThreadTicker()
{
   int frames = 0;
   uint32_t lastTime = SDL_GetTicks();
   uint32_t currentTime;
   uint32_t currentTick;
   uint32_t targetTick;

   while (!quitFlag)
   {
      // Poll all events
      while (Events::Poll()) ;

      currentTick = SDL_GetTicks();
      targetTick  = lastTick + (int)ticksPerFrame;

      if (currentTick <= targetTick)
      {
         std::this_thread::sleep_for(std::chrono::milliseconds(targetTick - currentTick));
      }
      currentTick = SDL_GetTicks();

      Events::Tick(instance, new TickEventArgs(currentTick, lastTick, fps));
      lastTick = currentTick;
      currentTime = SDL_GetTicks();
      frames++;

      if (lastTime + 1000 <= currentTime)
      {
         fps = frames;
         frames = 0;
         lastTime = currentTime;
      }
   }
}

void Events::ProcessEvent(const SDL_Event &event)
{   
   switch (event.type)
   {
   case SDL_ACTIVEEVENT:
      AppActive(instance, new Input::ActiveEventArgs(event));
      break;

   case SDL_JOYAXISMOTION:
      //TODO: implement me
      break;

   case SDL_JOYBALLMOTION:
      //TODO: implement me
      break;

   case SDL_JOYBUTTONDOWN:
      //TODO: implement me
      break;

   case SDL_JOYBUTTONUP:
      //TODO: implement me
      break;

   case SDL_JOYHATMOTION:

      break;

   case SDL_KEYDOWN:
      KeyboardDown(instance, new Input::KeyboardEventArgs(event));
      break;

   case SDL_KEYUP:
      KeyboardUp(instance, new Input::KeyboardEventArgs(event));
      break;

   case SDL_MOUSEBUTTONDOWN:
      MouseButtonDown(instance, new Input::MouseButtonEventArgs(event));
      break;

   case SDL_MOUSEBUTTONUP:
      MouseButtonUp(instance, new Input::MouseButtonEventArgs(event));
      break;

   case SDL_MOUSEMOTION:
      MouseMotion(instance, new Input::MouseMotionEventArgs(event));
      break;

   case SDL_QUIT:
      Quit(instance, new Core::QuitEventArgs(event));
      break;

   case SDL_USEREVENT:
      UserEvent(instance, new Core::UserEventArgs(event));
      break;

   case SDL_VIDEOEXPOSE:
      VideoExpose(instance, new SdlDotNetCompat::Graphics::VideoExposeEventArgs(event));
      break;

   case SDL_VIDEORESIZE:
      VideoResize(instance, new SdlDotNetCompat::Graphics::VideoResizeEventArgs(event));
      break;
   }
}

} // namespace Core
} // namespace SdlDotNetCompat
