#include "shared/service/momentum/einstein/EinsteinMomentumService.cuh"

#if defined(USE_GPU)
__device__ __host__
#endif
Real EinsteinMomentumService::getGamma(
    Vector3D<Real> velocity
) {
    return 1 / 
        sqrt(
            1 - (velocity.magnitudeSquared() / speedLightSquared)
        );
}

#if defined(USE_GPU)
__device__ __host__
#endif
Vector3D<Real> EinsteinMomentumService::getVelocityFromMomentum(
    Real mass,
    Vector3D<Real> momentum
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
Vector3D<Real> EinsteinMomentumService::getVelocityPlusAcceleration(
    Real mass,
    Vector3D<Real> acceleration, 
    Real deltaTime,
    Vector3D<Real> velocity
) {
    auto classicalVelocityChange = acceleration * deltaTime;
    auto classicalVelocityChangeMagnitudeSquared = classicalVelocityChange.magnitudeSquared();
    auto massMomentumChange = mass;
    // Condition for completeness sake. 
    // Condition rarely met. But if met, would otherwise create imaginary numbers in the gamma calculation.
    if (classicalVelocityChangeMagnitudeSquared > speedLightSquared) {
        //large offset is due to Real errors
        Real belowSpeedOfLight = (Real)speedLight - 1000000.0;
        classicalVelocityChange = belowSpeedOfLight * classicalVelocityChange.unit();
        massMomentumChange *= classicalVelocityChangeMagnitudeSquared / belowSpeedOfLight;
    }
    // Assumption: a small change in classical momentum is equal to a small change in relativistic
    auto relativisticMomentumChange = getMomentum(massMomentumChange, classicalVelocityChange);
    auto currentMomentum = getMomentum(mass, velocity);
    auto newMomentum = currentMomentum + relativisticMomentumChange;
    
    return getVelocityFromMomentum(mass, newMomentum);
}

#if defined(USE_GPU)
__device__ __host__
#endif 
Vector3D<Real> EinsteinMomentumService::mergeVelocity(
    Real mass1, 
    Vector3D<Real> velocity1,
    Real mass2, 
    Vector3D<Real> velocity2
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
Vector3D<Real> EinsteinMomentumService::getMomentum(
    Real mass, 
    Vector3D<Real> velocity
) {
    return getGamma(velocity) * NewtonMomentumService::getMomentum(mass, velocity);
}
