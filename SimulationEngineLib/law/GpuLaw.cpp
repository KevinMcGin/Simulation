#include "law/GpuLaw.h"

GpuLaw::GpuLaw(std::string className) : className(className) {
	cudaWithError = new CudaWithError(className);
}