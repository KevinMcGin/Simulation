#pragma once
#include "cpp/universe/input/SimulationInputFile.h"
#include "cpp/particle/ParticleSimple.h"

#include <vector>

// Particles read from a CSV file on disk. The format itself lives in
// ParticlesCsv, which this and SimulationInputCsvText share.
class SimulationInputCsv: public SimulationInputFile {
	public:
		SimulationInputCsv(const char* fileName);
		~SimulationInputCsv();
		std::vector<Particle*> input();
};
