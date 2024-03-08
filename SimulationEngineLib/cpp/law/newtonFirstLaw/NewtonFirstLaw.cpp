#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "shared/particle/Particle.cuh"
#include "cpp/law/newtonFirstLaw/CpuNewtonFirstLaw.h"
#include "cpp/law/GpuLaw.h"
#if defined(USE_GPU) 
    #include "cuda/law/newtonFirstLaw/gpuKernel/GpuNewtonFirstLaw.cuh"
#else
    #include "gpuMock/law/newtonFirstLaw/gpuKernel/GpuNewtonFirstLaw.cuh"
#endif

NewtonFirstLaw::NewtonFirstLaw() : 
    Law(
	    "NewtonFirstLaw",
        std::make_shared<CpuNewtonFirstLaw>(),
        std::make_shared<GpuNewtonFirstLaw>()
    ) {}
