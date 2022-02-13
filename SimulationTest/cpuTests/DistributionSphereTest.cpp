#include  <gtest/gtest.h>
#include "distribution/DistributionSphere.h"

TEST(DistributionSphereTest, ParticleInGlobe) {
	Vector3D<float> mean = { 1,-1,0 };
	float delta = 2;
	DistributionSphere sphere(mean, delta);
	Vector3D<float> position = sphere.getValue();
	float magnitude = (position - mean).magnitude();
	EXPECT_TRUE(magnitude <= delta);
}
