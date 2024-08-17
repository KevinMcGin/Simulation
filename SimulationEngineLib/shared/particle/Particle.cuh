#pragma once
#include "shared/particle/model/Vector3D.cuh"

class Particle {
public:
	float mass;
	float radius;
	Vector3D<float> position;
	Vector3D<float> velocity;
	bool deleted = false;

	#if defined(USE_GPU)
	__device__ __host__
	#endif
	Particle(
		float mass,
		float radius,
		Vector3D<float>  position,
		Vector3D<float>  velocity,
		bool deleted = false
	);

	Particle();

	#if defined(USE_GPU)
		__device__ __host__
	#endif
	Particle(Particle* p);

	#if defined(USE_GPU)
	__device__ __host__
	#endif
	void advance(unsigned int deltaTime);

	#if defined(USE_GPU)
	__device__ __host__
	#endif
	virtual void addMomentum(Vector3D<float> acceleration, unsigned int deltaTime);

	#if defined(USE_GPU)
	__device__ __host__
	#endif
	virtual Vector3D<float> getMomentum();

	#if defined(USE_GPU)
	__device__ __host__
	#endif
	virtual Vector3D<float> mergeVelocity(Particle* p);

	#if defined(USE_GPU)
		__device__ 
	#endif
	bool particlesExist(Particle* p2);

	// virtual float getTemperature() = 0;
	}; 