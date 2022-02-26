#pragma once
#include "cuda_runtime.h"

#include <string>



class CudaWithError {
public:
    CudaWithError(std::string className);
    void setDevice(int device);
    void malloc(void** devPtr, size_t size);
    void memcpy(void* dst, const void* src, size_t count, cudaMemcpyKind kind);
    void deviceSynchronize(std::string message = "");
    void peekAtLastError(std::string message);
    void free(void* devPtr);
    unsigned long long getFreeGpuMemory();
    unsigned long long getMaxThreads();
    
    static void setMinMemoryRemaining(unsigned long long minMemoryRemaining);
    static void setMaxMemoryPerEvent(unsigned long long maxMemoryPerEvent);
private: 
    std::string className;
    static unsigned long long minMemoryRemaining;
    static unsigned long long maxMemoryPerEvent;

    void throwErrorMaybe(cudaError_t cudaStatus, std::string error);
};