#!/usr/bin/env sh
cd build/bin/Debug
# TODO: configure this directory
cp F:/"Program Files"/freeglut/bin/x64/freeglut.dll .
./SimulationRenderer.exe
if [ $? -ne 0 ]
then
    echo -e "\render failed"
    exit 1
fi