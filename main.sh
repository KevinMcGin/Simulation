#!/usr/bin/env sh
./compile.sh
if [ $? -eq 1 ]
then
   exit 1
fi
./build/bin/Debug/SimulationMain.exe
if [ $? -eq 1 ]
then
   echo -e "\nmain failed"
   exit 1
fi
./render.sh

echo "end"
echo $?