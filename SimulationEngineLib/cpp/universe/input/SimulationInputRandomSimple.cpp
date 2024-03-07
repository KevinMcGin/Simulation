#include "cpp/universe/input/SimulationInputRandomSimple.h"



SimulationInputRandomSimple::SimulationInputRandomSimple(std::vector<unsigned long> particleCounts, std::vector<std::shared_ptr<ParticleDistribution>> particleDistributions) :
	particleCounts(particleCounts),
	particleDistributions(particleDistributions) {

}

std::vector<Particle*> SimulationInputRandomSimple::input() {
	std::vector<Particle*> particles;
	unsigned long distrbutionsCount = static_cast<unsigned long>(particleCounts.size());
	for (unsigned long j = 0; j < distrbutionsCount; j++) {
		for (unsigned long i = 0; i < particleCounts[j]; i++) {
			particles.push_back(particleDistributions[j]->getParticle());
		}
	}

	return particles;
}
