cmake_minimum_required (VERSION 3.25)

project(Simulation LANGUAGES CXX C)

message("CMAKE_CXX_SOURCE_FILE_EXTENSIONS ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS}")

if(USE_GPU)
  add_definitions(-DUSE_GPU)
  set(CUDA_SEPARABLE_COMPILATION ON)
  find_package(CUDA REQUIRED)
  enable_language(CUDA)
endif()

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  message("Coverage enabled")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -g -O0 -Wno-error")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -fno-exceptions -fno-inline")
endif()

option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)

add_subdirectory(SimulationEngineLib)
add_subdirectory(SimulationEngine)
add_subdirectory(SimulationEngineServer)
if(USE_OPENGL_RENDERER)
  add_subdirectory(SimulationRenderer)
endif()
add_subdirectory(SimulationRendererLib)
add_subdirectory(SimulationCommon)

enable_testing()
add_subdirectory(SimulationTest/common)
add_subdirectory(SimulationTest/cpuTests)
if(USE_GPU)
  add_subdirectory(SimulationTest/gpuTests)
endif()