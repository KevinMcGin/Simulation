﻿#pragma once
#include "CollisionResolver.cuh"

#include <vector>
#include <cmath>
#include <iostream>

class CollisionResolverCoalesce: public CollisionResolver {
public:
	static const int INDEX = 0;
public:
	__device__ __host__ virtual void resolve(Particle* p1, Particle* p2);
	virtual int getIndex() { return INDEX; };
private:
	__device__ __host__ Vector3D getCoalesced(double mass1, double mass2, Vector3D vec1, Vector3D vec2);
};