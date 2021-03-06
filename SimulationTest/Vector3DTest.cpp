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
	EXPECT_EQ(0, vUnit.x);
	EXPECT_EQ(-1 / sqrt(2), vUnit.y);
	EXPECT_EQ(1 / sqrt(2), vUnit.z);
}

TEST(Vector3DTest, vectorsAdd) {
	Vector3D v1({ 0,1,0 });
	Vector3D v2({ -1,0,0 });
	Vector3D v3 = v1 + v2;
	EXPECT_EQ(-1, v3.x);
	EXPECT_EQ(1, v3.y);
	EXPECT_EQ(0, v3.z);
}

TEST(Vector3DTest, vectorsSubtract) {
	Vector3D v1({ 0,1,0 });
	Vector3D v2({ -1,0,2 });
	Vector3D v3 = v1 - v2;
	EXPECT_EQ(1, v3.x);
	EXPECT_EQ(1, v3.y);
	EXPECT_EQ(-2, v3.z);
}

TEST(Vector3DTest, vectorsMultiply) {
	Vector3D v1({ 0,1,-1 });
	Vector3D v2 = 3.0 * v1;
	EXPECT_EQ(0, v2.x);
	EXPECT_EQ(3, v2.y);
	EXPECT_EQ(-3, v2.z);
}


TEST(Vector3DTest, vectorsDivide) {
	Vector3D v1({ 0,1,-1 });
	Vector3D v2 = v1 / 2.0;
	EXPECT_EQ(0, v2.x);
	EXPECT_EQ(0.5, v2.y);
	EXPECT_EQ(-0.5, v2.z);
}