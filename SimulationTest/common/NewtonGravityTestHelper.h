#include  <gtest/gtest.h>
#include "cpp/particle/ParticleSimple.h"

#include <algorithm>

class NewtonGravityTestHelper {
public:
    static std::vector<Particle*> getParticlesAccelerate();
    static void testParticlesAccelerate(std::vector<Particle*> particles);
};