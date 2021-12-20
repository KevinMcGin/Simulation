#!/bin/bash
delete_build='false'
build_folder='builds/build'

print_usage() {
  printf "Usage: $0 [-f <specify folder to build to> -d <delete build folder before build>]"
}

do_delete_build() {
    rm -rf $build_folder
    mkdir $build_folder
}

set_build_folder() {
   build_folder="builds/$1"
}

create_config_maybe() {
   test -f $1 || (cp $1.example $1 && echo "Created config file: $1")
}

while getopts 'b:d' flag; do
  case "${flag}" in
    b) set_build_folder "${OPTARG}" ;;
    d) delete_build='true' ;;
    *) print_usage
       exit 1 ;;
  esac
done

if [ $delete_build = 'true' ]; then do_delete_build; fi

cmake -S. -B$build_folder -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON 
if [ $? -ne 0 ]; then echo -e "\ncompile failed"; exit 1; fi

cmake --build $build_folder
if [ $? -ne 0 ]; then echo -e "\nbuild failed"; exit 1; fi

create_config_maybe config/project.config
create_config_maybe config/engine/engine.config

# TODO: link these instead of copying the file
source ./config/project.config
cp SimulationRenderer/lib/freeglut/bin/x64/freeglut.dll ./$build_folder${BUILD_PATH_END:-'/bin'}