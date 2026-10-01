#pragma once
#include "shared/particle/Particle.cuh"

#include <string>
#include <vector>

// The whole state of a set of particles, in the engine's own particle input
// format — mass and velocity included, which the animation output leaves
// out.
//
// This is what makes a run continuable. The animation output carries only
// what is needed to draw a frame, and position alone cannot be fed back in:
// velocity would have to be guessed from two frames, and mass cannot be
// recovered at all once a collision has merged two particles into one.
namespace ParticleStateCsv {
    // The header, which is exactly the one SimulationInputCsv parses.
    extern const char* header;

    std::string render(const std::vector<Particle*>& particles);
}
