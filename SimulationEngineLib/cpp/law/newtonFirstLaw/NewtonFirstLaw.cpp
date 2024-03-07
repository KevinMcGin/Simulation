#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "shared/particle/Particle.cuh"
#include "cpp/law/newtonFirstLaw/CpuNewtonFirstLaw.h"
#include "cuda/law/newtonFirstLaw/gpuKernel/GpuNewtonFirstLaw.cuh"

NewtonFirstLaw::NewtonFirstLaw() : 
    Law(
        std::make_shared<CpuNewtonFirstLaw>(), 
        std::make_shared<GpuNewtonFirstLaw>()
    ) {}
