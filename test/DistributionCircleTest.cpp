#include "pch.h"
#include "../src/DistributionCircle.h"

TEST(DistributionCircleTest, ParticleInGlobe) {
	DistributionCircle globe({ 0,0,0 }, 1);
	array<double, 3> position = globe.getValue();
	EXPECT_TRUE(position[0] <= 1 && position[0] >= -1);
	EXPECT_TRUE(position[1] <= 1 && position[1] >= -1);
	EXPECT_TRUE(position[2] == 0);
}