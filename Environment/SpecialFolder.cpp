#include "SpecialFolder.h"

#include <cstring>
#include <ftw.h>
#include <functional>

namespace Environment {

namespace {

std::string getEnv(const std::string &var)
{
   const char  *val = std::getenv(var.c_str());
   return val ? val : std::string();
}

void splitPathsInto(std::vector<std::string> &res, const std::string &s, char c)
{
   auto   end = s.cend();
   auto start = end;

   for (auto it = s.cbegin(); it != end; ++it)
   {
      if (*it != c)
      {
         if (start == end)
             start = it;

         continue;
      }
      if (start != end)
      {
         res.emplace_back(start, it);
         start = end;
      }
   }

   if (start != end)
      res.emplace_back(start, end);
}

}

std::vector<std::string> SpecialFolder::xdg_data_dirs()
{
   // $XDG_DATA_HOME defines the base directory relative to which user-specific data files should be stored.
   std::string xdg_data_home = getEnv("XDG_DATA_HOME");

   // If $XDG_DATA_HOME is either not set or empty, a default equal to $HOME/.local/share should be used.
   if (xdg_data_home.empty())
   {
      std::string homedir = getEnv("HOME");
      xdg_data_home.append(homedir).append("/.local/share");
   }

   // $XDG_DATA_DIRS defines the preference-ordered set of base directories to search for data files in addition to the $XDG_DATA_HOME base directory.
   std::string xdg_data_dirs = getEnv("XDG_DATA_DIRS");

   // If $XDG_DATA_DIRS is either not set or empty, a value equal to /usr/local/share/:/usr/share/ should be used.
   if (xdg_data_dirs.empty())
   {
      xdg_data_dirs = "/usr/local/share/:/usr/share/";
   }

   std::vector<std::string> xdg_dirs; xdg_dirs.reserve(8);

   splitPathsInto(xdg_dirs, xdg_data_home, ':');
   splitPathsInto(xdg_dirs, xdg_data_dirs, ':');

   return xdg_dirs;
}

std::string SpecialFolder::ApplicationData()
{
   std::string res;

   std::vector<std::string> dirs = xdg_data_dirs();
   if (!dirs.empty())
   {
      res = std::move(dirs.front());
   }

   return res;
}


} // namespace Environment
