include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

file(GLOB cpp_headers CONFIGURE_DEPENDS "*.h")
file(GLOB cpp_source CONFIGURE_DEPENDS "*.cpp")

add_library(SimulationTestCommon STATIC ${cpp_source} ${cpp_headers})
if(USE_GPU)    
  set_target_properties(SimulationTestCommon PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
  set_target_properties(SimulationTestCommon PROPERTIES CUDA_RESOLVE_DEVICE_SYMBOLS ON)
endif()

target_include_directories(SimulationTestCommon
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

if(USE_GPU)
  if(NOT DEFINED CMAKE_CUDA_STANDARD)
      set(CMAKE_CUDA_STANDARD 11)
      set(CMAKE_CUDA_STANDARD_REQUIRED ON)
  endif()

  if (CUDA_FOUND)
      message("CUDA found")
      #include(FindCUDA)
      INCLUDE_DIRECTORIES(${CUDA_INCLUDE_DIRS})
      target_include_directories(SimulationTestCommon PUBLIC ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

  else()
      message("CUDA not found")
  endif()
endif()

target_link_libraries(SimulationTestCommon
  PRIVATE
    SimulationEngineLib
  PUBLIC
    gtest_main
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-error")
