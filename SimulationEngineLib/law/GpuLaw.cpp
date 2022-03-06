#include "law/GpuLaw.h"

GpuLaw::GpuLaw(std::string className) : 
	className(className), 
	cudaWithError(std::make_shared<CudaWithError>(className)) { }