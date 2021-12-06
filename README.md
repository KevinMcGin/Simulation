[![Build Status](https://github.com/KevinMcGin/Simulation/actions/workflows/actions.yml/badge.svg)](https://github.com/KevinMcGin/Simulation/actions/workflows/action.yml)

# Simulation
Simulate and render the motion of particles.

## Dependencies
- CMake
- CUDA
- OpenGL (Python3 currently)

## Build
./compile.sh

## Test
./test.sh

## Run Engine
./engine.sh

### Engine Configuration
#### Config example file at project root 
File name: engine.config

```
USE_GPU=true
PARTICLE_COUNT=200
SECONDS=300
MEAN_MASS=0.01
STAR_MASS=50
MEAN_SPEED=0.04
DELTA_SPEED=0.2
RADIUS=15
FRAME_RATE=60 
```

## Run Renderer
./render.sh