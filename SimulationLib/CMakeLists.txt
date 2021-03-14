add_library(SimulationLib)

file(GLOB cpp_headers CONFIGURE_DEPENDS "*.h")
file(GLOB cpp_source CONFIGURE_DEPENDS "*.cpp")
file(GLOB cu_headers CONFIGURE_DEPENDS "*.cu")
file(GLOB cu_source CONFIGURE_DEPENDS "*.cu")

# if(USE_CUDA)
  target_sources(SimulationLib PRIVATE ${cpp_source} ${cu_source} PUBLIC ${cpp_headers} ${cu_headers})
# else()
  # target_sources(SimulationLib PRIVATE ${cpp_source} PUBLIC ${cpp_headers})
# endif()

target_include_directories(SimulationLib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

if(NOT DEFINED CMAKE_CUDA_STANDARD)
    set(CMAKE_CUDA_STANDARD 11)
    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
endif()

if (CUDA_FOUND)
    message("CUDA found")
    SET(CUDA_INCLUDE_DIRS "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v8.0/include" ${CUDA_INCLUDE_DIRS})
    #include(FindCUDA)
    INCLUDE_DIRECTORIES($ENV{CUDA_PATH}/include)
    target_link_libraries(SimulationLib ${CUDA_LIBRARIES} ${CUDA_CUFFT_LIBRARIES} ${CUDA_CUBLAS_LIBRARIES} ${CUDA_cupti_LIBRARY} ${CUDA_curand_LIBRARY} ${CUDA_cusparse_LIBRARY} ${CUDA_npp_LIBRARY} ${CUDA_nppc_LIBRARY} ${CUDA_nppi_LIBRARY} ${CUDA_npps_LIBRARY} ${CUDA_nvcuvenc_LIBRARY} ${CUDA_nvcuvid_LIBRARY})

else()
    message("CUDA not found")
endif()


# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
#if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
 # target_compile_options(Simulation
  #  PUBLIC
   #   "--coverage"
    #)
  #target_link_options(Simulation
   # INTERFACE
    #  "--coverage"
    #)
#endif()
