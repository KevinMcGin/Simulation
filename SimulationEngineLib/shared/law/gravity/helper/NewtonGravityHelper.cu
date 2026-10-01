#include "shared/law/gravity/helper/NewtonGravityHelper.cuh"
#include "cpp/particle/ParticleSimple.h"
#include "shared/particle/Particle.cuh"
#include "shared/util/MatrixMaths.cuh"

#include <cmath>

#if defined(USE_GPU)
   __device__ __host__
#endif
Vector3D<Real> getAcceleration(Real mass, Vector3D<Real> radiusComponent) {	
	return mass * radiusComponent;
}

#if defined(USE_GPU)
   __device__ __host__
#endif
void runOnParticle(
	Particle* p1, Vector3D<Real> acceleration, 
	Real deltaTime,
	MomentumService* momentumService
) {
	p1->velocity = momentumService->getVelocityPlusAcceleration(
		p1->mass,
		acceleration, 
		deltaTime, 
		p1->velocity
	);
}

#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D<Real> getRadiusComponent(Particle* p1, Particle* p2, Real G) {
	Vector3D<Real> displacement = p1->position - p2->position;
	Real displacementSquared = displacement.magnitudeSquared();
	if (displacementSquared <= pow(p1->radius + p2->radius, 2)) {
		return {0, 0, 0};
	} else {
		Vector3D<Real> unit = displacement / sqrt(displacementSquared);
		return (G / displacementSquared) * unit;
	}
}