#include "shared/particle/Particle.cuh"

#if defined(USE_GPU)
   __device__ __host__
#endif
void Particle::advance(
	unsigned int deltaTime
) {
	position = position + velocity * deltaTime;
}

#if defined(USE_GPU)
   __device__ __host__
#endif
void Particle::addMomentum(Vector3D<float> acceleration, unsigned int deltaTime) {
	velocity = velocity + acceleration * deltaTime;
}


#if defined(USE_GPU)
	__device__ 
#endif
bool Particle::particlesExist(Particle* p2) {
	return !deleted && !p2->deleted;
}