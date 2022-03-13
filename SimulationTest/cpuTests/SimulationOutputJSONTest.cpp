#include  "gtest/gtest.h"
#include "universe/output/SimulationOutputJSON.h"
#include "particle/ParticleSimple.h"

TEST(SimulationOutputJSONTest, SimulationOutputtedToJSON) {
	SimulationOutputJSON simulationOutputJSON("simulation_output/SimulationOutputJSONTest_SimulationOutputtedToJSON.json");
    std::vector<Particle*> particles = {
        new ParticleSimple(1,1,{0,0.1,0},{0,0,0}),
        new ParticleSimple(2,2,{2,-0.2,0},{0,0,0})
    };
	simulationOutputJSON.output(particles, 0);
	simulationOutputJSON.output(particles, 1);
}

