#pragma once
#include "particle/Particle.cuh"

class ParticleSimple: public Particle {
	public:
		Vector3D  angle;
		Vector3D  angularVelocity;
		
		ParticleAngularSimple(
			double  mass,
			double radius,
			Vector3D  position,
			Vector3D  velocity,
			Vector3D  angle;
			Vector3D  angularVelocity
		) : Particle(mass, radius, position, velocity), 
			angle(angle),
			angularVelocity(angularVelocity) {}
};