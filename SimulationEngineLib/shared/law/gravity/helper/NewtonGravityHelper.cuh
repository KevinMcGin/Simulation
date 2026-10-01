#pragma once
#include "shared/precision/Real.cuh"
#include "shared/particle/Particle.cuh"
#include "shared/service/momentum/MomentumService.cuh"

#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D<Real> getAcceleration(Real mass, Vector3D<Real> radiusComponent);

#if defined(USE_GPU)
   __device__ __host__
#endif 
void runOnParticle(
   Particle* p1, 
   Vector3D<Real> acceleration, 
   Real deltaTime,
   MomentumService* momentumService
);	

#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D<Real> getRadiusComponent(Particle* p1, Particle* p2, Real G);
