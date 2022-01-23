#include "particle/helper/ParticlesHelper.h"

bool ParticlesHelper::removeDeletedParticles(vector<Particle*>& particles) {
    bool particleDeleted = false;
    for (auto it = particles.begin(); it != particles.end();) {
        if((*it)->deleted) {
            delete *it;
            it = particles.erase(it);
            particleDeleted = true;
        }
        else
            ++it;
    }
    return particleDeleted;
}
