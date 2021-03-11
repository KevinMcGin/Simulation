cmake_minimum_required (VERSION 3.8)

project(Simulation LANGUAGES CXX)

# we cannot analyse results without gcov
#find_program(GCOV_PATH gcov)
#if(NOT GCOV_PATH)
  #message(FATAL_ERROR "Code coverage analysis requires gcov!")
#endif()

add_subdirectory(SimulationSrc)

enable_testing()

add_subdirectory(SimulationTest)