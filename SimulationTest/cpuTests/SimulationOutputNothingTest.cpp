#include  "gtest/gtest.h"
#include "cpp/universe/output/SimulationOutputNothing.h"
#include "cpp/particle/ParticleSimple.h"

TEST(SimulationOutputNothingTest, SimulationOutputsNothing) {
	SimulationOutputNothing simulationOutputNothing;
    std::vector<Particle*> particles = {
        new ParticleSimple(1,1,{0,0.1,0},{0,0,0}),
        new ParticleSimple(2,2,{2,-0.2,0},{0,0,0})
    };
	simulationOutputNothing.output(particles, 0);
	simulationOutputNothing.output(particles, 1);
}

