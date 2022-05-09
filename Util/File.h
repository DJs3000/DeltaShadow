#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

namespace Util {
namespace File {

void ReadAllBytes(const std::string &path, std::vector<uint8_t> &buf);
bool Exists(const std::string &path);

} // namespace File
} // namespace Util

#endif // FILE_H
