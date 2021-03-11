#pragma once
#include "Particle.h"


class CollisionDetector {
public:
	virtual bool isCollision(Particle* p1, Particle* p2) = 0;
};