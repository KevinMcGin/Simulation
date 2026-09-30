#include "ParticleTestHelper.h"

void ParticleTestHelper::deleteParticles(std::vector<Particle*>& particles) {
    for (auto particle : particles) {
        delete particle;
    }
    particles.clear();
}
