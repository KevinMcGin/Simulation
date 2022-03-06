#include  <gtest/gtest.h>
#include "law/collision/Collision.h"
#include "law/collision/detector/CollisionDetectorSimple.cuh"
#include "law/collision/resolver/CollisionResolverCoalesce.cuh"
#include "LawHelper.h"
#include "CollisionTestHelper.h"

TEST(CollisionTest, ParticlesCollideGpu) {
	auto law = std::make_shared<Collision>(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>(), true);
	std::vector<Particle*> particles = CollisionTestHelper::getParticlesCollideParticles();  
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testParticlesCollide(particles);
}

TEST(CollisionTest, MultipleParticlesAllCollideGpu) {
	auto law = std::make_shared<Collision>(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>(), true);
	std::vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesAllCollide();
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testMultipleParticlesAllCollide(particles);
}

TEST(CollisionTest, MultipleParticlesPartialCollideGpu) {
	auto law = std::make_shared<Collision>(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>(), true);
	std::vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesPartialCollide();
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testMultipleParticlesPartialCollide(particles);
}

TEST(CollisionTest, MultipleParticlesIndependentlyCollide) {
	auto law = std::make_shared<Collision>(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>(), true);
	std::vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesIndependentlyCollide();
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testMultipleParticlesIndependentlyCollide(particles);
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpuSimple) {
	const int particleCount = 75;
	const int stepsCount = 1;
	auto law = std::make_shared<Collision>(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>(), true);

	LawHelper::expectGpuLikeCpuRounded(law, particleCount, stepsCount);
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpuMemoryLow) {
	CudaWithError::setMaxMemoryPerEvent(1000 * 1000);

	const int particleCount = 75;
	const int stepsCount = 1;
	auto law = std::make_shared<Collision>(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>(), true);

	LawHelper::expectGpuLikeCpuRounded(law, particleCount, stepsCount);
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpuMemoryVeryLow) {
	CudaWithError::setMaxMemoryPerEvent(1000);

	const int particleCount = 75;
	const int stepsCount = 1;
	auto law = std::make_shared<Collision>(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>(), true);

	LawHelper::expectGpuLikeCpuRounded(law, particleCount, stepsCount);
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpuMemoryTooLow1) {
	CudaWithError::setMaxMemoryPerEvent(100);

	const int particleCount = 75;
	const int stepsCount = 1;
	auto law = std::make_shared<Collision>(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>(), true);

	 try {
        LawHelper::expectGpuLikeCpuRounded(law, particleCount, stepsCount);
        FAIL() << "No error thrown: expected Max Loops in GpuCollision reached";
    } catch(std::runtime_error const &err) {
        EXPECT_EQ(err.what(), std::string("Max Loops in GpuCollision reached"));
    } catch(...) {
        FAIL() << "Wrong error thrown: expected Max Loops in GpuCollision reached";
    }
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpuMemoryTooLow2) {
	CudaWithError::setMaxMemoryPerEvent(10);

	const int particleCount = 75;
	const int stepsCount = 1;
	auto law = std::make_shared<Collision>(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>(), true);

	 try {
        LawHelper::expectGpuLikeCpuRounded(law, particleCount, stepsCount);
        FAIL() << "No error thrown: expected Ran out of GPU memory";
    } catch(std::runtime_error const &err) {
        EXPECT_EQ(err.what(), std::string("Ran out of GPU memory"));
    } catch(...) {
        FAIL() << "Wrong error thrown: expected Ran out of GPU memory";
    }
}
