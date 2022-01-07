#include  <gtest/gtest.h>
#include "NewtonGravity.h"
#include "LawHelper.h"
#include "NewtonGravityTestHelper.h"

TEST(NewtonGravityTest, ParticlesAccelerateGpu) {
	Law* law = new NewtonGravity(0.05);
	vector<Particle*> particles = NewtonGravityTestHelper::getParticlesAccelerate();
    LawHelper::runGpuLaw(law, particles);
	NewtonGravityTestHelper::testParticlesAccelerate(particles);
}

TEST(NewtonGravityTest, ParticlesAccelerateGpuLikeCpu) {
	const int particleCount = 300;
	const int stepsCount = 2;
	Law* law = new NewtonGravity(0.05);
	LawHelper::expectGpuLikeCpu(law, particleCount, stepsCount);
}