#include "SdlException.h"

namespace SdlDotNetCompat {
namespace Core {

SdlException::SdlException(const std::string &what_arg)
   : std::runtime_error(what_arg)
{

}

SdlException::SdlException(const char *what_arg)
   : std::runtime_error(what_arg)
{

}

} // namespace Core
} // namespace SdlDotNetCompat
