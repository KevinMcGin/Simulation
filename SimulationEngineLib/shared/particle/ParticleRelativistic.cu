#include "shared/particle/ParticleRelativistic.cuh"


#if defined(USE_GPU)
    __device__ __host__
#endif
ParticleRelativistic::ParticleRelativistic(Particle* p) : Particle(p) {}

#if defined(USE_GPU)
    __device__ __host__
#endif
ParticleRelativistic::ParticleRelativistic(
    float			  mass,
    float            radius,
    Vector3D<float>  position,
    Vector3D<float>  velocity,
    bool             deleted
) : Particle(mass, radius, position, velocity, deleted) {}

#if defined(USE_GPU)
__device__ __host__
#endif
float ParticleRelativistic::getGamma() {
    return 1 / sqrt(1 - velocity.magnitudeSquared() / speedLightSquared);
}

#if defined(USE_GPU)
__device__ __host__
#endif
void ParticleRelativistic::addMomentum(
    Vector3D<float> acceleration, 
    unsigned int deltaTime
) {
    auto classicalForce = acceleration * mass;
    auto realtivisticForce = pow(getGamma(), 3) * classicalForce;
    Particle::addMomentum(realtivisticForce / mass, deltaTime);
}

#if defined(USE_GPU)
__device__ __host__
#endif
Vector3D<float> ParticleRelativistic::getMomentum() {
	return getGamma() * mass * velocity;
}

#if defined(USE_GPU)
__device__ __host__
#endif
Vector3D<float> ParticleRelativistic::mergeVelocity(Particle* p) {
	auto u = (getMomentum() + p->getMomentum()) / 
		(mass + p->mass);
    return speedLight * u / sqrt(speedLightSquared + u.magnitudeSquared());
}
