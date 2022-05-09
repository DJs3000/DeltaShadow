#include "BaseSdlResource.h"

namespace SdlDotNetCompat {
namespace Core {

BaseSdlResource::BaseSdlResource()
 : handle(nullptr)
{

}

BaseSdlResource::BaseSdlResource(void *handle)
 : handle(handle)
{

}

BaseSdlResource::~BaseSdlResource()
{}

} // namespace Core
} // namespace SdlDotNetCompat
