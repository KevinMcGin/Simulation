#include  <gtest/gtest.h>
#include "distribution/DistributionSquare.h"

TEST(DistributionSquareTest, ParticleInGlobe) {
	DistributionSquare square({ 0,0,0 }, 1);
	Vector3D<float> position = square.getValue();
	EXPECT_TRUE(position.x <= 1 && position.y >= -1);
	EXPECT_TRUE(position.y <= 1 && position.y >= -1);
	EXPECT_TRUE(position.z == 0);
}