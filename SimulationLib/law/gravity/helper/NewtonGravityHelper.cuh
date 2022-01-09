#pragma once
#include "particle/Particle.cuh"

__device__ __host__ Vector3D getAcceleration(double mass, Vector3D radiusComponent);
__device__ __host__ void runOnParticle(Particle* p1, Vector3D acceleration);	
__device__ __host__ Vector3D getRadiusComponent(Particle* p1, Particle* p2, double G);