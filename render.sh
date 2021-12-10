#!/usr/bin/env sh

if [[ $* == *-h* ]] || [[ $* == *--help* ]]
then
   echo "Usage: $0 [-nc --no-compile <don't compile before running>" 1>&2; exit 1;
fi

if [[ $* != *-nc* ]] && [[ $* != *--no-compile* ]]
then
   ./compile.sh
   if [ $? -ne 0 ]
   then
      exit 1
   fi
fi

# TODO: configure this directory
cd build/bin/Debug
cp F:/"Program Files"/freeglut/bin/x64/freeglut.dll .
cd ../../..

./build/bin/Debug/SimulationRenderer.exe
if [ $? -ne 0 ]
then
    echo -e "\nrender failed"
    exit 1
fi