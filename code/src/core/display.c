#include "core/display.h"

#include <GL/glut.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

int window;
int projection = PERSPECTIVE;
GLsizei width, height;

// PRIVATE

void redisplay()
{
    glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    if (projection == PERSPECTIVE)
    {
	    gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);
        glEnable(GL_DEPTH_TEST);
    } else {
	    gluOrtho2D(0.0, 1.0, 1.0, 0.0);
        glDisable(GL_DEPTH_TEST);
    }
}

void reshape(GLsizei w, GLsizei h)
{
    width = w;
    height = h;

    redisplay();
}

void initialize()
{
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
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

void set_display_mode(int mode)
{
    projection = mode;
    redisplay();
}
