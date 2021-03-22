#pragma once
#include "Law.h"
#include "CollisionDetector.h"
#include "CollisionResolver.h"
class Collision :
    public Law
{
public:
    Collision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver);

    void run(vector<Particle*>& particles) override;
	void runParallel(vector<Particle*>& particles) override;

private:
    CollisionDetector* collisionDetector;
    CollisionResolver* collisionResolver;
};

