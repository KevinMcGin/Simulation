#pragma once
#include "shared/particle/Particle.cuh"
#include "cpp/constant/PhysicalConstants.h"	

class ParticleRelativistic: public Particle {
	public:
		#if defined(USE_GPU)
			__device__ __host__
		#endif
		ParticleRelativistic(
			float			  mass,
			float            radius,
			Vector3D<float>  position,
			Vector3D<float>  velocity,
			bool             deleted = false
		);

		#if defined(USE_GPU)
			__device__ __host__
		#endif
		ParticleRelativistic(Particle* p);
		// float getTemperature() override;

	#if defined(USE_GPU)
		__device__ __host__
	#endif
	void addMomentum(
		Vector3D<float> acceleration, 
		unsigned int deltaTime
	) override;

	#if defined(USE_GPU)
		__device__ __host__
	#endif
	Vector3D<float> mergeVelocity(Particle* p) override;

	#if defined(USE_GPU)
		__device__ __host__
	#endif
	Vector3D<float> getMomentum() override;

private:
	#if defined(USE_GPU)
		__device__ __host__
	#endif
	float getGamma();

	const long double speedLight = PhysicalConstants::SPEED_OF_LIGHT;
	const long double speedLightSquared = speedLight * speedLight;
};