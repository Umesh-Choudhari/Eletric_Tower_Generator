#pragma once
#include "pch.h"
#include <vector>
#include "Point3D.h"

// This class is exported from the dll
class TOWERCREATOR_API TowerCreator {
public:
	TowerCreator(void);
	std::vector<float> addTower(const Point3D& position,const float mTowerHeight);
	void deleteTower(std::vector<float>& mTowerVertices);

public:
	std::vector<float> mTowerVertices;
};


extern TOWERCREATOR_API int nTowerCreator;

TOWERCREATOR_API int fnTowerCreator(void);
