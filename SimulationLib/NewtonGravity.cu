#include "NewtonGravity.cuh"
#include "ParticleSimple.h"

#include <cmath>



NewtonGravity::NewtonGravity() : Law(), G(PhysicalConstants::GRAVITATIONAL_CONSTANT)
{

}

NewtonGravity::NewtonGravity(double G) : Law(), G(G)
{

}


__device__ __host__ void runParticle(Particle* p1, Particle* p2, double G);	
__device__ __host__ Vector3D getRadiusComponent(Vector3D position1, Vector3D position2, double G);

__global__ 
void newtonGravityKernel(CopyClass* copy, int particleMatchingsCount, double G)
{
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < particleMatchingsCount) { 
		int y = (int)((-1+sqrt((float)8*idx+1))/2) + 1;
		int x = idx - (y-1)*y/2;
		printf("%d  -> (%d,%d)\n", idx, x, y);
		printf("%d -> (%lf,%lf,%lf)\n", idx, copy->par[x]->velocity.x, copy->par[x]->velocity.y, copy->par[x]->velocity.z);
		runParticle(copy->par[x],copy->par[y],G);
		printf("%d -> (%lf,%lf,%lf)\n", idx, copy->par[x]->velocity.x, copy->par[x]->velocity.y, copy->par[x]->velocity.z);
	} 
}

void NewtonGravity::run(vector<Particle*>& particles)
{
	#if USE_CUDA
		cudaError_t cudaStatus;
		cudaStatus = cudaSetDevice(0);
		if (cudaStatus != cudaSuccess) {
			fprintf(stderr, "\ncudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
		}
		int particleCount = particles.size();
		int particleMatchingsCount = (particleCount-1)*particleCount/2;

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
			printf("\tCopying data\n");
			cudaMemcpy(d_par[i],cpuClass.par[i],sizeof(ParticleSimple),cudaMemcpyHostToDevice);
		}

		//Copy the d_par array itself to the device

		Particle ** td_par;
		cudaMalloc(&td_par, particleCount * sizeof(Particle *));
		cudaMemcpy(td_par, d_par, particleCount * sizeof(Particle *), cudaMemcpyHostToDevice);

		//copy *pointer value* of td_par to appropriate location in top level object
		cudaMemcpy(&(gpuClass->par),&(td_par),sizeof(Particle **),cudaMemcpyHostToDevice);

		newtonGravityKernel <<<1 + particleMatchingsCount/256, 256>>> (gpuClass, particleMatchingsCount, G);
		cudaDeviceSynchronize();
		cudaStatus = cudaGetLastError();
		if (cudaStatus != cudaSuccess) {
			fprintf(stderr, "\nNewtonGravity: addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
		}
		for(int i = 0; i < particleMatchingsCount; i++) {
			cudaStatus = cudaMemcpy(cpuClass.par[i],d_par[i],sizeof(ParticleSimple),cudaMemcpyDeviceToHost);
			if (cudaStatus != cudaSuccess) {
				fprintf(stderr, "\n\nNewtonGravity: cudaMemcpy4 failed: %s\n", cudaGetErrorString(cudaStatus));
			}
			particles[i]->velocity = cpuClass.par[i]->velocity;
		}
	#else
		for (auto it1 = particles.begin(); it1 != particles.end(); it1++) {
			auto p1 = *it1;
			for (auto it2 = it1+1; it2 < particles.end(); it2++) {
				auto p2 = *it2;
				runParticle(p1,p2,G);
			}
		}
	#endif
}

__device__ __host__ 
void runParticle(Particle* p1, Particle* p2, double G) {	
	// printf("getting radius component");
	Vector3D radiusComponent = getRadiusComponent(p1->position, p2->position, G);
	// printf("got radius component");
	Vector3D acceleration1 = p2->mass * radiusComponent;
	p1->velocity = p1->velocity + acceleration1;
	Vector3D acceleration2 = p1->mass * radiusComponent * -1;
	p2->velocity = p2->velocity + acceleration2;
	// printf("updated velocities");
}

__device__ __host__ 
Vector3D getRadiusComponent(Vector3D position1, Vector3D position2, double G)
{
	// printf("in getRadiusComponent");
	Vector3D displacement = position2 - position1;
	double displacementSquared = displacement.magnitudeSquared();
	// printf("if statement in getRadiusComponent");
	if (displacementSquared == 0 ) return {0,0,0};
	// printf("finished getRadiusComponent");
	return (G / displacementSquared) * displacement.unit();
}
