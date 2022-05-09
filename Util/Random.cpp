#include "Random.h"
#include <random>
#include <limits>

class Util::Random::Generator
{
public:
   Generator() : rng(rd())
   {}

   int32_t next()
   {
      std::uniform_int_distribution<int32_t> uni(0, std::numeric_limits<int32_t>::max());
      return uni(rng);
   }

private:
   std::random_device rd;
   std::mt19937 rng;
};

namespace Util {

Random::Random()
   : m_privateImp(new Random::Generator())
{

}

Random::~Random()
{
   delete m_privateImp;
}

int32_t Random::Next()
{
   return m_privateImp->next();
}

}
