#include "SimulationInputSimple.h"



std::vector<Particle*> SimulationInputSimple::input()
{
	return {
		new ParticleSimple(1, 1, { 1, 0, 0}, {1, 0, 0}, {0, 0, 0 }),
		new ParticleSimple(1, 1, { 0, 1, 0}, {0, 1, 0}, {0, 0, 0 })
	};
}
