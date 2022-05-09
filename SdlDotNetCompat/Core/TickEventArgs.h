#ifndef TICKEVENTARGS_H
#define TICKEVENTARGS_H

#include "SdlDotNetCompat/Core/UserEventArgs.h"

namespace SdlDotNetCompat {
namespace Core {

class TickEventArgs : public SdlDotNetCompat::Core::UserEventArgs
{
public:
   TickEventArgs(int tick, int lastTick, int fps);

   int LastTick() const;

   int Fps() const;

   int Tick() const;

   int TicksElapsed() const;

   double SecondsElapsed() const;

private:   
   int m_tick;
   int m_lastTick;
   int m_fps;
};

} // namespace Core
} // namespace SdlDotNetCompat

#endif // TICKEVENTARGS_H
