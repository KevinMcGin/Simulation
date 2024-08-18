#include "shared/service/momentum/einstein/EinsteinMomentumService.cuh"

#if defined(USE_GPU)
__device__ __host__
#endif
float EinsteinMomentumService::getGamma(
    Vector3D<float> velocity
) {
    return 1 / sqrt(1 - velocity.magnitudeSquared() / speedLightSquared);
}

#if defined(USE_GPU)
__device__ __host__
#endif 
Vector3D<float> EinsteinMomentumService::addMomentum(
    Vector3D<float> acceleration, 
    unsigned int deltaTime,
    float mass,
    Vector3D<float> velocity
) {
    auto classicalForce = acceleration * mass;
    auto realtivisticForce = pow(getGamma(velocity), 3) * classicalForce;
    return NewtonMomentumService::addMomentum(
        realtivisticForce / mass, 
        deltaTime,
        mass,
        velocity
    );
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
    return (
        getMomentum(mass1, velocity1) + 
        getMomentum(mass2, velocity2)
    ) / (mass1 + mass2);

    auto u = NewtonMomentumService::getMomentum(mass1, velocity1) + 
        NewtonMomentumService::getMomentum(mass2, velocity2);
    return speedLight * u / sqrt(speedLightSquared + u.magnitudeSquared());
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
