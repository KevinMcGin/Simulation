#pragma once
#include "shared/particle/model/Vector3D.cuh"

class Particle {
public:
	float			  mass;
	float            radius;
	Vector3D<float>  position;
	Vector3D<float>  velocity;
	bool deleted = false;

#if defined(USE_GPU)
   __device__ __host__
#endif
Particle(
		float mass,
		float radius,
		Vector3D<float>  position,
		Vector3D<float>  velocity
	) : mass(mass), radius(radius), position(position), velocity(velocity) {}
#if defined(USE_GPU)
   __device__ __host__
#endif
void advance();
	#if defined(USE_GPU)
		__device__ 
	#endif
	bool particlesExist(Particle* p2);
	// virtual float getTemperature() = 0;
}; 