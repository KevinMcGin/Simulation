#pragma once
#include "Law.h"

#include <vector>
#include <stdio.h>
#include <iostream>

const double GRAVITATIONAL_CONSTANT = 0.00005;

class NewtonGravity: public Law {
public:
	NewtonGravity(double G = GRAVITATIONAL_CONSTANT) : G(G), Law() {}

	virtual void run(vector<Particle*> particles) {
		for (const auto& p1 : particles)
			for (const auto& p2 : particles) {
				Vector3D displacement = p1->position - p2->position;
				p1->velocity.x += getAcceleration(p2->mass, displacement.x);
				p1->velocity.y += getAcceleration(p2->mass, displacement.y);
				p1->velocity.z += getAcceleration(p2->mass, displacement.z);
			}
	}

protected:
	const double G;

private:
	double getAcceleration(double mass, double displacement) {
		if (displacement == 0) return 0;
		const int sign = displacement < 0 ? 1 : -1;
		const unsigned int radiusSquared = displacement * displacement;
		return (sign * G * mass) / radiusSquared;
	}
};