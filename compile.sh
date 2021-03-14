#!/usr/bin/env sh
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DUSE_CUDA=ON
cmake --build build