#include  <gtest/gtest.h>
#include "law/collision/detector/CollisionDetectorSimple.cuh"
#include "law/collision/resolver/CollisionResolverCoalesce.cuh"
#include "particle/ParticleSimple.h"

#include <algorithm>

class CollisionTestHelper {
public:
    template <typename T>
    static bool sortVector(T const &lhs, T const &rhs, std::vector<double*> compareLhs, std::vector<double*> compareRhs);
    static bool sortParticles(Particle* const &lhs, Particle* const &rhs);

    static std::vector<Particle*> getParticlesCollideParticles();
    static void testParticlesCollide(std::vector<Particle*> particles);

    static std::vector<Particle*> getMultipleParticlesAllCollide();
    static void testMultipleParticlesAllCollide(std::vector<Particle*> particles);

    static std::vector<Particle*> getMultipleParticlesPartialCollide();
    static void testMultipleParticlesPartialCollide(std::vector<Particle*> particles);

    static std::vector<Particle*> getMultipleParticlesIndependentlyCollide();
    static void testMultipleParticlesIndependentlyCollide(std::vector<Particle*> particles);
};