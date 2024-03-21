#pragma once
#include "cpp/law/collision/Collision.h"


class CollisionCoalesce :
    public Collision
{
public:
    CollisionCoalesce(bool useGpu = false);
};

