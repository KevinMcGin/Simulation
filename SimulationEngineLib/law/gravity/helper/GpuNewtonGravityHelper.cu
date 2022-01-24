#include "particle/ParticleSimple.h"
#include "particle/Particle.cuh"
#include "util/MatrixMaths.cuh"
#include "law/gravity/helper/NewtonGravityHelper.cuh"
#include "law/gravity/helper/GpuNewtonGravityHelper.cuh"

#include <cmath>

__device__ 
void radiusComponentKernelHelper(int idx, Particle** particles, Vector3D* accelerations, int betweenParticlesTriangularCount, double G, int vectorsProcessedTriangular) {
	unsigned long long x, y;
	MatrixMaths::getLowerTriangularCoordinates(idx + vectorsProcessedTriangular, &x, &y);
	Vector3D devicePRadiusComponent = getRadiusComponent(particles[x], particles[y], G);
	accelerations[idx] = -getAcceleration(particles[y]->mass, devicePRadiusComponent);
	accelerations[idx + betweenParticlesTriangularCount] = getAcceleration(particles[x]->mass, devicePRadiusComponent);
}

__device__ 
void addAccelerationsKernelLowerHelper(int idx, Particle** particles, Vector3D* accelerations, int x0, int y, int n, int vectorsProcessedTriangular) {
	int x = idx + x0;
	if(x < n) { 
		unsigned long long radiusComponentIndex = MatrixMaths::getLowerTriangularIndex(x, y);
		runOnParticle(particles[x], accelerations[radiusComponentIndex - vectorsProcessedTriangular]);
	} 
}

__device__ 
void addAccelerationsKernelUpperHelper(int idx, Particle** particles, Vector3D* accelerations, int x0, int y, int n, int vectorsProcessedTriangular, int particlesProcessed, int betweenParticlesTriangularCount) {
	int x = idx + x0;
	if(x < n && x >= particlesProcessed) { 
		unsigned long long radiusComponentIndex = MatrixMaths::getUpperTriangularIndex(x, y);
		runOnParticle(particles[x], accelerations[radiusComponentIndex - vectorsProcessedTriangular + betweenParticlesTriangularCount]);
	} 
}
