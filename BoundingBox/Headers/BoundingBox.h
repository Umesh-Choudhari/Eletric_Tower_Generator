#pragma once
#include "pch.h"
#include <vector>

class BOUNDINGBOX_API BoundingBox {
public:
	BoundingBox(void);
	std::vector<double> boundingBoxOfTerrain(std::vector<float> mVerticesOfOrignalLine);
};

extern BOUNDINGBOX_API int nBoundingBox;

BOUNDINGBOX_API int fnBoundingBox(void);



