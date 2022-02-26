#include "particle/Particle.cuh"

__device__ __host__
void Particle::advance() {
	position = position + velocity;
}


__device__ 
bool Particle::particlesExist(Particle* p2) {
	return !deleted && !p2->deleted;
}