#pragma once
#include "shared/particle/Particle.cuh"
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

#include <vector>

class ParticleInput {
public:
    ParticleInput(std::vector<std::string> headers);
    void set(Particle* particle, std::vector<std::string> values);

private:
    ParticleInputField* findInputField(std::string header);

    std::vector<ParticleInputField*> inputsInUse;
    std::vector<ParticleInputField*> inputsAvailable;
};