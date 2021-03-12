add_library(SimulationLib)

file(GLOB headers_src CONFIGURE_DEPENDS "*.h")
file(GLOB cpp_source CONFIGURE_DEPENDS "*.cpp")
file(GLOB cu_source CONFIGURE_DEPENDS "*.cu")

target_sources(SimulationLib PRIVATE ${cpp_source} PUBLIC ${headers_src})

target_include_directories(SimulationLib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

# TODO: Add tests and install targets if needed.
if(USE_CUDA)
    if(NOT DEFINED CMAKE_CUDA_STANDARD)
        set(CMAKE_CUDA_STANDARD 11)
        set(CMAKE_CUDA_STANDARD_REQUIRED ON)
    endif()
    target_include_directories(SimulationLib PRIVATE "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.2/include")
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
