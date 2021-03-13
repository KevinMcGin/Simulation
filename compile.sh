#REM rmdir build -R
#REM mkdir build
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug
cmake --build build