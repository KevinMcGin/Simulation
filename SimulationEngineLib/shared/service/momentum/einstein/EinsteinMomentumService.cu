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
    auto classicalVelocityChangeMagnitudeSquared = classicalVelocityChange.magnitudeSquared();
    if (classicalVelocityChangeMagnitudeSquared > speedLightSquared) {
        //offset is due to float errors
        float belowSpeedOfLight = (float)speedLight - 1000000.0f;
        classicalVelocityChange = belowSpeedOfLight * classicalVelocityChange.unit();
        mass *= classicalVelocityChangeMagnitudeSquared / belowSpeedOfLight;
    }
    auto relativisticMomentumChange = getMomentum(mass, classicalVelocityChange);
    auto currentMomentum = getMomentum(mass, velocity);
    auto newMomentum = currentMomentum + relativisticMomentumChange;
    
    return getVelocityFromMomentum(mass, newMomentum);
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
