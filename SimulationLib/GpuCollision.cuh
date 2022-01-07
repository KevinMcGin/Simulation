#pragma once
#include "GpuLaw.h"
#include "CollisionDetector.cuh"
#include "CollisionResolver.cuh"

#include <vector>
#include <stdio.h>
#include <iostream>

class GpuCollision: public GpuLaw {
public:
	GpuCollision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver);
    ~GpuCollision();
	virtual void run(Particle** td_par, int particleCount);

private:
    CollisionDetector** collisionDetectorGpu = NULL;
    CollisionResolver** collisionResolverGpu = NULL;
};