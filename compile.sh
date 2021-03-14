#!/usr/bin/env sh
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DUSE_CUDA=ON
if [ $? -eq 1 ]
then
   echo -e "\ncompile failed"
   exit
fi
cmake --build build
if [ $? -eq 1 ]
then
   echo -e "\ncompile failed"
   exit
fi