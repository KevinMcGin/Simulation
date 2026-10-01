#include  <gtest/gtest.h>
#include "cpp/distribution/SimulationInputDistributionStarSystem.h"
#include "ParticleTestHelper.h"

TEST(SimulationInputDistributionStarSystemTest, getStarSystemDistribution) {
	StarSystemConfig config;
	config.meanMass = 1.0;
	config.meanDensity = 1.0;
	config.starMass = 10.0;
	config.starDensity = 2.0;
	config.diskCentralMass = 10.0;
	config.outerRadius = 12.0;
	config.particleCount = 10L;
	auto distributionBuilder = SimulationInputDistributionStarSystem(config);
	auto particles = distributionBuilder.getStarSystemDistribution()
		->input();
	EXPECT_EQ(10, particles.size());
	ParticleTestHelper::deleteParticles(particles);
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
	ParticleTestHelper::deleteParticles(particles);
}

// Every particle but the star sits in the ring between the two radii: the
// inner radius is what keeps a disk from being generated on top of the star
// it orbits.
TEST(SimulationInputDistributionStarSystemTest, disksStayWithinTheirRadii) {
	StarSystemConfig config;
	config.particleCount = 50L;
	config.innerRadius = 4.0;
	config.outerRadius = 6.0;
	auto particles = SimulationInputDistributionStarSystem(config)
		.getStarSystemDistribution()
		->input();

	unsigned int atCentre = 0;
	for (const auto& particle : particles) {
		const Real radius = particle->position.magnitude();
		if (radius == 0) {
			atCentre++;
			continue;
		}
		// A hair of slack either side: the radius is rebuilt out of a sine
		// and a cosine, so an edge sample lands a rounding error outside.
		EXPECT_GE(radius, 3.99);
		EXPECT_LE(radius, 6.01);
	}
	EXPECT_EQ(1, atCentre) << "the star, and only the star, sits at the centre";
	ParticleTestHelper::deleteParticles(particles);
}

// The star's density is its own: at the same mass, a denser star is a
// smaller one.
TEST(SimulationInputDistributionStarSystemTest, starDensityIsSeparateFromTheDisk) {
	auto starRadius = [](Real starDensity) {
		StarSystemConfig config;
		config.particleCount = 2L;
		config.starMass = 100.0;
		config.starDensity = starDensity;
		auto particles = SimulationInputDistributionStarSystem(config)
			.getStarSystemDistribution()
			->input();
		// The star is the last particle: the disk is generated first.
		const Real radius = particles.back()->radius;
		ParticleTestHelper::deleteParticles(particles);
		return radius;
	};

	EXPECT_LT(starRadius(8000.0), starRadius(1000.0));
}

// particleCount is unsigned, so a system of none used to underflow into a
// request for eighteen quintillion disk particles. An empty star system is
// an ordinary thing to ask for now that the particles can be arriving as
// CSV instead.
TEST(SimulationInputDistributionStarSystemTest, zeroParticlesProducesNothing) {
	StarSystemConfig config;
	config.particleCount = 0L;
	auto particles = SimulationInputDistributionStarSystem(config)
		.getStarSystemDistribution()
		->input();
	EXPECT_EQ(0, particles.size());
	ParticleTestHelper::deleteParticles(particles);
}

// A massless star is a request for no star, which is how a disk is seeded
// around something supplied separately.
TEST(SimulationInputDistributionStarSystemTest, zeroStarMassLeavesOutTheStar) {
	StarSystemConfig config;
	config.particleCount = 5L;
	config.starMass = 0.0;
	auto particles = SimulationInputDistributionStarSystem(config)
		.getStarSystemDistribution()
		->input();

	// All five are disk particles now, where a star would have taken one of
	// the places, and none of them sits at the centre.
	EXPECT_EQ(5, particles.size());
	for (const auto& particle : particles) {
		EXPECT_GT(particle->position.magnitude(), 0) << "nothing should be at the centre";
	}
	ParticleTestHelper::deleteParticles(particles);
}

TEST(SimulationInputDistributionStarSystemTest, oneParticleIsJustTheStar) {
	StarSystemConfig config;
	config.particleCount = 1L;
	auto particles = SimulationInputDistributionStarSystem(config)
		.getStarSystemDistribution()
		->input();
	ASSERT_EQ(1, particles.size());
	EXPECT_EQ(0, particles.front()->position.magnitude()) << "the star sits at the centre";
	ParticleTestHelper::deleteParticles(particles);
}
