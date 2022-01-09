#include "law/newtonFirstLaw/CpuNewtonFirstLaw.h"
#include "particle/Particle.cuh"

CpuNewtonFirstLaw::CpuNewtonFirstLaw() : CpuLaw() { }

void CpuNewtonFirstLaw::run(vector<Particle*>& particles) {
	for (const auto& p : particles)
		p->advance();
}