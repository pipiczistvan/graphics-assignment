#include <GL/glut.h>
#include <stdio.h>
#include "window.h"
#include "input.h"

void display_handler()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0, 0);
    glVertex3d(-0.5, -0.5, 0.0);
    glColor3f(0, 1.0, 0);
    glVertex3d(-0.5, 0.5, 0.0);
    glColor3f(0, 0, 1.0);
    glVertex3d(0.5, 0.5, 0.0);
    glColor3f(1.0, 1.0, 0);
    glVertex3d(0.5, -0.5, 0.0);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
    if (keyboard.ESCAPE == PRESSED)
    {
        glutLeaveMainLoop();
        close_window();
    }
}

void callback(int a, int b)
{
    printf("%d, %d\n", a, b);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    
    init_window(640, 480, "Graphics assignment");
    init_input(callback);
    
    glutDisplayFunc(display_handler);

    glutMainLoop();

    return 0;
}
