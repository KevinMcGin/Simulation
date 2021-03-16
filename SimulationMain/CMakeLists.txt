add_executable (SimulationMain main.cu)
set_target_properties(SimulationMain PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(SimulationMain
  PRIVATE
  SimulationLib
  )