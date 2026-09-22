#include  <gtest/gtest.h>
#include "cpp/universe/UniverseImplSimple.h"
#include "cpp/law/LawConfig.h"
#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "cpp/law/gravity/NewtonGravity.h"
#include "cpp/universe/input/SimulationInputSimple.h"
#include "cpp/universe/input/SimulationInputSimpleLargeVelocities.h"
#include "cpp/universe/output/SimulationOutputNothing.h"

TEST(UniverseImplSimpleTest, UniverseRuns) {
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputNothing>();
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
	LawConfig lawConfig;
	ASSERT_EQ("", lawConfig.setMomentum("newton"));
	auto input = std::make_shared<SimulationInputSimpleLargeVelocities>();
	auto output = std::make_shared<SimulationOutputNothing>();
	UniverseImplSimple universe(input, output, 100, 10, FALSE, lawConfig);
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
	LawConfig lawConfig;
	ASSERT_EQ("", lawConfig.setMomentum("einstein"));
	auto input = std::make_shared<SimulationInputSimpleLargeVelocities>();
	auto output = std::make_shared<SimulationOutputNothing>();
	UniverseImplSimple universe(input, output, 100, 10, FALSE, lawConfig);
	universe.run();
	Vector3D<float> position1 = universe.particles.front()->position;
	Vector3D<float> position2 = universe.particles.back()->position;
	EXPECT_EQ(Vector3D<float>(99999956992, 2.9064437967463164e-07, 0), position1);
	EXPECT_EQ(Vector3D<float>(6.1988242316957098e-10, 99999965184, 0), position2);
	Vector3D<float> velocity1 = universe.particles.front()->velocity;
	Vector3D<float> velocity2 = universe.particles.back()->velocity;
	EXPECT_EQ(Vector3D<float>(100000000, 2.9064453621607811e-10, 0), velocity1);
	EXPECT_EQ(Vector3D<float>(6.1988315955968654e-13, 100000016, 0), velocity2);
}

// The law config decides which laws run, so the observable check is what
// each configuration does to the particles — not which objects got built.
//
// SimulationInputSimple's first particle starts at (1, 0, 0) travelling
// along x at 1 unit/s, and these runs are 100 frames of 10s each, so
// inertia alone lands it at exactly x = 1001 with nothing at all on y.

TEST(UniverseImplSimpleTest, WithoutGravityParticlesOnlyCoast) {
	LawConfig lawConfig;
	ASSERT_EQ("", lawConfig.setLaws("newtonFirstLaw"));
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputNothing>();
	UniverseImplSimple universe(input, output, 100, 10, FALSE, lawConfig);
	universe.run();
	// Exactly zero off-axis, where the same run with gravity on drifts to
	// 3.36e-07: nothing pulled it sideways.
	EXPECT_EQ(Vector3D<float>(1001, 0, 0), universe.particles.front()->position);
	EXPECT_EQ(Vector3D<float>(1, 0, 0), universe.particles.front()->velocity);
}

TEST(UniverseImplSimpleTest, WithNoLawsAtAllNothingMoves) {
	LawConfig lawConfig;
	ASSERT_EQ("", lawConfig.setLaws(""));
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputNothing>();
	UniverseImplSimple universe(input, output, 100, 10, FALSE, lawConfig);
	universe.run();
	EXPECT_EQ(Vector3D<float>(1, 0, 0), universe.particles.front()->position);
	EXPECT_EQ(Vector3D<float>(1, 0, 0), universe.particles.front()->velocity);
}

TEST(UniverseImplSimpleTest, GravitationalConstantScalesTheAttraction) {
	auto run = [](float gravitationalConstant) {
		LawConfig lawConfig;
		lawConfig.setLaws("newtonGravity,newtonFirstLaw");
		lawConfig.gravitationalConstant = gravitationalConstant;
		auto input = std::make_shared<SimulationInputSimple>();
		auto output = std::make_shared<SimulationOutputNothing>();
		UniverseImplSimple universe(input, output, 100, 10, FALSE, lawConfig);
		universe.run();
		return universe.particles.front()->position.y;
	};

	const float realG = (float)PhysicalConstants::GRAVITATIONAL_CONSTANT;
	const float drift = run(realG);
	// The other particles all sit up the y axis, so the first one is pulled
	// off its own axis — further the stronger gravity is made.
	EXPECT_GT(drift, 0);
	EXPECT_GT(run(realG * 1000), drift);
}

// A default-constructed config has to mean the full set of laws, since that
// is what a caller who never mentions laws — the constructor's own default
// argument — silently gets.
TEST(UniverseImplSimpleTest, TheDefaultConfigRunsEveryLaw) {
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputNothing>();
	UniverseImplSimple defaulted(input, output, 100, 10, FALSE);
	defaulted.run();

	auto explicitInput = std::make_shared<SimulationInputSimple>();
	auto explicitOutput = std::make_shared<SimulationOutputNothing>();
	LawConfig lawConfig;
	ASSERT_EQ("", lawConfig.setLaws("collisionCoalesce,newtonGravity,newtonFirstLaw"));
	ASSERT_EQ("", lawConfig.setMomentum("newton"));
	UniverseImplSimple configured(explicitInput, explicitOutput, 100, 10, FALSE, lawConfig);
	configured.run();

	EXPECT_EQ(configured.particles.front()->position, defaulted.particles.front()->position);
	EXPECT_EQ(configured.particles.back()->position, defaulted.particles.back()->position);
}
