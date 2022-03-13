#pragma once
#include "law/collision/detector/CollisionDetector.cuh"
#include "particle/model/Vector3D.cuh"
#include <cmath>

class CollisionDetectorSimple: public CollisionDetector {
public:
	static const int INDEX = 0;
public:
	__device__ __host__ bool isCollision(Particle* p1, Particle* p2) override;
	int getIndex() override { return INDEX; };
};