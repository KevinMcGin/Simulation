#pragma once
#include "shared/particle/Particle.cuh"

#include <vector>

class ParticleInputField {
public:
    // The fields are owned as unique_ptr<ParticleInputField> by
    // ParticleInput and deleted through this base.
    virtual ~ParticleInputField() = default;
    virtual void set(Particle* particle, std::string value) = 0;
    virtual std::string getHeader() = 0;
protected:
    float parseValue(std::string value);
};