#include "particle/ParticleSimple.h"
#include "particle/Particle.cuh"
#include "util/MatrixMaths.cuh"
#include "law/gravity/helper/NewtonGravityHelper.cuh"
#include "law/gravity/helper/GpuNewtonGravityHelper.cuh"

#include <cmath>

__device__
bool particlesExist(Particle* p1, Particle* p2) {
	return !p1->deleted && !p2->deleted;
}

__device__ 
void radiusComponentKernelHelper(unsigned long long idx, Particle** particles, Vector3D<float>* accelerations, unsigned long long betweenParticlesTriangularCount, float G, unsigned long long vectorsProcessedTriangular) {
	unsigned long long x, y;
	if(particlesExist(particles[x], particles[y])) {
		MatrixMaths::getLowerTriangularCoordinates(idx + vectorsProcessedTriangular, &x, &y);
		Vector3D<float> devicePRadiusComponent = getRadiusComponent(particles[x], particles[y], G);
		accelerations[idx] = -getAcceleration(particles[y]->mass, devicePRadiusComponent);
		accelerations[idx + betweenParticlesTriangularCount] = getAcceleration(particles[x]->mass, devicePRadiusComponent);
	 }
}

__device__ 
void addAccelerationsKernelLowerHelper(unsigned long long idx, Particle** particles, Vector3D<float>* accelerations, unsigned long long y, unsigned long long vectorsProcessedTriangular) {
	unsigned long long x = idx;
	if(x < y) {
		if(particlesExist(particles[x], particles[y])) {
			unsigned long long radiusComponentIndex = MatrixMaths::getLowerTriangularIndex(x, y);
			runOnParticle(particles[x], accelerations[radiusComponentIndex - vectorsProcessedTriangular]);
		} 
	}
}

__device__ 
void addAccelerationsKernelUpperHelper(unsigned long long idx, Particle** particles, Vector3D<float>* accelerations, unsigned long long xOffset, unsigned long long y, unsigned long long n, unsigned long long vectorsProcessedTriangular, unsigned long long betweenParticlesTriangularCount) {
	unsigned long long x = idx + y + 1 + xOffset;
	if(x < n) {
		if(particlesExist(particles[x], particles[y])) {
			unsigned long long radiusComponentIndex = MatrixMaths::getUpperTriangularIndex(x, y);
			runOnParticle(particles[x], accelerations[radiusComponentIndex - vectorsProcessedTriangular + betweenParticlesTriangularCount]);
		} 
	}
}
