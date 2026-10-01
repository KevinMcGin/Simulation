#pragma once
#include "shared/particle/model/Vector3D.cuh"
#include "shared/precision/Real.cuh"

class Particle {
public:
	Real mass;
	Real radius;
	Vector3D<Real> position;
	Vector3D<Real> velocity;
	bool deleted = false;

	#if defined(USE_GPU)
	__device__ __host__
	#endif
	Particle(
		Real mass,
		Real radius,
		Vector3D<Real>  position,
		Vector3D<Real>  velocity,
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
	void advance(Real deltaTime);

	#if defined(USE_GPU)
		__device__ 
	#endif
	bool particlesExist(Particle* p2);

	// virtual Real getTemperature() = 0;
	}; 