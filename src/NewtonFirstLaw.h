#pragma once
#include "Law.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class NewtonFirstLaw: public Law {
	public:
		virtual void run(vector<Particle*> particles) {
			for (const auto& p : particles)
				p->position = p->position + p->velocity;
		}
};