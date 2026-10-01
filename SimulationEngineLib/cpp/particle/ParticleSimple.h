#pragma once
#include "shared/precision/Real.cuh"
#include "shared/particle/Particle.cuh"

class ParticleSimple: public Particle {
	public:
		ParticleSimple(
			Real			  mass,
			Real            radius,
			Vector3D<Real>  position,
			Vector3D<Real>  velocity
		) : Particle(mass, radius, position, velocity) {}
		// Real getTemperature() override;

	// private:
		// Real temperature = 273;
};