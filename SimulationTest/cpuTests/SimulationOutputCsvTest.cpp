#include  "gtest/gtest.h"
#include "cpp/universe/output/SimulationOutputCsv.h"
#include "cpp/particle/ParticleSimple.h"
#include "cpp/util/FileUtil.h"
#include "ParticleTestHelper.h"

TEST(SimulationOutputCsvTest, SimulationOutputtedToCsv) {
	SimulationOutputCsv simulationOutputCsv("simulation_output/SimulationOutputCsvTest_SimulationOutputtedToCsv.json");
    std::vector<Particle*> particles = {
        new ParticleSimple(1,1,{0,0.1,0},{0,0,0}),
        new ParticleSimple(2,2,{2,-0.2,0},{0,0,0})
    };
	simulationOutputCsv.output(particles, 0);
	simulationOutputCsv.output(particles, 1);
	ParticleTestHelper::deleteParticles(particles);
}

// The values here are all exactly representable as a float, so the only
// difference between what goes in and what comes out is the padding the
// fixed precision would otherwise add.
TEST(SimulationOutputCsvTest, TrailingZerosAreTrimmed) {
	// Written to the working directory rather than simulation_output/,
	// which doesn't exist where the tests run — the stream would fail to
	// open and there'd be nothing to read back.
	const char* outputFile = "SimulationOutputCsvTest_TrailingZerosAreTrimmed.csv";
    std::vector<Particle*> particles = {
        new ParticleSimple(1,1,{0,0.5,-0.25},{0,0,0}),
        new ParticleSimple(2,2.5,{-2,0,10.125},{0,0,0})
    };

	SimulationOutputCsv simulationOutputCsv(outputFile);
	simulationOutputCsv.output(particles, 0);
	simulationOutputCsv.close();

	std::string expected =
		"frame,radius,postitionX,positionY,positionZ\n"
		"0,1,0,0.5,-0.25\n"
		"0,2.5,-2,0,10.125\n"
		"\n";
	EXPECT_EQ(expected, FileUtil::fileToString(outputFile));
	ParticleTestHelper::deleteParticles(particles);
}

