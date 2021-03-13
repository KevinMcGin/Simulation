#pragma once
#include "Law.h"
#include "CollisionDetector.h"
#include "CollisionResolver.h"
class Collission :
    public Law
{
public:
    Collission(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver);

    void run(vector<Particle*>& particles) override;

private:
    CollisionDetector* collisionDetector;
    CollisionResolver* collisionResolver;
};

