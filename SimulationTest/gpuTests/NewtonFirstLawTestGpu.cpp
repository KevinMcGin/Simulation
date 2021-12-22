#include  <gtest/gtest.h>
#include "NewtonFirstLaw.cuh"
#include "LawHelper.h"

TEST(NewtonFirstLawTest, ParticleMoveGpu) {
	Law* law = new NewtonFirstLaw();
	vector<Particle*> particles = { new ParticleSimple(1,1,{0,0,0},{1,-1,0},{0,0,0}) };
    LawHelper::runGpuLaw(law, particles);
	Vector3D positions = particles.front()->position;
	EXPECT_EQ(1, positions.x);
	EXPECT_EQ(-1, positions.y);
	EXPECT_EQ(0, positions.z);
}

TEST(NewtonFirstLawTest, ParticleMoveGpuLikeCpu) {
	const int particleCount = 300;
	const int stepsCount = 2;
	Law* law = new NewtonFirstLaw();
	LawHelper::expectGpuLikeCpu(law, particleCount, stepsCount);
}