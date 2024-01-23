#include "pch.h"
#include "gtest/gtest.h"
#include "Point3D.h"

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}


TEST(Point3DTest, DefaultConstructor) {
    Point3D point(0.0f, 0.0f);
    EXPECT_FLOAT_EQ(point.x(), 0.0f);
    EXPECT_FLOAT_EQ(point.y(), 0.0f);
}

TEST(Point3DTest, ParameterizedConstructor) {
    Point3D point(1.0f, 2.0f);
    EXPECT_FLOAT_EQ(point.x(), 1.0f);
    EXPECT_FLOAT_EQ(point.y(), 2.0f);
}

TEST(Point3DTest, SettersAndGetters) {
    Point3D point(0.0f, 0.0f);
    point.setX(3.0f);
    point.setY(4.0f);

    EXPECT_FLOAT_EQ(point.x(), 3.0f);
    EXPECT_FLOAT_EQ(point.y(), 4.0f);
}
