#include  <gtest/gtest.h>

#include "cpp/universe/input/particleInput/field/ParticleInputFieldRadius.h"

TEST(ParticleInputFieldRadius, input) {
    ParticleInputFieldRadius field;
    Particle particle;
    field.set(&particle, "1.0");
    ASSERT_EQ(particle.radius, 1.0);
}