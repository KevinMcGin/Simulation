#pragma once
#include "shared/law/gravity/helper/NewtonGravityHelper.cuh"
#include "cpp/particle/ParticleSimple.h"
#include "shared/particle/Particle.cuh"
#include "shared/util/MatrixMaths.cuh"

#include <cmath>

#if defined(USE_GPU)
   __device__ __host__
#endif
Vector3D<float> getAcceleration(float mass, Vector3D<float> radiusComponent) {	
	return mass * radiusComponent;
}

#if defined(USE_GPU)
   __device__ __host__
#endif
void runOnParticle(Particle* p1, Vector3D<float> acceleration, unsigned int deltaTime) {
	p1->velocity = p1->velocity + acceleration * deltaTime;
}

#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D<float> getRadiusComponent(Particle* p1, Particle* p2, float G) {
	Vector3D<float> displacement = p1->position - p2->position;
	float displacementSquared = displacement.magnitudeSquared();
	if (displacementSquared <= pow(p1->radius + p2->radius, 2)) {
		return {0, 0, 0};
	} else {
		Vector3D<float> unit = displacement / sqrt(displacementSquared);
		return (G / displacementSquared) * unit;
	}
}