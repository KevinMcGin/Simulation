#include "NewtonGravity.cuh"
#include "ParticleSimple.h"

#include <cmath>



NewtonGravity::NewtonGravity() : Law("NewtonGravity"), G(PhysicalConstants::GRAVITATIONAL_CONSTANT) { }

NewtonGravity::NewtonGravity(double G) : Law("NewtonGravity"), G(G) { }

void runOnParticles(Particle* p1, Particle* p2, double G);
__device__ __host__ void runOnParticle(Particle* p1, Particle* p2, Vector3D radiusComponent);	
__device__ __host__ Vector3D getRadiusComponent(Vector3D position1, Vector3D position2, double G);

__global__ 
void radiusComponentKernel(Particle** particles, Vector3D* devicePRadiusComponent, int n, double G) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < n) { 
		unsigned long y = (long long)((-1+sqrt((double)8*idx+1))/2) + 1;
		unsigned long x = idx - (y-1)*y/2;
		devicePRadiusComponent[idx] = getRadiusComponent(particles[x]->position, particles[y]->position, G);
	} 
}

__global__ 
void newtonGravityKernelLower(Particle** particles, Vector3D* devicePRadiusComponent, int x0, int y, int n) {
	unsigned long idx = threadIdx.x + blockIdx.x*blockDim.x;
	unsigned long x = idx + x0;
	if(x < n) { 
		int radiusComponentIndex = x + (y-1)*y/2;
		runOnParticle(particles[x], particles[y], -devicePRadiusComponent[radiusComponentIndex]);
	} 
}

__global__ 
void newtonGravityKernelUpper(Particle** particles, Vector3D* devicePRadiusComponent, int x0, int y, int n) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	int x = idx + x0;
	if(x < n) { 
		int radiusComponentIndex = y + (x-1)*x/2;
		runOnParticle(particles[x], particles[y], devicePRadiusComponent[radiusComponentIndex]);
	} 
}

void NewtonGravity::cpuRun(vector<Particle*>& particles) {
	for (auto it1 = particles.begin(); it1 != particles.end(); it1++) {
		auto p1 = *it1;
		for (auto it2 = it1+1; it2 < particles.end(); it2++) {
			auto p2 = *it2;
			runOnParticles(p1,p2,G);
		}
	}
}

void NewtonGravity::gpuRun(vector<Particle*>& particles) {
	cudaWithError->setDevice(0);
	int particleCount = particles.size();

	//Instantiate object on the CPU
	UniverseGPU cpuClass;
	cpuClass.particles = new Particle*[particleCount];
	for(int i = 0; i < particleCount; ++i)
		cpuClass.particles[i] = particles[i];

	//Copy dynamically allocated child objects to GPU
	Particle ** d_par;
	d_par = new Particle*[particleCount];
	for(int i = 0; i < particleCount; ++i) {
		cudaWithError->malloc((void**)&d_par[i],sizeof(ParticleSimple));
		cudaWithError->memcpy(d_par[i], cpuClass.particles[i], sizeof(ParticleSimple), cudaMemcpyHostToDevice);
	}

	//Copy the d_par array itself to the device
	Particle ** td_par;
	cudaWithError->malloc((void**)&td_par, particleCount * sizeof(Particle *));
	cudaWithError->memcpy(td_par, d_par, particleCount * sizeof(Particle *), cudaMemcpyHostToDevice);

	//Radius component
	int betweenParticlesCount = (particleCount-1)*particleCount/2;
	Vector3D* devicePRadiusComponent = NULL;
	cudaWithError->malloc((void**)&devicePRadiusComponent, betweenParticlesCount*sizeof(Vector3D));
	radiusComponentKernel <<<1 + betweenParticlesCount/256, 256>>> (td_par, devicePRadiusComponent, betweenParticlesCount, G);
	cudaWithError->deviceSynchronize();

	for(int i = 0; i < particleCount; i++) {
		newtonGravityKernelLower <<<1 + i/256, 256>>> (td_par, devicePRadiusComponent, 0, i, i);
		newtonGravityKernelUpper <<<1 + (particleCount-1-i)/256, 256>>> (td_par, devicePRadiusComponent, i+1, i, particleCount);
		cudaWithError->deviceSynchronize();
	}
	for(int i = 0; i < particleCount; i++) {
		cudaWithError->memcpy(cpuClass.particles[i],d_par[i],sizeof(ParticleSimple),cudaMemcpyDeviceToHost);
		cudaWithError->free(d_par[i]);
		particles[i]->velocity = cpuClass.particles[i]->velocity;
	}
	
	cudaWithError->free(devicePRadiusComponent);
	cudaWithError->free(td_par);
	delete cpuClass.particles;
	delete d_par;
}

void runOnParticles(Particle* p1, Particle* p2, double G) {	
	Vector3D radiusComponent = getRadiusComponent(p1->position, p2->position, G);
	runOnParticle(p1, p2, -1*radiusComponent);
	runOnParticle(p2, p1, radiusComponent);
}

__device__ __host__ 
void runOnParticle(Particle* p1, Particle* p2, Vector3D radiusComponent) {	
	Vector3D acceleration1 = p2->mass * radiusComponent;
	p1->velocity = p1->velocity + acceleration1;
}

__device__ __host__ 
Vector3D getRadiusComponent(Vector3D position1, Vector3D position2, double G)
{
	Vector3D displacement = position1 - position2;
	double displacementSquared = displacement.magnitudeSquared();
	if (displacementSquared == 0 ) {
		return {0,0,0};
	} else {
		Vector3D unit = displacement / sqrt(displacementSquared);
		return (G / displacementSquared) * unit;
	}
}
