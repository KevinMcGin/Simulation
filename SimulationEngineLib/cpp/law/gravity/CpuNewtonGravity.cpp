#include "cpp/law/gravity/CpuNewtonGravity.h"
#include "shared/particle/Particle.cuh"
#include "cpp/particle/ParticleSimple.h"
#include "shared/law/gravity/helper/NewtonGravityHelper.cuh"

#include <cmath>

CpuNewtonGravity::CpuNewtonGravity(
	float G,
	std::shared_ptr<MomentumService> momentumService
) : CpuLaw(), G(G), momentumService(momentumService) { }

void runOnParticles(
	Particle* p1,
	Particle* p2, 
	float G, 
	unsigned int deltaTime,
	MomentumService* momentumService
);

void CpuNewtonGravity::run(
	std::vector<Particle*>& particles,
	unsigned int deltaTime
) {
	for (auto it1 = particles.begin(); it1 != particles.end(); it1++) {
		auto p1 = *it1;
		for (auto it2 = it1 + 1; it2 < particles.end(); it2++) {
			auto p2 = *it2;
			runOnParticles(
				p1, 
				p2, 
				G, 
				deltaTime,
				momentumService.get()
			);
		}
	}
} 

void runOnParticles(
	Particle* p1, 
	Particle* p2, 
	float G, 
	unsigned int deltaTime,
	MomentumService* momentumService
) {	
	Vector3D<float> radiusComponent = getRadiusComponent(p1, p2, G);
	runOnParticle(
		p1, 
		-getAcceleration(p2->mass, radiusComponent), 
		deltaTime,
		momentumService
	);
	runOnParticle(
		p2, 
		getAcceleration(p1->mass, radiusComponent), 
		deltaTime,
		momentumService
	);
}