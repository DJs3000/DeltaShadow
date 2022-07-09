#include "BinaryStreamWriter.h"

typedef unsigned int uint;

BinaryStreamWriter::BinaryStreamWriter(const char *filePath)
  : m_stream(filePath, std::ios::binary | std::ios::out)
{

}

BinaryStreamWriter::~BinaryStreamWriter()
{
   m_stream.flush();
   m_stream.close();
}

void BinaryStreamWriter::Write(int32_t val)
{
   uint8_t buf[4];
   buf[0] = uint8_t(val);
   buf[1] = uint8_t(val >> 8 );
   buf[2] = uint8_t(val >> 16);
   buf[3] = uint8_t(val >> 24);
   m_stream.write(reinterpret_cast<char*>(buf), sizeof(buf));
}

void BinaryStreamWriter::Write(bool val)
{
   m_stream.put(uint8_t(val ? 0x01 : 0x00));
}

void BinaryStreamWriter::Write(float val)
{
   uint32_t t = *(reinterpret_cast<uint*>(&val));
   uint8_t buf[4];
   buf[0] = uint8_t(t);
   buf[1] = uint8_t(t >> 8 );
   buf[2] = uint8_t(t >> 16);
   buf[3] = uint8_t(t >> 24);
   m_stream.write(reinterpret_cast<char*>(buf), sizeof(buf));
}

void BinaryStreamWriter::Write(const std::string &str)
{
   size_t len = str.length();
   while (len >= 0x80)
   {
      Write(uint8_t(len | 0x80));
      len >>= 7;
   }
   Write(uint8_t(len));

   m_stream.write(str.c_str(), str.length());
}

void BinaryStreamWriter::Write(uint8_t byte)
{
   m_stream.put(byte);
}

void BinaryStreamWriter::Write(uint64_t val)
{
   uint8_t buf[8];
   buf[0] = uint8_t(val);
   buf[1] = uint8_t(val >> 8);
   buf[2] = uint8_t(val >> 16);
   buf[3] = uint8_t(val >> 24);
   buf[4] = uint8_t(val >> 32);
   buf[5] = uint8_t(val >> 40);
   buf[6] = uint8_t(val >> 48);
   buf[7] = uint8_t(val >> 56);
   m_stream.write(reinterpret_cast<char*>(buf), sizeof(buf));
}
