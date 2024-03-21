#ifdef _WIN32
#include <windows.h>  // For MS Windows
#endif
#include <glut.h>  // GLUT, includes glu.h and gl.h
#include <chrono>
#include <memory>

#include "InputJson.h"
#include "util/Timing.h"

void display_scene();
        

char name[] = "Simulation Renderer";

unsigned int frameRate = 60;
float frameTime = 1.f / frameRate;

std::unique_ptr<InputJson> input;
Timing timing = Timing();
float slackTime = 0.f;

int main(int argc, char** argv) {
    std::cout << "Renderer running" << std::endl;

    const char* inputFile = argc > 1 ? argv[1] : "simulation_output/simulation_output.json";

    input = std::make_unique<InputJson>(inputFile);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(name);
    timing.setTime();
    glClearColor(0., 0., 0., 1.);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    GLfloat lightZeroPosition[] = {0.0f, 0.0f, 10000.0f, 1.0f};
    GLfloat lightZeroColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
    // glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.01f);
    // glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.008f);
    glEnable(GL_LIGHT0);
    glutDisplayFunc(display_scene);
    glutIdleFunc(display_scene);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(100., 1920.0/1080.0, 1., 40.);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 5,
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
    GLfloat color[][10] = {
        {1.0, 1.0 , 1.0, 1.0},
        {0.15, 0.15, 0.15, 1.0},
        {0.7, 0.7, 0.7, 1.0},
        {0.1875, 0.4180, 0.4141, 1.0},
        {0.6016, 0.2422, 0.0039, 1.0},
        {0.6914, 0.50, 0.2109, 1.0},
        {0.6914, 0.5625, 0.2148, 1.0},
        {0.3359, 0.5039, 0.6680, 1.0},
        {0.2148, 0.4102, 0.5898, 1.0},
        {1.0, 0.62 , 0.0, 1.0},
    };
    int i = 0;
    for(const auto& p : particles->GetArray()) {
        GLfloat scale = 1.0 / 1.0;
        GLfloat pScale = 1.0 / 700000000000.0;
        GLfloat pR = p["r"].GetFloat();
        float radius;
        if (i == 0)
            radius = pR * 0.03 / 696340000.0;
        else 
           radius = pR * 0.05 / 6371000.0;
        glMaterialfv(GL_FRONT, GL_DIFFUSE, color[i++]);
        glPushMatrix();
        glTranslatef(p["pos"][0].GetFloat() * pScale, p["pos"][1].GetFloat() * pScale, p["pos"][2].GetFloat() * pScale);
        glColor3f(1, 1, 1);
        glScalef(scale,scale, scale);
        glutSolidSphere(radius, 50, 50);
        glPopMatrix();
    }

    glutSwapBuffers();
}
    
