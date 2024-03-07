#include  <gtest/gtest.h>
#include "cpp/law/collision/Collision.h"
#include "shared/law/collision/detector/CollisionDetectorSimple.cuh"
#include "shared/law/collision/resolver/CollisionResolverCoalesce.cuh"
#include "cpp/particle/ParticleSimple.h"
#include "CollisionTestHelper.h"

#include <algorithm>

template <typename T>
bool sortVector(T const &lhs, T const &rhs, std::vector<float*> compareLhs, std::vector<float*> compareRhs) {
	if (*(compareLhs.back()) < *(compareRhs.back())) {
      	return true; 
	} else if (*(compareRhs.back()) < *(compareLhs.back())) {
      	return false;
	} else {
		if (compareLhs.size() == 1) {
			return true;
		}
		compareLhs.pop_back();
		compareRhs.pop_back();
		return sortVector(lhs, rhs, compareLhs, compareRhs);
	}
}

bool sortParticles(Particle* const &lhs, Particle* const &rhs) {
	auto compareLhs = std::vector<float*> {
		&(lhs->velocity.z),
		&(lhs->velocity.y),
		&(lhs->velocity.x),
		&(lhs->position.z),
		&(lhs->position.y),
		&(lhs->position.x),
		&(lhs->radius),
		&(lhs->mass)
	};
	auto compareRhs = std::vector<float*> {
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
	Collision law(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>());
	std::vector<Particle*> particles = CollisionTestHelper::getParticlesCollideParticles();
	law.cpuLaw->run(particles);
	CollisionTestHelper::testParticlesCollide(particles);
}

TEST(CollisionTest, MultipleParticlesAllCollide) {
	Collision law(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>());
	std::vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesAllCollide();
	law.cpuLaw->run(particles);
	std::sort(particles.begin(), particles.end(), sortParticles);
	CollisionTestHelper::testMultipleParticlesAllCollide(particles);
}

TEST(CollisionTest, MultipleParticlesPartialCollide) {
	Collision law(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>());
	std::vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesPartialCollide();
	law.cpuLaw->run(particles);
	std::sort(particles.begin(), particles.end(), sortParticles);
	CollisionTestHelper::testMultipleParticlesPartialCollide(particles);
}

TEST(CollisionTest, MultipleParticlesIndependentlyCollide) {
	Collision law(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>());
	std::vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesIndependentlyCollide();
	law.cpuLaw->run(particles);
	CollisionTestHelper::testMultipleParticlesIndependentlyCollide(particles);
}