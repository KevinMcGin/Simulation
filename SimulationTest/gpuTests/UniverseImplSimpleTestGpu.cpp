#include  <gtest/gtest.h>
#include "cpp/universe/UniverseImplSimple.h"
#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "cpp/law/gravity/NewtonGravity.h"
#include "cpp/universe/input/SimulationInputSimple.h"
#include "cpp/universe/output/SimulationOutputPrint.h"
#include "ParticleTestHelper.h"

TEST(UniverseImplSimpleTestGpu, UniverseRunsGpu) {
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputPrint>();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	const unsigned int stepCount = 1;
	UniverseImplSimple universe(input, output, stepCount, TRUE);
	universe.run();
	Vector3D<float> position1 = universe.particles.front()->position;
	Vector3D<float> position2 = universe.particles.back()->position;
	EXPECT_EQ(Vector3D<float>(10.99970817565918, 0.00042869150638580322, 0), position1);
	EXPECT_EQ(Vector3D<float>(3.744336027011741e-06, 19.999950408935547, 0), position2);
}

TEST(UniverseImplSimpleTestGpu, UniverseCpuLikeGpu) {
	const unsigned int stepCount = 1;
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputPrint>();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	UniverseImplSimple universeCpu(input, output, stepCount, FALSE);
	UniverseImplSimple universeGpu(input, output, stepCount, TRUE);
	universeCpu.run();
	universeGpu.run();
	ParticleTestHelper::expectParticlesEqual(universeCpu.particles, universeGpu.particles);
}