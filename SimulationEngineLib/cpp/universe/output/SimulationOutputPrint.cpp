#include "cpp/universe/output/SimulationOutputPrint.h"



void SimulationOutputPrint::output(std::vector<Particle*> particles, unsigned long time)
{
	unsigned int i = 0;
	for (const auto& p : particles) {
		std::cout << "particle[" << i++ << "] position: \n";
		std::cout << p->position.x << '\n';
		std::cout << p->position.y << '\n';
		std::cout << p->position.z << '\n';
	}
}
