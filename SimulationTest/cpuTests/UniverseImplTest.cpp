#include  <gtest/gtest.h>
#include "universe/UniverseImpl.h"
#include "law/newtonFirstLaw/NewtonFirstLaw.h"
#include "law/gravity/NewtonGravity.h"
#include "universe/input/SimulationInputSimple.h"
#include "universe/output/SimulationOutputPrint.h"

TEST(UniverseImplTest, UniverseRuns) {
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputPrint>();
	Law* law1 = new NewtonGravity(0.05);
	Law* law2 = new NewtonFirstLaw();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	Universe* universe = new UniverseImpl({ law1, law2 }, input, output, 1, 10, FALSE);
	universe->run();
	Vector3D position1 = universe->particles.front()->position;
	Vector3D position2 = universe->particles.back()->position;
	EXPECT_EQ(Vector3D(10.705396036418106, 0.43437401693910876, 0), position1);
	EXPECT_EQ(Vector3D(0.0040383300853633879, 19.94956988354156, 0), position2);
}