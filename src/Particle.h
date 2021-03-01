#pragma once
#include <array> 

using namespace std;

class Particle {
public:
	double			  mass;
	double            radius;
	array<double, 3>  position;
	array<double, 3>  velocity;
	array<double, 3>  angularVelocity;

	Particle(
		double			  mass,
		double            radius,
		array<double, 3>  position,
		array<double, 3>  velocity,
		array<double, 3>  angularVelocity
	) {
		this->mass = mass;
		this->radius = radius;
		this->position = position;
		this->velocity = velocity;
		this->angularVelocity = angularVelocity;
	}
	virtual double getTemperature() = 0;
}; 