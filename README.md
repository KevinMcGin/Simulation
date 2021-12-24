﻿[![Ubuntu CPU Build & Test](https://github.com/KevinMcGin/Simulation/actions/workflows/actions.yml/badge.svg)](https://github.com/KevinMcGin/Simulation/actions/workflows/actions.yml)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=KevinMcGin_Simulation&metric=alert_status)](https://sonarcloud.io/dashboard?id=KevinMcGin_Simulation)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=KevinMcGin_Simulation&metric=coverage)](https://sonarcloud.io/dashboard?id=KevinMcGin_Simulation)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=KevinMcGin_Simulation&metric=bugs)](https://sonarcloud.io/dashboard?id=KevinMcGin_Simulation)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=KevinMcGin_Simulation&metric=code_smells)](https://sonarcloud.io/dashboard?id=KevinMcGin_Simulation)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=KevinMcGin_Simulation&metric=duplicated_lines_density)](https://sonarcloud.io/dashboard?id=KevinMcGin_Simulation)
[![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=KevinMcGin_Simulation&metric=sqale_rating)](https://sonarcloud.io/dashboard?id=KevinMcGin_Simulation)
[![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=KevinMcGin_Simulation&metric=reliability_rating)](https://sonarcloud.io/dashboard?id=KevinMcGin_Simulation)
[![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=KevinMcGin_Simulation&metric=security_rating)](https://sonarcloud.io/dashboard?id=KevinMcGin_Simulation)
[![Technical Debt](https://sonarcloud.io/api/project_badges/measure?project=KevinMcGin_Simulation&metric=sqale_index)](https://sonarcloud.io/dashboard?id=KevinMcGin_Simulation)
[![Vulnerabilities](https://sonarcloud.io/api/project_badges/measure?project=KevinMcGin_Simulation&metric=vulnerabilities)](https://sonarcloud.io/dashboard?id=KevinMcGin_Simulation)

# Simulation
Simulates the motion of particles on the GPU with Nvidia's CUDA, or just on the CPU if a GPU is not available.

Renders these simulations with OpenGL.

## Render Example
https://user-images.githubusercontent.com/23276119/146377747-62b6992a-f834-4974-bd93-1703e3e06ea8.mp4

## Project Goals
- Simulate real world phenomenon.
- Predict future motion of asteroids, planets, and stars.
- Reverse engineer past motion of asteroids, planets, and stars.
- Display the above simulations in dynamic views.

## Dependencies
- CMake
- CUDA
- OpenGL

## Install
### CMake
``sudo apt install cmake``

### CUDA
``export cuda=11.2``

``./scripts/installation/install_cuda_ubuntu.sh``

``export CUDA_HOME=/usr/local/cuda-$cuda``

``export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$cuda/lib64:$cuda/extras/CUPTI/lib64``

``export PATH=$PATH:$CUDA_HOME/bin``

### OpenGL
```./scripts/installation/install_open_gl_ubuntu.sh```

## Build
``./compile.sh``

## Configuration
Configuration files are in the ``config`` folder.

Git ignored configuration files are generate from ``*.config.example`` files after building.

### Project
The project config file allows the configuration of the ``BUILD_PATH`` and whether to ``USE_GPU`` in the simulation engine.

## Test
### All Tests
``./test.sh``

### CPU Tests Only
``./test.sh -c``

## Run Engine
``./engine.sh``

## Run Renderer
``./render.sh``
