#include  <gtest/gtest.h>
#include "cpp/particle/ParticleSimple.h"

#include <algorithm>

class NewtonFirstLawTestHelper {
public:
    static std::vector<Particle*> getParticleMove();
    static void testParticleMove(std::vector<Particle*> particles);
};