#include  <gtest/gtest.h>
#include "cpp/universe/UniverseImpl.h"
#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "cpp/law/gravity/NewtonGravity.h"
#include "cpp/universe/input/SimulationInputSimple.h"
#include "cpp/universe/output/SimulationOutputNothing.h"
#include "shared/service/momentum/newton/NewtonMomentumService.cuh"


TEST(UniverseImplTest, UniverseRuns) {
	auto momentumService = std::make_shared<NewtonMomentumService>();
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputNothing>();
	auto law1 = std::make_shared<NewtonGravity>(momentumService, 0.05);
	auto law2 = std::make_shared<NewtonFirstLaw>();
	//TODO: change delta time to non 1 value with required implementation and change in expects
	UniverseImpl universe({ law1, law2 }, input, output, 1, 10, FALSE);
	universe.run();
	Vector3D<Real> position1 = universe.particles.front()->position;
	Vector3D<Real> position2 = universe.particles.back()->position;
	EXPECT_EQ(Vector3D<Real>(10.705396036418106, 0.43437401693910876, 0), position1);
	EXPECT_EQ(Vector3D<Real>(0.0040383300853633879, 19.94956988354156, 0), position2);
}