#include "Particle.cuh"

void Particle::advance() {
	position = position + velocity;
}