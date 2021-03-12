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
				double displacementSquared = displacement.magnitudeSquared();
				Vector3D acceleration = getAcceleration(p2->mass, displacementSquared) * displacement.unit();
				p1->velocity = p1->velocity + acceleration;
			}
		}
}

double NewtonGravity::getAcceleration(double mass, double displacementSquared)
{
	//collision should handle causes where displacementSquared is << 1
	//if (abs(displacementSquared) < 0.005 ) return 0;
	if (displacementSquared == 0 ) return 0;
	return (G * mass) / displacementSquared;
}
