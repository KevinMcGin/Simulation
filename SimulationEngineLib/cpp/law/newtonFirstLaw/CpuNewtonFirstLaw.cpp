#include "cpp/law/newtonFirstLaw/CpuNewtonFirstLaw.h"
#include "shared/particle/Particle.cuh"

CpuNewtonFirstLaw::CpuNewtonFirstLaw() : CpuLaw() { }

void CpuNewtonFirstLaw::run(std::vector<Particle*>& particles) {
	for (const auto& p : particles)
		p->advance();
}