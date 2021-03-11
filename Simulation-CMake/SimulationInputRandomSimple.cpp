#include "SimulationInputRandomSimple.h"



SimulationInputRandomSimple::SimulationInputRandomSimple(vector<unsigned long> particleCounts, vector<ParticleDistributionSimple> particleDistributions) :
	particleCounts(particleCounts),
	particleDistributions(particleDistributions)
{

}

std::vector<Particle*> SimulationInputRandomSimple::input()
{
	vector<Particle*> particles;
	unsigned int distrbutionsCount = particleCounts.size();
	for (unsigned long j = 0; j < distrbutionsCount; j++) {
		for (unsigned long i = 0; i < particleCounts[j]; i++) {
			particles.push_back(particleDistributions[j].getParticle());
		}
	}

	return particles;
}
