#ifndef BINARYSTREAMWRITER_H
#define BINARYSTREAMWRITER_H

#include <fstream>

class BinaryStreamWriter
{
public:
   BinaryStreamWriter(const char *filePath);
  ~BinaryStreamWriter();

   void Write(int32_t val);

   void Write(bool val);

   void Write(float val);

   void Write(const std::string& str);

   void Write(uint8_t byte);

   void Write(uint64_t val);

private:
   std::ofstream m_stream;
};

#endif // BINARYSTREAMWRITER_H
