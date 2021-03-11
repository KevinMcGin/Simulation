# CMakeList.txt : CMake project for Simulation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
option(USE_CUDA "Use CUDA" ON)

project ("Simulation")

if(USE_CUDA)
    enable_language(CUDA)
    add_executable (Simulation  "kernel.cu" "CollisionDetector.h" "CollisionDetectorSimple.cpp" "CollisionDetectorSimple.h" "CollisionResolver.h" "CollisionResolverCoalesce.cpp" "CollisionResolverCoalesce.h" "Collission.cpp" "Collission.h" "CollissionCoalesce.cpp" "CollissionCoalesce.h" "Distribution.cpp" "Distribution.h" "Distribution3D.cpp" "Distribution3D.h" "DistributionCircle.cpp" "DistributionCircle.h" "DistributionCube.cpp" "DistributionCube.h" "DistributionCuboid.cpp" "DistributionCuboid.h" "DistributionDensity.cpp" "DistributionDensity.h" "DistributionGlobe.cpp" "DistributionGlobe.h" "DistributionMassDensity.cpp" "DistributionMassDensity.h" "DistributionSimple.cpp" "DistributionSimple.h" "DistributionSphere.cpp" "DistributionSphere.h" "DistributionSquare.cpp" "DistributionSquare.h" "DistributionValue.cpp" "DistributionValue.h" "Law.h" "main.cpp" "NewtonFirstLaw.cpp" "NewtonFirstLaw.h" "NewtonGravity.cpp" "NewtonGravity.h" "Particle.h" "ParticleDistribution.cpp" "ParticleDistribution.h" "ParticleDistributionSimple.cpp" "ParticleDistributionSimple.h" "ParticleSimple.cpp" "ParticleSimple.h" "SimulationInput.h" "SimulationInputRandomSimple.cpp" "SimulationInputRandomSimple.h" "SimulationInputSimple.cpp" "SimulationInputSimple.h" "SimulationOutput.h" "SimulationOutputJSON.cpp" "SimulationOutputJSON.h" "SimulationOutputPrint.cpp" "SimulationOutputPrint.h" "Universe.cpp" "Universe.h" "UniverseImpl.cpp" "UniverseImpl.h" "UniverseImplSimple.cpp" "UniverseImplSimple.h" "Vector3D.cpp" "Vector3D.h")
else(USE_CUDA)
    add_executable (Simulation   "CollisionDetector.h" "CollisionDetectorSimple.cpp" "CollisionDetectorSimple.h" "CollisionResolver.h" "CollisionResolverCoalesce.cpp" "CollisionResolverCoalesce.h" "Collission.cpp" "Collission.h" "CollissionCoalesce.cpp" "CollissionCoalesce.h" "Distribution.cpp" "Distribution.h" "Distribution3D.cpp" "Distribution3D.h" "DistributionCircle.cpp" "DistributionCircle.h" "DistributionCube.cpp" "DistributionCube.h" "DistributionCuboid.cpp" "DistributionCuboid.h" "DistributionDensity.cpp" "DistributionDensity.h" "DistributionGlobe.cpp" "DistributionGlobe.h" "DistributionMassDensity.cpp" "DistributionMassDensity.h" "DistributionSimple.cpp" "DistributionSimple.h" "DistributionSphere.cpp" "DistributionSphere.h" "DistributionSquare.cpp" "DistributionSquare.h" "DistributionValue.cpp" "DistributionValue.h" "Law.h" "main.cpp" "NewtonFirstLaw.cpp" "NewtonFirstLaw.h" "NewtonGravity.cpp" "NewtonGravity.h" "Particle.h" "ParticleDistribution.cpp" "ParticleDistribution.h" "ParticleDistributionSimple.cpp" "ParticleDistributionSimple.h" "ParticleSimple.cpp" "ParticleSimple.h" "SimulationInput.h" "SimulationInputRandomSimple.cpp" "SimulationInputRandomSimple.h" "SimulationInputSimple.cpp" "SimulationInputSimple.h" "SimulationOutput.h" "SimulationOutputJSON.cpp" "SimulationOutputJSON.h" "SimulationOutputPrint.cpp" "SimulationOutputPrint.h" "Universe.cpp" "Universe.h" "UniverseImpl.cpp" "UniverseImpl.h" "UniverseImplSimple.cpp" "UniverseImplSimple.h" "Vector3D.cpp" "Vector3D.h")

endif()

# TODO: Add tests and install targets if needed.
if(USE_CUDA)
    if(NOT DEFINED CMAKE_CUDA_STANDARD)
        set(CMAKE_CUDA_STANDARD 11)
        set(CMAKE_CUDA_STANDARD_REQUIRED ON)
    endif()
    target_include_directories(Simulation PRIVATE "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.2/include")
endif()
