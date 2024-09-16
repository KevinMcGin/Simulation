#include  <gtest/gtest.h>
#include "cpp/law/collision/Collision.h"
#include "shared/law/collision/detector/CollisionDetectorSimple.cuh"
#include "shared/law/collision/resolver/CollisionResolverCoalesce.cuh"
#include "LawHelper.h"
#include "CollisionTestHelper.h"
#include "shared/service/momentum/newton/NewtonMomentumService.cuh"


TEST(CollisionTest, ParticlesCollideGpu) {
	auto law = std::make_shared<Collision>(
		std::make_shared<CollisionDetectorSimple>(), 
		std::make_shared<CollisionResolverCoalesce>(), 
		std::make_shared<NewtonMomentumService>(), 
		true
	);
	std::vector<Particle*> particles = CollisionTestHelper::getParticlesCollideParticles();  
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testParticlesCollide(particles);
}

TEST(CollisionTest, MultipleParticlesAllCollideGpu) {
	auto law = std::make_shared<Collision>(
		std::make_shared<CollisionDetectorSimple>(), 
		std::make_shared<CollisionResolverCoalesce>(), 
		std::make_shared<NewtonMomentumService>(), 
		true
	);	
	std::vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesAllCollide();
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testMultipleParticlesAllCollide(particles);
}

TEST(CollisionTest, MultipleParticlesPartialCollideGpu) {
	auto law = std::make_shared<Collision>(
		std::make_shared<CollisionDetectorSimple>(), 
		std::make_shared<CollisionResolverCoalesce>(), 
		std::make_shared<NewtonMomentumService>(), 
		true
	);	
	std::vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesPartialCollide();
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testMultipleParticlesPartialCollide(particles);
}

TEST(CollisionTest, MultipleParticlesIndependentlyCollide) {
	auto law = std::make_shared<Collision>(
		std::make_shared<CollisionDetectorSimple>(), 
		std::make_shared<CollisionResolverCoalesce>(), 
		std::make_shared<NewtonMomentumService>(), 
		true
	);	
	std::vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesIndependentlyCollide();
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testMultipleParticlesIndependentlyCollide(particles);
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpuSimple) {
	const int particleCount = 1000;
	const int stepsCount = 1;
	auto law = std::make_unique<Collision>(
		std::make_shared<CollisionDetectorSimple>(), 
		std::make_shared<CollisionResolverCoalesce>(), 
		std::make_shared<NewtonMomentumService>(), 
		true
	);

	LawHelper::expectGpuLikeCpuRounded(
		std::move(law),
		particleCount,
		stepsCount
	);
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpuMemoryLow) {
	CudaWithError::setMaxMemoryPerEvent(1000 * 1000);

	const int particleCount = 1000;
	const int stepsCount = 1;
	auto law = std::make_unique<Collision>(
		std::make_shared<CollisionDetectorSimple>(), 
		std::make_shared<CollisionResolverCoalesce>(), 
		std::make_shared<NewtonMomentumService>(), 
		true
	);	

	LawHelper::expectGpuLikeCpuRounded(
		std::move(law),
		particleCount,
		stepsCount
	);
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpuMemoryVeryLow) {
	CudaWithError::setMaxMemoryPerEvent(1000);

	const int particleCount = 100;
	const int stepsCount = 1;
	auto law = std::make_unique<Collision>(
		std::make_shared<CollisionDetectorSimple>(), 
		std::make_shared<CollisionResolverCoalesce>(), 
		std::make_shared<NewtonMomentumService>(), 
		true
	);	

	LawHelper::expectGpuLikeCpuRounded(
		std::move(law),
		particleCount,
		stepsCount
	);
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpuMemoryLow1) {
	CudaWithError::setMaxMemoryPerEvent(100);

	const int particleCount = 100;
	const int stepsCount = 1;
	auto law = std::make_unique<Collision>(
		std::make_shared<CollisionDetectorSimple>(), 
		std::make_shared<CollisionResolverCoalesce>(), 
		std::make_shared<NewtonMomentumService>(), 
		true
	);	
	
	 try {
		LawHelper::expectGpuLikeCpuRounded(
			std::move(law),
			particleCount,
			stepsCount
		);
    } catch(...) {
        FAIL() << "Wrong error thrown: expected No error";
    }
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpuMemoryLow2) {
	CudaWithError::setMaxMemoryPerEvent(10);

	const int particleCount = 10;
	const int stepsCount = 1;
	auto law = std::make_unique<Collision>(
		std::make_shared<CollisionDetectorSimple>(), 
		std::make_shared<CollisionResolverCoalesce>(), 
		std::make_shared<NewtonMomentumService>(), 
		true
	);	
	
	 try {
		LawHelper::expectGpuLikeCpuRounded(
			std::move(law),
			particleCount,
			stepsCount
		);
	} catch(std::runtime_error const &err) {
        EXPECT_EQ(err.what(), std::string("Max Loops in GpuCollision reached"));
    } catch(...) {
        FAIL() << "Wrong error thrown: expected Max Loops in GpuCollision reached";
    }
}
