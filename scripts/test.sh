#!/bin/bash
build_folder='build'
no_compile='false'
cpu_only='false'
verbose=''
single_test=''

print_usage() {
  printf "Usage: $0 [-n <don't compile before running> [-c <only CPU tests>] [-v <verbose output>] [-s <single_test>]"
}

get_build_path() {
   build_path="builds/$1"
}

while getopts 'b:cns:v' flag; do
  case "${flag}" in
    b) build_folder="${OPTARG}" ;;
    c) cpu_only='true' ;;
    n) no_compile='true' ;;
    v) verbose='-v' ;;
    s) single_test="-R ${OPTARG}" ;;
    *) print_usage
       exit 1 ;;
  esac
done

if [ $no_compile = 'false' ]
then 
   ./compile.sh -b $build_folder $verbose
   if [ $? -ne 0 ];  then exit 1; fi
fi

cd ..

get_build_path $build_folder
cd $build_path
if [ $cpu_only = 'true' ]
then
   export SIMULATION_USE_GPU=false
   cd SimulationTest/cpuTests
else
   export SIMULATION_USE_GPU=true
fi

ctest -C Debug $single_test --output-on-failure .. 2>ctest.error
if [ $? -ne 0 ]; then exit 1; fi
if grep "No tests were found" ctest.error  ; then exit 1 ; fi
