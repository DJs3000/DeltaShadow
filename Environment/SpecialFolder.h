#ifndef SPECIALFOLDER_H
#define SPECIALFOLDER_H

#include <vector>
#include <string>

namespace Environment {
namespace SpecialFolder {

std::vector<std::string> xdg_data_dirs();

std::string ApplicationData();

} // namespace SpecialFolder
} // namespace Environment

#endif // SPECIALFOLDER_H
