#include  <gtest/gtest.h>
#include "ParticleTestHelper.h"

void ParticleTestHelper::expectParticlesEqual(std::vector<Particle*> particlesCpu, std::vector<Particle*> particlesGpu) {
    ASSERT_EQ(particlesCpu.size(), particlesGpu.size());
	for(int i = 0; i < particlesCpu.size(); i++) {
		auto particleCpu = particlesCpu[i];
		auto particleGpu = particlesGpu[i];
		EXPECT_FLOAT_EQ(particleCpu->mass, particleGpu->mass);
		EXPECT_FLOAT_EQ(particleCpu->radius, particleGpu->radius);
		EXPECT_EQ(particleCpu->position, particleGpu->position);
		EXPECT_EQ(particleCpu->velocity, particleGpu->velocity);
	}
}