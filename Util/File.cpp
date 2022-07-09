#include "File.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <fstream>
#include <sstream>

void Util::File::ReadAllBytes(const std::string &path, std::vector<uint8_t> &buf)
{
   std::ifstream input(path, std::ios::binary | std::ios::ate);
   std::ifstream::pos_type pos = input.tellg();

   buf.resize(pos);

   input.seekg(0, std::ios::beg);
   input.read(reinterpret_cast<char*>(&buf[0]), pos);
}

bool Util::File::Exists(const std::string &path)
{
   std::ifstream file(path);

   if (file)
   {
      return true;
   }

   return false;
}
