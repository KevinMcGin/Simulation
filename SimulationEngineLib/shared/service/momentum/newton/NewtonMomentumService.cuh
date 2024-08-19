#pragma once
#include "shared/service/momentum/MomentumService.cuh"

class NewtonMomentumService : public MomentumService {
public:
	static const int INDEX = 0;
    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<float> getVelocityPlusAcceleration(
        float mass,
        Vector3D<float> acceleration, 
        unsigned int deltaTime,
        Vector3D<float> velocity
    ) override;

    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<float> mergeVelocity(
        float mass1, 
        Vector3D<float> velocity1,
        float mass2, 
        Vector3D<float> velocity2
    ) override;

    virtual int getIndex() override { return INDEX; };

protected:
    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<float> getMomentum(
        float mass, 
        Vector3D<float> velocity
    ) override;
};