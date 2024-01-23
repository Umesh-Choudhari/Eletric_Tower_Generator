#include "pch.h"
#include "gtest/gtest.h"
#include "TowerCreator.h"
#include<cassert>
#include<vector>

TEST(TowerCreatorTest, AddTower) {
    Point3D vertex1(0.0f, 0.0f,0.0f);
    float mTowerHeight = 10.0f;

    TowerCreator tower;
    std::vector<float> mTowerVertices;
    mTowerVertices = tower.addTower(vertex1, mTowerHeight);

    //Method to check the Tower is created or not their are total 54 vertices are needed to create tower
    assert(mTowerVertices.size() == 54);

}

TEST(TowerCreatorTest, DeleteTower) {
    Point3D vertex1(0.0f, 0.0f, 0.0f);
    float mTowerHeight = 10.0f;

    TowerCreator tower;
    std::vector<float> mTowerVertices;
    mTowerVertices = tower.addTower(vertex1, mTowerHeight);

    //Method to check the Tower is created or not their are total 54 vertices are needed to create tower
    assert(mTowerVertices.size() == 54);

    //Method to check the Tower is Deleted or not
    tower.deleteTower(mTowerVertices);
    assert(mTowerVertices.size() == 0);

}