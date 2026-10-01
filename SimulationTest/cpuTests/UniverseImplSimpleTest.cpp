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
	Vector3D<Real> position1 = universe.particles.front()->position;
	Vector3D<Real> position2 = universe.particles.back()->position;
	EXPECT_EQ(Vector3D<Real>(1000.9999997370859, 3.3596766197369523e-07, 0), position1);
	EXPECT_EQ(Vector3D<Real>(2.1543967972467369e-09, 1009.999999575092, 0), position2);
	Vector3D<Real> velocity1 = universe.particles.front()->velocity;
	Vector3D<Real> velocity2 = universe.particles.back()->velocity;
	EXPECT_EQ(Vector3D<Real>(0.99999999973601683, 3.3718547082873006e-10, 0), velocity1);
	EXPECT_EQ(Vector3D<Real>(2.2411244267660272e-12, 0.99999999916711924, 0), velocity2);
}

// Worth reading the x figures: the first particle starts at x = 1 moving
// at 1e8 m/s, and the run is 1000 simulated seconds, so inertia alone puts
// it at exactly 1e11 + 1. That is what comes out now. At float these same
// expectations read 99999956992 — 43 kilometres short — because a float
// simply cannot hold 1e11 to the metre.
TEST(UniverseImplSimpleTest, UniverseRunsLargeVelocitiesNewtonMomentum) {
	LawConfig lawConfig;
	ASSERT_EQ("", lawConfig.setMomentum("newton"));
	auto input = std::make_shared<SimulationInputSimpleLargeVelocities>();
	auto output = std::make_shared<SimulationOutputNothing>();
	UniverseImplSimple universe(input, output, 100, 10, FALSE, lawConfig);
	universe.run();
	Vector3D<Real> position1 = universe.particles.front()->position;
	Vector3D<Real> position2 = universe.particles.back()->position;
	EXPECT_EQ(Vector3D<Real>(100000000001, 3.0830178691416724e-07, 0), position1);
	EXPECT_EQ(Vector3D<Real>(6.5754583968155485e-10, 100000000010, 0), position2);
	Vector3D<Real> velocity1 = universe.particles.front()->velocity;
	Vector3D<Real> velocity2 = universe.particles.back()->velocity;
	EXPECT_EQ(Vector3D<Real>(100000000, 3.0830178691416754e-10, 0), velocity1);
	EXPECT_EQ(Vector3D<Real>(6.5755291366497002e-13, 100000000, 0), velocity2);
}

TEST(UniverseImplSimpleTest, UniverseRunsLargeVelocitiesEinsteinMomentum) {
	LawConfig lawConfig;
	ASSERT_EQ("", lawConfig.setMomentum("einstein"));
	auto input = std::make_shared<SimulationInputSimpleLargeVelocities>();
	auto output = std::make_shared<SimulationOutputNothing>();
	UniverseImplSimple universe(input, output, 100, 10, FALSE, lawConfig);
	universe.run();
	Vector3D<Real> position1 = universe.particles.front()->position;
	Vector3D<Real> position2 = universe.particles.back()->position;
	EXPECT_EQ(Vector3D<Real>(100000000001.00002, 2.9064454913595461e-07, 0), position1);
	EXPECT_EQ(Vector3D<Real>(6.1988630120868725e-10, 100000000010.00002, 0), position2);
	Vector3D<Real> velocity1 = universe.particles.front()->velocity;
	Vector3D<Real> velocity2 = universe.particles.back()->velocity;
	EXPECT_EQ(Vector3D<Real>(100000000.00000003, 2.9064454913595453e-10, 0), velocity1);
	EXPECT_EQ(Vector3D<Real>(6.1989258810534321e-13, 100000000.00000003, 0), velocity2);
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
	EXPECT_EQ(Vector3D<Real>(1001, 0, 0), universe.particles.front()->position);
	EXPECT_EQ(Vector3D<Real>(1, 0, 0), universe.particles.front()->velocity);
}

TEST(UniverseImplSimpleTest, WithNoLawsAtAllNothingMoves) {
	LawConfig lawConfig;
	ASSERT_EQ("", lawConfig.setLaws(""));
	auto input = std::make_shared<SimulationInputSimple>();
	auto output = std::make_shared<SimulationOutputNothing>();
	UniverseImplSimple universe(input, output, 100, 10, FALSE, lawConfig);
	universe.run();
	EXPECT_EQ(Vector3D<Real>(1, 0, 0), universe.particles.front()->position);
	EXPECT_EQ(Vector3D<Real>(1, 0, 0), universe.particles.front()->velocity);
}

TEST(UniverseImplSimpleTest, GravitationalConstantScalesTheAttraction) {
	auto run = [](Real gravitationalConstant) {
		LawConfig lawConfig;
		lawConfig.setLaws("newtonGravity,newtonFirstLaw");
		lawConfig.gravitationalConstant = gravitationalConstant;
		auto input = std::make_shared<SimulationInputSimple>();
		auto output = std::make_shared<SimulationOutputNothing>();
		UniverseImplSimple universe(input, output, 100, 10, FALSE, lawConfig);
		universe.run();
		return universe.particles.front()->position.y;
	};

	const Real realG = (Real)PhysicalConstants::GRAVITATIONAL_CONSTANT;
	const Real drift = run(realG);
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
