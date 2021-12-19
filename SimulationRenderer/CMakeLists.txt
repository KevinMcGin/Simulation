file(GLOB cpp_headers CONFIGURE_DEPENDS "*.h")
file(GLOB cpp_source CONFIGURE_DEPENDS "*.cpp")

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

add_executable (SimulationRenderer ${cpp_source} ${cu_source} ${cpp_headers} ${cu_headers}
)

add_dependencies(SimulationRenderer rapidjson)

# TODO: configure these dependencies dynamically from https://www.transmissionzero.co.uk/software/freeglut-devel
set(GLUT_INCLUDE_DIR "lib/freeglut/include/GL")
set(OPENGL_LIBRARY_DIR  "lib/freeglut/lib/x64")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( 
    ${OPENGL_INCLUDE_DIRS}  
    ${GLUT_INCLUDE_DIR} 
    "${CMAKE_CURRENT_BINARY_DIR}/vendor/rapidjson/src/rapidjson/include" 
    "lib/freeglut/bin/x64"
)

target_link_libraries(SimulationRenderer ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
