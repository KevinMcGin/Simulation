#pragma once
#include "shared/particle/Particle.cuh"

#include <vector>

class ParticleInputField {
public:
    virtual void set(Particle* particle, std::string value) = 0;
    virtual std::string getHeader() = 0;
protected:
    float parseValue(std::string value);
};