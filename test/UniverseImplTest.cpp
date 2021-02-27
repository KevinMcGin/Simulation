#include "pch.h"
#include "../src/UniverseImpl.h"
#include "../src/NewtonFirstLaw.h"
#include "../src/NewtonGravity.h"
#include "../src/SimulationInputSimple.h"
#include "../src/SimulationOutputSimple.h"

TEST(UniverseImplTest, UniverseRuns) {
	SimulationInput* input = new SimulationInputSimple();
	SimulationOutput* output = new SimulationOutputSimple();
	Law* law1 = new NewtonGravity();
	Law* law2 = new NewtonFirstLaw();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	Universe* universe = new UniverseImpl({ law1, law2 }, input, output, 1, 10);
	universe->run();
	array<double, 3> positions = universe->particles.front()->position;
	EXPECT_EQ(5, positions[0]);
	EXPECT_EQ(6, positions[1]);
	EXPECT_EQ(0, positions[2]);
}