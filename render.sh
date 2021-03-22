#!/usr/bin/env sh
cd SimulationRenderer
py main.py
if [ $? -ne 0 ]
then
    echo -e "\render failed"
    exit 1
fi