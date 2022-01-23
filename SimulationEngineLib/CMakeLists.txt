file(GLOB_RECURSE  cpp_headers CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE  cpp_source CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE  cu_headers CONFIGURE_DEPENDS "*.cuh")
file(GLOB_RECURSE  cu_source CONFIGURE_DEPENDS "*.cu")

add_library(SimulationEngineLib STATIC ${cpp_source} ${cu_source} ${cpp_headers} ${cu_headers})
set_target_properties(SimulationEngineLib PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
set_target_properties(SimulationEngineLib PROPERTIES CUDA_RESOLVE_DEVICE_SYMBOLS ON)

target_include_directories(SimulationEngineLib
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(SimulationEngineLib
  PUBLIC
  SimulationCommon
)

if(NOT DEFINED CMAKE_CUDA_STANDARD)
    set(CMAKE_CUDA_STANDARD 11)
    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
endif()

if (CUDA_FOUND)
    message("CUDA found")
    #include(FindCUDA)
    INCLUDE_DIRECTORIES(${CUDA_INCLUDE_DIRS})
    target_include_directories(SimulationEngineLib PUBLIC ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

else()
    message("CUDA not found")
endif()
