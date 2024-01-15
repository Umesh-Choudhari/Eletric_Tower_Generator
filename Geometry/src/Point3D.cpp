#include "pch.h"
#include "Point3D.h"

// Constructor for the Point3D class
Point3D::Point3D(double inX, double inY, double inZ) :
    mX(inX),
    mY(inY),
    mZ(inZ)
{

}

// Destructor for the Point3D class
Point3D::~Point3D()
{

}

// Getter for the X coordinate
double Point3D::x() const
{
    return mX;
}

// Getter for the Y coordinate
double Point3D::y() const
{
    return mY;
}

// Getter for the Z coordinate
double Point3D::z() const
{
    return mZ;
}

// Setter for the X coordinate
void Point3D::setX(double inX)
{
    mX = inX;
}

// Setter for the Y coordinate
void Point3D::setY(double inY)
{
    mY = inY;
}


// Setter for the Z coordinate
void Point3D::setZ(double inZ)
{
    mZ = inZ;
}

