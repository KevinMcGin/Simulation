#pragma once
#include "cpp/law/collision/Collision.h"
#include "shared/service/momentum/MomentumService.cuh"


class CollisionCoalesce :
    public Collision
{
public:
    CollisionCoalesce(
        std::shared_ptr<MomentumService> momentumService,
        bool useGpu = false
    );
};

