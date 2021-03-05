#include "NewtonFirstLaw.h"



void NewtonFirstLaw::run(vector<Particle*> particles)
{
	for (const auto& p : particles)
		p->position = p->position + p->velocity;
}
