#include "cpp/universe/input/SimulationInputCombined.h"

SimulationInputCombined::SimulationInputCombined(
	std::vector<std::shared_ptr<SimulationInput>> inputs
) : inputs(std::move(inputs)) {}

std::vector<Particle*> SimulationInputCombined::input() {
	std::vector<Particle*> combined;
	for (const auto& input : inputs) {
		std::vector<Particle*> particles;
		try {
			particles = input->input();
		} catch (...) {
			// One source failing abandons the run, so the particles the
			// earlier sources already produced have nobody left to free
			// them.
			for (auto particle : combined) {
				delete particle;
			}
			throw;
		}
		combined.insert(combined.end(), particles.begin(), particles.end());
	}
	return combined;
}
