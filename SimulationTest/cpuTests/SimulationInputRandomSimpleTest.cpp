#include  <gtest/gtest.h>
#include "cpp/universe/input/SimulationInputRandomSimple.h"
#include "cpp/distribution/ParticleDistribution.h"
#include "cpp/distribution/ParticleDistributionSimple.h"
#include "cpp/distribution/DistributionMassDensity.h"
#include "cpp/distribution/DistributionValue.h"
#include "cpp/distribution/DistributionSphere.h"
#include "ParticleTestHelper.h"

TEST(SimulationInputRandomSimpleTest, input) {
    std::vector<unsigned long> particleCounts = { 10 };
    std::vector<std::shared_ptr<ParticleDistribution>> particleDistributions = {
        std::make_shared<ParticleDistributionSimple>(
            std::make_shared<DistributionMassDensity>(
                 std::make_shared<DistributionValue>(1),
                 std::make_shared<DistributionValue>(1)
            ),
            std::make_shared<DistributionSphere>(
                Vector3D<Real>(-1.0, -1.0, -1.0),
                0.0
            ),
            std::make_shared<DistributionSphere>(
                Vector3D<Real>(1.0, 1.0, 1.0),
                0.0
            )
        )
    };

    auto simulationInputRandomSimple = SimulationInputRandomSimple(particleCounts, particleDistributions);
    auto particles = simulationInputRandomSimple.input();
    EXPECT_EQ(10, particles.size());
    for(auto p : particles) {
        // (3V/4pi)^(1/3) for a volume of 1, which is what unit mass at unit
        // density gives. The float literal this replaced was 0.62035048.
        EXPECT_DOUBLE_EQ(0.62035049089940009, p->radius);
        EXPECT_EQ(1, p->mass);
        EXPECT_EQ(Vector3D<Real>(-1.0, -1.0, -1.0), p->position);
        EXPECT_EQ(Vector3D<Real>(1.0, 1.0, 1.0), p->velocity);
    }
    ParticleTestHelper::deleteParticles(particles);
}