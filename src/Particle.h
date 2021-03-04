#pragma once
#include "Vector3D.h"

using namespace std;

class Particle {
public:
	double			  mass;
	double            radius;
	Vector3D  position;
	Vector3D  velocity;
	Vector3D  angularVelocity;

	Particle(
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
	}
	virtual double getTemperature() = 0;
}; 