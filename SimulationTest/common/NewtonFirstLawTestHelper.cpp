#include "NewtonFirstLawTestHelper.h"

vector<Particle*> NewtonFirstLawTestHelper::getParticleMove() {
    vector<Particle*> particles = { new ParticleSimple(1,1,{0,0,0},{1,-1,0}) };
    return particles;
}

void NewtonFirstLawTestHelper::testParticleMove(vector<Particle*> particles) {
	Vector3D positions = particles.front()->position;
	EXPECT_EQ(1, positions.x);
	EXPECT_EQ(-1, positions.y);
	EXPECT_EQ(0, positions.z);
}