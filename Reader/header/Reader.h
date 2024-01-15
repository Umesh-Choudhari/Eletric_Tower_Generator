#include "pch.h"
#include <vector>
#include <bitset>
#include <string>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class READER_API Reader {
public:
    // Default constructor
    Reader(void);

    // Method to read the entire STL file and extract vertices
    vector<float> readSTL(const string& mFileName, std::vector<float>& mNormals);

public:
    // Public member variables to store vertices and colors 
    vector<float> mVertices;
    vector<float> mColors;
};

// Declaration of the exported variable nReader
extern READER_API int nReader;


// Declaration of the exported function fnReader
READER_API int fnReader(void);

