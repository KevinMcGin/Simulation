#pragma once
#include "particle/model/Vector3D.cuh"

using namespace std;

class Particle {
public:
	double			  mass;
	double            radius;
	Vector3D  position;
	Vector3D  velocity;
	bool deleted = false;

	__device__ __host__ Particle(
		double mass,
		double radius,
		Vector3D  position,
		Vector3D  velocity
	) : mass(mass), radius(radius), position(position), velocity(velocity) {}
	__device__ __host__ void advance();
	// virtual double getTemperature() = 0;
}; 