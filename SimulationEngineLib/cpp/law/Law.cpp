#include "cpp/law/Law.h"

Law::Law(std::shared_ptr<CpuLaw> cpuLaw, std::shared_ptr<GpuLaw> gpuLaw) : cpuLaw(cpuLaw), gpuLaw(gpuLaw) {}