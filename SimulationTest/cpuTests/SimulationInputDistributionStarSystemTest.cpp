#include  <gtest/gtest.h>
#include "cpp/distribution/SimulationInputDistributionStarSystem.h"

TEST(SimulationInputDistributionStarSystemTest, getStarSystemDistribution) {
	StarSystemConfig config;
	config.meanMass = 1.0f;
	config.meanDensity = 1.0f;
	config.starMass = 10.0f;
	config.starDensity = 2.0f;
	config.diskCentralMass = 10.0f;
	config.outerRadius = 12.0f;
	config.particleCount = 10L;
	auto distributionBuilder = SimulationInputDistributionStarSystem(config);
	auto particles = distributionBuilder.getStarSystemDistribution()
		->input();
	EXPECT_EQ(10, particles.size());
}

// The config's defaults are what the engine generated before any of it was
// configurable, so a caller that sets nothing still gets a star system.
TEST(SimulationInputDistributionStarSystemTest, defaultsProduceAStarSystem) {
	StarSystemConfig config;
	config.particleCount = 5L;
	auto particles = SimulationInputDistributionStarSystem(config)
		.getStarSystemDistribution()
		->input();
	EXPECT_EQ(5, particles.size());
	for (const auto& particle : particles) {
		EXPECT_GT(particle->mass, 0);
		EXPECT_GT(particle->radius, 0);
	}
}

// Every particle but the star sits in the ring between the two radii: the
// inner radius is what keeps a disk from being generated on top of the star
// it orbits.
TEST(SimulationInputDistributionStarSystemTest, disksStayWithinTheirRadii) {
	StarSystemConfig config;
	config.particleCount = 50L;
	config.innerRadius = 4.0f;
	config.outerRadius = 6.0f;
	auto particles = SimulationInputDistributionStarSystem(config)
		.getStarSystemDistribution()
		->input();

	unsigned int atCentre = 0;
	for (const auto& particle : particles) {
		const float radius = particle->position.magnitude();
		if (radius == 0) {
			atCentre++;
			continue;
		}
		// A hair of slack either side: the radius is rebuilt out of a sine
		// and a cosine, so an edge sample lands a rounding error outside.
		EXPECT_GE(radius, 3.99f);
		EXPECT_LE(radius, 6.01f);
	}
	EXPECT_EQ(1, atCentre) << "the star, and only the star, sits at the centre";
}

// The star's density is its own: at the same mass, a denser star is a
// smaller one.
TEST(SimulationInputDistributionStarSystemTest, starDensityIsSeparateFromTheDisk) {
	auto starRadius = [](float starDensity) {
		StarSystemConfig config;
		config.particleCount = 2L;
		config.starMass = 100.0f;
		config.starDensity = starDensity;
		auto particles = SimulationInputDistributionStarSystem(config)
			.getStarSystemDistribution()
			->input();
		// The star is the last particle: the disk is generated first.
		return particles.back()->radius;
	};

	EXPECT_LT(starRadius(8000.0f), starRadius(1000.0f));
}
