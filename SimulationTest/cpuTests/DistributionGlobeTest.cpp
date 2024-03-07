#include  <gtest/gtest.h>
#include "cpp/distribution/DistributionGlobe.h"

TEST(DistributionGlobeTest, ParticleInGlobe) {
	//TODO transform test from testing a cuboid to a globe
	Vector3D<float> mean = { 1,-1,1, };
	Vector3D<float> delta = { 1,3,1 };
	DistributionGlobe globe(mean, delta);
	Vector3D<float> position = globe.getValue();
	Vector3D<float> vec = position-mean;
	EXPECT_TRUE(vec.x <= 1 && vec.x >= -1);
	EXPECT_TRUE(vec.y <= 3 && vec.y >= -3);
	EXPECT_TRUE(vec.z <= 1 && vec.z >= -1);
}