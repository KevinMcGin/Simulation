#include "cpp/universe/input/SimulationInputCsv.h"
#include "cpp/universe/input/ParticlesCsv.h"

SimulationInputCsv::SimulationInputCsv(const char* fileName) :
	SimulationInputFile(fileName) {}

SimulationInputCsv::~SimulationInputCsv() {
	if (file.is_open()) {
		file.close();
	}
}

std::vector<Particle*> SimulationInputCsv::input() {
	return ParticlesCsv::parse(file);
}
