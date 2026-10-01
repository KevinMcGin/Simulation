#include  <gtest/gtest.h>
#include "cpp/particle/helper/ParticlesHelper.h"
#include "cpp/particle/ParticleSimple.h"
#include "ParticleTestHelper.h"

TEST(ParticlesHelperTest, removeDeletedParticles) {
    std::vector<Particle*> particles = {
        new ParticleSimple(
            1,
            1,
            { -1.0, -1.0, -1.0 },
            { 1.0, 1.0, 1.0 }
        ),
        new ParticleSimple(
            10,
            10,
            { -10.0, -10.0, -10.0 },
            { 10.0, 10.0, 10.0 }
        )
    };
    particles.front()->deleted = true;
    ParticlesHelper::removeDeletedParticles(particles);
    EXPECT_EQ(1, particles.size());
    auto p = particles.front();
    EXPECT_DOUBLE_EQ(10, p->mass);
    EXPECT_DOUBLE_EQ(10, p->radius);
    EXPECT_EQ(Vector3D<Real>(-10.0, -10.0, -10.0), p->position);
    EXPECT_EQ(Vector3D<Real>(10.0, 10.0, 10.0), p->velocity);
    ParticleTestHelper::deleteParticles(particles);
}