#include  <gtest/gtest.h>

#include "cpp/universe/input/particleInput/field/ParticleInputFieldVelocityY.h"

TEST(ParticleInputFieldVelocityY, input) {
    ParticleInputFieldVelocityY field;
    Particle particle;
    field.set(&particle, "1.0");
    ASSERT_EQ(particle.velocity.y, 1.0);
}