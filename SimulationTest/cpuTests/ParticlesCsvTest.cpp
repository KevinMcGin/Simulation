#include  <gtest/gtest.h>
#include "cpp/universe/input/ParticlesCsv.h"
#include "cpp/universe/input/SimulationInputCsvText.h"
#include "cpp/universe/input/SimulationInputCombined.h"
#include "cpp/universe/input/SimulationInputSimple.h"
#include "ParticleTestHelper.h"

#include <sstream>

namespace {
	const char* header = "mass,radius,positionX,positionY,positionZ,velocityX,velocityY,velocityZ";

	std::vector<Particle*> parse(const std::string& csv) {
		std::istringstream stream(csv);
		return ParticlesCsv::parse(stream);
	}
}

TEST(ParticlesCsvTest, ReadsAParticlePerRow) {
	auto particles = parse(std::string(header) + "\n1,2,3,4,5,6,7,8\n9,10,11,12,13,14,15,16\n");

	ASSERT_EQ(2, particles.size());
	EXPECT_EQ(1, particles[0]->mass);
	EXPECT_EQ(8, particles[0]->velocity.z);
	EXPECT_EQ(9, particles[1]->mass);
	EXPECT_EQ(16, particles[1]->velocity.z);

	ParticleTestHelper::deleteParticles(particles);
}

TEST(ParticlesCsvTest, ReadsAHeaderWithNoRowsAsNoParticles) {
	auto particles = parse(std::string(header) + "\n");
	EXPECT_EQ(0, particles.size());
}

TEST(ParticlesCsvTest, RejectsAColumnTheEngineDoesNotKnow) {
	EXPECT_THROW(parse("mass,radius,wobble\n1,2,3\n"), std::invalid_argument);
}

// A row that cannot be read abandons the document, and the particles read
// before it must not be left behind — the leak checker in CI would see it,
// but only if something exercises the path.
TEST(ParticlesCsvTest, FreesWhatItReadWhenARowIsUnreadable) {
	EXPECT_THROW(
		parse(std::string(header) + "\n1,2,3,4,5,6,7,8\n9,10,11,12,13,14,15,16,17\n"),
		std::invalid_argument
	);
}

TEST(SimulationInputCsvTextTest, ReadsCsvHeldInMemory) {
	SimulationInputCsvText input(std::string(header) + "\n1,2,3,4,5,6,7,8\n");
	auto particles = input.input();

	ASSERT_EQ(1, particles.size());
	EXPECT_EQ(1, particles[0]->mass);

	ParticleTestHelper::deleteParticles(particles);
}

// The point of combining: a generated system and a supplied one seed the
// same universe, rather than the caller having to choose between them.
TEST(SimulationInputCombinedTest, ConcatenatesEveryInputInOrder) {
	auto generated = std::make_shared<SimulationInputSimple>();
	auto supplied = std::make_shared<SimulationInputCsvText>(
		std::string(header) + "\n100,2,3,4,5,6,7,8\n"
	);

	SimulationInputCombined combined({ generated, supplied });
	auto particles = combined.input();

	// SimulationInputSimple's four, then the supplied one.
	ASSERT_EQ(5, particles.size());
	EXPECT_EQ(100, particles.back()->mass) << "the supplied particle should come last";

	ParticleTestHelper::deleteParticles(particles);
}

TEST(SimulationInputCombinedTest, CombiningNothingIsNotAnError) {
	SimulationInputCombined combined({});
	auto particles = combined.input();
	EXPECT_EQ(0, particles.size());
}

// One source failing abandons the run, so the particles the earlier sources
// already produced have nobody left to free them.
TEST(SimulationInputCombinedTest, FreesEarlierInputsWhenALaterOneFails) {
	auto generated = std::make_shared<SimulationInputSimple>();
	auto broken = std::make_shared<SimulationInputCsvText>("mass,radius,wobble\n1,2,3\n");

	SimulationInputCombined combined({ generated, broken });
	EXPECT_THROW(combined.input(), std::invalid_argument);
}

// The inputs are additive and each source brings its own header, so the
// bodies someone pastes in follow a generated system's columns without
// having to agree with them.
TEST(ParticlesCsvTest, ReadsSeveralDocumentsConcatenated) {
	auto particles = parse(
		std::string(header) + "\n1,2,3,4,5,6,7,8\n" +
		std::string(header) + "\n9,10,11,12,13,14,15,16\n"
	);

	ASSERT_EQ(2, particles.size());
	EXPECT_EQ(1, particles[0]->mass);
	EXPECT_EQ(9, particles[1]->mass);

	ParticleTestHelper::deleteParticles(particles);
}

// Each header describes only the rows beneath it. Merging the two
// documents under one would read this second particle's mass as its
// position.
TEST(ParticlesCsvTest, EachDocumentKeepsItsOwnColumnOrder) {
	auto particles = parse(
		std::string(header) + "\n1,2,3,4,5,6,7,8\n"
		"positionX,mass,radius\n"
		"100,7,0.5\n"
	);

	ASSERT_EQ(2, particles.size());
	EXPECT_EQ(3, particles[0]->position.x);
	EXPECT_EQ(7, particles[1]->mass);
	EXPECT_EQ(0.5, particles[1]->radius);
	EXPECT_EQ(100, particles[1]->position.x);

	ParticleTestHelper::deleteParticles(particles);
}

TEST(ParticlesCsvTest, RejectsASecondDocumentWithAnUnknownColumn) {
	EXPECT_THROW(
		parse(std::string(header) + "\n1,2,3,4,5,6,7,8\nmass,wobble\n1,2\n"),
		std::invalid_argument
	);
}

// Scientific notation is how the solar system data arrives — 1.988e+30 is a
// value, not a column name.
TEST(ParticlesCsvTest, TreatsScientificNotationAsAValue) {
	auto particles = parse(std::string(header) + "\n1.988409871326422e+30,6.957e+08,0,0,0,0,0,0\n");

	ASSERT_EQ(1, particles.size());
	EXPECT_DOUBLE_EQ(1.988409871326422e+30, particles[0]->mass);

	ParticleTestHelper::deleteParticles(particles);
}
