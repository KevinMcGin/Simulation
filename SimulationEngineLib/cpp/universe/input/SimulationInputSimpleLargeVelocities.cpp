#include "cpp/universe/input/SimulationInputSimpleLargeVelocities.h"



std::vector<Particle*> SimulationInputSimpleLargeVelocities::input()
{
	return {
		new ParticleSimple(1, 0.1, { 1, 0, 0}, {100000000, 0, 0}),
		new ParticleSimple(1, 0.1, { 0, 1, 0}, {0, 100000000, 0}),
		new ParticleSimple(1, 0.1, { 0, 10, 0}, {0, 100000000, 0}),
		new ParticleSimple(10, 0.1, { 0, 10, 0}, {0, 100000000, 0})
	};
}
