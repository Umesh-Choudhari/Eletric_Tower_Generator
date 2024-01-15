#include "pch.h"
#include "framework.h"
#include "TowerCreator.h"

// This is an example of an exported variable
TOWERCREATOR_API int nTowerCreator = 0;

// This is an example of an exported function.
TOWERCREATOR_API int fnTowerCreator(void)
{
    return 0;
}

// Constructor for the TowerCreator class
TowerCreator::TowerCreator()
{
    return;
}

// Function to add tower vertices based on a given position and tower height
std::vector<float> TowerCreator::addTower(const Point3D& position,const float mTowerHeight)
{
    // Base square
    mTowerVertices.push_back(position.x());
    mTowerVertices.push_back(position.y());
    mTowerVertices.push_back(position.z());

    mTowerVertices.push_back(position.x() + 0.10f);
    mTowerVertices.push_back(position.y());
    mTowerVertices.push_back(position.z());

    mTowerVertices.push_back(position.x() + 0.10f);
    mTowerVertices.push_back(position.y() + 0.10f);
    mTowerVertices.push_back(position.z());

    mTowerVertices.push_back(position.x());
    mTowerVertices.push_back(position.y() + 0.10f);
    mTowerVertices.push_back(position.z());

    mTowerVertices.push_back(position.x());
    mTowerVertices.push_back(position.y());
    mTowerVertices.push_back(position.z());

    // Top square
    mTowerVertices.push_back(position.x());
    mTowerVertices.push_back(position.y());
    mTowerVertices.push_back(position.z() + mTowerHeight);

    mTowerVertices.push_back(position.x() + 0.10f);
    mTowerVertices.push_back(position.y());
    mTowerVertices.push_back(position.z() + mTowerHeight);

    mTowerVertices.push_back(position.x() + 0.10f);
    mTowerVertices.push_back(position.y() + 0.10f);
    mTowerVertices.push_back(position.z() + mTowerHeight);

    mTowerVertices.push_back(position.x());
    mTowerVertices.push_back(position.y() + 0.10f);
    mTowerVertices.push_back(position.z() + mTowerHeight);

    mTowerVertices.push_back(position.x());
    mTowerVertices.push_back(position.y());
    mTowerVertices.push_back(position.z() + mTowerHeight);

    // Side faces
    mTowerVertices.push_back(position.x() + 0.10f);
    mTowerVertices.push_back(position.y());
    mTowerVertices.push_back(position.z() + mTowerHeight);

    mTowerVertices.push_back(position.x() + 0.10f);
    mTowerVertices.push_back(position.y() + 0.10f);
    mTowerVertices.push_back(position.z() + mTowerHeight);

    mTowerVertices.push_back(position.x() + 0.10f);
    mTowerVertices.push_back(position.y() + 0.10f);
    mTowerVertices.push_back(position.z());

    mTowerVertices.push_back(position.x());
    mTowerVertices.push_back(position.y() + 0.10f);
    mTowerVertices.push_back(position.z());

    mTowerVertices.push_back(position.x());
    mTowerVertices.push_back(position.y() + 0.10f);
    mTowerVertices.push_back(position.z() + mTowerHeight);

    mTowerVertices.push_back(position.x());
    mTowerVertices.push_back(position.y());
    mTowerVertices.push_back(position.z() + mTowerHeight);

    mTowerVertices.push_back(position.x() + 0.10f);
    mTowerVertices.push_back(position.y());
    mTowerVertices.push_back(position.z() + mTowerHeight);

    mTowerVertices.push_back(position.x() + 0.10f);
    mTowerVertices.push_back(position.y());
    mTowerVertices.push_back(position.z());
    return mTowerVertices;
}


void TowerCreator:: deleteTower(std::vector<float>& mTowerVertices)
{
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    // Top square
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    // Side faces
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();

    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
    mTowerVertices.pop_back();
}