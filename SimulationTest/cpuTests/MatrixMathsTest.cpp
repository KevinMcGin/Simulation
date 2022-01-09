#include  <gtest/gtest.h>
#include "util/MatrixMaths.cuh"

TEST(MatrixMathsTest, getLowerTriangularCoordinates) {
    int x, y;

    int i = 0;
    MatrixMaths::getLowerTriangularCoordinates(i, &x, &y);
	EXPECT_EQ(0, x);
	EXPECT_EQ(1, y);

    i = 2;
    MatrixMaths::getLowerTriangularCoordinates(i, &x, &y);
	EXPECT_EQ(1, x);
	EXPECT_EQ(2, y);

    i = 5;
    MatrixMaths::getLowerTriangularCoordinates(i, &x, &y);
	EXPECT_EQ(2, x);
	EXPECT_EQ(3, y);
}

TEST(MatrixMathsTest, getUpperTriangularIndex) {
    int x = 1;
    int y = 0;
    auto i = MatrixMaths::getUpperTriangularIndex(x, y);
	EXPECT_EQ(0, i);

    x = 4;
    y = 0;
    i = MatrixMaths::getUpperTriangularIndex(x, y);
	EXPECT_EQ(6, i);
    
    x = 3;
    y = 2;
    i = MatrixMaths::getUpperTriangularIndex(x, y);
	EXPECT_EQ(5, i);
}

TEST(MatrixMathsTest, getLowerTriangularIndex) {
    int x = 0;
    int y = 01;
    auto i = MatrixMaths::getLowerTriangularIndex(x, y);
	EXPECT_EQ(0, i);

    x = 0;
    y = 4;
    i = MatrixMaths::getLowerTriangularIndex(x, y);
	EXPECT_EQ(6, i);
    
    x = 2;
    y = 3;
    i = MatrixMaths::getLowerTriangularIndex(x, y);
	EXPECT_EQ(5, i);
}