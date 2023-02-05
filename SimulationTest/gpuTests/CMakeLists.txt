file(GLOB tests_src CONFIGURE_DEPENDS "*.cpp" "*.cu" )

add_executable(
    SimulationTestGpu
    ${tests_src}
  )
  
if(USE_GPU)    
  set_target_properties(SimulationTestCpu PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
endif()

target_link_libraries(SimulationTestGpu
  PRIVATE
    SimulationEngineLib
    SimulationCommon
    SimulationTestCommon
    gtest_main
)

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(SimulationTestGpu
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
)