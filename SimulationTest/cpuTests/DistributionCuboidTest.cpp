#include  <gtest/gtest.h>
#include "cpp/distribution/DistributionCuboid.h"

TEST(DistributionCuboidTest, ParticleInCuboid) {
	Vector3D<Real> mean = { 1,-1,1, };
	Vector3D<Real> delta = { 1,3,1 };
	DistributionCuboid cuboid(mean, delta);
	Vector3D<Real> position = cuboid.getValue();
	Vector3D<Real> vec = position - mean;
	EXPECT_TRUE(vec.x <= 1 && vec.x >= -1);
	EXPECT_TRUE(vec.y <= 3 && vec.y >= -3);
	EXPECT_TRUE(vec.z <= 1 && vec.z >= -1);
}