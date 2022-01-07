#pragma once
#include "CpuLaw.h"
#include "CollisionDetector.cuh"
#include "CollisionResolver.cuh"

#include <vector>
#include <stdio.h>
#include <iostream>

class CpuCollision: public CpuLaw {
public:
	CpuCollision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver);
	virtual void run(vector<Particle*>& particles);

private:
    CollisionDetector* collisionDetector;
    CollisionResolver* collisionResolver;
};