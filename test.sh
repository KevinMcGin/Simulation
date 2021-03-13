#!/usr/bin/env sh
./compile.sh
cd build
ctest -C Debug --output-on-failure
# REM ./build\bin\Debug\SimulationTest.exe