#pragma once
#include "Particle.cuh"


class CollisionDetector {
public:
	virtual bool isCollision(Particle* p1, Particle* p2) = 0;
};