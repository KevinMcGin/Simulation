#pragma once
#include "shared/particle/Particle.cuh"
#include <vector>


class CollisionResolver {
public:
#if defined(USE_GPU)
   __device__ __host__
#endif
virtual void resolve(Particle* p1, Particle* p2) = 0;
	virtual int getIndex() = 0;
};