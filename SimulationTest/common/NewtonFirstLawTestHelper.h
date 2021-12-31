#include  <gtest/gtest.h>
#include "ParticleSimple.h"

#include <algorithm>

class NewtonFirstLawTestHelper {
public:
    static vector<Particle*> getParticleMove();
    static void testParticleMove(vector<Particle*> particles);
};