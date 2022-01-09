#pragma once
#include "law/CpuLaw.h"
#include "law/collision/detector/CollisionDetector.cuh"
#include "law/collision/resolver/CollisionResolver.cuh"

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