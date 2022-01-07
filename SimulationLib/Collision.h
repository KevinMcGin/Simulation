#pragma once
#include "Law.h"
#include "CollisionDetector.cuh"
#include "CollisionResolver.cuh"
class Collision :
    public Law
{
public:
    Collision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver, bool use_gpu = false);

private:
    CollisionDetector* collisionDetector;
    CollisionResolver* collisionResolver;
};

