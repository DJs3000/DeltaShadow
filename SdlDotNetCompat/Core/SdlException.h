#ifndef SDLEXCEPTION_H
#define SDLEXCEPTION_H

#include <stdexcept>

namespace SdlDotNetCompat {
namespace Core {

class SdlException : public std::runtime_error
{
public:
   SdlException(const std::string &what_arg);
   SdlException(const char *what_arg);
};

} // namespace Core
} // namespace SdlDotNetCompat

#endif // SDLEXCEPTION_H
