#pragma once
#if defined(USE_GPU)
    #include "cuda_runtime.h"
#endif
#include "shared/particle/model/Vector3D.cuh"

class MomentumService {
public:
    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<float> addMomentum(
        Vector3D<float> acceleration, 
        unsigned int deltaTime,
        float mass,
        Vector3D<float> velocity
    ) = 0;

    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<float> mergeVelocity(
        float mass1, 
        Vector3D<float> velocity1,
        float mass2, 
        Vector3D<float> velocity2
    ) = 0;

protected:
    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<float> getMomentum(
        float mass, 
        Vector3D<float> velocity
    ) = 0;
};