#pragma 
#include "CollisionDetector.h"
#include "Vector3D.h"
#include <cmath>

class CollisionDetectorSimple: public CollisionDetector {
public:
	virtual bool isCollision(Particle* p1, Particle* p2) {
		Vector3D difference = {
			p1->position.x - p2->position.x,
			p1->position.y - p2->position.y,
			p1->position.z - p2->position.z
		};
		double absoluteDifference =
			sqrt(pow(difference.x, 2) + pow(difference.y, 2) + pow(difference.z, 2));
		return absoluteDifference < p1->radius + p2->radius;
	}
};