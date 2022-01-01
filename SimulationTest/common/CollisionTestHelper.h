#include  <gtest/gtest.h>
#include "CollisionDetectorSimple.cuh"
#include "CollisionResolverCoalesce.cuh"
#include "ParticleSimple.h"

#include <algorithm>

class CollisionTestHelper {
public:
    template <typename T>
    static bool sortVector(T const &lhs, T const &rhs, vector<double*> compareLhs, vector<double*> compareRhs);
    static bool sortParticles(Particle* const &lhs, Particle* const &rhs);

    static vector<Particle*> getParticlesCollideParticles();
    static void testParticlesCollide(vector<Particle*> particles);

    static vector<Particle*> getMultipleParticlesAllCollide();
    static void testMultipleParticlesAllCollide(vector<Particle*> particles);

    static vector<Particle*> getMultipleParticlesPartialCollide();
    static void testMultipleParticlesPartialCollide(vector<Particle*> particles);

    static vector<Particle*> getMultipleParticlesIndependentlyCollide();
    static void testMultipleParticlesIndependentlyCollide(vector<Particle*> particles);
};