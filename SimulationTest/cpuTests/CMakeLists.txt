include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

file(GLOB tests_src CONFIGURE_DEPENDS "*.cpp" "*.cu" )

add_executable(
    SimulationTestCpu
    ${tests_src}
    )
    set_target_properties(SimulationTestCpu PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(SimulationTestCpu
  PRIVATE
    SimulationLib
    gtest_main
  )

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(SimulationTestCpu
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
  )