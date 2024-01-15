#pragma once
#include "pch.h"
#include "Point3D.h"

// Class representing a triangle in 3D space
class GEOMETRY_API Triangle
{
public:
    Triangle(Point3D p1, Point3D p2, Point3D p3);

    // Destructor for the Triangle class
    ~Triangle();

    // Getter function for the first vertex (Point3D) of the triangle
    Point3D p1() const;

    // Getter function for the second vertex (Point3D) of the triangle
    Point3D p2() const;

    // Getter function for the third vertex (Point3D) of the triangle
    Point3D p3() const;

private:
    //  member variables 
    Point3D mP1;
    Point3D mP2;
    Point3D mP3;
};
