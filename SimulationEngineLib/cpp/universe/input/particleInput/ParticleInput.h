#pragma once
#include "shared/particle/Particle.cuh"
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

#include <memory>
#include <vector>

class ParticleInput {
public:
    ParticleInput(std::vector<std::string> headers);
    void set(Particle* particle, std::vector<std::string> values);

private:
    ParticleInputField* findInputField(std::string header);

    // inputsAvailable owns every field; inputsInUse just points at the
    // subset the file's headers asked for, so the two must not both free
    // them.
    std::vector<ParticleInputField*> inputsInUse;
    std::vector<std::unique_ptr<ParticleInputField>> inputsAvailable;
};