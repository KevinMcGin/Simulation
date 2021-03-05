#include "UniverseImplSimple.h"



UniverseImplSimple::UniverseImplSimple(SimulationInput* input, SimulationOutput* output, unsigned long endTime) : UniverseImpl({ new NewtonGravity(), new NewtonFirstLaw() }, input, output, 1, endTime)
{

}
