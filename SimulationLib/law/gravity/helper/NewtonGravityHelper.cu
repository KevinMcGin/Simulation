#pragma once
#include "law/gravity/helper/NewtonGravityHelper.cuh"
#include "particle/ParticleSimple.h"
#include "particle/Particle.cuh"
#include "util/MatrixMaths.cuh"

#include <cmath>

__device__ __host__
Vector3D getAcceleration(double mass, Vector3D radiusComponent) {	
	return mass * radiusComponent;
}

__device__ __host__
void runOnParticle(Particle* p1, Vector3D acceleration) {
	p1->velocity = p1->velocity + acceleration;
}

__device__ __host__ 
Vector3D getRadiusComponent(Particle* p1, Particle* p2, double G) {
	Vector3D displacement = p1->position - p2->position;
	double displacementSquared = displacement.magnitudeSquared();
	if (displacementSquared <= pow(p1->radius + p2->radius, 2)) {
		return {0, 0, 0};
	} else {
		Vector3D unit = displacement / sqrt(displacementSquared);
		return (G / displacementSquared) * unit;
	}
}