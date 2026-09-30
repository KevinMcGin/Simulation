#pragma once
#include "shared/particle/Particle.cuh"

#include <vector>

class ParticleTestHelper {
public:
    // Particles are handed around as raw pointers, and in a real run the
    // universe is what frees them at the end. A test that builds its own
    // particles without a universe has to do that itself, or every one of
    // them leaks.
    //
    // Only the particles still in the vector are freed: a law that merges
    // particles deletes the losers and erases them as it goes, so anything
    // left is exactly what is still owned.
    static void deleteParticles(std::vector<Particle*>& particles);
};
