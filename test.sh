#!/usr/bin/env sh
no_compile='false'
cpu_only='false'

print_usage() {
  printf "Usage: $0 [-n <don't compile before running> [-c <only CPU tests>]"
}

while getopts 'cn' flag; do
  case "${flag}" in
    c) cpu_only='true' ;;
    n) no_compile='true' ;;
    *) print_usage
       exit 1 ;;
  esac
done

if [ $no_compile == 'false' ]
then 
   ./compile.sh
   if [ $? -ne 0 ]
   then
      exit 1
   fi
fi

cd build
if [ $cpu_only = 'true' ]
then
   export SIMULATION_USE_GPU=false
   cd SimulationTest/cpuTests
else
   export SIMULATION_USE_GPU=true
fi

ctest -C Debug --output-on-failure .. 2>ctest.error
if grep "No tests were found" ctest.error  ; then exit 1 ; fi

# Todo: is this output better?
# ./build/bin/Debug/SimulationTest.exe
# ctest -R NewtonGravityTest.ParticlesAccelerate 
