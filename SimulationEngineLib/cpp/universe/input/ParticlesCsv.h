#pragma once
#include "shared/particle/Particle.cuh"

#include <istream>
#include <vector>

// Reads particles from the engine's CSV particle format: a header naming
// the columns, then one row per particle.
//
// A stream rather than a file name, because the same format arrives two
// ways — a file on disk, and the body of a request — and the parsing has no
// business knowing which.
//
// The caller owns the particles that come back.
namespace ParticlesCsv {
    std::vector<Particle*> parse(std::istream& csv);
}
