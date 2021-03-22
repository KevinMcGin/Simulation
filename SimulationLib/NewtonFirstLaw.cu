#include "NewtonFirstLaw.cuh"
#include "Particle.cuh"

__global__ 
static void advanceParticles(Vector3D* position, const Vector3D* velocity, int particleCount)
{
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < particleCount) { 
		position[idx] = position[idx] + velocity[idx];
	} 
}

void NewtonFirstLaw::run(vector<Particle*>& particles) {
	for (const auto& p : particles)
		p->advance();
}

void NewtonFirstLaw::runParallel(vector<Particle*>& particles) {
	cudaError_t cudaStatus;
	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "\nNewtonFirstLaw: cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
	}
	int n = particles.size();
	Vector3D* pPosition = new Vector3D[n];
	Vector3D* pVelocity = new Vector3D[n];
	for(int i = 0; i < n; i++) {
		pPosition[i] = particles[i]->position;
		pVelocity[i] = particles[i]->velocity;
	}
	Vector3D* devicePPosition = NULL;
	Vector3D* devicePVelocity = NULL;
	cudaMalloc(&devicePPosition, n*sizeof(Vector3D));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "\nNewtonFirstLaw: cudaMalloc failed!\n");
	}
	cudaMalloc(&devicePVelocity, n*sizeof(Vector3D));
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
