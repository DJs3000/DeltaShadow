#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2004 - 2021 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class includes methods to convert multidimensional arrays to C++ vectors.
//----------------------------------------------------------------------------------------
#include <vector>

class RectangularVectors
{
public:
    static std::vector<std::vector<Color>> RectangularColorVector(int size1, int size2)
    {
        std::vector<std::vector<Color>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<Color>(size2);
        }

        return newVector;
    }

    static std::vector<std::vector<std::vector<Color>>> RectangularColorVector(int size1, int size2, int size3)
    {
        std::vector<std::vector<std::vector<Color>>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::vector<Color>>(size2);
            for (int vector2 = 0; vector2 < size2; vector2++)
            {
                newVector[vector1][vector2] = std::vector<Color>(size3);
            }
        }

        return newVector;
    }

    static std::vector<std::vector<std::int32_t>> RectangularStdInt32_tVector(int size1, int size2)
    {
        std::vector<std::vector<std::int32_t>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::int32_t>(size2);
        }

        return newVector;
    }

    static std::vector<std::vector<std::vector<std::uint8_t>>> RectangularStdUint8_tVector(int size1, int size2, int size3)
    {
        std::vector<std::vector<std::vector<std::uint8_t>>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::vector<std::uint8_t>>(size2);
            for (int vector2 = 0; vector2 < size2; vector2++)
            {
                newVector[vector1][vector2] = std::vector<std::uint8_t>(size3);
            }
        }

        return newVector;
    }

    static std::vector<std::vector<Surface*>> RectangularSurfaceVector(int size1, int size2)
    {
        std::vector<std::vector<Surface*>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<Surface*>(size2);
        }

        return newVector;
    }

    static std::vector<std::vector<std::vector<std::vector<Color>>>> RectangularColorVector(int size1, int size2, int size3, int size4)
    {
        std::vector<std::vector<std::vector<std::vector<Color>>>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::vector<std::vector<Color>>>(size2);
            for (int vector2 = 0; vector2 < size2; vector2++)
            {
                newVector[vector1][vector2] = std::vector<std::vector<Color>>(size3);
                for (int vector3 = 0; vector3 < size3; vector3++)
                {
                    newVector[vector1][vector2][vector3] = std::vector<Color>(size4);
                }
            }
        }

        return newVector;
    }

    static std::vector<std::vector<bool>> RectangularBoolVector(int size1, int size2)
    {
        std::vector<std::vector<bool>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<bool>(size2);
        }

        return newVector;
    }

    static std::vector<std::vector<Tile*>> RectangularTileVector(int size1, int size2)
    {
        std::vector<std::vector<Tile*>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<Tile*>(size2);
        }

        return newVector;
    }

    static std::vector<std::vector<std::vector<bool>>> RectangularBoolVector(int size1, int size2, int size3)
    {
        std::vector<std::vector<std::vector<bool>>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::vector<bool>>(size2);
            for (int vector2 = 0; vector2 < size2; vector2++)
            {
                newVector[vector1][vector2] = std::vector<bool>(size3);
            }
        }

        return newVector;
    }
};
