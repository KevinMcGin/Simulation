#include  <gtest/gtest.h>

#include "cpp/universe/input/particleInput/field/ParticleInputFieldVelocityZ.h"

TEST(ParticleInputFieldVelocityZ, input) {
    ParticleInputFieldVelocityZ field;
    Particle particle;
    field.set(&particle, "1.0");
    ASSERT_EQ(particle.velocity.z, 1.0);
}