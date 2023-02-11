add_executable (SimulationEngine main.cpp)

if (USE_GPU)
  set_target_properties(SimulationEngine PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
endif()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/cargs) 

target_link_libraries(SimulationEngine
  PRIVATE
  SimulationEngineLib
  cargs
)
