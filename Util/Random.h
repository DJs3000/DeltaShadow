#ifndef RANDOM_H
#define RANDOM_H

#include <cstdint>

namespace Util {

class Random
{
public:
   Random();
  ~Random();

   int32_t Next();

private:
   class Generator;
   class Generator *m_privateImp = nullptr;

};

}

#endif // RANDOM_H
