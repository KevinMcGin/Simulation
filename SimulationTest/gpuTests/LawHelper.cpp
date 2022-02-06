#include  <gtest/gtest.h>
#include "LawHelper.h"
#include "particle/helper/ParticlesHelper.h"
#include "ParticleTestHelper.h"

#include <math.h>

double roundToNPlaces(const double value, const unsigned int nDecimalPlaces) {
	const unsigned int decimalPlaces = pow(10, nDecimalPlaces);
	return round(value * decimalPlaces) / (double)decimalPlaces;
}

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

void runGpuAndCpu(Law* law, vector<Particle*>& particlesCpu, vector<Particle*>& particlesGpu, const int stepsCount) {
	LawHelper::runCpuLaw(law, particlesCpu, stepsCount);
	LawHelper::runGpuLaw(law, particlesGpu, stepsCount);
}

void LawHelper::expectGpuLikeCpu(Law* law, const int particleCount, const int stepsCount) {
    vector<Particle*> particlesCpu = LawHelper::setupParticles(particleCount);
	vector<Particle*> particlesGpu = LawHelper::setupParticles(particleCount);
	runGpuAndCpu(law, particlesCpu, particlesGpu, stepsCount);
	ParticleTestHelper::expectParticlesEqual(particlesCpu, particlesGpu);
}

double roundTo5Places(double value) {
	return roundToNPlaces(value, 5);
}

void LawHelper::expectGpuLikeCpuRounded(Law* law, const int particleCount, const int stepsCount) {
    vector<Particle*> particlesCpu = LawHelper::setupParticles(particleCount);
	vector<Particle*> particlesGpu = LawHelper::setupParticles(particleCount);
	runGpuAndCpu(law, particlesCpu, particlesGpu, stepsCount);
    ASSERT_EQ(particlesCpu.size(), particlesGpu.size());
	for(int i = 0; i < particlesCpu.size(); i++) {
		auto particleCpu = particlesCpu[i];
		auto particleGpu = particlesGpu[i];

		particleCpu->mass = roundTo5Places(particleCpu->mass);
		particleGpu->mass = roundTo5Places(particleGpu->mass);
		particleCpu->radius = roundTo5Places(particleCpu->radius);
		particleGpu->radius = roundTo5Places(particleGpu->radius);
		particleCpu->position.x = roundTo5Places(particleGpu->position.x);
		particleCpu->position.y = roundTo5Places(particleGpu->position.y);
		particleCpu->position.z = roundTo5Places(particleGpu->position.z);
		particleGpu->position.x = roundTo5Places(particleGpu->position.x);
		particleGpu->position.y = roundTo5Places(particleGpu->position.y);
		particleGpu->position.z = roundTo5Places(particleGpu->position.z);
		particleCpu->velocity.x = roundTo5Places(particleGpu->velocity.x);
		particleCpu->velocity.y = roundTo5Places(particleGpu->velocity.y);
		particleCpu->velocity.z = roundTo5Places(particleGpu->velocity.z);
		particleGpu->velocity.x = roundTo5Places(particleGpu->velocity.x);
		particleGpu->velocity.y = roundTo5Places(particleGpu->velocity.y);
		particleGpu->velocity.z = roundTo5Places(particleGpu->velocity.z);

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
