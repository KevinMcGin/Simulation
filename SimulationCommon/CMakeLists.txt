file(GLOB_RECURSE  cpp_headers CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE  cpp_source CONFIGURE_DEPENDS "*.cpp")

add_library(SimulationCommon STATIC ${cpp_headers} ${cpp_source})

target_include_directories(SimulationCommon
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)