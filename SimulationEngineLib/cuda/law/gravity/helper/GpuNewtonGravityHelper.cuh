#include "shared/particle/Particle.cuh"

__device__
void radiusComponentKernelHelper(
    unsigned long long betweenParticlesTriangularIndex, 
    Particle** particles, 
    Vector3D<float>* accelerations, 
    unsigned long long betweenParticlesTriangularCount, 
    float G, 
    unsigned long long vectorsProcessedTriangular
);

__device__
void addAccelerationsKernelLowerHelper(
    unsigned long long particleIndex1, 
    Particle** particles,
    Vector3D<float>* accelerations, 
    unsigned long long particleIndex2,
    unsigned long long vectorsProcessedTriangular,
    unsigned int deltaTime,
    MomentumService* momentumServiceGpu
);

__device__
void addAccelerationsKernelUpperHelper(
    unsigned long long particleIndex1Local, 
    Particle** particles, 
    Vector3D<float>* accelerations, 
    unsigned long long xOffset, 
    unsigned long long particleIndex2, 
    unsigned long long particleCount,
    unsigned long long vectorsProcessedTriangular, 
    unsigned long long betweenParticlesTriangularCount, 
    unsigned int deltaTime,
    MomentumService* momentumServiceGpu
);
