#include  "gtest/gtest.h"
#include "cpp/universe/output/SimulationOutputCsv.h"
#include "cpp/particle/ParticleSimple.h"

TEST(SimulationOutputCsvTest, SimulationOutputtedToCsv) {
	SimulationOutputCsv simulationOutputCsv("simulation_output/SimulationOutputCsvTest_SimulationOutputtedToCsv.json");
    std::vector<Particle*> particles = {
        new ParticleSimple(1,1,{0,0.1,0},{0,0,0}),
        new ParticleSimple(2,2,{2,-0.2,0},{0,0,0})
    };
	simulationOutputCsv.output(particles, 0);
	simulationOutputCsv.output(particles, 1);
}

