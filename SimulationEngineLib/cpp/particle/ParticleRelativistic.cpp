#include "cpp/particle/ParticleRelativistic.h"

const static double speedLight = 299792458.0;
const static double speedLightSquared = speedLight * speedLight;

float ParticleRelativistic::getGamma() {
    return 1 / sqrt(1 - velocity.magnitudeSquared() / speedLightSquared);
}

void ParticleRelativistic::addMomentum(
    Vector3D<float> acceleration, 
    unsigned int deltaTime
) {
    auto classicalForce = acceleration * mass;
    auto realtivisticForce = pow(getGamma(), 3) * classicalForce;
    Particle::addMomentum(realtivisticForce / mass, deltaTime);
}

Vector3D<float> ParticleRelativistic::getMomentum() {
	return getGamma() * mass * velocity;
}

Vector3D<float> ParticleRelativistic::mergeVelocity(Particle* p) {
	auto u = (getMomentum() + p->getMomentum()) / 
		(mass + p->mass);
    return speedLight * u / sqrt(speedLightSquared + u.magnitudeSquared());
}
