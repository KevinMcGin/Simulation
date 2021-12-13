#pragma once
#include "Law.h"
#include "CollisionDetector.h"
#include "CollisionResolver.h"
class Collision :
    public Law
{
public:
    Collision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver);

    void cpuRun(vector<Particle*>& particles) override;
	void gpuRun(vector<Particle*>& particles) override;

private:
    CollisionDetector* collisionDetector;
    CollisionResolver* collisionResolver;
};

