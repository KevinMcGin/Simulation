#include  <gtest/gtest.h>
#include "particle/helper/ParticlesHelper.h"
#include "particle/ParticleSimple.h"

TEST(ParticlesHelperTest, removeDeletedParticles) {
    std::vector<Particle*> particles = {
        new ParticleSimple(
            1,
            1,
            { -1.0f, -1.0f, -1.0f },
            { 1.0f, 1.0f, 1.0f }
        ),
        new ParticleSimple(
            10,
            10,
            { -10.0f, -10.0f, -10.0f },
            { 10.0f, 10.0f, 10.0f }
        )
    };
    particles.front()->deleted = true;
    ParticlesHelper::removeDeletedParticles(particles);
    EXPECT_EQ(1, particles.size());
    auto p = particles.front();
    EXPECT_FLOAT_EQ(10, p->mass);
    EXPECT_FLOAT_EQ(10, p->radius);
    EXPECT_EQ(Vector3D<float>(-10.0f, -10.0f, -10.0f), p->position);
    EXPECT_EQ(Vector3D<float>(10.0f, 10.0f, 10.0f), p->velocity);
}