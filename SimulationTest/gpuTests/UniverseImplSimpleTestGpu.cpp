#include  <gtest/gtest.h>
#include "universe/UniverseImplSimple.h"
#include "law/newtonFirstLaw/NewtonFirstLaw.h"
#include "law/gravity/NewtonGravity.h"
#include "universe/input/SimulationInputSimple.h"
#include "universe/output/SimulationOutputPrint.h"
#include "ParticleTestHelper.h"

TEST(UniverseImplSimpleTest, UniverseRunsGpu) {
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputPrint>();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	Universe* universe = new UniverseImplSimple(input, output, 10, TRUE);
	universe->run();
	Vector3D<float> position1 = universe->particles.front()->position;
	Vector3D<float> position2 = universe->particles.back()->position;
	EXPECT_EQ(Vector3D<float>(10.99970817565918, 0.00042869150638580322, 0), position1);
	EXPECT_EQ(Vector3D<float>(3.744336027011741e-06, 19.999950408935547, 0), position2);
}

TEST(UniverseImplSimpleTest, UniverseCpuLikeGpu) {
	const int stepCount = 2;
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputPrint>();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	Universe* universeCpu = new UniverseImplSimple(input, output, stepCount, FALSE);
	universeCpu->run();
	Universe* universeGpu = new UniverseImplSimple(input, output, stepCount, TRUE);
	universeGpu->run();
	ParticleTestHelper::expectParticlesEqual(universeCpu->particles, universeGpu->particles);
}