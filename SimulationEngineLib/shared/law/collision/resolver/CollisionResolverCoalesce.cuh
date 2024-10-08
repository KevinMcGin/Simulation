﻿#pragma once
#include "shared/law/collision/resolver/CollisionResolver.cuh"

#include <vector>
#include <cmath>
#include <iostream>

class CollisionResolverCoalesce: public CollisionResolver {
public:
	static const int INDEX = 0;

	#if defined(USE_GPU)
	__device__ __host__
	#endif
	CollisionResolverCoalesce();
	#if defined(USE_GPU)
	__device__ __host__
	#endif
	void resolve(
		Particle* p1, 
		Particle* p2,
		MomentumService* momentumService
	) override;
		int getIndex() override { return INDEX; };
private:
	#if defined(USE_GPU)
	__device__ __host__
	#endif
	Vector3D<float> getCoalesced(float mass1, float mass2, Vector3D<float> vec1, Vector3D<float> vec2);
	Vector3D<float> getCoalescedVelocity(
		Particle* p1, Particle* p2, MomentumService* momentumService
	);

};