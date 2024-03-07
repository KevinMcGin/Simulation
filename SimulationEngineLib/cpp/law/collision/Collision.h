#pragma once
#include "cpp/law/Law.h"
#include "shared/law/collision/detector/CollisionDetector.cuh"
#include "shared/law/collision/resolver/CollisionResolver.cuh"
class Collision :
    public Law
{
public:
    Collision(std::shared_ptr<CollisionDetector> collisionDetector, std::shared_ptr<CollisionResolver> collisionResolver, bool useGpu = false);

private:
    std::shared_ptr<CollisionDetector> collisionDetector;
    std::shared_ptr<CollisionResolver> collisionResolver;
};

