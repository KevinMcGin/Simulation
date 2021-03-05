#include "SimulationInputRandomSimple.h"



SimulationInputRandomSimple::SimulationInputRandomSimple(unsigned long particleCount, ParticleDistributionSimple particleDistribution) :
	particleCount(particleCount),
	particleDistribution(particleDistribution)
{

}

std::vector<Particle*> SimulationInputRandomSimple::input()
{
	vector<Particle*> particles;
	for (unsigned long i = 0; i < particleCount; i++) {
		particles.push_back(particleDistribution.getParticle());
	}

	return particles;
}
