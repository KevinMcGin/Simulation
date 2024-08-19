#pragma once
#include "shared/particle/Particle.cuh"
#include "shared/service/momentum/MomentumService.cuh"
#include <vector>
#include <memory>

class CollisionResolver {
public:
#if defined(USE_GPU)
   __device__ __host__
#endif
   CollisionResolver() {}
#if defined(USE_GPU)
   __device__ __host__
#endif
virtual void resolve(
   Particle* p1, 
   Particle* p2,
	MomentumService* momentumService
) = 0;
	virtual int getIndex() = 0;
};