#include  <gtest/gtest.h>

#include "cpp/universe/input/particleInput/field/ParticleInputFieldPositionZ.h"

TEST(ParticleInputFieldPositionZ, input) {
    ParticleInputFieldPositionZ field;
    Particle particle;
    field.set(&particle, "1.0");
    ASSERT_EQ(particle.position.z, 1.0);
}