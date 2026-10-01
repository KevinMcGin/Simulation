#include "cpp/universe/input/SimulationInputCsvText.h"
#include "cpp/universe/input/ParticlesCsv.h"

#include <sstream>

SimulationInputCsvText::SimulationInputCsvText(std::string csv) :
	csv(std::move(csv)) {}

std::vector<Particle*> SimulationInputCsvText::input() {
	std::istringstream stream(csv);
	return ParticlesCsv::parse(stream);
}
