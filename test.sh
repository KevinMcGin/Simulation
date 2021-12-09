#!/usr/bin/env sh
if [[ $* == *-h* ]] || [[ $* == *--help* ]]
then
   echo "Usage: $0 [-nc --no-compile <compile bfore running>]" 1>&2; exit 1;
fi
if [[ $* != *-nc* ]] && [[ $* != *--no-compile* ]]
then
   ./compile.sh
   if [ $? -ne 0 ]
   then
      exit 1
   fi
fi
if [[ $* == *--cpu* ]]
then
   export SIMULATION_USE_GPU=false
   test_dir="--test-dir SimulationTest/cpuTests"
else
   export SIMULATION_USE_GPU=true
fi

cd build
ctest -C Debug $test_dir --output-on-failure .. 2>ctest.error
if grep "No tests were found" ctest.error  ; then exit 1 ; fi

# Todo: is this output better?
# ./build/bin/Debug/SimulationTest.exe
# ctest -R NewtonGravityTest.ParticlesAccelerate 