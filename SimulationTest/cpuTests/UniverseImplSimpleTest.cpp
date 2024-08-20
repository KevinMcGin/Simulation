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
	Vector3D<float> velocity1 = universe.particles.front()->velocity;
	Vector3D<float> velocity2 = universe.particles.back()->velocity;
	EXPECT_EQ(Vector3D<float>(1, 3.3718564051987698e-10, 0), velocity1);
	EXPECT_EQ(Vector3D<float>(2.2411248204456946e-12, 1, 0), velocity2);
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
	Vector3D<float> velocity1 = universe.particles.front()->velocity;
	Vector3D<float> velocity2 = universe.particles.back()->velocity;
	EXPECT_EQ(Vector3D<float>(100000000, 3.0830177299989714e-10, 0), velocity1);
	EXPECT_EQ(Vector3D<float>(2.0267091824233141e-11, 100000000, 0), velocity2);
}

TEST(UniverseImplSimpleTest, UniverseRunsLargeVelocitiesEinsteinMomentum) {
	auto einsteinMomentum = true;
	auto input = std::make_shared<SimulationInputSimpleLargeVelocities>();
	auto output = std::make_shared<SimulationOutputPrint>();
	UniverseImplSimple universe(input, output, 100, 10, FALSE, einsteinMomentum);
	universe.run();
	Vector3D<float> position1 = universe.particles.front()->position;
	Vector3D<float> position2 = universe.particles.back()->position;
	EXPECT_EQ(Vector3D<float>(99999956992, 2.5830607341958967e-07, 0), position1);
	EXPECT_EQ(Vector3D<float>(5.5091159412157253e-10, 99999965184, 0), position2);
	Vector3D<float> velocity1 = universe.particles.front()->velocity;
	Vector3D<float> velocity2 = universe.particles.back()->velocity;
	EXPECT_EQ(Vector3D<float>(100000000, 2.5830593219922093e-10, 0), velocity1);
	EXPECT_EQ(Vector3D<float>(5.5091180098734704e-13, 100000008, 0), velocity2);
}