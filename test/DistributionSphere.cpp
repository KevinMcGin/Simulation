#include "pch.h"
#include "../src/DistributionSphere.h"

TEST(DistributionSphereTest, ParticleInGlobe) {
	DistributionSphere globe({ 0,0,0 }, 1);
	array<double, 3> position = globe.getValue();
	EXPECT_TRUE(position[0] <= 1 && position[0] >= -1);
	EXPECT_TRUE(position[1] <= 1 && position[1] >= -1);
	EXPECT_TRUE(position[1] <= 1 && position[1] >= -1);
}