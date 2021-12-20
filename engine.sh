#!/bin/bash
build_folder='build'
config_file='engine.config'
output_file='simulation_output.json'
no_compile='false'
render='false'

get_config() {
   config="config/engine/$1"
   echo "Configuration: $config"
   source ./$config
}

get_build_path() {
   build_path="builds/$1"
}

get_output_path() {
   output_path="simulation_output/$1"
}

print_usage() {
  printf "Usage: $0 [-n <don't compile before running>] [-r <render after running>] [-f <config file>] [-o <output file name>]"
}

while getopts 'b:f:o:nr' flag; do
  case "${flag}" in
    b) build_folder="${OPTARG}" ;;
    f) config_file="${OPTARG}" ;;
    n) no_compile='true' ;;
    o) output_file="${OPTARG}" ;;
    r) render='true' ;;
    *) print_usage
       exit 1 ;;
  esac
done

if [ $no_compile = 'false' ]
then 
   ./compile.sh -b $build_folder
   if [ $? -ne 0 ]; then exit 1; fi
fi

get_config $config_file
source ./config/project.config

export SIMULATION_USE_GPU=${USE_GPU:-false}
get_build_path $build_folder

get_output_path $output_file

./$build_path${BUILD_PATH_END:-'/bin'}/SimulationEngine \
   --output-file=$output_path \
   --particle-count=${PARTICLE_COUNT:-200} \
   --seconds=${SECONDS:-30} \
   --mean-mass=${MEAN_MASS:-0.01} \
   --mean-density=${MEAN_DENSITY:-1000} \
   --star-mass=${STAR_MASS:-50} \
   --mean-speed=${MEAN_SPEED:-0.04} \
   --delta-speed=${DELTA_SPEED:-0.2} \
   --radius=${RADIUS:-15} \
   --frame-rate=${FRAME_RATE:-60} 
if [ $? -ne 0 ]; then echo -e "\nengine failed"; exit 1; fi
if [ $render = 'true' ]
then
   ./render.sh -n -b $build_folder -i $output_file 
   if [ $? -ne 0 ]; then exit 1; fi
fi
