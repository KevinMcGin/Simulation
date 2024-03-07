#include  <gtest/gtest.h>
#include "cpp/universe/UniverseImpl.h"
#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "cpp/law/gravity/NewtonGravity.h"
#include "cpp/universe/input/SimulationInputSimple.h"
#include "cpp/universe/output/SimulationOutputPrint.h"

TEST(UniverseImplTest, UniverseRuns) {
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputPrint>();
	auto law1 = std::make_shared<NewtonGravity>(0.05);
	auto law2 = std::make_shared<NewtonFirstLaw>();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	UniverseImpl universe({ law1, law2 }, input, output, 1, 10, FALSE);
	universe.run();
	Vector3D<float> position1 = universe.particles.front()->position;
	Vector3D<float> position2 = universe.particles.back()->position;
	EXPECT_EQ(Vector3D<float>(10.70539665222168, 0.43437403440475464, 0), position1);
	EXPECT_EQ(Vector3D<float>(0.0040383300853633879, 19.94956988354156, 0), position2);
}