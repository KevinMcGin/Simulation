#include  <gtest/gtest.h>
#include "universe/input/SimulationInputRandomSimple.h"
#include "distribution/ParticleDistribution.h"
#include "distribution/ParticleDistributionSimple.h"
#include "distribution/DistributionMassDensity.h"
#include "distribution/DistributionValue.h"
#include "distribution/DistributionSphere.h"

TEST(SimulationInputRandomSimpleTest, input) {
    std::vector<unsigned long> particleCounts = { 10 };
    std::vector<std::shared_ptr<ParticleDistribution>> particleDistributions = {
        std::make_shared<ParticleDistributionSimple>(
            std::make_shared<DistributionMassDensity>(
                 std::make_shared<DistributionValue>(1),
                 std::make_shared<DistributionValue>(1)
            ),
            std::make_shared<DistributionSphere>(
                Vector3D<float>(-1.0f, -1.0f, -1.0f),
                0.0f
            ),
            std::make_shared<DistributionSphere>(
                Vector3D<float>(1.0f, 1.0f, 1.0f),
                0.0f
            )
        )
    };

    auto simulationInputRandomSimple = SimulationInputRandomSimple(particleCounts, particleDistributions);
    auto particles = simulationInputRandomSimple.input();
    EXPECT_EQ(10, particles.size());
    for(auto p : particles) {
        EXPECT_FLOAT_EQ(0.62035048f, p->radius);
        EXPECT_EQ(1, p->mass);
        EXPECT_EQ(Vector3D<float>(-1.0f, -1.0f, -1.0f), p->position);
        EXPECT_EQ(Vector3D<float>(1.0f, 1.0f, 1.0f), p->velocity);
    }
}