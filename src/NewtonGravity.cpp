#include "NewtonGravity.h"
#include <cmath>



NewtonGravity::NewtonGravity(double G /*= GRAVITATIONAL_CONSTANT*/) : G(G), Law()
{

}

void NewtonGravity::run(vector<Particle*> particles)
{
	for (const auto& p1 : particles)
		for (const auto& p2 : particles) {
			if (p1 != p2) {
				Vector3D displacement = p1->position - p2->position;
				p1->velocity.x += getAcceleration(p2->mass, displacement.x);
				p1->velocity.y += getAcceleration(p2->mass, displacement.y);
				p1->velocity.z += getAcceleration(p2->mass, displacement.z);
			}
		}
}

double NewtonGravity::getAcceleration(double mass, double displacement)
{
	if (displacement == 0) return 0;
	int sign = displacement < 0 ? 1 : -1;
	double radiusSquared = pow(displacement, 2.0);
	return (sign * G * mass) / radiusSquared;
}
