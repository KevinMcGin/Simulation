#pragma once
#include "Particle.h"

class ParticleSimple: public Particle {
	public:
		ParticleSimple(
			double			  mass,
			double            radius,
			array<double, 3>  position,
			array<double, 3>  velocity,
			array<double, 3>  angularVelocity
		) : Particle(mass, radius, position, velocity, angularVelocity) {}
		virtual double getTemperature() { return temperature; }

	private:
		double temperature = 273;
};