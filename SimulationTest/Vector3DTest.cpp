#include "pch.h"
#include "../src/Vector3D.h"

TEST(Vector3DTest, vectorsMagnitudeSquared) {
	Vector3D v1({ -1/sqrt(2),1/sqrt(2),0 });
	double magnitudeSquared = v1.magnitudeSquared();
	EXPECT_DOUBLE_EQ(1, magnitudeSquared);
}

TEST(Vector3DTest, vectorsUnit) {
	Vector3D v1({ 0,-1,1 });
	Vector3D vUnit = v1.unit();
	EXPECT_EQ(Vector3D(0, -1 / sqrt(2) , 1 / sqrt(2)), vUnit);
}

TEST(Vector3DTest, vectorsAdd) {
	Vector3D v1({ 0,1,0 });
	Vector3D v2({ -1,0,0 });
	Vector3D v3 = v1 + v2;
	EXPECT_EQ(Vector3D(-1, 1, 0), v3);
}

TEST(Vector3DTest, vectorsSubtract) {
	Vector3D v1({ 0,1,0 });
	Vector3D v2({ -1,0,2 });
	Vector3D v3 = v1 - v2;
	EXPECT_EQ(Vector3D(1, 1, -2), v3);
}

TEST(Vector3DTest, vectorsMultiply) {
	Vector3D v1({ 0,1,-1 });
	Vector3D v2 = 3.0 * v1;
	EXPECT_EQ(Vector3D(0, 3, -3), v2);
}


TEST(Vector3DTest, vectorsDivide) {
	Vector3D v1({ 0,1,-1 });
	Vector3D v2 = v1 / 2.0;
	EXPECT_EQ(Vector3D(0, 0.5, -0.5), v2);
}