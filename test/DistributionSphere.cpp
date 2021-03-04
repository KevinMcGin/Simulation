#include "pch.h"
#include "../src/DistributionSphere.h"

TEST(DistributionSphereTest, ParticleInGlobe) {
	DistributionSphere globe({ 0,0,0 }, 1);
	Vector3D position = globe.getValue();
	EXPECT_TRUE(position.x <= 1 && position.x >= -1);
	EXPECT_TRUE(position.y <= 1 && position.y >= -1);
	EXPECT_TRUE(position.z <= 1 && position.z >= -1);
}