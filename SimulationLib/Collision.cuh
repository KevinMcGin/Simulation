#pragma once
#include "Law.h"
#include "CollisionDetector.cuh"
#include "CollisionResolver.cuh"
class Collision :
    public Law
{
public:
    Collision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver, bool use_gpu = false);
    ~Collision();

    void cpuRun(vector<Particle*>& particles) override;
	void gpuRun(Particle** td_par, int particleCount) override;

private:
    CollisionDetector* collisionDetector;
    CollisionResolver* collisionResolver;
    CollisionDetector** collisionDetectorGpu = NULL;
    CollisionResolver** collisionResolverGpu = NULL;
};

