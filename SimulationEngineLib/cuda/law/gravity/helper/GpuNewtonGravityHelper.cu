#include "cpp/particle/ParticleSimple.h"
#include "shared/particle/Particle.cuh"
#include "shared/util/MatrixMaths.cuh"
#include "shared/law/gravity/helper/NewtonGravityHelper.cuh"
#include "cuda/law/gravity/helper/GpuNewtonGravityHelper.cuh"

#include <cmath>

__device__
void radiusComponentKernelHelper(unsigned long long betweenParticlesTriangularIndex, Particle** particles, Vector3D<float>* accelerations, unsigned long long betweenParticlesTriangularCount, float G, unsigned long long vectorsProcessedTriangular) {
	unsigned long long particleIndex1, particleIndex2;
	MatrixMaths::getLowerTriangularCoordinates(betweenParticlesTriangularIndex + vectorsProcessedTriangular, &particleIndex1, &particleIndex2);
	if (particles[particleIndex1]->particlesExist(particles[particleIndex2])) {
		Vector3D<float> devicePRadiusComponent = getRadiusComponent(particles[particleIndex1], particles[particleIndex2], G);
		accelerations[betweenParticlesTriangularIndex] = -getAcceleration(particles[particleIndex2]->mass, devicePRadiusComponent);
		accelerations[betweenParticlesTriangularIndex + betweenParticlesTriangularCount] = getAcceleration(particles[particleIndex1]->mass, devicePRadiusComponent);
	 }
}

__device__
void addAccelerationsKernelLowerHelper(unsigned long long particleIndex1, Particle** particles, Vector3D<float>* accelerations, unsigned long long particleIndex2, unsigned long long vectorsProcessedTriangular, unsigned int deltaTime, MomentumService** momentumServiceGpu) {
	if (particleIndex1 < particleIndex2) {
		if (particles[particleIndex1]->particlesExist(particles[particleIndex2])) {
			unsigned long long radiusComponentIndex = MatrixMaths::getLowerTriangularIndex(particleIndex1, particleIndex2);
			runOnParticle(particles[particleIndex1], accelerations[radiusComponentIndex - vectorsProcessedTriangular], deltaTime, *momentumServiceGpu);
		} 
	}
}

__device__
void addAccelerationsKernelUpperHelper(unsigned long long particleIndex1Local, Particle** particles, Vector3D<float>* accelerations, unsigned long long xOffset, unsigned long long particleIndex2, unsigned long long particleCount, unsigned long long vectorsProcessedTriangular, unsigned long long betweenParticlesTriangularCount, unsigned int deltaTime, MomentumService** momentumServiceGpu) {
	unsigned long long particleIndex1 = particleIndex1Local + particleIndex2 + 1 + xOffset;
	if (particleIndex1 < particleCount) {
		if (particles[particleIndex1]->particlesExist(particles[particleIndex2])) {
			unsigned long long radiusComponentIndex = MatrixMaths::getUpperTriangularIndex(particleIndex1, particleIndex2);
			runOnParticle(particles[particleIndex1], accelerations[radiusComponentIndex - vectorsProcessedTriangular + betweenParticlesTriangularCount], deltaTime, *momentumServiceGpu);
		} 
	}
}
