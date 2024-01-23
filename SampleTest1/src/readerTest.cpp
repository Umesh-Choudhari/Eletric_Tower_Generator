#include "pch.h"
#include "gtest/gtest.h"
#include<vector>
#include "Reader.h"
#include<cassert>



TEST(ReaderTest, readSTL) {
    Reader read;
    std::string mFilePath = "E:\\Ramesh__Workspace\\Visualizer\\SampleTest1\\src\\cube1.stl";
    std::vector<float> mNormals;

    //Method to check the Triangles are returned correctly or not and their are 12 normals for cube  
    assert(read.readSTL(mFilePath, mNormals).size() == 108 && mNormals.size()==36);
    std::vector<float> mNormals1;
}