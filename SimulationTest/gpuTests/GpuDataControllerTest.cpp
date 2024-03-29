#include  <gtest/gtest.h>
#include "cuda/gpuHelper/GpuDataController.cuh"
#include "shared/particle/Particle.cuh"

TEST(GpuDataControllerTest, putParticlesOnDevice) {
	auto gpuDataController = GpuDataController();
	std::vector<Particle*> particles {
		new Particle(),
	};

	gpuDataController.putParticlesOnDevice(
		particles, 
		true
	);

	gpuDataController.putParticlesOnDevice(
		particles, 
		false
	);
}

TEST(GpuDataControllerTest, getParticlesFromDevice) {
	auto gpuDataController = GpuDataController();
	std::vector<Particle*> particlesInput {
		new Particle(),
	};
	particlesInput[0]->mass = 1.0;
	std::vector<Particle*> particlesOutput {
		new Particle(),
	};
	EXPECT_NE(particlesOutput[0]->mass, particlesInput[0]->mass);

	gpuDataController.putParticlesOnDevice(
		particlesInput, 
		true
	);
	gpuDataController.getParticlesFromDevice(particlesOutput);

	EXPECT_EQ(particlesOutput.size(), particlesInput.size());
	EXPECT_EQ(particlesOutput[0]->mass, particlesInput[0]->mass);
}

TEST(GpuDataControllerTest, deleteParticlesOnDevice) {
	auto gpuDataController = GpuDataController();
	std::vector<Particle*> particlesInput {
		new Particle(),
		new Particle(),
	};
	particlesInput[0]->deleted = true;
	particlesInput[1]->mass = 1.0;
	std::vector<Particle*> particlesOutput {
		new Particle(),
		new Particle(),
	};
	EXPECT_EQ(particlesOutput.size(), 2);
	EXPECT_NE(particlesOutput[0]->deleted, particlesInput[0]->deleted);
	EXPECT_NE(particlesOutput[1]->mass, particlesInput[1]->mass);

	gpuDataController.putParticlesOnDevice(
		particlesInput, 
		true
	);
	gpuDataController.deleteParticlesOnDevice();
	gpuDataController.getParticlesFromDevice(particlesOutput);

	EXPECT_EQ(gpuDataController.getParticleCount(), 1);
	EXPECT_EQ(particlesOutput.size(), 1);
	EXPECT_EQ(particlesOutput[0]->mass, particlesInput[0]->mass);
}