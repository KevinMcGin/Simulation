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
    unsigned long getFreeGpuMemory();
private: 
    std::string className;
    void throwErrorMaybe(cudaError_t cudaStatus, std::string error);
};