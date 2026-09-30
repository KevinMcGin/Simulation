#pragma once
#include "cpp/universe/input/SimulationInputFile.h"
#include "cpp/particle/ParticleSimple.h"
#include "cpp/universe/input/particleInput/ParticleInput.h"

#include <memory>
#include <vector>

class SimulationInputCsv: public SimulationInputFile {
	public:
		SimulationInputCsv(const char* fileName);
		~SimulationInputCsv();
		std::vector<Particle*> input();
	private:
		std::unique_ptr<ParticleInput> particleInput;
};