#include "NewtonGravity.h"
#include <cmath>



NewtonGravity::NewtonGravity(double G /*= GRAVITATIONAL_CONSTANT*/) : G(G), Law()
{

}

void NewtonGravity::run(vector<Particle*>& particles)
{
	for (const auto& p1 : particles)
		for (const auto& p2 : particles) {
			if (p1 != p2) {
				Vector3D displacement = (p2->position - p1->position);
				Vector3D displacementSquared = displacement.magnitudeSquared() * displacement.unit();
				p1->velocity.x += getAcceleration(p2->mass, displacementSquared.x);
				p1->velocity.y += getAcceleration(p2->mass, displacementSquared.y);
				p1->velocity.z += getAcceleration(p2->mass, displacementSquared.z);
			}
		}
}

double NewtonGravity::getAcceleration(double mass, double displacementSquared)
{
	//collision should handle causes where displacementSquared is << 1
	//if (abs(displacementSquared) < 0.0005 ) return 0;
	if (displacementSquared == 0 ) return 0;
	return (G * mass) / displacementSquared;
}
