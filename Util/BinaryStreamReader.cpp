#include "BinaryStreamReader.h"

#include <iostream>

namespace Util {

BinaryStreamReader::BinaryStreamReader(const char *filePath)
  : m_stream(filePath, std::ios::binary | std::ios::in)
{

}

BinaryStreamReader::~BinaryStreamReader()
{
   m_stream.close();
}

std::string BinaryStreamReader::ReadString()
{
   std::string res;

   const int strLen = readStringLength();
   if ( strLen > 0 )
   {
      res.resize(strLen);
      m_stream.read(&res[0], strLen);
   }

   return res;
}

int32_t BinaryStreamReader::ReadInt32()
{
   uint8_t buf[4];

   m_stream.read(reinterpret_cast<char*>(buf), sizeof(buf));

   if (m_stream.gcount() < 4)
      throw std::runtime_error("Read beyond EOF");

   return int32_t( buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24) );
}

uint8_t BinaryStreamReader::ReadByte()
{
   const int res = m_stream.get();

   if ( res == EOF )   
      throw std::runtime_error("Read beyond EOF");

   return res;
}

bool BinaryStreamReader::ReadBoolean()
{
   char c = ReadByte();

   return (c != '\0');
}

int32_t BinaryStreamReader::PeekChar()
{
   const int res = m_stream.peek();

   return (res == EOF) ? (-1) : res;
}

uint64_t BinaryStreamReader::ReadUInt64()
{
   uint8_t buf[8];

   m_stream.read(reinterpret_cast<char*>(buf), sizeof(buf));

   if (m_stream.gcount() < 8)
      throw std::runtime_error("Read beyond EOF");

   uint32_t lo = uint32_t( buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24) );
   uint32_t hi = uint32_t( buf[4] | (buf[5] << 8) | (buf[6] << 16) | (buf[7] << 24) );

   return uint64_t( (static_cast<uint64_t>(hi) << 32) | lo );
}

float BinaryStreamReader::ReadSingle()
{
   uint8_t buf[4];

   m_stream.read(reinterpret_cast<char*>(buf), sizeof(buf));

   if (m_stream.gcount() < 4)
      throw std::runtime_error("Read beyond EOF");

   uint32_t intVal = ( buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24) );

   return *((float*)&intVal);
}

int BinaryStreamReader::readStringLength()
{   
   int res = 0;

   int shift = 0;
   uint8_t b;

   do
   {      
      if (shift == 5 * 7)
         throw std::runtime_error("Invalid string format");

      b = ReadByte();
      res |= (b & 0x7F) << shift;
      shift += 7;
   }
   while ((b & 0x80) != 0);

   return res;
}

} // namespace Util
