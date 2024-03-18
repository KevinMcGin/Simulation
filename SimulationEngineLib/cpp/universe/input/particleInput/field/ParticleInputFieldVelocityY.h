#pragma once
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

class ParticleInputFieldVelocityY : public ParticleInputField {
public:
    void set(Particle* particle, std::string value) override {
        particle->velocity.y = parseValue(value);
    }
    std::string getHeader() override { return "velocityY"; }
};