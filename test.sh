#!/usr/bin/env sh
./compile.sh
if [ $? -eq 1 ]
then
   exit 1
fi
cd build
ctest -C Debug --output-on-failure .. 2>ctest.error
if grep "No tests were found" ctest.error  ; then exit 1 ; fi
# REM ./build\bin\Debug\SimulationTest.exe