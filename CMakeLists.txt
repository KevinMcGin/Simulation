cmake_minimum_required (VERSION 3.13)

project(Simulation LANGUAGES CUDA CXX)
find_package(CUDA REQUIRED)

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# we cannot analyse results without gcov
#find_program(GCOV_PATH gcov)
#if(NOT GCOV_PATH)
  #message(FATAL_ERROR "Code coverage analysis requires gcov!")
#endif()

option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)
option(USE_CUDA "Use CUDA" ON)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED true)
endif()

enable_language(CUDA)
if(USE_CUDA)
    add_definitions(-DUSE_CUDA)
endif()

add_subdirectory(SimulationLib)
add_subdirectory(SimulationMain)

enable_testing()

add_subdirectory(SimulationTest)