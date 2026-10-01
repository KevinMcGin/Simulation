#pragma once
#include "shared/precision/Real.cuh"
#include "shared/service/momentum/MomentumService.cuh"

class NewtonMomentumService : public MomentumService {
public:
	static const int INDEX = 0;
    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<Real> getVelocityPlusAcceleration(
        Real mass,
        Vector3D<Real> acceleration, 
        Real deltaTime,
        Vector3D<Real> velocity
    ) override;

    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<Real> mergeVelocity(
        Real mass1, 
        Vector3D<Real> velocity1,
        Real mass2, 
        Vector3D<Real> velocity2
    ) override;

    virtual int getIndex() override { return INDEX; };

protected:
    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<Real> getMomentum(
        Real mass, 
        Vector3D<Real> velocity
    ) override;
};