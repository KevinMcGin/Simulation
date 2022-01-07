#pragma once
#include "Collision.h"


class CollisionCoalesce :
    public Collision
{
public:
    CollisionCoalesce(bool use_gpu = false);
};

