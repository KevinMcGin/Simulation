#include  <gtest/gtest.h>

#include "cpp/universe/input/SimulationInputCsv.h"
#include "ParticleTestHelper.h"

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
    ParticleTestHelper::deleteParticles(particles);
}
// A file written by ParticleStateCsv ends in a newline, and so does almost
// anything a user uploads. The blank line that leaves behind is not a
// particle.
TEST(SimulationInputCsv, ignoresATrailingNewline) {
    std::ofstream file("test-trailing-newline.csv");
    file << "mass,radius,positionX,positionY,positionZ,velocityX,velocityY,velocityZ\n"
         << "1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0\n";
    file.close();

    SimulationInputCsv input("test-trailing-newline.csv");
    std::vector<Particle*> particles = input.input();
    ASSERT_EQ(particles.size(), 1);
    ASSERT_EQ(particles[0]->mass, 1.0);
    ParticleTestHelper::deleteParticles(particles);
}

TEST(SimulationInputCsv, ignoresWindowsLineEndings) {
    std::ofstream file("test-crlf.csv", std::ios::binary);
    file << "mass,radius,positionX,positionY,positionZ,velocityX,velocityY,velocityZ\r\n"
         << "1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0\r\n";
    file.close();

    SimulationInputCsv input("test-crlf.csv");
    std::vector<Particle*> particles = input.input();
    ASSERT_EQ(particles.size(), 1);
    // The carriage return would otherwise be parsed as part of velocityZ.
    ASSERT_EQ(particles[0]->velocity.z, 8.0);
    ParticleTestHelper::deleteParticles(particles);
}
