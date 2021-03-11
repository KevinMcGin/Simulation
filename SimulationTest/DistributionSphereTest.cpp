#include #include <gtest/gtest.h>
#include "DistributionSphere.h"

TEST(DistributionSphereTest, ParticleInGlobe) {
	Vector3D mean = { 1,-1,0 };
	double delta = 2;
	DistributionSphere sphere(mean, delta);
	Vector3D position = sphere.getValue();
	double magnitude = (position - mean).magnitude();
	EXPECT_TRUE(magnitude <= delta);
}
