#pragma once

#include <stdexcept>
#include <string>

// The gpuMock classes stand in for the real CUDA ones in a CPU-only build,
// so the code that references them still compiles and links. None of them
// do any work.
//
// Reaching one at runtime therefore means the simulation was asked to use
// the GPU in a build with no GPU support compiled in — a misconfiguration.
// Left silent, every GPU call would be a no-op and the run would finish
// looking like a simulation while having computed nothing, so fail loudly
// instead.
//
// Constructors are the exception: a CPU build still builds its laws, and
// every Law holds a GpuLaw whether or not it will ever be used, so those
// are legitimately reached and stay as no-ops. It's the work methods that
// can only be called by a run that thinks it has a GPU.
[[noreturn]] inline void gpuMockUnreachable(const std::string& method) {
    throw std::runtime_error(
        "GPU code reached in a CPU-only build: " + method + " has no implementation. "
        "Either rebuild with USE_GPU on, or run with SIMULATION_USE_GPU=false."
    );
}
