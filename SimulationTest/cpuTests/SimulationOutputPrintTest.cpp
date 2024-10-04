#include  "gtest/gtest.h"
#include "cpp/universe/output/SimulationOutputPrint.h"
#include "cpp/particle/ParticleSimple.h"

TEST(SimulationOutputPrintTest, SimulationPrints) {
	SimulationOutputPrint simulationOutputPrint;
    std::vector<Particle*> particles = {
        new ParticleSimple(1,1,{0,0.1,0},{0,0,0}),
        new ParticleSimple(2,2,{2,-0.2,0},{0,0,0})
    };
	simulationOutputPrint.output(particles, 0);
	simulationOutputPrint.output(particles, 1);
}

