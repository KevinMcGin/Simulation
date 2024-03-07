#pragma once
#include "shared/particle/Particle.cuh"

class ParticleSimple: public Particle {
	public:
		ParticleSimple(
			float			  mass,
			float            radius,
			Vector3D<float>  position,
			Vector3D<float>  velocity
		) : Particle(mass, radius, position, velocity) {}
		// float getTemperature() override;

	// private:
		// float temperature = 273;
};