#include  <gtest/gtest.h>
#include "NewtonGravity.cuh"
#include "ParticleSimple.h"

#include <vector>

TEST(NewtonGravityTest, ParticlesAccelerateGPU) {
	Law* law = new NewtonGravity(0.05);
	vector<Particle*> particles = { 
		new ParticleSimple(1,1,{0,0.1,0},{0,0,0},{0,0,0}),  
		new ParticleSimple(100,1,{10,0,-0.03},{0,0,0},{0,0,0}),
		new ParticleSimple(1,1,{-10,0,-0.03},{0,0,0},{0,0,0})
	 };
	law->gpuRun(particles);
	Vector3D velocity1 = particles.front()->velocity;
	Vector3D velocity2 = particles[1]->velocity;
	Vector3D velocity3 = particles.back()->velocity;

	EXPECT_DOUBLE_EQ(0.049491907852565097, velocity1.x);
	EXPECT_DOUBLE_EQ(-0.00050491744374839146, velocity1.y);
	EXPECT_DOUBLE_EQ(-0.00015147523312451739, velocity1.z);
	EXPECT_DOUBLE_EQ(-0.00062491826113702121, velocity2.x);
	EXPECT_DOUBLE_EQ(0.0000049991826113702119, velocity2.y);
	EXPECT_DOUBLE_EQ(0.0000014997547834110634, velocity2.z);
	EXPECT_DOUBLE_EQ(0.012999918261137023, velocity3.x);
	EXPECT_DOUBLE_EQ(0.0000049991826113702119, velocity3.y);
	EXPECT_DOUBLE_EQ(0.0000014997547834110634, velocity3.z);
}