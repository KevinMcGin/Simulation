#include  <gtest/gtest.h>
#include "universe/UniverseImplSimple.h"
#include "law/newtonFirstLaw/NewtonFirstLaw.h"
#include "law/gravity/NewtonGravity.h"
#include "universe/input/SimulationInputSimple.h"
#include "universe/output/SimulationOutputPrint.h"
#include "ParticleTestHelper.h"

TEST(UniverseImplSimpleTest, UniverseRunsGpu) {
	auto input = make_shared<SimulationInputSimple>();
	auto output = make_shared<SimulationOutputPrint>();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	Universe* universe = new UniverseImplSimple(input, output, 10, TRUE);
	universe->run();
	Vector3D position1 = universe->particles.front()->position;
	Vector3D position2 = universe->particles.back()->position;
	EXPECT_EQ(Vector3D(10.999709230039111, 0.00042869149976955677, 0), position1);
	EXPECT_EQ(Vector3D(3.7443363493448025e-06, 19.999949766975732, 0), position2);
}

TEST(UniverseImplSimpleTest, UniverseCpuLikeGpu) {
	const int stepCount = 2;
	auto input = make_shared<SimulationInputSimple>();
	auto output = make_shared<SimulationOutputPrint>();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	Universe* universeCpu = new UniverseImplSimple(input, output, stepCount, FALSE);
	universeCpu->run();
	Universe* universeGpu = new UniverseImplSimple(input, output, stepCount, TRUE);
	universeGpu->run();
	ParticleTestHelper::expectParticlesEqual(universeCpu->particles, universeGpu->particles);
}