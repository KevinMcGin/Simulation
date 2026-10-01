#pragma once
#include "shared/precision/Real.cuh"
#if defined(USE_GPU)
    #include "cuda_runtime.h"
#endif
#include "shared/particle/model/Vector3D.cuh"

class MomentumService {
public:
    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<Real> getVelocityPlusAcceleration(
        Real mass,
        Vector3D<Real> acceleration, 
        Real deltaTime,
        Vector3D<Real> velocity
    ) = 0;

    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<Real> mergeVelocity(
        Real mass1, 
        Vector3D<Real> velocity1,
        Real mass2, 
        Vector3D<Real> velocity2
    ) = 0;

    virtual int getIndex() = 0;

protected:
    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<Real> getMomentum(
        Real mass, 
        Vector3D<Real> velocity
    ) = 0;
};