#pragma once
#include "Particle.cuh"


class CollisionDetector {
public:
	__device__ __host__ virtual bool isCollision(Particle* p1, Particle* p2) = 0;
	virtual int getIndex() = 0;
};