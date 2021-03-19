#!/usr/bin/env sh
if [[ $* == *-h* ]] || [[ $* == *--help* ]]
then
   echo "Usage: $0 [-nc --no-compile <compile bfore running>]" 1>&2; exit 1;
fi
if [[ $* != *-nc* ]] && [[ $* != *--no-compile* ]]
then
   ./compile.sh
   if [ $? -eq 1 ]
   then
      exit 1
   fi
fi
cd build
ctest -C Debug --output-on-failure .. 2>ctest.error
if grep "No tests were found" ctest.error  ; then exit 1 ; fi

# Todo: is this output better?
# ./build/bin/Debug/SimulationTest.exe