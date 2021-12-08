#include  <gtest/gtest.h>
#include "Collision.h"
#include "CollisionDetectorSimple.h"
#include "CollisionResolverCoalesce.h"
#include "ParticleSimple.h"

TEST(CollisionTest, ParticlesCollide) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 20,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3 };
	law.run(particles);
	EXPECT_EQ(2, particles.size());
	EXPECT_EQ(2, particles[0]->mass);
	EXPECT_DOUBLE_EQ(1.2599210498948732, particles[0]->radius);
	EXPECT_EQ(Vector3D(2,0.5,0), particles[0]->position);
	EXPECT_EQ(Vector3D(1,0,0), particles[0]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[0]->angularVelocity);
}

TEST(CollisionTest, MultipleParticlesAllCollide) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p4 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3, p4 };
	law.run(particles);
	EXPECT_EQ(2, particles.size());
	EXPECT_EQ(3, particles[0]->mass);
	EXPECT_DOUBLE_EQ(1.4422495703074083, particles[0]->radius);
	EXPECT_EQ(Vector3D(2,1/3.0,0), particles[0]->position);
	EXPECT_EQ(Vector3D(1,1/3.0,0), particles[0]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[0]->angularVelocity);
}

TEST(CollisionTest, MultipleParticlesPartialCollide) {
	Collision law(new CollisionDetectorSimple(), new CollisionResolverCoalesce());
	Particle* p1 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 0.5,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 }, { 0,0,0 });
	Particle* p4 = new ParticleSimple(1, 1, { 1,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2, p3, p4 };
	law.run(particles);
	EXPECT_EQ(2, particles.size());
	EXPECT_EQ(3, particles[0]->mass);
	EXPECT_DOUBLE_EQ(1.4422495703074083, particles[0]->radius);
	EXPECT_EQ(Vector3D(0.5,0.0,0), particles[0]->position);
	EXPECT_EQ(Vector3D(1,1/3.0,0), particles[0]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[0]->angularVelocity);
}