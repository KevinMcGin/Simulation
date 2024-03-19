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
	__device__ 
#endif
bool Particle::particlesExist(Particle* p2) {
	return !deleted && !p2->deleted;
}