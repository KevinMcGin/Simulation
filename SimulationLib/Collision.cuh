#pragma once
#include "Law.h"
#include "CollisionDetector.cuh"
#include "CollisionResolver.cuh"
class Collision :
    public Law
{
public:
    Collision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver);

    void cpuRun(vector<Particle*>& particles) override;
	void gpuRun(Particle** td_par, int particleCount) override;

private:
    CollisionDetector* collisionDetector;
    CollisionResolver* collisionResolver;
};

