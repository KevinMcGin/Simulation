#include  <gtest/gtest.h>
#include "Collision.cuh"
#include "CollisionDetectorSimple.cuh"
#include "CollisionResolverCoalesce.cuh"
#include "GpuDataController.cuh"
#include "ParticleSimple.h"

TEST(CollisionTest, ParticlesCollideGpu) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 20,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3 };    
    GpuDataController gpuDataController = GpuDataController();
    gpuDataController.putParticlesOnDevice(particles, true);
	law.gpuRun(gpuDataController.get_td_par(), gpuDataController.getParticleCount());
    gpuDataController.getParticlesFromDevice(particles);
	EXPECT_TRUE(particles[0]->deleted);
	EXPECT_FALSE(particles[1]->deleted);
	EXPECT_FALSE(particles[2]->deleted);
	EXPECT_EQ(2, particles[1]->mass);
	EXPECT_DOUBLE_EQ(1.2599210498948732, particles[1]->radius);
	EXPECT_EQ(Vector3D(2,0.5,0), particles[1]->position);
	EXPECT_EQ(Vector3D(1,0,0), particles[1]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[1]->angularVelocity);
}

TEST(CollisionTest, MultipleParticlesAllCollideGpu) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p4 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3, p4 };
    GpuDataController gpuDataController = GpuDataController();
    gpuDataController.putParticlesOnDevice(particles, true);
	law.gpuRun(gpuDataController.get_td_par(), gpuDataController.getParticleCount());
    gpuDataController.getParticlesFromDevice(particles);
	EXPECT_TRUE(particles[0]->deleted);
	EXPECT_TRUE(particles[1]->deleted);
	EXPECT_FALSE(particles[2]->deleted);
	EXPECT_FALSE(particles[3]->deleted);
	EXPECT_EQ(3, particles[3]->mass);
	EXPECT_DOUBLE_EQ(1.4422495703074083, particles[3]->radius);
	EXPECT_EQ(Vector3D(2,1/3.0,0), particles[3]->position);
	EXPECT_EQ(Vector3D(1,1/3.0,0), particles[3]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[3]->angularVelocity);
}

TEST(CollisionTest, MultipleParticlesPartialCollideGpu) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 0.5,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p4 = new ParticleSimple(1, 1, { 1,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p5 = new ParticleSimple(1, 1, { 400,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3, p4, p5 };
    GpuDataController gpuDataController = GpuDataController();
    gpuDataController.putParticlesOnDevice(particles, true);
	law.gpuRun(gpuDataController.get_td_par(), gpuDataController.getParticleCount());
    gpuDataController.getParticlesFromDevice(particles);
	EXPECT_TRUE(particles[0]->deleted);
	EXPECT_TRUE(particles[1]->deleted);
	EXPECT_FALSE(particles[2]->deleted);
	EXPECT_FALSE(particles[3]->deleted);
	EXPECT_FALSE(particles[4]->deleted);
	EXPECT_EQ(1, particles[2]->mass);
	EXPECT_EQ(3, particles[3]->mass);
	EXPECT_EQ(1, particles[4]->mass);
	EXPECT_DOUBLE_EQ(1.4422495703074083, particles[3]->radius);
	EXPECT_EQ(Vector3D(0.5,0.0,0), particles[3]->position);
	EXPECT_EQ(Vector3D(1,1/3.0,0), particles[3]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[3]->angularVelocity);
}

TEST(CollisionTest, MultipleParticlesIndependentlyCollide) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 0.5,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p4 = new ParticleSimple(1.5, 1, { 201,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p5 = new ParticleSimple(1, 1, { 400,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3, p4, p5 };
    GpuDataController gpuDataController = GpuDataController();
    gpuDataController.putParticlesOnDevice(particles, true);
	law.gpuRun(gpuDataController.get_td_par(), gpuDataController.getParticleCount());
    gpuDataController.getParticlesFromDevice(particles);
	EXPECT_TRUE(particles[0]->deleted);
	EXPECT_FALSE(particles[1]->deleted);
	EXPECT_TRUE(particles[2]->deleted);
	EXPECT_FALSE(particles[3]->deleted);
	EXPECT_FALSE(particles[4]->deleted);
	EXPECT_EQ(2, particles[1]->mass);
	EXPECT_EQ(2.5, particles[3]->mass);
	EXPECT_EQ(1, particles[4]->mass);
	EXPECT_DOUBLE_EQ(1.2599210498948732, particles[1]->radius);
	EXPECT_EQ(Vector3D(0.25,0.0,0), particles[1]->position);
	EXPECT_EQ(Vector3D(1,0,0), particles[1]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[1]->angularVelocity);
}