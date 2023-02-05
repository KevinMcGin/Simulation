#include "particle/Particle.cuh"

#if defined(USE_GPU) 
	__device__
#endif
void radiusComponentKernelHelper(unsigned long long betweenParticlesTriangularIndex, Particle** particles, Vector3D<float>* accelerations, unsigned long long betweenParticlesTriangularCount, float G, unsigned long long vectorsProcessedTriangular);

#if defined(USE_GPU) 
	__device__
#endif
void addAccelerationsKernelLowerHelper(unsigned long long particleIndex1, Particle** particles, Vector3D<float>* accelerations, unsigned long long particleIndex2,unsigned long long vectorsProcessedTriangular);

#if defined(USE_GPU) 
	__device__
#endif
void addAccelerationsKernelUpperHelper(unsigned long long particleIndex1Local, Particle** particles, Vector3D<float>* accelerations, unsigned long long xOffset, unsigned long long particleIndex2, unsigned long long particleCount, unsigned long long vectorsProcessedTriangular, unsigned long long betweenParticlesTriangularCount);
