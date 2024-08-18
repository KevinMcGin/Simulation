#include "shared/service/momentum/newton/NewtonMomentumService.cuh"

#if defined(USE_GPU)
__device__ __host__
#endif 
Vector3D<float> NewtonMomentumService::addMomentum(
    Vector3D<float> acceleration, 
    unsigned int deltaTime,
    float mass,
    Vector3D<float> velocity
) {
    return velocity + acceleration * deltaTime;
}

#if defined(USE_GPU)
__device__ __host__
#endif 
Vector3D<float> NewtonMomentumService::mergeVelocity(
    float mass1, 
    Vector3D<float> velocity1,
    float mass2, 
    Vector3D<float> velocity2
) {
    return (
        getMomentum(mass1, velocity1) + 
        getMomentum(mass2, velocity2)
    ) / (mass1 + mass2);
}


#if defined(USE_GPU)
__device__ __host__
#endif 
Vector3D<float> NewtonMomentumService::getMomentum(
    float mass, 
    Vector3D<float> velocity
) {
    return mass * velocity;
}
