#include "cpp/law/Law.h"

Law::Law(
    std::string className,
    std::unique_ptr<CpuLaw> cpuLaw, 
    std::unique_ptr<GpuLaw> gpuLaw
) : className(className) {
    this->cpuLaw = std::move(cpuLaw);
    this->gpuLaw = std::move(gpuLaw);
}