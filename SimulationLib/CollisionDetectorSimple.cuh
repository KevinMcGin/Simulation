#pragma once
#include "CollisionDetector.cuh"
#include "Vector3D.cuh"
#include <cmath>

class CollisionDetectorSimple: public CollisionDetector {
public:
	static const int INDEX = 0;
public:
	__device__ __host__ virtual bool isCollision(Particle* p1, Particle* p2);
	virtual int getIndex() { return INDEX; };
};