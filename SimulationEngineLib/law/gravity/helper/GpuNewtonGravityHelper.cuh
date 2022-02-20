#include "particle/Particle.cuh"

__device__ 
void radiusComponentKernelHelper(unsigned long long idx, Particle** particles, Vector3D<float>* accelerations, unsigned long long betweenParticlesTriangularCount, float G, unsigned long long vectorsProcessedTriangular);

__device__ 
void addAccelerationsKernelLowerHelper(unsigned long long idx, Particle** particles, Vector3D<float>* accelerations, unsigned long long y,unsigned long long vectorsProcessedTriangular);

__device__ 
void addAccelerationsKernelUpperHelper(unsigned long long idx, Particle** particles, Vector3D<float>* accelerations, unsigned long long xOffset, unsigned long long y, unsigned long long n, unsigned long long vectorsProcessedTriangular, unsigned long long particlesProcessed, unsigned long long betweenParticlesTriangularCount);
