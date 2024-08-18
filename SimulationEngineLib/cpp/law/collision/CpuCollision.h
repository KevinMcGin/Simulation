#pragma once
#include "cpp/law/CpuLaw.h"
#include "shared/law/collision/detector/CollisionDetector.cuh"
#include "shared/law/collision/resolver/CollisionResolver.cuh"

#include <vector>
#include <stdio.h>
#include <iostream>
#include <memory>

class CpuCollision: public CpuLaw {
public:
	CpuCollision(
        std::shared_ptr<CollisionDetector> collisionDetector, 
        std::shared_ptr<CollisionResolver> collisionResolver,
	    std::shared_ptr<MomentumService> momentumService
    );
	virtual void run(
        std::vector<Particle*>& particles,
		unsigned int deltaTime
    );

private:
    std::shared_ptr<CollisionDetector> collisionDetector;
    std::shared_ptr<CollisionResolver> collisionResolver;
	    std::shared_ptr<MomentumService> momentumService;
};