file(GLOB cpp_headers CONFIGURE_DEPENDS "*.h")
file(GLOB cpp_source CONFIGURE_DEPENDS "*.cpp")

add_executable (SimulationRenderer ${cpp_source} ${cu_source} ${cpp_headers} ${cu_headers})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(SimulationRenderer ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
