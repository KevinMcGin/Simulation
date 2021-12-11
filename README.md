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

```export CUDA_HOME=/usr/local/cuda-$cuda```

```export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$cuda/lib64:$cuda/extras/CUPTI/lib64```

```export PATH=$PATH:$CUDA_HOME/bin```

### OpenGL
```./scripts/installation/install_open_gl_ubuntu.sh```

## Build
```./compile.sh```

## Test
### All Tests
```./test.sh```

### CPU Tests Only
```./test.sh --c```

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
