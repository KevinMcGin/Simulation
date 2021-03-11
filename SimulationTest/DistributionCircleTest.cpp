#include  <gtest/gtest.h>
#include "DistributionCircle.h"

TEST(DistributionCircleTest, ParticleInGlobe) {
	Vector3D mean = { 1,-1,0 };
	double delta = 2;
	DistributionCircle circle(mean, delta);
	Vector3D position = circle.getValue();
	double magnitude = Vector3D(position.x - mean.x, position.y - mean.y, 0).magnitude();
	EXPECT_TRUE(magnitude <= delta);
	EXPECT_TRUE(position.z == 0);
}