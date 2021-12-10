[![Build Status](https://github.com/KevinMcGin/Simulation/actions/workflows/actions.yml/badge.svg)](https://github.com/KevinMcGin/Simulation/actions/workflows/actions.yml)

# Simulation
Simulate and render the motion of particles.

## Dependencies
- CMake
- CUDA
- OpenGL

## Install
### CMake
```sudo apt install cmake```

### CUDA
```export cuda=11.2```

```./scripts/installation/install_cuda_ubuntu.sh```

```sudo ln -s /usr/local/cuda-11.2 /usr/local/cuda```

### OpenGL
```./scripts/installation/install_open_gl_ubuntu.sh```

## Build
```./compile.sh```

## Test
### All Tests
```./test.sh```

### CPU Tests Only
```./test.sh --cpu```

## Run Engine
```./engine.sh```

### Engine Configuration
Config example file at project root 

File name: ```engine.config```

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
```./render.sh```