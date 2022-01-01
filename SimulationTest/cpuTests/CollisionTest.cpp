#include  <gtest/gtest.h>
#include "Collision.cuh"
#include "CollisionDetectorSimple.cuh"
#include "CollisionResolverCoalesce.cuh"
#include "ParticleSimple.h"
#include "CollisionTestHelper.h"

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
	vector<Particle*> particles = CollisionTestHelper::getParticlesCollideParticles();
	law.cpuRun(particles);
	CollisionTestHelper::testParticlesCollide(particles);
}

TEST(CollisionTest, MultipleParticlesAllCollide) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesAllCollide();
	law.cpuRun(particles);
	std::sort(particles.begin(), particles.end(), sortParticles);
	CollisionTestHelper::testMultipleParticlesAllCollide(particles);
}

TEST(CollisionTest, MultipleParticlesPartialCollide) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesPartialCollide();
	law.cpuRun(particles);
	std::sort(particles.begin(), particles.end(), sortParticles);
	CollisionTestHelper::testMultipleParticlesPartialCollide(particles);
}

TEST(CollisionTest, MultipleParticlesIndependentlyCollide) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesIndependentlyCollide();
	law.cpuRun(particles);
	CollisionTestHelper::testMultipleParticlesIndependentlyCollide(particles);
}