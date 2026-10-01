#include "shared/service/momentum/newton/NewtonMomentumService.cuh"

#if defined(USE_GPU)
__device__ __host__
#endif 
Vector3D<Real> NewtonMomentumService::getVelocityPlusAcceleration(
    Real mass,
    Vector3D<Real> acceleration, 
    Real deltaTime,
    Vector3D<Real> velocity
) {
    return velocity + acceleration * deltaTime;
}

#if defined(USE_GPU)
__device__ __host__
#endif 
Vector3D<Real> NewtonMomentumService::mergeVelocity(
    Real mass1, 
    Vector3D<Real> velocity1,
    Real mass2, 
    Vector3D<Real> velocity2
) {
    return (
        getMomentum(mass1, velocity1) + 
        getMomentum(mass2, velocity2)
    ) / (mass1 + mass2);
}


#if defined(USE_GPU)
__device__ __host__
#endif 
Vector3D<Real> NewtonMomentumService::getMomentum(
    Real mass, 
    Vector3D<Real> velocity
) {
    return mass * velocity;
}
