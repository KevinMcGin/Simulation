#include  <gtest/gtest.h>
#include "universe/UniverseImplSimple.h"
#include "law/newtonFirstLaw/NewtonFirstLaw.h"
#include "law/gravity/NewtonGravity.h"
#include "universe/input/SimulationInputSimple.h"
#include "universe/output/SimulationOutputPrint.h"

TEST(UniverseImplSimpleTest, UniverseRuns) {
	auto input = make_shared<SimulationInputSimple>();
	auto output = make_shared<SimulationOutputPrint>();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	Universe* universe = new UniverseImplSimple(input, output, 10, FALSE);
	universe->run();
	Vector3D position1 = universe->particles.front()->position;
	Vector3D position2 = universe->particles.back()->position;
	EXPECT_EQ(Vector3D(10.999750414769919, 0.00024958523008162739, 0), position1);
	EXPECT_EQ(Vector3D(0.00024958523008162739, 10.999750414769919, 0), position2);
}