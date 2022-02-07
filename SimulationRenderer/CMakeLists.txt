file(GLOB cpp_headers CONFIGURE_DEPENDS "*.h")
file(GLOB cpp_source CONFIGURE_DEPENDS "*.cpp")

add_executable (SimulationRenderer 
    ${cpp_source} 
    ${cpp_headers} 
    "resource/resource.rc"
)

# TODO: configure these dependencies dynamically from https://www.transmissionzero.co.uk/software/freeglut-devel
set(GLUT_INCLUDE_DIR "lib/freeglut/include/GL")
set(OPENGL_LIBRARY_DIR  "lib/freeglut/lib/x64")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( 
    ${OPENGL_INCLUDE_DIRS}  
    ${GLUT_INCLUDE_DIR} 
    "lib/freeglut/bin/x64"
)

target_link_libraries(SimulationRenderer 
    SimulationCommon
    SimulationRendererLib
    ${OPENGL_LIBRARIES} 
    ${GLUT_LIBRARIES}
)
