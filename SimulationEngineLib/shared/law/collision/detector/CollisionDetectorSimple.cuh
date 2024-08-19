#pragma once
#include "shared/law/collision/detector/CollisionDetector.cuh"
#include "shared/particle/model/Vector3D.cuh"
#include <cmath>

class CollisionDetectorSimple: public CollisionDetector {
public:
	static const int INDEX = 0;
public:
#if defined(USE_GPU)
   __device__ __host__
#endif
bool isCollision(Particle* p1, Particle* p2) override;
int getIndex() override { return INDEX; };
};