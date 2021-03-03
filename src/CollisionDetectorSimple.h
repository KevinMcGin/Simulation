#pragma once
#include "CollisionDetector.h"
#include <cmath>

class CollisionDetectorSimple: public CollisionDetector {
public:
	virtual bool isCollision(Particle* p1, Particle* p2) {
		array<double, 3> difference = {
			p1->position[0] - p2->position[0],
			p1->position[1] - p2->position[1],
			p1->position[2] - p2->position[2]
		};
		double absoluteDifference =
			sqrt(pow(difference[0], 2) + pow(difference[1], 2) + pow(difference[2], 2));
		return absoluteDifference < p1->radius + p2->radius;
	}
};