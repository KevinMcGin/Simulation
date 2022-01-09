#include  <gtest/gtest.h>
#include "LawHelper.h"
#include "particle/helper/ParticlesHelper.h"

void LawHelper::runCpuLaw(Law* law, vector<Particle*>& particles, const int stepsCount) {
	for(int i = 0; i < stepsCount; i++) {
		law->cpuLaw->run(particles);
	}
}

void LawHelper::runGpuLaw(Law* law, vector<Particle*>& particles, const int stepsCount) {
    GpuDataController gpuDataController = GpuDataController();
	for(int i = 0; i < stepsCount; i++) {
    	gpuDataController.putParticlesOnDevice(particles, true);
		law->gpuLaw->run(gpuDataController.get_td_par(), gpuDataController.getParticleCount());
    	gpuDataController.getParticlesFromDevice(particles);
    	ParticlesHelper::removeDeletedParticles(particles);
	}
}

void LawHelper::expectGpuLikeCpu(Law* law, const int particleCount, const int stepsCount) {
    vector<Particle*> particlesCpu = LawHelper::setupParticles(particleCount);
	vector<Particle*> particlesGpu = LawHelper::setupParticles(particleCount);
	LawHelper::runCpuLaw(law, particlesCpu, stepsCount);
	LawHelper::runGpuLaw(law, particlesGpu, stepsCount);
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

vector<Particle*> LawHelper::setupParticles(const int particleCount) {
	vector<Particle*> particles = {};
	for(double i = 0; i < particleCount; i++) {
		particles.push_back(
			new ParticleSimple(
				i + 1, i + 1, { i, -i, i }, { -i, 2 * i, -2 * i }, { 0, 0, 0 }
			)
		);
	}
	return particles;
}
