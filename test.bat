CALL compile.bat
cd build
ctest -C Debug --output-on-failure
REM .\build\bin\Debug\SimulationTest.exe