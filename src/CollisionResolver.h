#pragma once
#include "Particle.h"


class CollisionResolver {
public:
	virtual void resolve(Particle* p1, Particle* p2) = 0;
};