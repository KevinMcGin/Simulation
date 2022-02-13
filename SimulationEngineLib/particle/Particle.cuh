#pragma once
#include "particle/model/Vector3D.cuh"



class Particle {
public:
	float			  mass;
	float            radius;
	Vector3D<float>  position;
	Vector3D<float>  velocity;
	bool deleted = false;

	__device__ __host__ Particle(
		float mass,
		float radius,
		Vector3D<float>  position,
		Vector3D<float>  velocity
	) : mass(mass), radius(radius), position(position), velocity(velocity) {}
	__device__ __host__ void advance();
	// virtual float getTemperature() = 0;
}; 