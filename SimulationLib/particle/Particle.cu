#include "particle/Particle.cuh"

__device__ __host__
void Particle::advance() {
	position = position + velocity;
}