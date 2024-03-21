#include "cpp/universe/input/SimulationInputSimple.h"



std::vector<Particle*> SimulationInputSimple::input()
{
	return {
		new ParticleSimple(1, 0.1, { 1, 0, 0}, {1, 0, 0}),
		new ParticleSimple(1, 0.1, { 0, 1, 0}, {0, 1, 0}),
		new ParticleSimple(1, 0.1, { 0, 10, 0}, {0, 1, 0}),
		new ParticleSimple(10, 0.1, { 0, 10, 0}, {0, 1, 0})
	};
}
