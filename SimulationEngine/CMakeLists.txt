add_executable (SimulationEngine main.cpp)
set_target_properties(SimulationEngine PROPERTIES CUDA_SEPARABLE_COMPILATION ON)


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/cargs) 

target_link_libraries(SimulationEngine
  PRIVATE
  SimulationLib
  cargs
)
