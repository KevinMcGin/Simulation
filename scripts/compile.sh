#!/bin/bash
delete_build='false'
build_folder='builds/build'
build_params=''
architecture_param=''
generator_param=''
toolset_version=''
ignore_output='true'
gpu_flag='-DUSE_GPU=OFF'

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

while getopts 'a:b:dg:t:v' flag; do
  case "${flag}" in
    a) architecture_param="-A ${OPTARG}" ;;
    b) set_build_folder "${OPTARG}" ;;
    d) delete_build='true' ;;
    g) generator_param="-G${OPTARG}" ;;
    v) ignore_output='false'  ;;
    t) toolset_version="-T version=${OPTARG}" ;;
    *) print_usage
       exit 1 ;;
  esac
done

cd ..

create_config_maybe config/project.config
create_config_maybe config/engine/engine.config
source ./config/project.config

if [ $delete_build = 'true' ]; then do_delete_build; fi

if [ $USE_GPU = 'true' ]; then 
  gpu_flag='-DUSE_GPU=ON'
else
  gpu_flag='-DUSE_GPU=OFF'
fi

echo -e "\ncompiling";
if [ $ignore_output = 'true' ]; then 
  cmake -S. -B$build_folder "$architecture_param" "$generator_param" "$toolset_version" "$gpu_flag" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON  > /dev/null 2>&1
else
  cmake -S. -B$build_folder "$architecture_param" "$generator_param" "$toolset_version" "$gpu_flag" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
fi

if [ $? -ne 0 ]; then echo -e "\ncompile failed"; exit 1; fi
echo -e "compile succeeded";

echo -e "\nbuilding";
build_cmd_params="--build $build_folder"
if [ $ignore_output = 'true' ]; then cmake $build_cmd_params > /dev/null 2>&1; else cmake $build_cmd_params; fi
if [ $? -ne 0 ]; then echo -e "\nbuild failed"; exit 1; fi
echo -e "build succeeded";

# TODO: link these instead of copying the file
cp SimulationRenderer/lib/freeglut/bin/x64/freeglut.dll ./$build_folder${BUILD_PATH_END:-'/bin'}
