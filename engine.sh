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

if [[ -f "engine.config" ]]
then
   echo "Configuration: engine.config"
   source ./engine.config
fi

# TODO: put into a reusable function
case "$OSTYPE" in
  msys*)    command_end=".exe" ;;
  cygwin*)  command_end=".exe" ;;
  *)        command_end="" ;;
esac

export SIMULATION_USE_GPU=${USE_GPU:-false}

./build/bin/Debug/SimulationEngine \
   --particle-count=${PARTICLE_COUNT:-200} --seconds=${SECONDS:-30} --mean-mass=${MEAN_MASS:-0.01} --star-mass=${STAR_MASS:-50} \
   --mean-speed=${MEAN_SPEED:-0.04} --delta-speed=${DELTA_SPEED:-0.2} --radius=${RADIUS:-15} --frame-rate=${FRAME_RATE:-60} 
if [ $? -ne 0 ]
then
   echo -e "\nengine failed"
   exit 1
fi
if [[ $* == *-r* ]] || [[ $* == *--render* ]]
then
   ./render.sh -nc
   if [ $? -ne 0 ]
   then
      exit 1
   fi
fi