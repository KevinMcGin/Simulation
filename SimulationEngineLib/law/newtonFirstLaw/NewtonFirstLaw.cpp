#include "law/newtonFirstLaw/NewtonFirstLaw.h"
#include "particle/Particle.cuh"
#include "law/newtonFirstLaw/CpuNewtonFirstLaw.h"
#include "law/newtonFirstLaw/gpuKernel/GpuNewtonFirstLaw.cuh"

NewtonFirstLaw::NewtonFirstLaw() : Law(new CpuNewtonFirstLaw(), new GpuNewtonFirstLaw()) { }
