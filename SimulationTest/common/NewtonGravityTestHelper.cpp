#include "NewtonGravityTestHelper.h"

std::vector<Particle*> NewtonGravityTestHelper::getParticlesAccelerate() {
    std::vector<Particle*> particles = { 
		new ParticleSimple(1,1,{0,0.1,0},{0,0,0}),  
		new ParticleSimple(100,1,{10,0,-0.03},{0,0,0}),
		new ParticleSimple(1,1,{-10,0,-0.03},{0,0,0}),
		new ParticleSimple(1.2,1,{10,40,-1.03},{0,0,0}),
		new ParticleSimple(1.5,1,{-10,-1,0.03},{0,0,0})
	 };
    return particles;
}

void NewtonGravityTestHelper::testParticlesAccelerate(std::vector<Particle*> particles) {
	Vector3D<float> velocity1 = particles.front()->velocity;
	Vector3D<float> velocity2 = particles[1]->velocity;
	Vector3D<float> velocity3 = particles[2]->velocity;
	Vector3D<float> velocity4 = particles[3]->velocity;
	Vector3D<float> velocity5 = particles.back()->velocity;

	EXPECT_FLOAT_EQ(0.048763939840287221, velocity1.x);
	EXPECT_FLOAT_EQ(-0.00055157670969448191, velocity1.y);
	EXPECT_FLOAT_EQ(-0.00015015259752594346, velocity1.z);
	EXPECT_FLOAT_EQ(-0.00081171481154151568, velocity2.x);
	EXPECT_FLOAT_EQ(3.3124226286952707e-05, velocity2.y);
	EXPECT_FLOAT_EQ(1.123522654729366e-06, velocity2.z);
	EXPECT_FLOAT_EQ(0.013013324612981398, velocity3.x);
	EXPECT_FLOAT_EQ(3.181188630011959e-05, velocity3.y);
	EXPECT_FLOAT_EQ(8.2943719119232886e-07, velocity3.z);
	EXPECT_FLOAT_EQ(-3.4137356128502802e-05, velocity4.x);
	EXPECT_FLOAT_EQ(-0.0032054194214723819, velocity4.y);
	EXPECT_FLOAT_EQ(8.0186440835739638e-05, velocity4.z);
	EXPECT_FLOAT_EQ(0.012956787685491428, velocity5.x);
	EXPECT_FLOAT_EQ(0.00070256366697729947, velocity5.y);
	EXPECT_FLOAT_EQ(-3.9501889427382019e-05, velocity5.z);
}