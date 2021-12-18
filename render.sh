#!/usr/bin/env sh
build_folder='builds/build'
no_compile='false'

print_usage() {
  printf "Usage: $0 [-n <don't compile before running>"
}

while getopts 'b:n' flag; do
  case "${flag}" in
    b) build_folder="${OPTARG}" ;;
    n) no_compile='true' ;;
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

source ./config/project.config
./$build_folder${BUILD_PATH_END:-'/bin'}/SimulationRenderer
if [ $? -ne 0 ]
then
    echo -e "\nrender failed"
    exit 1
fi
