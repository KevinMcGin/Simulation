#include "shared/particle/Particle.cuh"

#if defined(USE_GPU)
__device__ __host__
#endif
Particle::Particle(
	float mass,
	float radius,
	Vector3D<float>  position,
	Vector3D<float>  velocity,
	bool deleted
) : mass(mass), radius(radius), position(position), velocity(velocity), deleted(deleted) {}

Particle::Particle() : mass(0.0), 
	radius(0.0), 
	position({0.0, 0.0, 0.0}), 
	velocity({0.0, 0.0, 0.0}) {}

#if defined(USE_GPU)
	__device__ __host__
#endif
Particle::Particle(Particle* p) : Particle(p->mass, p->radius, p->position, p->velocity, p->deleted) {}

#if defined(USE_GPU)
   __device__ __host__
#endif
void Particle::advance(
	unsigned int deltaTime
) {
	printf("advancing\n");
	position = position + velocity * deltaTime;
}

#if defined(USE_GPU)
   __device__ __host__
#endif
void Particle::addMomentum(Vector3D<float> acceleration, unsigned int deltaTime) {
	velocity = velocity + acceleration * deltaTime;
}

#if defined(USE_GPU)
   __device__ __host__
#endif
Vector3D<float> Particle::getMomentum() {
	return mass * velocity;
}

#if defined(USE_GPU)
   __device__ __host__
#endif
Vector3D<float> Particle::mergeVelocity(Particle* p) {
	return (getMomentum() + p->getMomentum()) / 
		(mass + p->mass);
}


#if defined(USE_GPU)
	__device__ 
#endif
bool Particle::particlesExist(Particle* p2) {
	return !deleted && !p2->deleted;
}