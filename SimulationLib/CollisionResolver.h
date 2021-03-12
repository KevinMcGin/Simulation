#pragma once
#include "Particle.h"
#include <vector>


class CollisionResolver {
public:
	virtual void resolve(Particle* p1, vector<Particle*>::iterator it2, vector<Particle*>& particles) = 0;
};