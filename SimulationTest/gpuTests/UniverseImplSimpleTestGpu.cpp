#include  <gtest/gtest.h>
#include "cpp/universe/UniverseImplSimple.h"
#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "cpp/law/gravity/NewtonGravity.h"
#include "cpp/universe/input/SimulationInputSimple.h"
#include "cpp/universe/output/SimulationOutputPrint.h"
#include "cpp/universe/input/SimulationInputSimpleLargeVelocities.h"
#include "ParticleTestHelper.h"

TEST(UniverseImplSimpleTestGpu, UniverseRunsGpu) {
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputPrint>();
	const unsigned int stepCount = 1;
	const unsigned int deltaTime = 1;
	UniverseImplSimple universe(input, output, stepCount, deltaTime, TRUE);
	universe.run();
	Vector3D<float> position1 = universe.particles.front()->position;
	Vector3D<float> position2 = universe.particles.back()->position;
	EXPECT_EQ(Vector3D<float>(2, 3.0830178687768495e-11, 0), position1);
	EXPECT_EQ(Vector3D<float>(6.5754225794713989e-14, 11, 0), position2);
}

TEST(UniverseImplSimpleTestGpu, UniverseCpuLikeGpuNewtonMomentum) {
	auto einsteinMomentum = false;
	const unsigned int stepCount = 2;
	const unsigned int deltaTime = 2;
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputPrint>();
	UniverseImplSimple universeCpu(input, output, stepCount, deltaTime, FALSE, einsteinMomentum);
	UniverseImplSimple universeGpu(input, output, stepCount, deltaTime, TRUE, einsteinMomentum);
	universeCpu.run();
	universeGpu.run();
	ParticleTestHelper::expectParticlesEqual(universeCpu.particles, universeGpu.particles);
}

TEST(UniverseImplSimpleTestGpu, UniverseCpuLikeGpuEinsteinMomentum) {
	auto einsteinMomentum = true;
	const unsigned int stepCount = 2;
	const unsigned int deltaTime = 2;
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputPrint>();
	UniverseImplSimple universeCpu(input, output, stepCount, deltaTime, FALSE, einsteinMomentum);
	UniverseImplSimple universeGpu(input, output, stepCount, deltaTime, TRUE, einsteinMomentum);
	universeCpu.run();
	universeGpu.run();
	ParticleTestHelper::expectParticlesEqual(universeCpu.particles, universeGpu.particles);
}

TEST(UniverseImplSimpleTestGpu, UniverseCpuLikeGpuLargeVelocitiesNewtonMomentum) {
	auto einsteinMomentum = false;
	const unsigned int stepCount = 2;
	const unsigned int deltaTime = 2;
	auto input = std::make_shared<SimulationInputSimpleLargeVelocities>();
	auto output = std::make_shared<SimulationOutputPrint>();
	UniverseImplSimple universeCpu(input, output, stepCount, deltaTime, FALSE, einsteinMomentum);
	UniverseImplSimple universeGpu(input, output, stepCount, deltaTime, TRUE, einsteinMomentum);
	universeCpu.run();
	universeGpu.run();
	ParticleTestHelper::expectParticlesEqual(universeCpu.particles, universeGpu.particles);
}

TEST(UniverseImplSimpleTestGpu, UniverseRunsLargeVelocitiesEinsteinMomentum) {
	auto einsteinMomentum = true;
	const unsigned int stepCount = 2;
	const unsigned int deltaTime = 2;
	auto input = std::make_shared<SimulationInputSimpleLargeVelocities>();
	auto output = std::make_shared<SimulationOutputPrint>();
	UniverseImplSimple universeCpu(input, output, stepCount, deltaTime, FALSE, einsteinMomentum);
	UniverseImplSimple universeGpu(input, output, stepCount, deltaTime, TRUE, einsteinMomentum);
	universeCpu.run();
	universeGpu.run();
	ParticleTestHelper::expectParticlesEqual(universeCpu.particles, universeGpu.particles);
}