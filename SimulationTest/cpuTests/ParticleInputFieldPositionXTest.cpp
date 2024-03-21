#include  <gtest/gtest.h>

#include "cpp/universe/input/particleInput/field/ParticleInputFieldPositionX.h"

TEST(ParticleInputFieldPositionX, input) {
    ParticleInputFieldPositionX field;
    Particle particle;
    field.set(&particle, "1.0");
    ASSERT_EQ(particle.position.x, 1.0);
}