# Installation

## Ubuntu

### CMake
``sudo apt install cmake``

### CUDA
``export cuda=11.2``

``./install_cuda_ubuntu.sh``

``export CUDA_HOME=/usr/local/cuda-$cuda``

``export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$cuda/lib64:$cuda/extras/CUPTI/lib64``

``export PATH=$PATH:$CUDA_HOME/bin``

Credit: https://github.com/ptheywood/cuda-cmake-github-actions

### OpenGL
```./install_open_gl_ubuntu.sh```

## Windows

### CMake
[Install CMake](https://cmake.org/install/)

### CUDA
``export cuda=11.2.0``

``./install_cuda_windows.ps1``

TODO: Add environment variables to PATH

### OpenGL
- Temporary empty script: ```./install_open_gl_ubuntu.sh```
- No action should be needed
  - dlls are stored in `SimulationRenderer/lib/freeglut`
  - Environment variables should auto configure to these dlls