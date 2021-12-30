#include  <gtest/gtest.h>
#include "Collision.cuh"
#include "CollisionDetectorSimple.cuh"
#include "CollisionResolverCoalesce.cuh"
#include "ParticleSimple.h"

#include <algorithm>

template <typename T>
bool sortVector(T const &lhs, T const &rhs, vector<double*> compareLhs, vector<double*> compareRhs) {
	if (*(compareLhs.back()) < *(compareRhs.back())) {
      	return true; 
	} else if (*(compareRhs.back()) < *(compareLhs.back())) {
      	return false;
	} else {
		if(compareLhs.size() == 1) {
			return true;
		}
		compareLhs.pop_back();
		compareRhs.pop_back();
		return sortVector(lhs, rhs, compareLhs, compareRhs);
	}
}

bool sortParticles(Particle* const &lhs, Particle* const &rhs) {
	auto compareLhs = vector<double*> {
		&(lhs->velocity.z),
		&(lhs->velocity.y),
		&(lhs->velocity.x),
		&(lhs->position.z),
		&(lhs->position.y),
		&(lhs->position.x),
		&(lhs->radius),
		&(lhs->mass)
	};
	auto compareRhs = vector<double*> {
		&(rhs->velocity.z),
		&(rhs->velocity.y),
		&(rhs->velocity.x),
		&(rhs->position.z),
		&(rhs->position.y),
		&(rhs->position.x),
		&(rhs->radius),
		&(rhs->mass)
	};
	return sortVector(*lhs, *rhs, compareLhs, compareRhs);
}

TEST(CollisionTest, ParticlesCollide) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 20,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3 };
	law.cpuRun(particles);
	std::sort(particles.begin(), particles.end(), sortParticles);
	EXPECT_EQ(2, particles.size());
	EXPECT_EQ(2, particles[1]->mass);
	EXPECT_DOUBLE_EQ(1.2599210498948732, particles[1]->radius);
	EXPECT_EQ(Vector3D(2,0.5,0), particles[1]->position);
	EXPECT_EQ(Vector3D(1,0,0), particles[1]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[1]->angularVelocity);
}

TEST(CollisionTest, MultipleParticlesAllCollide) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p4 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3, p4 };
	law.cpuRun(particles);
	std::sort(particles.begin(), particles.end(), sortParticles);
	EXPECT_EQ(2, particles.size());
	EXPECT_EQ(3, particles[1]->mass);
	EXPECT_DOUBLE_EQ(1.4422495703074083, particles[1]->radius);
	EXPECT_EQ(Vector3D(2,1/3.0,0), particles[1]->position);
	EXPECT_EQ(Vector3D(1,1/3.0,0), particles[1]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[1]->angularVelocity);
}

TEST(CollisionTest, MultipleParticlesPartialCollide) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 0.5,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p4 = new ParticleSimple(1, 1, { 1,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p5 = new ParticleSimple(1, 1, { 400,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3, p4, p5 };
	law.cpuRun(particles);
	std::sort(particles.begin(), particles.end(), sortParticles);
	EXPECT_EQ(3, particles.size());
	EXPECT_EQ(1, particles[0]->mass);
	EXPECT_EQ(1, particles[1]->mass);
	EXPECT_EQ(3, particles[2]->mass);
	EXPECT_DOUBLE_EQ(1.4422495703074083, particles[2]->radius);
	EXPECT_EQ(Vector3D(0.5,0.0,0), particles[2]->position);
	EXPECT_EQ(Vector3D(1,1/3.0,0), particles[2]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[2]->angularVelocity);
}

TEST(CollisionTest, MultipleParticlesIndependentlyCollide) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 0.5,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p4 = new ParticleSimple(1.5, 1, { 201,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p5 = new ParticleSimple(1, 1, { 400,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3, p4, p5 };
	law.cpuRun(particles);
	std::sort(particles.begin(), particles.end(), sortParticles);
	EXPECT_EQ(3, particles.size());
	EXPECT_EQ(2, particles[1]->mass);
	EXPECT_EQ(2.5, particles[2]->mass);
	EXPECT_EQ(1, particles[0]->mass);
	EXPECT_DOUBLE_EQ(1.2599210498948732, particles[1]->radius);
	EXPECT_EQ(Vector3D(0.25,0.0,0), particles[1]->position);
	EXPECT_EQ(Vector3D(1,0,0), particles[1]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[1]->angularVelocity);
}