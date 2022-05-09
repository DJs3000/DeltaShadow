#ifndef BASESDLRESOURCE_H
#define BASESDLRESOURCE_H

namespace SdlDotNetCompat {
namespace Core {

class BaseSdlResource
{
public:
   BaseSdlResource();
   BaseSdlResource(void *handle);

   virtual ~BaseSdlResource();

   void *Handle() const { return handle; }

   void SetHandle(void *h) { handle = h; }

protected:
   virtual void CloseHandle() = 0;

private:
   void *handle = nullptr;
};

} // namespace Core
} // namespace SdlDotNetCompat

#endif // BASESDLRESOURCE_H
