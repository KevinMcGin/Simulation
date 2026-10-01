#pragma once
#include "shared/precision/Real.cuh"
#include "shared/particle/Particle.cuh"

class ParticleAngularSimple: public Particle {
	public:
		Vector3D<Real>  angle;
		Vector3D<Real>  angularVelocity;
		
		ParticleAngularSimple(
			Real  mass,
			Real radius,
			Vector3D<Real>  position,
			Vector3D<Real>  velocity,
			Vector3D<Real>  angle,
			Vector3D<Real>  angularVelocity
		) : Particle(mass, radius, position, velocity), 
			angle(angle),
			angularVelocity(angularVelocity) {}
};