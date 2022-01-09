#pragma once
#include "particle/Particle.cuh"
#include <vector>


class CollisionResolver {
public:
	__device__ __host__ virtual void resolve(Particle* p1, Particle* p2) = 0;
	virtual int getIndex() = 0;
};