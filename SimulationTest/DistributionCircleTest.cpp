#include "pch.h"
#include "../src/DistributionCircle.h"

TEST(DistributionCircleTest, ParticleInGlobe) {
	DistributionCircle globe({ 0,0,0 }, 1);
	Vector3D position = globe.getValue();
	EXPECT_TRUE(position.x <= 1 && position.y >= -1);
	EXPECT_TRUE(position.y <= 1 && position.y >= -1);
	EXPECT_TRUE(position.z == 0);
}