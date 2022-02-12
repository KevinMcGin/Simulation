#!/bin/bash
delete_build='false'
build_folder='builds/build'
build_params=''
ignore_output='true'

print_usage() {
  printf "Usage: $0 [-f <specify folder to build to> -d <delete build folder before build> -v <verbose output>]"
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

while getopts 'b:dp:v' flag; do
  case "${flag}" in
    b) set_build_folder "${OPTARG}" ;;
    d) delete_build='true' ;;
    p) build_params="${OPTARG}" ;;
    v) ignore_output='false'  ;;
    *) print_usage
       exit 1 ;;
  esac
done

cd ..

if [ $delete_build = 'true' ]; then do_delete_build; fi

echo -e "\ncompiling and building";
compile_cmd_params="-S. -B$build_folder $build_params -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DUSE_GPU_TESTS=ON"
if [ $ignore_output = 'true' ]; then cmake $compile_cmd_params > /dev/null 2>&1; else cmake $compile_cmd_params; fi

if [ $? -ne 0 ]; then echo -e "\ncompile failed"; exit 1; fi
echo -e "\ncompile succeeded";

build_cmd_params="--build $build_folder"
if [ $ignore_output = 'true' ]; then cmake $build_cmd_params > /dev/null 2>&1; else cmake $build_cmd_params; fi
if [ $? -ne 0 ]; then echo -e "\nbuild failed"; exit 1; fi
echo -e "\nbuild succeeded";

create_config_maybe config/project.config
create_config_maybe config/engine/engine.config

# TODO: link these instead of copying the file
source ./config/project.config
cp SimulationRenderer/lib/freeglut/bin/x64/freeglut.dll ./$build_folder${BUILD_PATH_END:-'/bin'}
