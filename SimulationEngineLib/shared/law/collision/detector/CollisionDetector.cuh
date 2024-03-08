#pragma once
#include "shared/particle/Particle.cuh"

class CollisionDetector {
public:
#if defined(USE_GPU)
   __device__ __host__
#endif
virtual bool isCollision(Particle* p1, Particle* p2) = 0;
	virtual int getIndex() = 0;
};