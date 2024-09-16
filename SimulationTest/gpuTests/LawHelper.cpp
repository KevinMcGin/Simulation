#include  <gtest/gtest.h>
#include "LawHelper.h"
#include "cpp/particle/helper/ParticlesHelper.h"
#include "ParticleTestHelper.h"

#include <math.h>

float roundToNPlaces(const float value, const unsigned int nDecimalPlaces) {
	const unsigned int decimalPlaces = pow(10, nDecimalPlaces);
	return round(value * decimalPlaces) / (float)decimalPlaces;
}

void LawHelper::runCpuLaw(std::shared_ptr<Law> law, std::vector<Particle*>& particles, const int stepsCount) {
	for(int i = 0; i < stepsCount; i++) {
		law->cpuLaw->run(particles);
	}
}

void LawHelper::runGpuLaw(std::shared_ptr<Law> law, std::vector<Particle*>& particles, const int stepsCount) {
    GpuDataController gpuDataController = GpuDataController();
	for(int i = 0; i < stepsCount; i++) {
    	gpuDataController.putParticlesOnDevice(particles, true);
		law->gpuLaw->run(gpuDataController.get_td_par(), gpuDataController.getParticleCount());
    	gpuDataController.getParticlesFromDevice(particles);
    	ParticlesHelper::removeDeletedParticles(particles);
	}
}

void runGpuAndCpu(std::shared_ptr<Law> law, std::vector<Particle*>& particlesCpu, std::vector<Particle*>& particlesGpu, const int stepsCount) {
	LawHelper::runCpuLaw(law, particlesCpu, stepsCount);
	LawHelper::runGpuLaw(law, particlesGpu, stepsCount);
}

void LawHelper::expectGpuLikeCpu(std::shared_ptr<Law> law, const int particleCount, const int stepsCount) {
    std::vector<Particle*> particlesCpu = LawHelper::setupParticles(particleCount);
	std::vector<Particle*> particlesGpu = LawHelper::setupParticles(particleCount);
	runGpuAndCpu(law, particlesCpu, particlesGpu, stepsCount);
	ParticleTestHelper::expectParticlesEqual(particlesCpu, particlesGpu);
}

float roundTo3Places(float value) {
	return roundToNPlaces(value, 3);
}

void LawHelper::expectGpuLikeCpuRounded(
	std::unique_ptr<Law> law, 
	const int particleCount, 
	const int stepsCount,
	const bool doAsserts
) {
    std::vector<Particle*> particlesCpu = LawHelper::setupParticles(particleCount);
	std::vector<Particle*> particlesGpu = LawHelper::setupParticles(particleCount);
	runGpuAndCpu(
		stdd::move(law),
		particlesCpu,
		particlesGpu,
		stepsCount
	);
    ASSERT_EQ(particlesCpu.size(), particlesGpu.size());

	if (doAsserts) {
		for(int i = 0; i < particlesCpu.size(); i++) {
			auto particleCpu = particlesCpu[i];
			auto particleGpu = particlesGpu[i];

			particleCpu->mass = roundTo3Places(particleCpu->mass);
			particleGpu->mass = roundTo3Places(particleGpu->mass);
			particleCpu->radius = roundTo3Places(particleCpu->radius);
			particleGpu->radius = roundTo3Places(particleGpu->radius);
			particleCpu->position.x = roundTo3Places(particleGpu->position.x);
			particleCpu->position.y = roundTo3Places(particleGpu->position.y);
			particleCpu->position.z = roundTo3Places(particleGpu->position.z);
			particleGpu->position.x = roundTo3Places(particleGpu->position.x);
			particleGpu->position.y = roundTo3Places(particleGpu->position.y);
			particleGpu->position.z = roundTo3Places(particleGpu->position.z);
			particleCpu->velocity.x = roundTo3Places(particleGpu->velocity.x);
			particleCpu->velocity.y = roundTo3Places(particleGpu->velocity.y);
			particleCpu->velocity.z = roundTo3Places(particleGpu->velocity.z);
			particleGpu->velocity.x = roundTo3Places(particleGpu->velocity.x);
			particleGpu->velocity.y = roundTo3Places(particleGpu->velocity.y);
			particleGpu->velocity.z = roundTo3Places(particleGpu->velocity.z);

			EXPECT_FLOAT_EQ(particleCpu->mass, particleGpu->mass);
			EXPECT_FLOAT_EQ(particleCpu->radius, particleGpu->radius);
			EXPECT_EQ(particleCpu->position, particleGpu->position);
			EXPECT_EQ(particleCpu->velocity, particleGpu->velocity);
		}
	}
}

std::vector<Particle*> LawHelper::setupParticles(const int particleCount) {
	std::vector<Particle*> particles = {};
	for(float i = 0; i < particleCount; i++) {
		particles.push_back(
			new ParticleSimple(
				i + 1, i + 1, { i, -i, i }, { -i, 2 * i, -2 * i }
			)
		);
	}
	return particles;
}
