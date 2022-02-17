#include "law/gravity/CpuNewtonGravity.h"
#include "particle/Particle.cuh"
#include "particle/ParticleSimple.h"
#include "law/gravity/helper/NewtonGravityHelper.cuh"

#include <cmath>

CpuNewtonGravity::CpuNewtonGravity(float G) : CpuLaw(), G(G) { }

void runOnParticles(Particle* p1, Particle* p2, float G);

void CpuNewtonGravity::run(std::vector<Particle*>& particles) {
	for (auto it1 = particles.begin(); it1 != particles.end(); it1++) {
		auto p1 = *it1;
		for (auto it2 = it1 + 1; it2 < particles.end(); it2++) {
			auto p2 = *it2;
			runOnParticles(p1, p2, G);
		}
	}
} 

void runOnParticles(Particle* p1, Particle* p2, float G) {	
	Vector3D<float> radiusComponent = getRadiusComponent(p1, p2, G);
	runOnParticle(p1, -getAcceleration(p2->mass, radiusComponent));
	runOnParticle(p2, getAcceleration(p1->mass, radiusComponent));
}