#pragma once
#include "law/Law.h"
#include "law/collision/detector/CollisionDetector.cuh"
#include "law/collision/resolver/CollisionResolver.cuh"
class Collision :
    public Law
{
public:
    Collision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver, bool useGpu = false);

private:
    CollisionDetector* collisionDetector;
    CollisionResolver* collisionResolver;
};

