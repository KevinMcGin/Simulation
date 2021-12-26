#include  "gtest/gtest.h"
#include "SimulationOutputJSON.h"
#include "ParticleSimple.h"

TEST(SimulationOutputJSONTest, SimulationOutputtedToJSON) {
	SimulationOutput* simulationOutputJSON = new SimulationOutputJSON("simulation_output/SimulationOutputJSONTest_SimulationOutputtedToJSON.json");
    vector<Particle*> particles = {
        new ParticleSimple(1,1,{0,0.1,0},{0,0,0},{0,0,0}),
        new ParticleSimple(2,2,{2,-0.2,0},{0,0,0},{0,0,0})
    };
	simulationOutputJSON->output(particles, 0);
	simulationOutputJSON->output(particles, 1);
    delete simulationOutputJSON;
}

