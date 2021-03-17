#!/usr/bin/env sh
# if [ -h ] || [--hard]
# then
#     rm -rf build
#     mkdir build
# fi
rm -rf build/SimulationMain
rm -rf build/SimulationTest
# mkdir build
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DUSE_CUDA=ON -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
if [ $? -eq 1 ]
then
   echo -e "\ncompile failed"
   exit 1
fi
cmake --build build
if [ $? -eq 1 ]
then
   echo -e "\ncompile failed"
   exit 1
fi