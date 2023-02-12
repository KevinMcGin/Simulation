#ifdef _WIN32
#include <windows.h>  // For MS Windows
#endif
#include <glut.h>  // GLUT, includes glu.h and gl.h
#include <chrono>
#include <memory>

#include "InputJSON.h"
#include "util/Timing.h"

void display_scene();
        

char* name = "Simulation Renderer";

unsigned int frameRate = 60;
float frameTime = 1.f / frameRate;

std::unique_ptr<InputJSON> input;
Timing timing = Timing();
float slackTime = 0.f;

int main(int argc, char** argv) {
    std::cout << "Renderer running" << std::endl;

    const char* inputFile = argc > 1 ? argv[1] : "simulation_output/simulation_output.json";

    input = std::make_unique<InputJSON>(inputFile);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(350, 200);
    glutCreateWindow(name);
    timing.setTime();
    glClearColor(0., 0., 0., 1.);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    GLfloat lightZeroPosition[] = {10.0f, 4.0f, 10.0f, 1.0f};
    GLfloat lightZeroColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.01f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.008f);
    glEnable(GL_LIGHT0);
    glutDisplayFunc(display_scene);
    glutIdleFunc(display_scene);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(100., 1., 1., 40.);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10,
              0, 0, 0,
              0, 1, 0);
    glPushMatrix();
    glutMainLoop();
        
    return 0;
}

void display_scene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float elapsedSeconds = timing.getTimeSeconds();
    float totalElapsedSeconds = elapsedSeconds + slackTime;
    int elapsedFrames = (int)(totalElapsedSeconds / frameTime);
    slackTime = totalElapsedSeconds - elapsedFrames * frameTime;
    timing.setTime();
    
    auto particles = input->input(elapsedFrames);
    for(const auto& p : particles->GetArray()) {
        GLfloat color[] = {1.0, 1.0, 0.0, 1.0};
        float radius = p["r"].GetFloat();
        if (p["r"].GetFloat() >= 0.1) {
            // radius = 0.01f;
            color[0] = 1.0;
            color[1] = 0.0;
            color[2] = 0.0;
        }
        glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
        glPushMatrix();
        glTranslatef(p["pos"][0].GetFloat(), p["pos"][1].GetFloat(), p["pos"][2].GetFloat());
        glColor3f(1, 1, 1);
        GLfloat scale = 1.0;
        glScalef(scale,scale, scale);
        glutSolidSphere(radius, 10, 10);
        glPopMatrix();
    }

    glutSwapBuffers();
}
    
