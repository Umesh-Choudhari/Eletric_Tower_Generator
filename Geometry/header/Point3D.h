#pragma once
#include "pch.h"

// Class representing a 3D point
class GEOMETRY_API Point3D
{
public:
    // Constructor with initial x, y, and optional z coordinates
    Point3D(double inX, double inY, double inZ = 0);

    // Destructor for the Point3D class
    ~Point3D();

    // Getter function for the x-coordinate
    double x() const;

    // Getter function for the y-coordinate
    double y() const;

    // Getter function for the z-coordinate
    double z() const;

    // Setter function for the x-coordinate
    void setX(double inX);

    // Setter function for the y-coordinate
    void setY(double inY);

    // Setter function for the z-coordinate
    void setZ(double inZ);

private:
    // Private member variables representing the coordinates
    double mX;
    double mY;
    double mZ;
};
