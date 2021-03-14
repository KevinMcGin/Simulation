#!/usr/bin/env sh
./compile.sh
if [ $? -eq 1 ]
then
   echo -e "\ncompile failed"
   exit
fi
cd build
ctest -C Debug --output-on-failure
# REM ./build\bin\Debug\SimulationTest.exe