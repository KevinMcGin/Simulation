#include "gpuHelper/CudaWithError.cuh"
#include<iostream>


CudaWithError::CudaWithError(std::string className): className(className) { }

void CudaWithError::throwErrorMaybe(cudaError_t cudaStatus, std::string error) {
    if (cudaStatus != cudaSuccess) {
        std::string totalError = className + ": " + error + "\n" + cudaGetErrorString(cudaStatus);
        std::cerr << std::endl << totalError << std::endl;
        throw new std::runtime_error(totalError);
    }
}

void CudaWithError::setDevice(int device) {
	cudaError_t cudaStatus = cudaSetDevice(device);
    throwErrorMaybe(cudaStatus, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
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


unsigned long CudaWithError::getFreeGpuMemory() 
{
    size_t free_t, total_t;

    cudaMemGetInfo(&free_t, &total_t);

    free_t = free_t / 1.0485760;

    unsigned long free_m = (unsigned int)free_t;

    return free_m;
}
