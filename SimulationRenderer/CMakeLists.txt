file(GLOB cpp_headers CONFIGURE_DEPENDS "*.h")
file(GLOB cpp_source CONFIGURE_DEPENDS "*.cpp")

add_executable (SimulationRenderer ${cpp_source} ${cu_source} ${cpp_headers} ${cu_headers}
    "lib/json/json.h" "lib/json/json-forwards.h" "lib/json/jsoncpp.cpp"
)

find_package(OpenGL REQUIRED)
# TODO: configure these directories
set(GLUT_INCLUDE_DIR "F:/Program Files/freeglut/include/GL")
set(OPENGL_LIBRARY_DIR  "F:/Program Files/freeglut/lib/x64")
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIR} "F:/Program Files/freeglut/bin/x64")

target_link_libraries(SimulationRenderer ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
