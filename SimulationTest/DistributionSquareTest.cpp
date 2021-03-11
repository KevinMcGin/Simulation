#include "pch.h"
#include "DistributionSquare.h"

TEST(DistributionSquareTest, ParticleInGlobe) {
	DistributionSquare square({ 0,0,0 }, 1);
	Vector3D position = square.getValue();
	EXPECT_TRUE(position.x <= 1 && position.y >= -1);
	EXPECT_TRUE(position.y <= 1 && position.y >= -1);
	EXPECT_TRUE(position.z == 0);
}