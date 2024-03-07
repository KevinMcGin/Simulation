#include  <gtest/gtest.h>
#include "cpp/universe/input/SimulationInputRandomSimple.h"
#include "cpp/distribution/ParticleDistribution.h"
#include "cpp/distribution/ParticleDistributionSimple.h"
#include "cpp/distribution/DistributionMassDensity.h"
#include "cpp/distribution/DistributionValue.h"
#include "cpp/distribution/DistributionSphere.h"

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