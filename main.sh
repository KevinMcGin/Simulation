#!/usr/bin/env sh

if [[ $* == *-h* ]] || [[ $* == *--help* ]]
then
   echo "Usage: $0 [-nc --no-compile <don't compile before running>] [-r --render <render after running>]" 1>&2; exit 1;
fi
if [[ $* != *-nc* ]] && [[ $* != *--no-compile* ]]
then
   ./compile.sh
   if [ $? -ne 0 ]
   then
      exit 1
   fi
fi

export SIMULATION_USE_GPU=true

./build/bin/Debug/SimulationMain.exe \
   --particle-count=1000 --seconds=30 --mean-mass=0.01 --star-mass=50 \
   --mean-speed=0.04 --delta-speed=0.2 --radius=15 --frame-rate=60 
if [ $? -ne 0 ]
then
   echo -e "\nmain failed"
   exit 1
fi
if [[ $* == *-r* ]] || [[ $* == *--render* ]]
then
   ./render.sh
   if [ $? -ne 0 ]
   then
      exit 1
   fi
fi


echo "end"
echo $?