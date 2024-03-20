file(GLOB_RECURSE  cpp_headers CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE  cpp_source CONFIGURE_DEPENDS "*.cpp")

add_library(SimulationRendererLib STATIC ${cpp_source} ${cpp_headers})

# Download RapidJSON
include(ExternalProject)
ExternalProject_Add(
    rapidjson
    PREFIX "vendor/rapidjson"
    GIT_REPOSITORY "https://github.com/Tencent/rapidjson.git"
    GIT_TAG 060c348ea09a4b11df12342a7cb5995a94059c4e
    TIMEOUT 10
    CMAKE_ARGS
        -DRAPIDJSON_BUILD_TESTS=OFF
        -DRAPIDJSON_BUILD_DOC=OFF
        -DRAPIDJSON_BUILD_EXAMPLES=OFF
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
)

# Prepare RapidJSON (RapidJSON is a header-only library)
ExternalProject_Get_Property(rapidjson source_dir)
set(RAPIDJSON_INCLUDE_DIR ${source_dir}/include)

add_dependencies(SimulationRendererLib rapidjson)

target_include_directories(SimulationRendererLib
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/vendor/rapidjson/src/rapidjson/include
)

target_link_libraries(SimulationRendererLib
  PUBLIC
  SimulationCommon
)