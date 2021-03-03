#include "pch.h"
#include "../src/DistributionGlobe.h"

TEST(DistributionGlobeTest, ParticleInGlobe) {
	DistributionGlobe globe({ 0,0,0 }, { 1,3,1 });
	array<double, 3> position = globe.getValue();
	EXPECT_TRUE(position[0] <= 1 && position[0] >= -1);
	EXPECT_TRUE(position[1] <= 3 && position[1] >= -3);
	EXPECT_TRUE(position[2] <= 1 && position[2] >= -1);
}