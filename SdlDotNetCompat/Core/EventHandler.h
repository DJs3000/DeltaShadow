#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <vector>
#include <functional>

template <class T>
using HandlerFunc = std::function<void(void*, T*)>;

template <typename T>
class EventHandler
{
public:

   void operator()(void *sender, T *e)
   {      
      for (auto &callback : m_subscribers)
      {
         callback(sender, e);
      }

      delete e;
   }

   void operator+=(HandlerFunc<T> receiver)
   {      
      m_subscribers.push_back(receiver);
   }

private:

   std::vector<HandlerFunc<T>> m_subscribers;
};

#endif // EVENTHANDLER_H
