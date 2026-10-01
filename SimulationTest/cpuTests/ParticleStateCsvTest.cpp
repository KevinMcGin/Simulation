#include  <gtest/gtest.h>
#include "cpp/universe/output/ParticleStateCsv.h"
#include "cpp/universe/input/SimulationInputCsv.h"
#include "cpp/particle/ParticleSimple.h"
#include "ParticleTestHelper.h"

#include <fstream>

TEST(ParticleStateCsvTest, RendersEveryColumnTheEngineReads) {
	std::vector<Particle*> particles = {
		new ParticleSimple(1, 0.5, {0, 0.25, -2}, {3, 0, 0.125})
	};

	std::string expected =
		"mass,radius,positionX,positionY,positionZ,velocityX,velocityY,velocityZ\n"
		"1,0.5,0,0.25,-2,3,0,0.125\n";
	EXPECT_EQ(expected, ParticleStateCsv::render(particles));

	ParticleTestHelper::deleteParticles(particles);
}

TEST(ParticleStateCsvTest, RendersNoParticlesAsAHeaderAlone) {
	std::vector<Particle*> particles = {};
	EXPECT_EQ(std::string(ParticleStateCsv::header) + "\n", ParticleStateCsv::render(particles));
}

// The point of this format is that a run's end can be fed straight back in
// as a new run's start, so the two have to agree exactly. A column added to
// one and not the other would be read as a different quantity entirely,
// silently.
TEST(ParticleStateCsvTest, RoundTripsThroughTheCsvInput) {
	std::vector<Particle*> original = {
		new ParticleSimple(2, 1.5, {1, -2, 3}, {-4, 5, -6}),
		new ParticleSimple(0.125, 0.0625, {-7, 8, -9}, {10, -11, 12})
	};

	const char* file = "ParticleStateCsvTest_RoundTripsThroughTheCsvInput.csv";
	std::ofstream out(file);
	out << ParticleStateCsv::render(original);
	out.close();

	SimulationInputCsv input(file);
	std::vector<Particle*> reloaded = input.input();

	ASSERT_EQ(original.size(), reloaded.size());
	for (std::size_t i = 0; i < original.size(); i++) {
		EXPECT_DOUBLE_EQ(original[i]->mass, reloaded[i]->mass) << "particle " << i << " mass";
		EXPECT_DOUBLE_EQ(original[i]->radius, reloaded[i]->radius) << "particle " << i << " radius";
		EXPECT_EQ(original[i]->position, reloaded[i]->position) << "particle " << i << " position";
		EXPECT_EQ(original[i]->velocity, reloaded[i]->velocity) << "particle " << i << " velocity";
	}

	ParticleTestHelper::deleteParticles(original);
	ParticleTestHelper::deleteParticles(reloaded);
}
