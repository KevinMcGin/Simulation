#pragma once
#include "Law.h"

#include <list>
#include <stdio.h>
#include <iostream>

const double GRAVITATIONAL_CONSTANT = 0.5;

class NewtonGravity: public Law {
	public:
		NewtonGravity(double G = GRAVITATIONAL_CONSTANT) : G(G), Law() {}

		virtual void run(list<Particle*> particles) {
			for (const auto& p1 : particles)
				for (const auto& p2 : particles)
					for (int i = 0; i < p1->velocity.size(); i++) {
						const int positionDifference = p1->position[i] - p2->position[i];
						const int sign = positionDifference <= 0 ? 1 : -1;
						const unsigned int radiusSquared = positionDifference * positionDifference;
						if(radiusSquared != 0)
							p1->velocity[i] = p1->velocity[i] +
								(sign * G * p2->mass) / radiusSquared;
					}
		}

	protected:
		const double G;
};