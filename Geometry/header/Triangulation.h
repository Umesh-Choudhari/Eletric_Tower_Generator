#pragma once
#include "pch.h"
#include "Triangle.h"
#include <vector>

// Class representing a collection of triangles forming a triangulation
class GEOMETRY_API Triangulation
{
public:
    // Constructor taking a vector of triangles to initialize the triangulation
    Triangulation(const std::vector<Triangle>& inTriangles);

    // Destructor for the Triangulation class
    ~Triangulation();

    // Getter function to retrieve the vector of triangles in the triangulation
    std::vector<Triangle> getTriangles() const;

private:
    // Private member variable
    std::vector<Triangle> mTriangles;
};

