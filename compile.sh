#!/usr/bin/env sh
delete_build='false'

print_usage() {
  printf "Usage: $0 [-d <delete build folder before build>]"
}

do_delete_build() {
    rm -rf build
    mkdir build
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
