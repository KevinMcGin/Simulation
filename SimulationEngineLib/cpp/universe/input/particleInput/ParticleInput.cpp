#include "cpp/universe/input/particleInput/ParticleInput.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldMass.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldRadius.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldPositionX.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldPositionY.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldPositionZ.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldVelocityX.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldVelocityY.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldVelocityZ.h"

ParticleInput::ParticleInput(std::vector<std::string> headers) :
    inputsAvailable({
        new ParticleInputFieldMass(),
        new ParticleInputFieldRadius(),
        new ParticleInputFieldPositionX(),
        new ParticleInputFieldPositionY(),
        new ParticleInputFieldPositionZ(),
        new ParticleInputFieldVelocityX(),
        new ParticleInputFieldVelocityY(),
        new ParticleInputFieldVelocityZ(),
    }),
    inputsInUse({}) {

    for (const auto& header : headers) {
        std::cout << header << std::endl;
        ParticleInputField* input = findInputField(header);
        if (input != nullptr) {
            inputsInUse.push_back(input);
        } else {
            throw std::invalid_argument("ParticleInput: Header not found");
        }
    }
    for (const auto& input : inputsInUse) {
        std::cout << input->getHeader() << std::endl;
    }
}

void ParticleInput::set(Particle* particle, std::vector<std::string> values) {
    for (int i = 0; i < inputsInUse.size(); i++) {
        inputsInUse[i]->set(particle, values[i]);
    }
}

ParticleInputField* ParticleInput::findInputField(std::string header) {
    for (const auto& input : inputsAvailable) {
        if (input->getHeader() == header) {
            return input;
        }
    }
    return nullptr;
}
