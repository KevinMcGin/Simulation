#pragma once
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

class ParticleInputFieldMass : public ParticleInputField {
public:
    void set(Particle* particle, std::string value) override {
        particle->mass = parseValue(value);
    }
    std::string getHeader() override { return "mass"; }
};