#!/usr/bin/env sh
./compile.sh
if [ $? -eq 1 ]
then
   echo -e "\ncompile failed"
   exit
fi
./build/bin/Debug/SimulationMain.exe
if [ $? -eq 1 ]
then
   echo -e "\nmain failed"
   exit
fi
./render.sh

echo "end"
echo $?