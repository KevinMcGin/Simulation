#include "shared/service/momentum/einstein/EinsteinMomentumService.cuh"

#if defined(USE_GPU)
__device__ __host__
#endif
float EinsteinMomentumService::getGamma(
    Vector3D<float> velocity
) {
    return 1 / 
        sqrt(
            1 - (velocity.magnitudeSquared() / speedLightSquared)
        );
}

#if defined(USE_GPU)
__device__ __host__
#endif
Vector3D<float> EinsteinMomentumService::getVelocityFromMomentum(
    float mass,
    Vector3D<float> momentum
) {
    return momentum / (
        sqrt(
            pow(mass, 2) + (momentum.magnitudeSquared() / speedLightSquared)
        )
    );
}

#if defined(USE_GPU)
__device__ __host__
#endif 
Vector3D<float> EinsteinMomentumService::getVelocityPlusAcceleration(
    float mass,
    Vector3D<float> acceleration, 
    unsigned int deltaTime,
    Vector3D<float> velocity
) {
    auto classicalVelocityChange = acceleration * deltaTime;
    auto relativisticVelocityChange = classicalVelocityChange / pow(getGamma(velocity), 3);
    
    return velocity + relativisticVelocityChange;
}

#if defined(USE_GPU)
__device__ __host__
#endif 
Vector3D<float> EinsteinMomentumService::mergeVelocity(
    float mass1, 
    Vector3D<float> velocity1,
    float mass2, 
    Vector3D<float> velocity2
) {
    auto p =  (
        getMomentum(mass1, velocity1) + 
        getMomentum(mass2, velocity2)
    );
    return getVelocityFromMomentum(mass1 + mass2, p);
}


#if defined(USE_GPU)
__device__ __host__
#endif 
Vector3D<float> EinsteinMomentumService::getMomentum(
    float mass, 
    Vector3D<float> velocity
) {
    return getGamma(velocity) * 
        NewtonMomentumService::getMomentum(mass, velocity);
}
