#include "particle/Particle.cuh"

#if defined(USE_GPU)
   __device__ __host__
#endif
void Particle::advance() {
	position = position + velocity;
}


#if defined(USE_GPU)
	__device__ 
#endif
bool Particle::particlesExist(Particle* p2) {
	return !deleted && !p2->deleted;
}