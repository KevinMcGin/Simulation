#include  <gtest/gtest.h>
#include "distribution/DistributionCircle.h"

TEST(DistributionCircleTest, ParticleInGlobe) {
	Vector3D<float> mean = { 1,-1,0 };
	float delta = 2;
	DistributionCircle circle(mean, delta);
	Vector3D<float> position = circle.getValue();
	float magnitude = Vector3D<float>(position.x - mean.x, position.y - mean.y, 0).magnitude();
	EXPECT_TRUE(magnitude <= delta);
	EXPECT_TRUE(position.z == 0);
}