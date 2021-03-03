#pragma once
#include "Particle.h"


class CollisionResolver {
public:
	virtual bool resolve(Particle* p1, Particle* p2) = 0;
};