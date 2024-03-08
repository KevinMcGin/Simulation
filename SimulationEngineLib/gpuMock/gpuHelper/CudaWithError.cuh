#pragma once

#include <functional>

struct cudaError_t {};
struct cudaMemcpyKind {};

#include <string>

class CudaWithError {
public:
    CudaWithError(std::string className);
    void setDevice(int device);
    void resetDevice();
    void malloc(void** devPtr, size_t size);
    void memcpy(void* dst, const void* src, size_t count, cudaMemcpyKind kind);
    void deviceSynchronize(std::string message = "");
    void peekAtLastError(std::string message);
    void free(void* devPtr);
    unsigned long long getFreeGpuMemory();
    unsigned long long getMaxThreads();
    void runKernel(std::string message, std::function<void (unsigned int kernelSize)> kernelMethod);
    
    static void setMinMemoryRemaining(unsigned long long minMemoryRemaining);
    static void setMaxMemoryPerEvent(unsigned long long maxMemoryPerEvent);
    static void setKernelSize(unsigned long kernelSize);
};