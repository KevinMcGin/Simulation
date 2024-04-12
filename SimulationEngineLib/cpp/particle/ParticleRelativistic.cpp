#include "cpp/particle/ParticleRelativistic.h"

const static float speedLightSquared = 299792458 * 299792458;

void ParticleRelativistic::addMomentum(
    Vector3D<float> acceleration, 
    unsigned int deltaTime
) {
    auto classicalForce = acceleration * mass;
    auto gamma = 1 / sqrt(1 - velocity.magnitudeSquared() / speedLightSquared);
    auto realtivisticForce = pow(gamma, 3) * classicalForce;
    Particle::addMomentum(realtivisticForce / mass, deltaTime);
}
