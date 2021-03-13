#pragma once
#include "CollisionResolver.h"

#include <vector>
#include <cmath>
#include <iostream>

class CollisionResolverCoalesce: public CollisionResolver {
public:
	virtual void resolve(Particle* p1, Particle* p2);

private:
	Vector3D getCoalesced(double mass1, double mass2, Vector3D vec1, Vector3D vec2);
};