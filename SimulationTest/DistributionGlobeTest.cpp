#include "pch.h"
#include "../src/DistributionGlobe.h"

TEST(DistributionGlobeTest, ParticleInGlobe) {
	DistributionGlobe globe({ 0,0,0 }, { 1,3,1 });
	Vector3D position = globe.getValue();
	EXPECT_TRUE(position.x <= 1 && position.x >= -1);
	EXPECT_TRUE(position.y <= 3 && position.y >= -3);
	EXPECT_TRUE(position.z <= 1 && position.z >= -1);
}