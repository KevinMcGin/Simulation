#pragma once
#include "cpp/law/Law.h"
#include "shared/law/collision/detector/CollisionDetector.cuh"
#include "shared/law/collision/resolver/CollisionResolver.cuh"
#include "shared/service/momentum/MomentumService.cuh"
class Collision :
    public Law
{
public:
    Collision(
        std::shared_ptr<CollisionDetector> collisionDetector, 
        std::shared_ptr<CollisionResolver> collisionResolver, 
        std::shared_ptr<MomentumService> momentumService,
        bool useGpu = false
    );
};

