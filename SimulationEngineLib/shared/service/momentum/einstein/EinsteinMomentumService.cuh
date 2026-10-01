#pragma once
#include "shared/precision/Real.cuh"
#include "shared/service/momentum/newton/NewtonMomentumService.cuh"
#include "cpp/constant/PhysicalConstants.h"	

class EinsteinMomentumService : public NewtonMomentumService {
public:
	static const int INDEX = 1;
    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    Vector3D<Real> getVelocityPlusAcceleration(
        Real mass,
        Vector3D<Real> acceleration, 
        Real deltaTime,
        Vector3D<Real> velocity
    ) override;

    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    Vector3D<Real> mergeVelocity(
        Real mass1, 
        Vector3D<Real> velocity1,
        Real mass2, 
        Vector3D<Real> velocity2
    ) override;

    int getIndex() override { return INDEX; };

protected:
    #if defined(USE_GPU)
    __device__ __host__
    #endif 
    virtual Vector3D<Real> getMomentum(
        Real mass, 
        Vector3D<Real> velocity
    ) override;

private:
    const double speedLight = PhysicalConstants::SPEED_OF_LIGHT;
	const double speedLightSquared = speedLight * speedLight;

    Real getGamma(
        Vector3D<Real> velocity
    );

    Vector3D<Real> getVelocityFromMomentum(
        Real mass,
        Vector3D<Real> momentum
    );
};