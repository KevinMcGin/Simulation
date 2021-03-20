#include "NewtonGravity.cuh"
#include "ParticleSimple.h"

#include <cmath>



NewtonGravity::NewtonGravity() : Law(), G(PhysicalConstants::GRAVITATIONAL_CONSTANT)
{

}

NewtonGravity::NewtonGravity(double G) : Law(), G(G)
{

}

void runOnParticles(Particle* p1, Particle* p2, double G);
__device__ __host__ void runOnParticle(Particle* p1, Particle* p2, Vector3D radiusComponent);	
__device__ __host__ Vector3D getRadiusComponent(Vector3D position1, Vector3D position2, double G);

__global__ 
void newtonGravityKernel(CopyClass* copy, int n, double G)
{
	int x = threadIdx.x + blockIdx.x*blockDim.x;
	if(x < n) { 
		//int y = (int)((-1+sqrt((float)8*idx+1))/2) + 1;
		 //printf("%d  -> (%d,%d)\n", x, x, n);
		// printf("%d -> (%lf,%lf,%lf)\n", idx, copy->par[x]->velocity.x, copy->par[x]->velocity.y, copy->par[x]->velocity.z);
		// runParticle(copy->par[x],copy->par[n],G);
		// printf("%d -> (%lf,%lf,%lf)\n", idx, copy->par[x]->velocity.x, copy->par[x]->velocity.y, copy->par[x]->velocity.z);
	} 
}

void NewtonGravity::run(vector<Particle*>& particles)
{
	for (auto it1 = particles.begin(); it1 != particles.end(); it1++) {
		auto p1 = *it1;
		for (auto it2 = it1+1; it2 < particles.end(); it2++) {
			auto p2 = *it2;
			runOnParticles(p1,p2,G);
		}
	}
}

void NewtonGravity::runParallel(vector<Particle*>& particles) {
	cudaError_t cudaStatus;
	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "\ncudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
	}
	int particleCount = particles.size();
	//int particleMatchingsCount = (particleCount-1)*particleCount/2;

	//Instantiate object on the CPU
	CopyClass cpuClass;
	cpuClass.par = new Particle*[particleCount];
	for(int i = 0; i < particleCount; ++i)
		cpuClass.par[i] = particles[i];

	//Allocate storage for object onto GPU and copy host object to device
	CopyClass * gpuClass;
	cudaMalloc(&gpuClass,sizeof(CopyClass));
	cudaMemcpy(gpuClass,&cpuClass,sizeof(CopyClass),cudaMemcpyHostToDevice);

	//Copy dynamically allocated child objects to GPU
	Particle ** d_par;
	d_par = new Particle*[particleCount];
	for(int i = 0; i < particleCount; ++i) {
		cudaMalloc(&d_par[i],sizeof(ParticleSimple));
		cudaMemcpy(d_par[i],cpuClass.par[i],sizeof(ParticleSimple),cudaMemcpyHostToDevice);
	}

	//Copy the d_par array itself to the device

	Particle ** td_par;
	cudaMalloc(&td_par, particleCount * sizeof(Particle *));
	cudaMemcpy(td_par, d_par, particleCount * sizeof(Particle *), cudaMemcpyHostToDevice);

	//copy *pointer value* of td_par to appropriate location in top level object
	cudaMemcpy(&(gpuClass->par),&(td_par),sizeof(Particle **),cudaMemcpyHostToDevice);

	for(int i = 0; i < particleCount; i++) {
		newtonGravityKernel <<<1 + i/256, 256>>> (gpuClass, i, G);
		cudaDeviceSynchronize();
		cudaStatus = cudaGetLastError();
		if (cudaStatus != cudaSuccess) {
			fprintf(stderr, "\nNewtonGravity: addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
		}
	}
	for(int i = 0; i < particleCount; i++) {
		cudaStatus = cudaMemcpy(cpuClass.par[i],d_par[i],sizeof(ParticleSimple),cudaMemcpyDeviceToHost);
		if (cudaStatus != cudaSuccess) {
			fprintf(stderr, "\n\nNewtonGravity: cudaMemcpyDeviceToHost failed: %s\n", cudaGetErrorString(cudaStatus));
		}
		particles[i]->velocity = cpuClass.par[i]->velocity;
	}
}

void runOnParticles(Particle* p1, Particle* p2, double G) {	
	Vector3D radiusComponent = getRadiusComponent(p1->position, p2->position, G);
	runOnParticle(p1, p2, -1*radiusComponent);
	runOnParticle(p2, p1, radiusComponent);
}

//Vector3D radiusComponent = getRadiusComponent(p1->position, p2->position, G);
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
	if (displacementSquared == 0 ) return {0,0,0};
	return (G / displacementSquared) * displacement.unit();
}
