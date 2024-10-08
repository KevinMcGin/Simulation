#include "cuda/gpuHelper/CudaWithError.cuh"
#include <iostream>
#include <algorithm>


unsigned long long CudaWithError::minMemoryRemaining = 0;
unsigned long long CudaWithError::maxMemoryPerEvent = ULLONG_MAX;
unsigned long CudaWithError::kernelSize = 256;

CudaWithError::CudaWithError(std::string className): className(className) { }

void CudaWithError::throwErrorMaybe(cudaError_t cudaStatus, std::string error) {
    if (cudaStatus != cudaSuccess) {
        std::string totalError = className + ": " + error + "\n" + cudaGetErrorString(cudaStatus);
        std::cerr << '\n' << totalError << '\n';
        throw std::runtime_error(totalError);
    }
}

void CudaWithError::setDevice(int device) {
    cudaError_t cudaStatus = cudaSetDevice(device);
    throwErrorMaybe(cudaStatus, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
}

void CudaWithError::resetDevice() {
    cudaError_t cudaStatus = cudaDeviceReset();
    throwErrorMaybe(cudaStatus, "cudaDeviceReset failed!  Do you have a CUDA-capable GPU installed?");
}

void CudaWithError::malloc(void** devPtr, size_t size) {
    cudaError_t cudaStatus = cudaMalloc(devPtr, size);
    throwErrorMaybe(cudaStatus, "cudaMalloc failed!");
}

void CudaWithError::memcpy(void* dst, const void* src, size_t count, cudaMemcpyKind kind) {
    cudaError_t cudaStatus = cudaMemcpy(dst, src, count, kind);
    throwErrorMaybe(cudaStatus, "cudaMemcpy failed!");
}

void CudaWithError::deviceSynchronize(std::string message) {
    cudaError_t cudaStatus = cudaDeviceSynchronize();
    throwErrorMaybe(cudaStatus, message + ": cudaDeviceSynchronize failed!");
}

void CudaWithError::free(void* devPtr) {
    cudaError_t cudaStatus = cudaFree(devPtr);
    throwErrorMaybe(cudaStatus, "cudaFree failed!");
}

void CudaWithError::peekAtLastError(std::string message) {
    cudaError_t cudaStatus = cudaPeekAtLastError();
    throwErrorMaybe(cudaStatus, message + ": cudaPeekAtLastError failed!");
}

unsigned long long CudaWithError::getFreeGpuMemory() {
    size_t free_t, total_t;
    cudaMemGetInfo(&free_t, &total_t);
    float factor = 1.0485760;
    auto freeMemory = (unsigned long long)(free_t / factor) - CudaWithError::minMemoryRemaining;
    return std::min(freeMemory, maxMemoryPerEvent); 
}

unsigned long long CudaWithError::getMaxThreads() {
    struct cudaDeviceProp properties;
    cudaGetDeviceProperties(&properties, 0);
    return ((unsigned long long)properties.multiProcessorCount) * ((unsigned long long)properties.maxThreadsPerMultiProcessor);
}

void CudaWithError::runKernel(std::string message, std::function<void (unsigned int kernelSize)> kernelMethod) {
    kernelMethod(CudaWithError::kernelSize);
    peekAtLastError(message);
}

void CudaWithError::setMinMemoryRemaining(unsigned long long minMemoryRemaining) {
    CudaWithError::minMemoryRemaining = minMemoryRemaining;
}

void CudaWithError::setMaxMemoryPerEvent(unsigned long long maxMemoryPerEvent) {
    CudaWithError::maxMemoryPerEvent = maxMemoryPerEvent;
}

void CudaWithError::setKernelSize(unsigned long kernelSize) {
    CudaWithError::kernelSize = kernelSize;
}