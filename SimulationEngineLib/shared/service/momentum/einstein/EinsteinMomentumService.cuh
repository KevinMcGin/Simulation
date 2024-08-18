#pragma once
#include "shared/service/momentum/newton/NewtonMomentumService.cuh"
#include "cpp/constant/PhysicalConstants.h"	

class EinsteinMomentumService : public NewtonMomentumService {
public:
	static const int INDEX = 1;
    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    Vector3D<float> addMomentum(
        Vector3D<float> acceleration, 
        unsigned int deltaTime,
        float mass,
        Vector3D<float> velocity
    ) override;

    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    Vector3D<float> mergeVelocity(
        float mass1, 
        Vector3D<float> velocity1,
        float mass2, 
        Vector3D<float> velocity2
    ) override;

protected:
    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    Vector3D<float> getMomentum(
        float mass, 
        Vector3D<float> velocity
    ) override;

private:
    const long double speedLight = PhysicalConstants::SPEED_OF_LIGHT;
	const long double speedLightSquared = speedLight * speedLight;

    float getGamma(
        Vector3D<float> velocity
    );
};