#include "gpuMock/gpuHelper/CudaWithError.cuh"
#include "gpuMock/gpuHelper/GpuMockUnreachable.cuh"
#include <iostream>
#include <algorithm>


// Constructed by every GpuLaw in a CPU-only build, used or not, so this one
// stays a no-op — see GpuMockUnreachable.cuh.
CudaWithError::CudaWithError(std::string className) { }

void CudaWithError::setDevice(int device) { gpuMockUnreachable("CudaWithError::setDevice"); }

void CudaWithError::resetDevice() { gpuMockUnreachable("CudaWithError::resetDevice"); }

void CudaWithError::malloc(void** devPtr, size_t size) { gpuMockUnreachable("CudaWithError::malloc"); }

void CudaWithError::memcpy(void* dst, const void* src, size_t count, cudaMemcpyKind kind) { gpuMockUnreachable("CudaWithError::memcpy"); }

void CudaWithError::deviceSynchronize(std::string message) { gpuMockUnreachable("CudaWithError::deviceSynchronize"); }

void CudaWithError::free(void* devPtr) { gpuMockUnreachable("CudaWithError::free"); }

void CudaWithError::peekAtLastError(std::string message) { gpuMockUnreachable("CudaWithError::peekAtLastError"); }

unsigned long long CudaWithError::getFreeGpuMemory() { gpuMockUnreachable("CudaWithError::getFreeGpuMemory"); }

unsigned long long CudaWithError::getMaxThreads() { gpuMockUnreachable("CudaWithError::getMaxThreads"); }

void CudaWithError::runKernel(std::string message, std::function<void (unsigned int kernelSize)> kernelMethod) { gpuMockUnreachable("CudaWithError::runKernel"); }

void CudaWithError::setMinMemoryRemaining(unsigned long long minMemoryRemaining) { gpuMockUnreachable("CudaWithError::setMinMemoryRemaining"); }

void CudaWithError::setMaxMemoryPerEvent(unsigned long long maxMemoryPerEvent) { gpuMockUnreachable("CudaWithError::setMaxMemoryPerEvent"); }

void CudaWithError::setKernelSize(unsigned long kernelSize) { gpuMockUnreachable("CudaWithError::setKernelSize"); }
