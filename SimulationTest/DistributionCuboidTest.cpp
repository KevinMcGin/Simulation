#include  <gtest/gtest.h>
#include "DistributionCuboid.h"

TEST(DistributionCuboidTest, ParticleInCuboid) {
	Vector3D mean = { 1,-1,1, };
	Vector3D delta = { 1,3,1 };
	DistributionCuboid cuboid(mean, delta);
	Vector3D position = cuboid.getValue();
	Vector3D vec = position - mean;
	EXPECT_TRUE(vec.x <= 1 && vec.x >= -1);
	EXPECT_TRUE(vec.y <= 3 && vec.y >= -3);
	EXPECT_TRUE(vec.z <= 1 && vec.z >= -1);
}