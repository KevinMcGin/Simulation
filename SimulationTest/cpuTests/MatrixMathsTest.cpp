#include  <gtest/gtest.h>
#include "shared/util/MatrixMaths.cuh"

TEST(MatrixMathsTest, getLowerTriangularCoordinates) {
    unsigned long long x, y;

    unsigned long long i = 0;
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

    i = 5 * 1000 * 1000 * 1000;
    MatrixMaths::getLowerTriangularCoordinates(i, &x, &y);
	EXPECT_EQ(12679, x);
	EXPECT_EQ(37551, y);
}

TEST(MatrixMathsTest, getUpperTriangularIndex) {
    unsigned long long x = 1;
    unsigned long long y = 0;
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
    unsigned long long x = 0;
    unsigned long long y = 01;
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