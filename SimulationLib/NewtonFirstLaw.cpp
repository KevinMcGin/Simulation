#include "NewtonFirstLaw.h"
#include "Particle.cuh"
#include "CpuNewtonFirstLaw.h"
#include "GpuNewtonFirstLaw.cuh"

NewtonFirstLaw::NewtonFirstLaw() : Law(new CpuNewtonFirstLaw(), new GpuNewtonFirstLaw()) { }
