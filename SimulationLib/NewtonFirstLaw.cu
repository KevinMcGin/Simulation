#include "NewtonFirstLaw.cuh"
#include "Particle.cuh"

NewtonFirstLaw::NewtonFirstLaw() : Law("NewtonFirstLaw") { }


__global__ 
static void advanceParticles(Vector3D* position, const Vector3D* velocity, int particleCount)
{
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < particleCount) { 
		position[idx] = position[idx] + velocity[idx];
	} 
}

void NewtonFirstLaw::cpuRun(vector<Particle*>& particles) {
	for (const auto& p : particles)
		p->advance();
}

void NewtonFirstLaw::gpuRun(vector<Particle*>& particles) {
	cudaWithError->setDevice(0);
	int n = particles.size();
	Vector3D* pPosition = new Vector3D[n];
	Vector3D* pVelocity = new Vector3D[n];
	for(int i = 0; i < n; i++) {
		pPosition[i] = particles[i]->position;
		pVelocity[i] = particles[i]->velocity;
	}
	Vector3D* devicePPosition = NULL;
	Vector3D* devicePVelocity = NULL;
	cudaWithError->malloc((void**)&devicePPosition, n*sizeof(Vector3D));
	cudaWithError->malloc((void**)&devicePVelocity, n*sizeof(Vector3D));
	cudaWithError->memcpy(devicePPosition, pPosition, n*sizeof(Vector3D), cudaMemcpyHostToDevice);
	cudaWithError->memcpy(devicePVelocity, pVelocity, n*sizeof(Vector3D), cudaMemcpyHostToDevice);
	advanceParticles <<<1 + n/256, 256>>> (devicePPosition, devicePVelocity, n);
	cudaWithError->deviceSynchronize();
	cudaWithError->memcpy(pPosition, devicePPosition, n*sizeof(Vector3D), cudaMemcpyDeviceToHost);

	for(int i = 0; i < n; i++)
		particles[i]->position = pPosition[i];
	
	cudaWithError->free(devicePPosition);
	cudaWithError->free(devicePVelocity);
}
