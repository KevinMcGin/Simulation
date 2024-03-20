#include  <gtest/gtest.h>

#include "cpp/universe/input/particleInput/field/ParticleInputFieldVelocityX.h"

TEST(ParticleInputFieldVelocityX, input) {
    ParticleInputFieldVelocityX field;
    Particle particle;
    field.set(&particle, "1.0");
    ASSERT_EQ(particle.velocity.x, 1.0);
}