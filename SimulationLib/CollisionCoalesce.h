#pragma once
#include "Collision.cuh"


class CollisionCoalesce :
    public Collision
{
public:
    CollisionCoalesce(bool use_gpu = false);
};

