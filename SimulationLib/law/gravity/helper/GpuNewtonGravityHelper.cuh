#include "particle/Particle.cuh"

__device__ 
void radiusComponentKernelHelper(int idx, Particle** particles, Vector3D* accelerations, int n, double G);

__device__ 
void addAccelerationsKernelLowerHelper(int idx, Particle** particles, Vector3D* accelerations, int x0, int y, int n);

__device__ 
void addAccelerationsKernelUpperHelper(int idx, Particle** particles, Vector3D* accelerations, int x0, int y, int n, int betweenParticlesTriangularCount);
