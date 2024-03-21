#include  <gtest/gtest.h>

#include "cpp/universe/input/particleInput/field/ParticleInputFieldPositionY.h"

TEST(ParticleInputFieldPositionY, input) {
    ParticleInputFieldPositionY field;
    Particle particle;
    field.set(&particle, "1.0");
    ASSERT_EQ(particle.position.y, 1.0);
}