file(GLOB cpp_headers CONFIGURE_DEPENDS "*.h")
file(GLOB cpp_source CONFIGURE_DEPENDS "*.cpp")
file(GLOB cu_headers CONFIGURE_DEPENDS "*.cuh")
file(GLOB cu_source CONFIGURE_DEPENDS "*.cu")

add_library(SimulationLib STATIC ${cpp_source} ${cu_source} ${cpp_headers} ${cu_headers})
set_target_properties(SimulationLib PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
set_target_properties(SimulationLib PROPERTIES CUDA_RESOLVE_DEVICE_SYMBOLS ON)

target_include_directories(SimulationLib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

if(NOT DEFINED CMAKE_CUDA_STANDARD)
    set(CMAKE_CUDA_STANDARD 11)
    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
endif()

if (CUDA_FOUND)
    message("CUDA found")
    #include(FindCUDA)
    INCLUDE_DIRECTORIES(${CUDA_INCLUDE_DIRS})
    target_include_directories(SimulationLib PUBLIC ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

else()
    message("CUDA not found")
endif()


# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
#if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
 # target_compile_options(Simulation
  #  PUBLIC
   #   "--coverage"
    #)
  #target_link_options(Simulation
   # INTERFACE
    #  "--coverage"
    #)
#endif()
