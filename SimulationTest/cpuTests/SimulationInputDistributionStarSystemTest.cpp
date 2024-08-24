#include  <gtest/gtest.h>
#include "cpp/distribution/SimulationInputDistributionStarSystem.h"

TEST(SimulationInputDistributionStarSystemTest, getStarSystemDistribution) {
	auto distributionBuilder = SimulationInputDistributionStarSystem(
		1.0f,
		1.0f,
		10.0f,
		12.0f,
		10L
	);
	auto particles = distributionBuilder.getStarSystemDistribution()
		->input();
	EXPECT_EQ(10, particles.size());
}