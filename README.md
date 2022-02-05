[![Ubuntu CPU Build & Test](https://github.com/KevinMcGin/Simulation/actions/workflows/actions.yml/badge.svg)](https://github.com/KevinMcGin/Simulation/actions/workflows/actions.yml)
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

## Road Map
[Wiki](https://github.com/KevinMcGin/Simulation/wiki#road-map)

## Dependencies
- CMake
- CUDA
- OpenGL

## Installation
[Installation Guide](scripts/installation/README.md)

## Configuration
Configuration files are in the ``config`` folder.

Git ignored configuration files are generate from ``*.config.example`` files after building.

### Project
The project config file allows the configuration of the ``BUILD_PATH`` and whether to ``USE_GPU`` in the simulation engine.

## Scripts
[Scripts Guide](scripts/README.md)
