#pragma once
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

class ParticleInputFieldPositionY : public ParticleInputField {
public:
    void set(Particle* particle, std::string value) override {
        particle->position.y = parseValue(value);
    }
    std::string getHeader() override { return "positionY"; }
};