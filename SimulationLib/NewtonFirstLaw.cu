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
    cudaError_t cudaStatus;
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
	cudaStatus= cudaMalloc(&devicePPosition, n*sizeof(Vector3D));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "\nNewtonFirstLaw: cudaMalloc failed!\n");
	}
	cudaStatus= cudaMalloc(&devicePVelocity, n*sizeof(Vector3D));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "\nNewtonFirstLaw: cudaMalloc failed!\n");
	}
	cudaStatus = cudaMemcpy(devicePPosition, pPosition, n*sizeof(Vector3D), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "\nNewtonFirstLaw: cudaMemcpy failed!\n");
	}
	cudaStatus = cudaMemcpy(devicePVelocity, pVelocity, n*sizeof(Vector3D), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "\nNewtonFirstLaw: cudaMemcpy failed!\n");
	}
	advanceParticles <<<1 + n/256, 256>>> (devicePPosition, devicePVelocity, n);
	cudaDeviceSynchronize();
	cudaStatus = cudaGetLastError();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "\nNewtonFirstLaw: addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
	}
	cudaStatus = cudaMemcpy(pPosition, devicePPosition, n*sizeof(Vector3D), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "\nNewtonFirstLaw: cudaMemcpy failed!\n");
	}

	for(int i = 0; i < n; i++)
		particles[i]->position = pPosition[i];
	
	cudaFree(devicePPosition);
	cudaFree(devicePVelocity);
}
