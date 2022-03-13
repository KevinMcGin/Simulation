#pragma once
#include "law/CpuLaw.h"
#include "law/collision/detector/CollisionDetector.cuh"
#include "law/collision/resolver/CollisionResolver.cuh"

#include <vector>
#include <stdio.h>
#include <iostream>
#include <memory>

class CpuCollision: public CpuLaw {
public:
	CpuCollision(std::shared_ptr<CollisionDetector> collisionDetector, std::shared_ptr<CollisionResolver> collisionResolver);
	virtual void run(std::vector<Particle*>& particles);

private:
    std::shared_ptr<CollisionDetector> collisionDetector;
    std::shared_ptr<CollisionResolver> collisionResolver;
};