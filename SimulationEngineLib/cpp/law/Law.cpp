#include "cpp/law/Law.h"

Law::Law(
    std::string className,
    std::shared_ptr<CpuLaw> cpuLaw, 
    std::shared_ptr<GpuLaw> gpuLaw
) : className(className),
    cpuLaw(cpuLaw), 
    gpuLaw(gpuLaw) {}