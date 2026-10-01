#include  <gtest/gtest.h>
#include "cpp/distribution/DistributionCircle.h"

TEST(DistributionCircleTest, ParticleInGlobe) {
	Vector3D<Real> mean = { 1,-1,0 };
	Real delta = 2;
	DistributionCircle circle(mean, delta);
	Vector3D<Real> position = circle.getValue();
	Real magnitude = Vector3D<Real>(position.x - mean.x, position.y - mean.y, 0).magnitude();
	EXPECT_TRUE(magnitude <= delta);
	EXPECT_TRUE(position.z == 0);
}