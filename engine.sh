#!/usr/bin/env sh
file='engine.config'
no_compile='false'
render='false'

get_config() {
   echo "Configuration: engine.config"
   source ./$1
}

print_usage() {
  printf "Usage: $0 [-n <don't compile before running>] [-r -r <render after running>]"
}

while getopts 'f:nr' flag; do
  case "${flag}" in
    f) file="${OPTARG}" ;;
    n) no_compile='true' ;;
    r) render='true' ;;
    *) print_usage
       exit 1 ;;
  esac
done

if [ $no_compile == 'false' ]
then 
   ./compile.sh
   if [ $? -ne 0 ]
   then
      exit 1
   fi
fi

get_config $file

export SIMULATION_USE_GPU=${USE_GPU:-false}

./build/bin/Debug/SimulationEngine \
   --particle-count=${PARTICLE_COUNT:-200} --seconds=${SECONDS:-30} --mean-mass=${MEAN_MASS:-0.01} --star-mass=${STAR_MASS:-50} \
   --mean-speed=${MEAN_SPEED:-0.04} --delta-speed=${DELTA_SPEED:-0.2} --radius=${RADIUS:-15} --frame-rate=${FRAME_RATE:-60} 
if [ $? -ne 0 ]
then
   echo -e "\nengine failed"
   exit 1
fi
if [ $render == 'true' ]
then
   ./render.sh -n
   if [ $? -ne 0 ]
   then
      exit 1
   fi
fi
