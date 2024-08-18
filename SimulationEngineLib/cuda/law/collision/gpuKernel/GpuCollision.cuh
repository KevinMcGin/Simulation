#pragma once
#include "cpp/law/GpuLaw.h"
#include "shared/law/collision/detector/CollisionDetector.cuh"
#include "shared/law/collision/resolver/CollisionResolver.cuh"
#include "shared/service/momentum/MomentumService.cuh"

#include <vector>
#include <stdio.h>
#include <iostream>

class GpuCollision: public GpuLaw {
public:
	GpuCollision(
        std::shared_ptr<CollisionDetector> collisionDetector, 
        std::shared_ptr<CollisionResolver> collisionResolver,
        std::shared_ptr<MomentumService> momentumService
    );
    ~GpuCollision();
	void run(
        Particle** particles, 
        int particleCount,
		unsigned int deltaTime
    ) override;

private:
    CollisionDetector** collisionDetectorGpu = NULL;
    CollisionResolver** collisionResolverGpu = NULL;
    MomentumService** momentumServiceGpu = NULL;
};