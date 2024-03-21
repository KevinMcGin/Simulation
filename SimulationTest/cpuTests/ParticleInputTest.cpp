#include  <gtest/gtest.h>

#include "cpp/universe/input/particleInput/ParticleInput.h"

TEST(ParticleInput, input) {
   ParticleInput input({
        "mass",
        "radius",
        "positionX",
        "positionY",
        "positionZ",
        "velocityX",
        "velocityY",
        "velocityZ"
    });
    Particle particle;
    input.set(&particle, {
        "1.0",
        "2.0",
        "3.0",
        "4.0",
        "5.0",
        "6.0",
        "7.0",
        "8.0"
    });
    ASSERT_EQ(particle.mass, 1.0);
    ASSERT_EQ(particle.radius, 2.0);
    ASSERT_EQ(particle.position.x, 3.0);
    ASSERT_EQ(particle.position.y, 4.0);
    ASSERT_EQ(particle.position.z, 5.0);
    ASSERT_EQ(particle.velocity.x, 6.0);
    ASSERT_EQ(particle.velocity.y, 7.0);
    ASSERT_EQ(particle.velocity.z, 8.0);
}