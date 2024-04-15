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

TEST(ParticleTest, addMomentum) {
	auto p = Particle(1, 1, {1, 1, 1}, {100000000, 1, 1});
	p.addMomentum({100000000, 1, 1}, 1);
	ASSERT_EQ(
		Vector3D<float>(200000000, 2, 2), 
		p.velocity
	);
}

TEST(ParticleTest, getMomentum) {
	auto p = Particle(1, 1, {1, 1, 1}, {100000000, 1, 1});
	ASSERT_EQ(
		Vector3D<float>(100000000, 1, 1), 
		p.getMomentum()
	);
}

TEST(ParticleTest, mergeVelocitySame) {
	auto p1 = Particle(1, 1, {1, 1, 1}, {100000000, 1, 1});
	auto p2 = Particle(1, 1, {1, 1, 1}, {100000000, 1, 1});
	auto v3 = p1.mergeVelocity(&p2);
	ASSERT_EQ(
		Vector3D<float>(100000000, 1, 1), 
		v3
	);
}

TEST(ParticleTest, mergeVelocityDifferent) {
	auto p1 = Particle(1, 1, {1, 1, 1}, {100000000, 1, 1});
	auto p2 = Particle(1, 1, {1, 1, 1}, {200000000, 1, 1});
	auto v3 = p1.mergeVelocity(&p2);
	ASSERT_EQ(
		Vector3D<float>(150000000, 1, 1), 
		v3
	);
}