#pragma once
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

class ParticleInputFieldPositionZ : public ParticleInputField {
public:
    void set(Particle* particle, std::string value) override {
        particle->position.z = parseValue(value);
    }
    std::string getHeader() override { return "positionZ"; }
};