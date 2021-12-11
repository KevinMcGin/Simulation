#!/usr/bin/env sh
delete_build='false'

print_usage() {
  printf "Usage: $0 [-d <delete build folder before build>]"
}

do_delete_build() {
    rm -rf build
    mkdir build
}

create_config_maybe() {
   test -f $1 || (cp $1.example $1 && echo "Created config file: $1")
}

while getopts 'd' flag; do
  case "${flag}" in
    d) delete_build='true' ;;
    *) print_usage
       exit 1 ;;
  esac
done

if [ $delete_build = 'true' ]
then
   do_delete_build
fi

cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON 
if [ $? -ne 0 ]
then
   echo -e "\ncompile failed"
   exit 1
fi

cmake --build build
if [ $? -ne 0 ]
then
   echo -e "\nbuild failed"
   exit 1
fi

create_config_maybe config/project.config
create_config_maybe config/engine/engine.config

# TODO: link these instead of copying the file (move to compile?)
source ./config/project.config
cp SimulationRenderer/lib/freeglut/bin/x64/freeglut.dll ./${BUILD_PATH:-'build/bin'}
