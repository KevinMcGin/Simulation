#include "particle/Particle.cuh"

__device__ 
void radiusComponentKernelHelper(unsigned long long idx, Particle** particles, Vector3D* accelerations, unsigned long long betweenParticlesTriangularCount, double G, unsigned long long vectorsProcessedTriangular);

__device__ 
void addAccelerationsKernelLowerHelper(unsigned long long idx, Particle** particles, Vector3D* accelerations, unsigned long long x0, unsigned long long y, unsigned long long n, unsigned long long vectorsProcessedTriangular);

__device__ 
void addAccelerationsKernelUpperHelper(unsigned long long idx, Particle** particles, Vector3D* accelerations, unsigned long long x0, unsigned long long y, unsigned long long n, unsigned long long vectorsProcessedTriangular, unsigned long long particlesProcessed, unsigned long long betweenParticlesTriangularCount);
