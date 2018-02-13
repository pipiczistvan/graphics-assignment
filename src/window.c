#include "window.h"
#include <GL/glut.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport (x, y, w, h);
}

void initialize()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        3.0, 3.0, 4.0, // eye
        0.0, 0.0, 0.0, // look at
        0.0, 0.0, 1.0  // up
    );

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10.0);
}

void create_window(int width, int height, char* title, void (*display))
{
    glutInitWindowSize(width, height);     
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    int window = glutCreateWindow(title);
    glutSetWindow(window);

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
}
