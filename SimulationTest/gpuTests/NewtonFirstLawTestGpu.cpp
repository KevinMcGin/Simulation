#include  <gtest/gtest.h>
#include "NewtonFirstLaw.cuh"
#include "GpuDataController.cuh"
#include "ParticleSimple.h"

TEST(NewtonFirstLawTest, ParticleMoveGpu) {
	NewtonFirstLaw law = NewtonFirstLaw();
	vector<Particle*> particles = { new ParticleSimple(1,1,{0,0,0},{1,-1,0},{0,0,0}) };
    GpuDataController gpuDataController = GpuDataController();
    gpuDataController.putParticlesOnDevice(particles, true);
	law.gpuRun(gpuDataController.get_td_par(), gpuDataController.getParticleCount());
    gpuDataController.getParticlesFromDevice(particles);
	Vector3D positions = particles.front()->position;
	EXPECT_EQ(1, positions.x);
	EXPECT_EQ(-1, positions.y);
	EXPECT_EQ(0, positions.z);
}