#pragma once
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

class ParticleInputFieldRadius : public ParticleInputField {
public:
    void set(Particle* particle, std::string value) override {
        particle->radius = parseValue(value);
    }
    std::string getHeader() override { return "radius"; }
};