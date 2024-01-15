#include "pch.h"
#include "Triangulation.h"

// Constructor for the Triangulation class
Triangulation::Triangulation(const std::vector<Triangle>& inTriangles)
{
    mTriangles = inTriangles;
}

// Destructor for the Triangulation class
Triangulation::~Triangulation()
{

}

// Getter function to retrieve the triangles stored in the object
std::vector<Triangle> Triangulation::getTriangles() const
{
    return mTriangles;
}
