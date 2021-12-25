#include  <gtest/gtest.h>
#include "UniverseImpl.h"
#include "NewtonFirstLaw.cuh"
#include "NewtonGravity.cuh"
#include "SimulationInputSimple.h"
#include "SimulationOutputPrint.h"

TEST(UniverseImplTest, UniverseRuns) {
	auto input = make_shared<SimulationInputSimple>();
	auto output = make_shared<SimulationOutputPrint>();
	Law* law1 = new NewtonGravity(0.05);
	Law* law2 = new NewtonFirstLaw();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	Universe* universe = new UniverseImpl({ law1, law2 }, input, output, 1, 10);
	universe->run();
	Vector3D position1 = universe->particles.front()->position;
	Vector3D position2 = universe->particles.back()->position;
	EXPECT_EQ(Vector3D(10.746798179090352, 0.25320182090965099, 0), position1);
	EXPECT_EQ(Vector3D(0.25320182090965099, 10.746798179090352, 0), position2);
}