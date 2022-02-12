#include  <gtest/gtest.h>
#include "law/gravity/NewtonGravity.h"
#include "LawHelper.h"
#include "NewtonGravityTestHelper.h"

TEST(NewtonGravityTest, ParticlesAccelerateGpu) {
	Law* law = new NewtonGravity(0.05);
	std::vector<Particle*> particles = NewtonGravityTestHelper::getParticlesAccelerate();
    LawHelper::runGpuLaw(law, particles);
	NewtonGravityTestHelper::testParticlesAccelerate(particles);
}

TEST(NewtonGravityTest, ManyParticlesAccelerateGpu) {
	Law* law = new NewtonGravity(0.5);
	int particleCount = 30 * 1000;
	std::vector<Particle*> particles = LawHelper::setupParticles(particleCount);
	auto p1 = particles[20 * 1000];
	EXPECT_EQ(Vector3D(-20000, 40000, -40000), p1->velocity);
    LawHelper::runGpuLaw(law, particles);
	auto p2 = particles[2 * 1000];
	EXPECT_EQ(Vector3D(-1999.8196813033317, 3999.8196813033546, -3999.8196813033546), p2->velocity);
}

TEST(NewtonGravityTest, ParticlesAccelerateGpuLikeCpu) {
	const int particleCount = 300;
	const int stepsCount = 2;
	Law* law = new NewtonGravity(0.05);
	LawHelper::expectGpuLikeCpu(law, particleCount, stepsCount);
}