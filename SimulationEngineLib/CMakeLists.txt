file(GLOB_RECURSE  cpp_headers CONFIGURE_DEPENDS "cpp/*/*.h")
file(GLOB_RECURSE  cpp_source CONFIGURE_DEPENDS "cpp/*/*.cpp")
file(GLOB_RECURSE  cu_shared_headers CONFIGURE_DEPENDS "shared/*/*.cuh")
file(GLOB_RECURSE  cu_shared_source CONFIGURE_DEPENDS "shared/*/*.cu")
file(GLOB_RECURSE  cpp_shared_source CONFIGURE_DEPENDS "shared/*/*.cpp")
file(GLOB_RECURSE  cu_headers CONFIGURE_DEPENDS "cuda/*/*.cuh")
file(GLOB_RECURSE  cu_source CONFIGURE_DEPENDS "cuda/*/*.cu")
file(GLOB_RECURSE  gpu_mock_headers CONFIGURE_DEPENDS "gpuMock/*/*.cuh")
file(GLOB_RECURSE  gpu_mock_source CONFIGURE_DEPENDS "gpuMock/*/*.cu")


if (USE_GPU)
  add_library(SimulationEngineLib STATIC 
    ${cpp_source} 
    ${cu_shared_source} 
    ${cu_source} 
    ${cpp_headers} 
    ${cu_shared_headers} 
    ${cu_headers}
  )
else()
  add_library(SimulationEngineLib STATIC
    ${cpp_source} 
    ${cu_shared_source} 
    ${cpp_shared_source} 
    ${cpp_shared_source} 
    ${gpu_mock_source}
    ${cpp_headers}
    ${cu_shared_headers}
    ${gpu_mock_headers}
  ) 
  set_source_files_properties(${cu_shared_headers} ${gpu_mock_headers} PROPERTIES LANGUAGE CXX)
  set_source_files_properties(${cu_shared_source} ${gpu_mock_source} PROPERTIES LANGUAGE CXX)
  add_definitions("-xc++")
endif()

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
