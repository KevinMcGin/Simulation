#pragma once
#include "CollisionDetector.h"
#include "Vector3D.cuh"
#include <cmath>

class CollisionDetectorSimple: public CollisionDetector {
public:
	virtual bool isCollision(Particle* p1, Particle* p2);
};