#!/usr/bin/env sh

if [[ $* == *-h* ]] || [[ $* == *--help* ]]
then
   echo "Usage: $0 [-d --delete <delete build folder before build>]" 1>&2; exit 1;
fi
if [[ $* == *-d* ]] || [[ $* == *--delete* ]]
then
    rm -rf build
    mkdir build
fi

cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON 
if [ $? -ne 0 ]
then
   echo -e "\ncompile failed"
   exit 1
fi
cmake --build build
if [ $? -ne 0 ]
then
   echo -e "\nbuild failed"
   exit 1
fi