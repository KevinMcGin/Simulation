#pragma once
#include "law/gravity/helper/NewtonGravityHelper.cuh"
#include "particle/ParticleSimple.h"
#include "particle/Particle.cuh"
#include "util/MatrixMaths.cuh"

#include <cmath>

__device__ __host__
Vector3D<float> getAcceleration(float mass, Vector3D<float> radiusComponent) {	
	return mass * radiusComponent;
}

__device__ __host__
void runOnParticle(Particle* p1, Vector3D<float> acceleration) {
	p1->velocity = p1->velocity + acceleration;
}

__device__ __host__ 
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