#include  <gtest/gtest.h>

#include "cpp/universe/input/particleInput/field/ParticleInputFieldMass.h"

TEST(ParticleInputFieldMass, input) {
    ParticleInputFieldMass field;
    Particle particle;
    field.set(&particle, "1.0");
    ASSERT_EQ(particle.mass, 1.0);
}