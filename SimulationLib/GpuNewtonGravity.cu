#include "GpuNewtonGravity.cuh"
#include "ParticleSimple.h"
#include "Particle.cuh"
#include "MatrixMaths.cuh"
#include "NewtonGravityHeper.cuh"

#include <cmath>

GpuNewtonGravity::GpuNewtonGravity(double G) : GpuLaw("GpuNewtonGravity"), G(G) { }

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

void GpuNewtonGravity::run(Particle** td_par, int particleCount) {
	//Radius component
	int betweenParticlesCount = (particleCount-1)*particleCount;
	int betweenParticlesTriangularCount = betweenParticlesCount/2;
	Vector3D* accelerations = NULL;
	cudaWithError->malloc((void**)&accelerations, betweenParticlesCount*sizeof(Vector3D));
	radiusComponentKernel <<<1 + betweenParticlesTriangularCount/256, 256>>> (td_par, accelerations, betweenParticlesTriangularCount, G);
	cudaWithError->peekAtLastError("radiusComponentKernel");

	for(int i = 0; i < particleCount; i++) {
		addAccelerationsKernelLower <<<1 + i/256, 256>>> (td_par, accelerations, 0, i, i);
		cudaWithError->peekAtLastError("addAccelerationsKernelLower");
		addAccelerationsKernelUpper <<<1 + (particleCount-1-i)/256, 256>>> (td_par, accelerations, i+1, i, particleCount, betweenParticlesTriangularCount);
		cudaWithError->peekAtLastError("addAccelerationsKernelUpper");
	}
	
	cudaWithError->free(accelerations);
}

