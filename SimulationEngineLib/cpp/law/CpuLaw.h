#pragma once
#include "shared/precision/Real.cuh"
#include "shared/particle/Particle.cuh"

#include <vector>

class CpuLaw {
public:
	// Laws are held and deleted as unique_ptr<CpuLaw> by Law, so without
	// this the concrete law's destructor never runs and whatever it holds
	// — its detector, resolver and momentum service — is never released.
	virtual ~CpuLaw() = default;
	virtual void run(
		std::vector<Particle*>& particles,
		Real deltaTime = 1.0
	) = 0;
};