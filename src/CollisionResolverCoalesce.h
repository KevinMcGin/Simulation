#pragma once
#include "CollisionResolver.h"

#include <vector>
#include <cmath>
#include <iostream>

class CollisionResolverCoalesce {
public:
	virtual void resolve(Particle* p1, Particle* p2, vector<Particle*> &particles);

private:
	Vector3D getCoalesced(double mass1, double mass2, Vector3D vec1, Vector3D vec2) {
		return (mass1 * vec1 + mass2 * vec2) / (mass1 + mass2);
	}
};