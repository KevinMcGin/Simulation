#include "law/GpuLaw.h"

GpuLaw::GpuLaw(string className) : className(className) {
	cudaWithError = new CudaWithError(className);
}