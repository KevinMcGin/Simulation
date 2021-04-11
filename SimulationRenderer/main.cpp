#ifdef _WIN32
    #include <windows.h>  // For MS Windows
#endif
#include <glut.h>  // GLUT, includes glu.h and gl.h

#include "InputJSON.h"

// from OpenGL.GLUT import *
// from OpenGL.GLU import *
// from OpenGL.GL import *
// import sys
// from PIL import Image as Image
// import numpy
// import time
// import json

//TODO: get input

void display_scene();
// GLuint read_texture(char* filename);
        

char* name = "Navigation paradigm";

int main(int argc, char **argv) {

    InputJSON input("F:/workspace/Simulation/bin/test.json");
    input.input();


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(350, 200);
    glutCreateWindow(name);
    glClearColor(0., 0., 0., 1.);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    GLfloat lightZeroPosition[] = {10.0, 4.0, 10.0, 1.0};
    GLfloat lightZeroColor[] = {0.8, 1.0, 0.8, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);
    glEnable(GL_LIGHT0);
    glutDisplayFunc(display_scene);
    glutIdleFunc(display_scene);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(40., 1., 1., 40.);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10,
              0, 0, 0,
              0, 1, 0);
    glPushMatrix();
    glutMainLoop();
        
    
    return 0;
}

void display_scene() {
    // global sim
    // global frame
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // # Textured thing 
    // auto tex = read_texture("brick.jpg");
    auto qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, tex);
    gluSphere(qobj, 1, 50, 50);
    gluDeleteQuadric(qobj);
    glDisable(GL_TEXTURE_2D);
    
    GLfloat color[] = {0.0, 1.0, 0.0, 1.0};
    //for p in sim[str(frame)]:
    //     glPushMatrix();
    //     glTranslatef(p['pos'][0], p['pos'][1], p['pos'][2]);
    //     glColor3f(1, 0, 0);
    //     glScalef(1.0, 1.0, 1.0);
    //     glutSolidSphere(p['r'], 5, 5);
    //     glPopMatrix();
    // frame += 1;

    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    glutSwapBuffers();

    // time.sleep((1/60) * 1)
}
    
// GLuint read_texture(char* filename) {
//     auto img = Image.open(filename);
//     auto img_data = numpy.array(list(img.getdata()), numpy.int8);
//     auto textID = glGenTextures(1);
//     glBindTexture(GL_TEXTURE_2D, textID); //# This is what's missing
//     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.size[0], img.size[1], 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
//     return textID;
// }