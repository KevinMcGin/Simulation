#pragma once
#include "shared/particle/Particle.cuh"

class ParticleAngularSimple: public Particle {
	public:
		Vector3D<float>  angle;
		Vector3D<float>  angularVelocity;
		
		ParticleAngularSimple(
			float  mass,
			float radius,
			Vector3D<float>  position,
			Vector3D<float>  velocity,
			Vector3D<float>  angle,
			Vector3D<float>  angularVelocity
		) : Particle(mass, radius, position, velocity), 
			angle(angle),
			angularVelocity(angularVelocity) {}
};