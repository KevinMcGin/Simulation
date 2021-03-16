#pragma once
#include "Particle.cuh"
#include <vector>


class CollisionResolver {
public:
	virtual void resolve(Particle* p1, Particle* p2) = 0;
};