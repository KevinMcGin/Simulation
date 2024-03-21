#include  <gtest/gtest.h>
#include "cpp/distribution/DistributionCube.h"

TEST(DistributionCubeTest, ParticleInGlobe) {
	DistributionCube cube({ 0,0,0 }, 1);
	Vector3D<float> position = cube.getValue();
	EXPECT_TRUE(position.x <= 1 && position.x >= -1);
	EXPECT_TRUE(position.y <= 1 && position.y >= -1);
	EXPECT_TRUE(position.z <= 1 && position.z >= -1);
}

