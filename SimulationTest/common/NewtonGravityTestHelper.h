#include  <gtest/gtest.h>
#include "particle/ParticleSimple.h"

#include <algorithm>

class NewtonGravityTestHelper {
public:
    static vector<Particle*> getParticlesAccelerate();
    static void testParticlesAccelerate(vector<Particle*> particles);
};