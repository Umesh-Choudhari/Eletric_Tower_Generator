#include "pch.h"
#include "gtest/gtest.h"
#include "Triangle.h"


TEST(TriangleTest, ParameterizedConstructor) {
    Point3D vertex1(0.0f, 0.0f);
    Point3D vertex2(1.0f, 1.0f);
    Point3D vertex3(2.0f, 0.0f);
    Triangle triangle(vertex1, vertex2, vertex3);
    EXPECT_FLOAT_EQ(triangle.p1().x(), 0.0f);
    EXPECT_FLOAT_EQ(triangle.p3().x(), 2.0f);
}