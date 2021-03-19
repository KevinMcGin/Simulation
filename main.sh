#!/usr/bin/env sh

if [[ $* == *-h* ]] || [[ $* == *--help* ]]
then
   echo "Usage: $0 [-nc --no-compile <compile before running>] [-r --render <render after running>]" 1>&2; exit 1;
fi
if [[ $* != *-nc* ]] && [[ $* != *--no-compile* ]]
then
   ./compile.sh
   if [ $? -eq 1 ]
   then
      exit 1
   fi
fi

./build/bin/Debug/SimulationMain.exe
if [ $? -eq 1 ]
then
   echo -e "\nmain failed"
   exit 1
fi
if [[ $* == *-r* ]] || [[ $* == *--render* ]]
then
   ./render.sh
   if [ $? -eq 1 ]
   then
      exit 1
   fi
fi


echo "end"
echo $?