add_executable (SimulationEngineServer main.cpp)

if (USE_GPU)
  set_target_properties(SimulationEngineServer PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
target_include_directories(SimulationEngineServer PRIVATE ${CMAKE_CURRENT_LIST_DIR}/lib/httplib) 

target_link_libraries(SimulationEngineServer
  PRIVATE
  SimulationEngineLib
)
