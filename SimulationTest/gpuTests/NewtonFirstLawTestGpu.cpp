#include  <gtest/gtest.h>
#include "NewtonFirstLawTestHelper.h"
#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "LawHelper.h"

TEST(NewtonFirstLawTest, ParticleMoveGpu) {
	auto law = std::make_shared<NewtonFirstLaw>();
	std::vector<Particle*> particles = NewtonFirstLawTestHelper::getParticleMove();
    LawHelper::runGpuLaw(law, particles);
	NewtonFirstLawTestHelper::testParticleMove(particles);
}

TEST(NewtonFirstLawTest, ParticleMoveGpuLikeCpu) {
	const int particleCount = 300;
	const int stepsCount = 2;
	auto law = std::make_shared<NewtonFirstLaw>();
	LawHelper::expectGpuLikeCpu(law, particleCount, stepsCount);
}