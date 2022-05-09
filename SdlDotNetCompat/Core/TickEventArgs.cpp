#include "TickEventArgs.h"

namespace SdlDotNetCompat {
namespace Core {

TickEventArgs::TickEventArgs(int tick, int lastTick, int fps)
   : m_tick(tick)
   , m_lastTick(lastTick)
   , m_fps(fps)
{

}

int TickEventArgs::LastTick() const
{
   return m_lastTick;
}

int TickEventArgs::Fps() const
{
   return m_fps;
}

int TickEventArgs::Tick() const
{
   return m_tick;
}

int TickEventArgs::TicksElapsed() const
{
   return m_tick - m_lastTick;
}

double TickEventArgs::SecondsElapsed() const
{
   return TicksElapsed() / 1000.0;
}

} // namespace Core
} // namespace SdlDotNetCompat
