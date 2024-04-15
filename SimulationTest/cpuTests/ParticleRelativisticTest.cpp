#include  "gtest/gtest.h"
#include "cpp/particle/ParticleRelativistic.h"

TEST(ParticleRelativisticTest, advance) {
	auto p = ParticleRelativistic(1, 1, {1, 1, 1}, {1, 1, 1});
	p.advance(1);
	ASSERT_EQ(
		Vector3D<float>(2, 2, 2), 
		p.position
	);
}

TEST(ParticleRelativisticTest, addMomentum) {
	auto p = ParticleRelativistic(1, 1, {1, 1, 1}, {100000000, 1, 1});
	p.addMomentum({100000000, 1, 1}, 1);
	ASSERT_EQ(
		Vector3D<float>(219355264, 2.1935527324676514, 2.1935527324676514), 
		p.velocity
	);
}

TEST(ParticleRelativisticTest, getMomentum) {
	auto p = ParticleRelativistic(1, 1, {1, 1, 1}, {100000000, 1, 1});
	ASSERT_EQ(
		Vector3D<float>(106075200, 1.0607520341873169, 1.0607520341873169), 
		p.getMomentum()
	);
}

TEST(ParticleRelativisticTest, mergeVelocitySame) {
	auto p1 = ParticleRelativistic(1, 1, {1, 1, 1}, {100000000, 1, 1});
	auto p2 = ParticleRelativistic(1, 1, {1, 1, 1}, {100000000, 1, 1});
	auto v3 = p1.mergeVelocity(&p2);
	ASSERT_EQ(
		Vector3D<float>(100000000, 1, 1), 
		v3
	);
}

TEST(ParticleRelativisticTest, mergeVelocityDifferent) {
	auto p1 = ParticleRelativistic(1, 1, {1, 1, 1}, {100000000, 1, 1});
	auto p2 = ParticleRelativistic(1, 1, {1, 1, 1}, {200000000, 1, 1});
	auto v3 = p1.mergeVelocity(&p2);
	ASSERT_EQ(
		Vector3D<float>(158832208, 1.0190718173980713, 1.0190718173980713), 
		v3
	);
}