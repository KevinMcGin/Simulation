#pragma once
#include "shared/particle/Particle.cuh"

class ParticleRelativistic: public Particle {
	public:
		ParticleRelativistic(
			float			  mass,
			float            radius,
			Vector3D<float>  position,
			Vector3D<float>  velocity
		) : Particle(mass, radius, position, velocity) {}
		// float getTemperature() override;

	void addMomentum(
		Vector3D<float> acceleration, 
		unsigned int deltaTime
	) override;

	Vector3D<float> mergeVelocity(Particle* p) override;

	Vector3D<float> getMomentum() override;

private:
	float getGamma();

};