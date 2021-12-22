#pragma once
#include "Particle.cuh"
#include "CudaWithError.cuh"

#include <vector>

class Law {
public:
	Law(string className);
	virtual void cpuRun(vector<Particle*>& particles) = 0;
	virtual void gpuRun(Particle** td_par, int particleCount) = 0;
	string getClassName() { return className; }
protected:
	CudaWithError* cudaWithError;
private:
	string className = "Law";
};