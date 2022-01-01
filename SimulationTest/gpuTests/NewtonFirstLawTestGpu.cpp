#include  <gtest/gtest.h>
#include "NewtonFirstLawTestHelper.h"
#include "NewtonFirstLaw.cuh"
#include "LawHelper.h"

TEST(NewtonFirstLawTest, ParticleMoveGpu) {
	Law* law = new NewtonFirstLaw();
	vector<Particle*> particles = NewtonFirstLawTestHelper::getParticleMove();
    LawHelper::runGpuLaw(law, particles);
	NewtonFirstLawTestHelper::testParticleMove(particles);
}

TEST(NewtonFirstLawTest, ParticleMoveGpuLikeCpu) {
	const int particleCount = 300;
	const int stepsCount = 2;
	Law* law = new NewtonFirstLaw();
	LawHelper::expectGpuLikeCpu(law, particleCount, stepsCount);
}