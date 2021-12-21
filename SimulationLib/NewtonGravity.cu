#include "NewtonGravity.cuh"
#include "ParticleSimple.h"
#include "MatrixMaths.cuh"

#include <cmath>

NewtonGravity::NewtonGravity() : Law("NewtonGravity"), G(PhysicalConstants::GRAVITATIONAL_CONSTANT) { }

NewtonGravity::NewtonGravity(double G) : Law("NewtonGravity"), G(G) { }

void runOnParticles(Particle* p1, Particle* p2, double G);
__device__ __host__ Vector3D getAcceleration(double mass, Vector3D radiusComponent);
__device__ __host__ void runOnParticle(Particle* p1, Vector3D acceleration);	
__device__ __host__ Vector3D getRadiusComponent(Particle* p1, Particle* p2, double G);

__global__ 
void radiusComponentKernel(Particle** particles, Vector3D* accelerations, int n, double G) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < n) { 
		int x, y;
		MatrixMaths::getLowerTriangularCoordinates(idx, &x, &y);
		Vector3D devicePRadiusComponent = getRadiusComponent(particles[x], particles[y], G);
		accelerations[idx] = -getAcceleration(particles[y]->mass, devicePRadiusComponent);
		accelerations[idx + n] = getAcceleration(particles[x]->mass, devicePRadiusComponent);
	} 
}

__global__ 
void addAccelerationsKernelLower(Particle** particles, Vector3D* accelerations, int x0, int y, int n) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	int x = idx + x0;
	if(x < n) { 
		int radiusComponentIndex = MatrixMaths::getLowerTriangularIndex(x, y);
		runOnParticle(particles[x], accelerations[radiusComponentIndex]);
	} 
}

__global__ 
void addAccelerationsKernelUpper(Particle** particles, Vector3D* accelerations, int x0, int y, int n, int betweenParticlesTriangularCount) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	int x = idx + x0;
	if(x < n) { 
		int radiusComponentIndex = MatrixMaths::getUpperTriangularIndex(x, y);
		runOnParticle(particles[x], accelerations[radiusComponentIndex + betweenParticlesTriangularCount]);
	} 
}

void NewtonGravity::cpuRun(vector<Particle*>& particles) {
	for (auto it1 = particles.begin(); it1 != particles.end(); it1++) {
		auto p1 = *it1;
		for (auto it2 = it1 + 1; it2 < particles.end(); it2++) {
			auto p2 = *it2;
			runOnParticles(p1, p2, G);
		}
	}
} 

void NewtonGravity::gpuRun(Particle** td_par, int particleCount) {
	//Radius component
	int betweenParticlesCount = (particleCount-1)*particleCount;
	int betweenParticlesTriangularCount = betweenParticlesCount/2;
	Vector3D* accelerations = NULL;
	cudaWithError->malloc((void**)&accelerations, betweenParticlesCount*sizeof(Vector3D));
	radiusComponentKernel <<<1 + betweenParticlesTriangularCount/256, 256>>> (td_par, accelerations, betweenParticlesTriangularCount, G);
	cudaWithError->deviceSynchronize();

	for(int i = 0; i < particleCount; i++) {
		addAccelerationsKernelLower <<<1 + i/256, 256>>> (td_par, accelerations, 0, i, i);
		addAccelerationsKernelUpper <<<1 + (particleCount-1-i)/256, 256>>> (td_par, accelerations, i+1, i, particleCount, betweenParticlesTriangularCount);
	}
	cudaWithError->deviceSynchronize();
	
	cudaWithError->free(accelerations);
}

void runOnParticles(Particle* p1, Particle* p2, double G) {	
	Vector3D radiusComponent = getRadiusComponent(p1, p2, G);
	runOnParticle(p1, -getAcceleration(p2->mass, radiusComponent));
	runOnParticle(p2, getAcceleration(p1->mass, radiusComponent));
}

__device__ __host__ 
Vector3D getAcceleration(double mass, Vector3D radiusComponent) {	
	return mass * radiusComponent;
}

__device__ __host__ 
void runOnParticle(Particle* p1, Vector3D acceleration) {
	p1->velocity = p1->velocity + acceleration;
}

__device__ __host__ 
Vector3D getRadiusComponent(Particle* p1, Particle* p2, double G) {
	Vector3D displacement = p1->position - p2->position;
	double displacementSquared = displacement.magnitudeSquared();
	if (displacementSquared <= pow(p1->radius + p2->radius, 2)) {
		return {0, 0, 0};
	} else {
		Vector3D unit = displacement / sqrt(displacementSquared);
		return (G / displacementSquared) * unit;
	}
}
