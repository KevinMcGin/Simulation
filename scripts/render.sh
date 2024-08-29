#!/bin/bash
build_folder='build'
no_compile='false'
output_file=''
verbose=''

print_usage() {
  printf "Usage: $0 [-n <don't compile before running> -i <FILE_NAME> -v <verbose output>]"
}

get_build_path() {
   build_path="builds/$1"
}

set_output_path() {
   output_path="simulation_output/$1"
}

while getopts 'b:i:nv' flag; do
  case "${flag}" in
    b) build_folder="${OPTARG}" ;;
    i) set_output_path "${OPTARG}" ;;
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

get_build_path $build_folder
source ./config/project.config
./$build_path/${BUILD_PATH_END:-'/bin'}/SimulationRenderer $output_path
if [ $? -ne 0 ]; then echo -e "\nrender failed"; exit 1; fi
