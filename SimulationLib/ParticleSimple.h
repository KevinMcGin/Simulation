#pragma once
#include "Particle.cuh"

class ParticleSimple: public Particle {
	public:
		ParticleSimple(
			double			  mass,
			double            radius,
			Vector3D  position,
			Vector3D  velocity,
			Vector3D  angularVelocity
		) : Particle(mass, radius, position, velocity, angularVelocity) {}
		virtual double getTemperature();

	private:
		double temperature = 273;
};