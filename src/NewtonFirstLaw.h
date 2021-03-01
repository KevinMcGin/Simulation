#pragma once
#include "Law.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class NewtonFirstLaw: public Law {
	public:
		virtual void run(vector<Particle*> particles) {
			for (const auto& p : particles) 
				for (int i = 0; i < p->position.size(); i++)
					p->position[i] = p->position[i] + p->velocity[i];
		}
};