#pragma once
#include "particle/Particle.cuh"

__device__ __host__ Vector3D<float> getAcceleration(float mass, Vector3D<float> radiusComponent);
__device__ __host__ void runOnParticle(Particle* p1, Vector3D<float> acceleration);	
__device__ __host__ Vector3D<float> getRadiusComponent(Particle* p1, Particle* p2, float G);