file(GLOB_RECURSE  cpp_headers CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE  cpp_source CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE  cu_headers CONFIGURE_DEPENDS "*.cuh")
file(GLOB_RECURSE  cu_source CONFIGURE_DEPENDS "*.cu")

if (NOT USE_GPU)
  set_source_files_properties(${cu_headers} PROPERTIES LANGUAGE CXX)
  set_source_files_properties(${cu_source} PROPERTIES LANGUAGE CXX)
  add_definitions("-xc++")
endif()


add_library(SimulationEngineLib STATIC ${cpp_source} ${cu_source} ${cpp_headers} ${cu_headers})

target_include_directories(SimulationEngineLib
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(SimulationEngineLib
  PUBLIC
  SimulationCommon
)

if (USE_GPU)
  set_target_properties(SimulationEngineLib PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
  set_target_properties(SimulationEngineLib PROPERTIES CUDA_RESOLVE_DEVICE_SYMBOLS ON)
  set(CMAKE_CUDA_STANDARD 12)
  set(CMAKE_CUDA_STANDARD_REQUIRED ON)
  if(NOT DEFINED CMAKE_CUDA20_STANDARD_COMPILE_OPTION)
    set(CMAKE_CUDA20_STANDARD_COMPILE_OPTION "")
    set(CMAKE_CUDA20_EXTENSION_COMPILE_OPTION "")
  endif()

set(CMAKE_CUDA_FLAGS "-std=c++20")


  if (CUDA_FOUND)
      message("CUDA found")
      #include(FindCUDA)
      INCLUDE_DIRECTORIES(${CUDA_INCLUDE_DIRS})
      target_include_directories(SimulationEngineLib PUBLIC ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
  else()
      message("CUDA not found")
  endif()
endif()
