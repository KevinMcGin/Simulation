#include  <gtest/gtest.h>
#include "law/collision/Collision.h"
#include "law/collision/detector/CollisionDetectorSimple.cuh"
#include "law/collision/resolver/CollisionResolverCoalesce.cuh"
#include "LawHelper.h"
#include "CollisionTestHelper.h"

TEST(CollisionTest, ParticlesCollideGpu) {
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);
	vector<Particle*> particles = CollisionTestHelper::getParticlesCollideParticles();  
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testParticlesCollide(particles);
}

TEST(CollisionTest, MultipleParticlesAllCollideGpu) {
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);
	vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesAllCollide();
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testMultipleParticlesAllCollide(particles);
}

TEST(CollisionTest, MultipleParticlesPartialCollideGpu) {
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);
	vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesPartialCollide();
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testMultipleParticlesPartialCollide(particles);
}

TEST(CollisionTest, MultipleParticlesIndependentlyCollide) {
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);
	vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesIndependentlyCollide();
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testMultipleParticlesIndependentlyCollide(particles);
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpu) {
	//TODO find out why particleCount fails for > 12
	const int particleCount = 50;
	const int stepsCount = 2;
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);

	LawHelper::expectGpuLikeCpuRounded(law, particleCount, stepsCount);
}
