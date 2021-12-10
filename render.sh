#!/usr/bin/env sh
no_compile='false'

print_usage() {
  printf "Usage: $0 [-n <don't compile before running>"
}

while getopts 'f:n' flag; do
  case "${flag}" in
    n) no_compile='true' ;;
    *) print_usage
       exit 1 ;;
  esac
done

if [[ $no_compile == 'false' ]]
then 
   ./compile.sh
   if [ $? -ne 0 ]
   then
      exit 1
   fi
fi

# TODO: link these instead of copying the file (move to compile?)
cp SimulationRenderer/lib/freeglut/bin/x64/freeglut.dll ./build/bin/Debug

./build/bin/Debug/SimulationRenderer
if [ $? -ne 0 ]
then
    echo -e "\nrender failed"
    exit 1
fi
