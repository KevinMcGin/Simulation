#pragma once
#include "shared/particle/Particle.cuh"
#include "shared/service/momentum/MomentumService.cuh"

#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D<float> getAcceleration(float mass, Vector3D<float> radiusComponent);

#if defined(USE_GPU)
   __device__ __host__
#endif 
void runOnParticle(
   Particle* p1, 
   Vector3D<float> acceleration, 
   unsigned int deltaTime,
   MomentumService* momentumService
);	

#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D<float> getRadiusComponent(Particle* p1, Particle* p2, float G);
