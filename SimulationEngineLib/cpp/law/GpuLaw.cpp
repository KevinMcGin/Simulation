#include "cpp/law/GpuLaw.h"

GpuLaw::GpuLaw(std::string className)
		: cudaWithError(std::make_shared<CudaWithError>(className))
	{ }

	
GpuLaw::~GpuLaw() = default;