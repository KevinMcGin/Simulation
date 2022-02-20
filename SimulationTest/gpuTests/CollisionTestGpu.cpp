#include  <gtest/gtest.h>
#include "law/collision/Collision.h"
#include "law/collision/detector/CollisionDetectorSimple.cuh"
#include "law/collision/resolver/CollisionResolverCoalesce.cuh"
#include "LawHelper.h"
#include "CollisionTestHelper.h"

TEST(CollisionTest, ParticlesCollideGpu) {
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);
	std::vector<Particle*> particles = CollisionTestHelper::getParticlesCollideParticles();  
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testParticlesCollide(particles);
}

TEST(CollisionTest, MultipleParticlesAllCollideGpu) {
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);
	std::vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesAllCollide();
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testMultipleParticlesAllCollide(particles);
}

TEST(CollisionTest, MultipleParticlesPartialCollideGpu) {
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);
	std::vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesPartialCollide();
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testMultipleParticlesPartialCollide(particles);
}

TEST(CollisionTest, MultipleParticlesIndependentlyCollide) {
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);
	std::vector<Particle*> particles = CollisionTestHelper::getMultipleParticlesIndependentlyCollide();
    LawHelper::runGpuLaw(law, particles);
	CollisionTestHelper::testMultipleParticlesIndependentlyCollide(particles);
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpuSimple) {
	const int particleCount = 100;
	const int stepsCount = 1;
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);

	LawHelper::expectGpuLikeCpuRounded(law, particleCount, stepsCount);
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpuMemoryLow) {
	CudaWithError::setMaxMemoryPerEvent(1000 * 1000);

	const int particleCount = 75;
	const int stepsCount = 1;
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);

	LawHelper::expectGpuLikeCpuRounded(law, particleCount, stepsCount);
}

//TODO get passing
// TEST(CollisionTest, ParticlesCollideGpuLikeCpuMemoryVeryLow) {
// 	CudaWithError::setMaxMemoryPerEvent(1000);

// 	const int particleCount = 75;
// 	const int stepsCount = 1;
// 	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);

// 	LawHelper::expectGpuLikeCpuRounded(law, particleCount, stepsCount);
// }

TEST(CollisionTest, ParticlesCollideGpuLikeCpuMemoryTooLow) {
	CudaWithError::setMaxMemoryPerEvent(10);

	const int particleCount = 75;
	const int stepsCount = 1;
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), true);

	 try {
        LawHelper::expectGpuLikeCpuRounded(law, particleCount, stepsCount);
        FAIL() << "No error thrown: expected Ran out of GPU memory";
    } catch(std::runtime_error const &err) {
        EXPECT_EQ(err.what(), std::string("Ran out of GPU memory"));
    } catch(...) {
        FAIL() << "Wrong error thrown: expected Ran out of GPU memory";
    }
}
