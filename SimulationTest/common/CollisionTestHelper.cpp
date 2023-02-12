#include "CollisionTestHelper.h"

template <typename T>
bool CollisionTestHelper::sortVector(T const &lhs, T const &rhs, std::vector<float*> compareLhs, std::vector<float*> compareRhs) {
    if (*(compareLhs.back()) < *(compareRhs.back())) {
        return true; 
    } else if (*(compareRhs.back()) < *(compareLhs.back())) {
        return false;
    } else {
        if (compareLhs.size() == 1) {
            return true;
        }
        compareLhs.pop_back();
        compareRhs.pop_back();
        return CollisionTestHelper::sortVector(lhs, rhs, compareLhs, compareRhs);
    }
}

bool CollisionTestHelper::sortParticles(Particle* const &lhs, Particle* const &rhs) {
    auto compareLhs = std::vector<float*> {
        &(lhs->velocity.z),
        &(lhs->velocity.y),
        &(lhs->velocity.x),
        &(lhs->position.z),
        &(lhs->position.y),
        &(lhs->position.x),
        &(lhs->radius),
        &(lhs->mass)
    };
    auto compareRhs = std::vector<float*> {
        &(rhs->velocity.z),
        &(rhs->velocity.y),
        &(rhs->velocity.x),
        &(rhs->position.z),
        &(rhs->position.y),
        &(rhs->position.x),
        &(rhs->radius),
        &(rhs->mass)
    };
    return CollisionTestHelper::sortVector(*lhs, *rhs, compareLhs, compareRhs);
}

std::vector<Particle*> CollisionTestHelper::getParticlesCollideParticles() {
    Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 });
    Particle* p2 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 });
    Particle* p3 = new ParticleSimple(1, 1, { 20,0,0 }, { 1,1,0 });
    std::vector<Particle*> particles = { p1, p2, p3 };
    return particles;
}

void CollisionTestHelper::testParticlesCollide(std::vector<Particle*> particles) {
    std::sort(particles.begin(), particles.end(), CollisionTestHelper::sortParticles);
    EXPECT_EQ(2, particles.size());
    EXPECT_EQ(2, particles[1]->mass);
    EXPECT_FLOAT_EQ(1.2599210498948732, particles[1]->radius);
    EXPECT_EQ(Vector3D<float>(2,0.5,0), particles[1]->position);
    EXPECT_EQ(Vector3D<float>(1,0,0), particles[1]->velocity);
}

std::vector<Particle*> CollisionTestHelper::getMultipleParticlesAllCollide() {
    Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 });
    Particle* p2 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 });
    Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 });
    Particle* p4 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 });
    std::vector<Particle*> particles = { p1, p2, p3, p4 };
    return particles;
}

void CollisionTestHelper::testMultipleParticlesAllCollide(std::vector<Particle*> particles) {
    std::sort(particles.begin(), particles.end(), CollisionTestHelper::sortParticles);
    EXPECT_EQ(2, particles.size());
    EXPECT_EQ(3, particles[1]->mass);
    EXPECT_FLOAT_EQ(1.4422495703074083, particles[1]->radius);
    EXPECT_EQ(Vector3D<float>(2,1/3.0,0), particles[1]->position);
    EXPECT_EQ(Vector3D<float>(1,1/3.0,0), particles[1]->velocity);
}

std::vector<Particle*> CollisionTestHelper::getMultipleParticlesPartialCollide() {
    Particle* p1 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,-1,0 });
    Particle* p2 = new ParticleSimple(1, 1, { 0.5,0,0 }, { 1,1,0 });
    Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 });
    Particle* p4 = new ParticleSimple(1, 1, { 1,0,0 }, { 1,1,0 });
    Particle* p5 = new ParticleSimple(1, 1, { 400,0,0 }, { 1,1,0 });
    std::vector<Particle*> particles = { p1, p2, p3, p4, p5 };
    return particles;
}

void CollisionTestHelper::testMultipleParticlesPartialCollide(std::vector<Particle*> particles) {
    std::sort(particles.begin(), particles.end(), CollisionTestHelper::sortParticles);
    EXPECT_EQ(3, particles.size());
    EXPECT_EQ(1, particles[0]->mass);
    EXPECT_EQ(1, particles[1]->mass);
    EXPECT_EQ(3, particles[2]->mass);
    EXPECT_FLOAT_EQ(1.4422495703074083, particles[2]->radius);
    EXPECT_EQ(Vector3D<float>(0.5,0.0,0), particles[2]->position);
    EXPECT_EQ(Vector3D<float>(1,1/3.0,0), particles[2]->velocity);
}

std::vector<Particle*> CollisionTestHelper::getMultipleParticlesIndependentlyCollide() {
    Particle* p1 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,-1,0 });
    Particle* p2 = new ParticleSimple(1, 1, { 0.5,0,0 }, { 1,1,0 });
    Particle* p3 = new ParticleSimple(1, 1, { 200,0,0 }, { 1,1,0 });
    Particle* p4 = new ParticleSimple(1.5, 1, { 201,0,0 }, { 1,1,0 });
    Particle* p5 = new ParticleSimple(1, 1, { 400,0,0 }, { 1,1,0 });
    std::vector<Particle*> particles = { p1, p2, p3, p4, p5 };
    return particles;
}

void CollisionTestHelper::testMultipleParticlesIndependentlyCollide(std::vector<Particle*> particles) {
    std::sort(particles.begin(), particles.end(), CollisionTestHelper::sortParticles);
    EXPECT_EQ(3, particles.size());
    EXPECT_EQ(2, particles[1]->mass);
    EXPECT_EQ(2.5, particles[2]->mass);
    EXPECT_EQ(1, particles[0]->mass);
    EXPECT_FLOAT_EQ(1.2599210498948732, particles[1]->radius);
    EXPECT_EQ(Vector3D<float>(0.25,0.0,0), particles[1]->position);
    EXPECT_EQ(Vector3D<float>(1,0,0), particles[1]->velocity);
}