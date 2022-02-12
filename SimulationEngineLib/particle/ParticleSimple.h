#pragma once
#include "particle/Particle.cuh"

class ParticleSimple: public Particle {
	public:
		ParticleSimple(
			double			  mass,
			double            radius,
			Vector3D  position,
			Vector3D  velocity
		) : Particle(mass, radius, position, velocity) {}
		// virtual double getTemperature();

	// private:
		// double temperature = 273;
};