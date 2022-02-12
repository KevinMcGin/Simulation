#include  <gtest/gtest.h>
#include "ParticleTestHelper.h"

void ParticleTestHelper::expectParticlesEqual(vector<Particle*> particlesCpu, vector<Particle*> particlesGpu) {
    ASSERT_EQ(particlesCpu.size(), particlesGpu.size());
	for(int i = 0; i < particlesCpu.size(); i++) {
		auto particleCpu = particlesCpu[i];
		auto particleGpu = particlesGpu[i];
		EXPECT_DOUBLE_EQ(particleCpu->mass, particleGpu->mass);
		EXPECT_DOUBLE_EQ(particleCpu->radius, particleGpu->radius);
		EXPECT_EQ(particleCpu->position, particleGpu->position);
		EXPECT_EQ(particleCpu->velocity, particleGpu->velocity);
	}
}