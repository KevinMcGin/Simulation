#include "pch.h"
#include "../src/CollisionDetectorSimple.h"
#include "../src/ParticleSimple.h"

#include <vector>

TEST(CollisionDetectorSimpleTest, particlesNotIntersect) {
	CollisionDetectorSimple detector;
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,-1,0 }, { 0,0,0 });
	bool didCollide = detector.isCollision(p1, p2);
	EXPECT_TRUE(!didCollide);
}

TEST(CollisionDetectorSimpleTest, particlesIntersectByZero) {
	CollisionDetectorSimple detector;
	Particle* p1 = new ParticleSimple(1, 1, { 1,2,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 1,0,0 }, { 1,-1,0 }, { 0,0,0 });
	bool didCollide = detector.isCollision(p1, p2);
	EXPECT_TRUE(!didCollide);
}

TEST(CollisionDetectorSimpleTest, particlesIntersect) {
	CollisionDetectorSimple detector;
	Particle* p1 = new ParticleSimple(1, 1, { 1,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,-1,0 }, { 0,0,0 });
	bool didCollide = detector.isCollision(p1, p2);
	EXPECT_TRUE(didCollide);
}