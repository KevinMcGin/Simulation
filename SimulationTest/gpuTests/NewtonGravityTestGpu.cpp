#include  <gtest/gtest.h>
#include "cpp/law/gravity/NewtonGravity.h"
#include "LawHelper.h"
#include "NewtonGravityTestHelper.h"
#include "shared/service/momentum/newton/NewtonMomentumService.cuh"

TEST(NewtonGravityTest, ParticlesAccelerateGpu) {
	auto law = std::make_shared<NewtonGravity>(std::make_shared<NewtonMomentumService>(), 0.05);
	std::vector<Particle*> particles = NewtonGravityTestHelper::getParticlesAccelerate();
    LawHelper::runGpuLaw(law, particles);
	NewtonGravityTestHelper::testParticlesAccelerate(particles);
}

//Todo: sometimes this fails, github ticket: #192
TEST(NewtonGravityTest, ManyParticlesAccelerateGpu) {
	auto law = std::make_shared<NewtonGravity>(std::make_shared<NewtonMomentumService>(), 2000);
	int particleCount = 30 * 1000;
	std::vector<Particle*> particles = LawHelper::setupParticles(particleCount);

	auto p11 = particles[2 * 1000];
	auto p12 = particles[29 * 1000];
	EXPECT_EQ(Vector3D<float>(-2000, 4000, -4000), p11->velocity);
	EXPECT_EQ(Vector3D<float>(-29000, 58000, -58000), p12->velocity);

    LawHelper::runGpuLaw(law, particles);

	auto p21 = particles[2 * 1000];
	auto p22 = particles[29 * 1000];
	EXPECT_EQ(Vector3D<float>(-1278.722412109375, 3278.724853515625, -3278.724853515625), p21->velocity);
	EXPECT_EQ(Vector3D<float>(-29020.396484375, 58019.4453125, -58019.4453125), p22->velocity);
}

TEST(NewtonGravityTest, ParticlesAccelerateGpuLikeCpuSimple) {
	const int particleCount = 300;
	const int stepsCount = 2;
	auto law = std::make_shared<NewtonGravity>(std::make_shared<NewtonMomentumService>(), 0.05);
	
	LawHelper::expectGpuLikeCpu(law, particleCount, stepsCount);
}

TEST(NewtonGravityTest, ParticlesAccelerateGpuLikeCpuMemoryLow) {
	CudaWithError::setMaxMemoryPerEvent(500);

	const int particleCount = 20;
	const int stepsCount = 1;
	auto law = std::make_shared<NewtonGravity>(std::make_shared<NewtonMomentumService>(), 5);

	LawHelper::expectGpuLikeCpu(law, particleCount, stepsCount);
}

TEST(NewtonGravityTest, ParticlesAccelerateGpuLikeCpuMemoryTooLowToContinue) {
	CudaWithError::setMaxMemoryPerEvent(100);

	const int particleCount = 30;
	const int stepsCount = 2;
	auto law = std::make_shared<NewtonGravity>(std::make_shared<NewtonMomentumService>(), 0.05);

	try {
		LawHelper::expectGpuLikeCpu(law, particleCount, stepsCount);
        FAIL() << "No error thrown: expected GPU can not run these many particles in Gravity";
    } catch(std::runtime_error const &err) {
        EXPECT_EQ(err.what(), std::string("GPU can not run these many particles in Gravity"));
    } catch(...) {
        FAIL() << "Wrong error thrown: expected GPU can not run these many particles in Gravity";
    }
}

TEST(NewtonGravityTest, ParticlesAccelerateGpuLikeCpuMemoryTooLowToAllocate) {
	CudaWithError::setMaxMemoryPerEvent(10);
	
	const int particleCount = 30;
	const int stepsCount = 2;
	auto law = std::make_shared<NewtonGravity>(std::make_shared<NewtonMomentumService>(), 0.05);

	 try {
		LawHelper::expectGpuLikeCpu(law, particleCount, stepsCount);
        FAIL() << "No error thrown: expected Ran out of GPU memory";
    } catch(std::runtime_error const &err) {
        EXPECT_EQ(err.what(), std::string("Ran out of GPU memory"));
    } catch(...) {
        FAIL() << "Wrong error thrown: expected Ran out of GPU memory";
    }
}