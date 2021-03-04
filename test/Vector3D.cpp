#include "pch.h"
#include "../src/Vector3D.h"

TEST(DistributionSphereTest, vectorsAdd) {
	Vector3D v1({ 0,1,0 });
	Vector3D v2({ -1,0,0 });
	Vector3D v3 = v1 + v2;
	EXPECT_EQ(-1, v3.x);
	EXPECT_EQ(1, v3.y);
	EXPECT_EQ(0, v3.z);
}

TEST(DistributionSphereTest, vectorsSubtract) {
	Vector3D v1({ 0,1,0 });
	Vector3D v2({ -1,0,2 });
	Vector3D v3 = v1 - v2;
	EXPECT_EQ(1, v3.x);
	EXPECT_EQ(1, v3.y);
	EXPECT_EQ(-2, v3.z);
}