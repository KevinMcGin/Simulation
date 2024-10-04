#!/bin/bash
build_folder='build'
config_file='engine.config'
output_file='simulation_output.json'
no_compile='false'
render='false'
verbose=''

get_config() {
   config="config/engine/$1"
   echo "Configuration: $config"
   source ./$config
}

get_build_path() {
   build_path="builds/$1"
}


print_usage() {
  printf "Usage: $0 [-n <don't compile before running>] [-f <config file>]"
}

while getopts 'b:f:o:nrv' flag; do
  case "${flag}" in
    b) build_folder="${OPTARG}" ;;
    f) config_file="${OPTARG}.config" ;;
    n) no_compile='true' ;;
    v) verbose='-v' ;;
    *) print_usage
       exit 1 ;;
  esac
done

if [ $no_compile = 'false' ]
then 
   ./compile.sh -b $build_folder $verbose
   if [ $? -ne 0 ]; then exit 1; fi
fi

cd ..

get_config $config_file
source ./config/project.config

export SIMULATION_USE_GPU=${USE_GPU:-false}
get_build_path $build_folder

./$build_path${BUILD_PATH_END:-'/bin'}/SimulationEngineServer

if [ $? -ne 0 ]; then echo -e "\nengine failed"; exit 1; fi
