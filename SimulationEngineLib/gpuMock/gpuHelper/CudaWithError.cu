#include "gpuMock/gpuHelper/CudaWithError.cuh"
#include <iostream>
#include <algorithm>


CudaWithError::CudaWithError(std::string className) { }

void CudaWithError::setDevice(int device) {}

void CudaWithError::resetDevice() {}

void CudaWithError::malloc(void** devPtr, size_t size) {}

void CudaWithError::memcpy(void* dst, const void* src, size_t count, cudaMemcpyKind kind) {}

void CudaWithError::deviceSynchronize(std::string message) {}

void CudaWithError::free(void* devPtr) {}

void CudaWithError::peekAtLastError(std::string message) {}

unsigned long long CudaWithError::getFreeGpuMemory() { return 0; }

unsigned long long CudaWithError::getMaxThreads() { return 0; }

void CudaWithError::runKernel(std::string message, std::function<void (unsigned int kernelSize)> kernelMethod) {}

void CudaWithError::setMinMemoryRemaining(unsigned long long minMemoryRemaining) {}

void CudaWithError::setMaxMemoryPerEvent(unsigned long long maxMemoryPerEvent) {}

void CudaWithError::setKernelSize(unsigned long kernelSize) {}