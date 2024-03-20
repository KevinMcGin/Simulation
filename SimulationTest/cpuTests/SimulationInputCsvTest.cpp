#include  <gtest/gtest.h>

#include "cpp/universe/input/SimulationInputCsv.h"

TEST(SimulationInputCsv, input) {
    std::string content = "mass,radius,positionX,positionY,positionZ,velocityX,velocityY,velocityZ\n1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0";
    std::ofstream file("test.csv");
    file << content;
    file.close();
    
    SimulationInputCsv input("test.csv");
    std::vector<Particle*> particles = input.input();
    ASSERT_EQ(particles.size(), 1);
    ASSERT_EQ(particles[0]->mass, 1.0);
    ASSERT_EQ(particles[0]->radius, 2.0);
    ASSERT_EQ(particles[0]->position.x, 3.0);
    ASSERT_EQ(particles[0]->position.y, 4.0);
    ASSERT_EQ(particles[0]->position.z, 5.0);
    ASSERT_EQ(particles[0]->velocity.x, 6.0);
    ASSERT_EQ(particles[0]->velocity.y, 7.0);
    ASSERT_EQ(particles[0]->velocity.z, 8.0);
}