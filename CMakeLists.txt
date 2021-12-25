cmake_minimum_required (VERSION 3.13)

project(Simulation LANGUAGES CUDA CXX C)
set(CUDA_SEPARABLE_COMPILATION ON)
find_package(CUDA REQUIRED)

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  message("Coverage enabled")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -g -O0")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
enable_language(CUDA)


add_subdirectory(SimulationLib)
add_subdirectory(SimulationEngine)
add_subdirectory(SimulationRenderer)

enable_testing()
add_subdirectory(SimulationTest/cpuTests)
if(USE_GPU_TESTS)
  add_subdirectory(SimulationTest/gpuTests)
endif()