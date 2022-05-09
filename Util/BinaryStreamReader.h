#ifndef BINARYSTREAMREADER_H
#define BINARYSTREAMREADER_H

#include <fstream>

namespace Util
{

class BinaryStreamReader
{
public:
   BinaryStreamReader(const char *filePath);

  ~BinaryStreamReader();

   std::string ReadString();

   int32_t ReadInt32();

   uint8_t ReadByte();

   bool ReadBoolean();

   int32_t PeekChar();

   uint64_t ReadUInt64();

   float ReadSingle();

private:
   std::ifstream m_stream;

   int readStringLength();
};

} // namespace Util

#endif // BINARYSTREAMREADER_H
