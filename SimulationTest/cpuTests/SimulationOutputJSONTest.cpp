#include  "gtest/gtest.h"
#include "universe/output/SimulationOutputJson.h"
#include "particle/ParticleSimple.h"

TEST(SimulationOutputJsonTest, SimulationOutputtedToJson) {
	SimulationOutputJson simulationOutputJson("simulation_output/SimulationOutputJsonTest_SimulationOutputtedToJson.json");
    std::vector<Particle*> particles = {
        new ParticleSimple(1,1,{0,0.1,0},{0,0,0}),
        new ParticleSimple(2,2,{2,-0.2,0},{0,0,0})
    };
	simulationOutputJson.output(particles, 0);
	simulationOutputJson.output(particles, 1);
}

