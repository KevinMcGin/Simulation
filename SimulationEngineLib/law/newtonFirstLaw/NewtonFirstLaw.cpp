#include "law/newtonFirstLaw/NewtonFirstLaw.h"
#include "particle/Particle.cuh"
#include "law/newtonFirstLaw/CpuNewtonFirstLaw.h"
#include "law/newtonFirstLaw/gpuKernel/GpuNewtonFirstLaw.cuh"

NewtonFirstLaw::NewtonFirstLaw() : Law(std::make_shared<CpuNewtonFirstLaw>(), std::make_shared<GpuNewtonFirstLaw>()) { }
