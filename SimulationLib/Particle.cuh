#pragma once
#include "Vector3D.cuh"

using namespace std;

class Particle {
public:
	double			  mass;
	double            radius;
	Vector3D  position;
	Vector3D  velocity;
	Vector3D  angularVelocity;
	bool deleted;

	__device__ __host__ Particle(
		double			  mass,
		double            radius,
		Vector3D  position,
		Vector3D  velocity,
		Vector3D  angularVelocity
	) {
		this->mass = mass;
		this->radius = radius;
		this->position = position;
		this->velocity = velocity;
		this->angularVelocity = angularVelocity;
		this->deleted = false;
	}
	__device__ __host__ void advance();
	virtual double getTemperature() = 0;
}; 