#include "pch.h"
#include "../src/UniverseImpl.h"
#include "../src/NewtonFirstLaw.h"
#include "../src/NewtonGravity.h"
#include "../src/SimulationInputSimple.h"
#include "../src/SimulationOutputPrint.h"

TEST(UniverseImplTest, UniverseRuns) {
	SimulationInput* input = new SimulationInputSimple();
	SimulationOutput* output = new SimulationOutputPrint();
	Law* law1 = new NewtonGravity(0.5);
	Law* law2 = new NewtonFirstLaw();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	Universe* universe = new UniverseImpl({ law1, law2 }, input, output, 1, 10);
	universe->run();
	Vector3D positions = universe->particles.front()->position;
	EXPECT_EQ(5, positions.x);
	EXPECT_EQ(6, positions.y);
	EXPECT_EQ(0, positions.z);
}