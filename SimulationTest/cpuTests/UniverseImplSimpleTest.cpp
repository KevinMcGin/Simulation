#include  <gtest/gtest.h>
#include "cpp/universe/UniverseImplSimple.h"
#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "cpp/law/gravity/NewtonGravity.h"
#include "cpp/universe/input/SimulationInputSimple.h"
#include "cpp/universe/input/SimulationInputSimpleLargeVelocities.h"
#include "cpp/universe/output/SimulationOutputPrint.h"

TEST(UniverseImplSimpleTest, UniverseRuns) {
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputPrint>();
	UniverseImplSimple universe(input, output, 100, 10, FALSE);
	universe.run();
	Vector3D<float> position1 = universe.particles.front()->position;
	Vector3D<float> position2 = universe.particles.back()->position;
	EXPECT_EQ(Vector3D<float>(1001, 3.3596782600398001e-07, 0), position1);
	EXPECT_EQ(Vector3D<float>(2.1543971051585231e-09, 1010, 0), position2);
}

TEST(UniverseImplSimpleTest, UniverseRunsLargeVelocitiesNewtonMomentum) {
	auto einsteinMomentum = false;
	auto input = std::make_shared<SimulationInputSimpleLargeVelocities>();
	auto output = std::make_shared<SimulationOutputPrint>();
	UniverseImplSimple universe(input, output, 100, 10, FALSE, einsteinMomentum);
	universe.run();
	Vector3D<float> position1 = universe.particles.front()->position;
	Vector3D<float> position2 = universe.particles.back()->position;
	EXPECT_EQ(Vector3D<float>(99999956992, 3.0830167929707386e-07, 0), position1);
	EXPECT_EQ(Vector3D<float>(2.0267103550963839e-08, 99999956992, 0), position2);
}

TEST(UniverseImplSimpleTest, UniverseRunsLargeVelocitiesEinsteinMomentum) {
	auto einsteinMomentum = true;
	auto input = std::make_shared<SimulationInputSimpleLargeVelocities>();
	auto output = std::make_shared<SimulationOutputPrint>();
	UniverseImplSimple universe(input, output, 100, 10, FALSE, einsteinMomentum);
	universe.run();
	Vector3D<float> position1 = universe.particles.front()->position;
	Vector3D<float> position2 = universe.particles.back()->position;
	EXPECT_EQ(Vector3D<float>(99999956992, 3.6797393931919942e-07, 0), position1);
	EXPECT_EQ(Vector3D<float>(8.0363060650512352e-10, 106075144192, 0), position2);
}