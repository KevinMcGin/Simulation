#!/usr/bin/env sh
cd SimulationRenderer
py main.py
if [ $? -eq 1 ]
then
    echo -e "\render failed"
    exit 1
fi