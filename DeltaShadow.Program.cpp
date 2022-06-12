#include "DeltaShadow.Program.h"

#include "Environment/PrimaryScreen.h"
#include "Environment/SpecialFolder.h"

#include "Util/File.h"
#include "Util/BinaryStreamReader.h"
#include "Util/BinaryStreamWriter.h"

using namespace SdlDotNetCompat::Core;
using namespace SdlDotNetCompat::Graphics;
using namespace SdlDotNetCompat::Audio;
using namespace SdlDotNetCompat::Input;
using namespace SdlDotNetCompat::Drawing;
using namespace Util;

namespace DeltaShadow
{

template <typename T>
T **AllocateDynamicArray(int nRows, int nCols)
{
    T **array = new T*[nCols];
    for (int i = 0; i < nCols; ++i)
    {
        array[i] = new T[nRows];
    }
    return array;
}

template <typename T>
void FreeDynamicArray(T** array)
{
    delete [] *array;
    delete []  array;
}

void toLower(std::string &str)
{
   for (auto &c : str)
   {
      c = tolower(c);
   }
}

}