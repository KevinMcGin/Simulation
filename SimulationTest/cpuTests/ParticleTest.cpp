#include  "gtest/gtest.h"
#include "shared/particle/Particle.cuh"

TEST(ParticleTest, advance) {
	auto p = Particle(1, 1, {1, 1, 1}, {1, 1, 1});
	p.advance(1);
	ASSERT_EQ(
		Vector3D<float>(2, 2, 2), 
		p.position
	);
}