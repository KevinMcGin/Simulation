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

//Todo: sometimes this fails, github ticket: #192
TEST(NewtonGravityTest, ManyParticlesAccelerateGpu) {
	Law* law = new NewtonGravity(5);
	int particleCount = 30 * 1000;
	std::vector<Particle*> particles = LawHelper::setupParticles(particleCount);
	auto p1 = particles[20 * 1000];
	EXPECT_EQ(Vector3D<float>(-20000, 40000, -40000), p1->velocity);
    LawHelper::runGpuLaw(law, particles);
	auto p2 = particles[2 * 1000];
	EXPECT_EQ(Vector3D<float>(-1998.4111328125, 3999.052490234375, -3999.052490234375), p2->velocity);
}

TEST(NewtonGravityTest, ParticlesAccelerateGpuLikeCpu) {
	const int particleCount = 300;
	const int stepsCount = 2;
	Law* law = new NewtonGravity(0.05);
	LawHelper::expectGpuLikeCpu(law, particleCount, stepsCount);
}