add_executable (SimulationMain main.cu)
set_target_properties(SimulationMain PROPERTIES CUDA_SEPARABLE_COMPILATION ON)


  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/cargs) 

target_link_libraries(SimulationMain
  PRIVATE
  SimulationLib
  cargs
  )
