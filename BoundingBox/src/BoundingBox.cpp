#include "pch.h"
#include "framework.h"
#include "BoundingBox.h"
#include <cmath>
#include <algorithm>
#include <string>


// This is an example of an exported variable
BOUNDINGBOX_API int nBoundingBox=0;

// This is an example of an exported function.
BOUNDINGBOX_API int fnBoundingBox(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
BoundingBox::BoundingBox()
{
    return;
}

std::vector<double> BoundingBox::boundingBoxOfTerrain(const std::vector<float> mVerticesOfOrignalLine)
{
    std::vector<double> mboundingBox;
    double minX = DBL_MAX;
    double minY = DBL_MAX;
    double minZ = DBL_MAX;
    double maxX = DBL_MIN;
    double maxY = DBL_MIN;
    double maxZ = DBL_MIN;

    std::string line;
    for (int i = 9; i < mVerticesOfOrignalLine.size(); i += 3)
    {
        double x = mVerticesOfOrignalLine[i];
        double y = mVerticesOfOrignalLine[i + 1];
        double z = mVerticesOfOrignalLine[i + 2];
        // Update bounding box coordinates
        minX = (((minX) < (x)) ? (minX) : (x));
        minY = (((minY) < (y)) ? (minY) : (y));
        minZ = (((minZ) < (z)) ? (minZ) : (z));
        maxX = (((maxX) > (x)) ? (maxX) : (x));
        maxY = (((maxY) > (y)) ? (maxY) : (y));
        maxZ = (((maxZ) > (z)) ? (maxZ) : (z));

    }
    mboundingBox.push_back(minX);
    mboundingBox.push_back(minY);
    mboundingBox.push_back(minZ);
    mboundingBox.push_back(maxX);
    mboundingBox.push_back(maxY);
    mboundingBox.push_back(maxZ);

    return mboundingBox;
}