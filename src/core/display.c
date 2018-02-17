#include "display.h"
#include <GL/glut.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

int window;

// PRIVATE

void reshape(GLsizei width, GLsizei height)
{
	glViewport (0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);
}

void initialize()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
        0.0, 0.0, -200, // eye
        0.0, 0.0, 0.0, // look at
        0.0, 1.0, 0.0  // up
    );

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glClearDepth(1.0);
}

int create_window(int width, int height, char* title)
{
    glutInitWindowSize(width, height);     
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    int window = glutCreateWindow(title);
    glutSetWindow(window);

    return window;
}

// PUBLIC

void init_display(int width, int height, char* title)
{
    window = create_window(width, height, title);

    initialize();

    glutReshapeFunc(reshape);
}

void close_display()
{
    glutDestroyWindow(window);
}
