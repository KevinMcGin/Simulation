#include  <gtest/gtest.h>
#include "Collision.cuh"
#include "CollisionDetectorSimple.cuh"
#include "CollisionResolverCoalesce.cuh"
#include "LawHelper.h"

TEST(CollisionTest, ParticlesCollideGpu) {
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 20,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3 };    
    LawHelper::runGpuLaw(law, particles);
	EXPECT_EQ(2, particles.size());
	EXPECT_EQ(2, particles[0]->mass);
	EXPECT_DOUBLE_EQ(1.2599210498948732, particles[0]->radius);
	EXPECT_EQ(Vector3D(2,0.5,0), particles[0]->position);
	EXPECT_EQ(Vector3D(1,0,0), particles[0]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[0]->angularVelocity);
}

TEST(CollisionTest, MultipleParticlesAllCollideGpu) {
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p4 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3, p4 }; 
    LawHelper::runGpuLaw(law, particles);
	EXPECT_EQ(2, particles.size());
	EXPECT_EQ(3, particles.back()->mass);
	EXPECT_DOUBLE_EQ(1.4422495703074083, particles.back()->radius);
	EXPECT_EQ(Vector3D(2,1/3.0,0), particles.back()->position);
	EXPECT_EQ(Vector3D(1,1/3.0,0), particles.back()->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles.back()->angularVelocity);
}

TEST(CollisionTest, MultipleParticlesPartialCollideGpu) {
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 0.5,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p4 = new ParticleSimple(1, 1, { 1,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p5 = new ParticleSimple(1, 1, { 400,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3, p4, p5 }; 
    LawHelper::runGpuLaw(law, particles);
	EXPECT_EQ(3, particles.size());
	EXPECT_EQ(1, particles[0]->mass);
	EXPECT_EQ(3, particles[1]->mass);
	EXPECT_EQ(1, particles[2]->mass);
	EXPECT_DOUBLE_EQ(1.4422495703074083, particles[1]->radius);
	EXPECT_EQ(Vector3D(0.5,0.0,0), particles[1]->position);
	EXPECT_EQ(Vector3D(1,1/3.0,0), particles[1]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[1]->angularVelocity);
}

TEST(CollisionTest, MultipleParticlesIndependentlyCollide) {
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 0.5,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p4 = new ParticleSimple(1.5, 1, { 201,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p5 = new ParticleSimple(1, 1, { 400,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3, p4, p5 }; 
    LawHelper::runGpuLaw(law, particles);
	EXPECT_EQ(3, particles.size());
	EXPECT_EQ(2, particles[0]->mass);
	EXPECT_EQ(2.5, particles[1]->mass);
	EXPECT_EQ(1, particles[2]->mass);
	EXPECT_DOUBLE_EQ(1.2599210498948732, particles[0]->radius);
	EXPECT_EQ(Vector3D(0.25,0.0,0), particles[0]->position);
	EXPECT_EQ(Vector3D(1,0,0), particles[0]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[0]->angularVelocity);
}

TEST(CollisionTest, ParticlesCollideGpuLikeCpu) {
	const int particleCount = 10;
	const int stepsCount = 2;
	Law* law = new Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	LawHelper::expectGpuLikeCpu(law, particleCount, stepsCount);
}
