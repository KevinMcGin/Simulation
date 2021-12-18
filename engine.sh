#!/usr/bin/env sh
build_folder='builds/build'
file='engine.config'
no_compile='false'
render='false'

get_config() {
   config="config/engine/$1"
   echo "Configuration: $config"
   source ./$config
}

print_usage() {
  printf "Usage: $0 [-n <don't compile before running>] [-r -r <render after running>]"
}

while getopts 'b:f:nr' flag; do
  case "${flag}" in
    b) build_folder="${OPTARG}" ;;
    f) file="${OPTARG}" ;;
    n) no_compile='true' ;;
    r) render='true' ;;
    *) print_usage
       exit 1 ;;
  esac
done

if [ $no_compile = 'false' ]
then 
   ./compile.sh -b $build_folder
   if [ $? -ne 0 ]
   then
      exit 1
   fi
fi

get_config $file
source ./config/project.config

export SIMULATION_USE_GPU=${USE_GPU:-false}

./$build_folder${BUILD_PATH_END:-'/bin'}/SimulationEngine \
   --particle-count=${PARTICLE_COUNT:-200} --seconds=${SECONDS:-30} --mean-mass=${MEAN_MASS:-0.01} \
   --mean-density=${MEAN_DENSITY:-1000} --star-mass=${STAR_MASS:-50} \
   --mean-speed=${MEAN_SPEED:-0.04} --delta-speed=${DELTA_SPEED:-0.2} --radius=${RADIUS:-15} --frame-rate=${FRAME_RATE:-60} 
if [ $? -ne 0 ]
then
   echo -e "\nengine failed"
   exit 1
fi
if [ $render = 'true' ]
then
   ./render.sh -n -b $build_folder
   if [ $? -ne 0 ]
   then
      exit 1
   fi
fi
