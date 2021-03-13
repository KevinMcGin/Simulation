#!/usr/bin/env sh
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug
cmake --build build