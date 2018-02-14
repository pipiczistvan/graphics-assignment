#include <GL/glut.h>
#include <stdio.h>
#include "window.h"
#include "input.h"
#include "camera.h"

#define CAMERA_SPEED 1.0

struct Camera camera;
int time;

void update_camera_position(struct Camera* camera, double elapsed_time)
{
    double distance;

    distance = elapsed_time * CAMERA_SPEED;

    if (keyboard.W == PRESSED) {
		move_camera_forward(camera, distance);
    }

    if (keyboard.S == PRESSED) {
		move_camera_backward(camera, distance);
    }

    if (keyboard.A == PRESSED) {
	    step_camera_left(camera, distance);
    }

    if (keyboard.D == PRESSED) {
		step_camera_right(camera, distance);
    }
}

double calc_elapsed_time()
{
    int current_time;
    double elapsed_time;
    
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - time) / 1000.0;
    time = current_time;

    return elapsed_time;
}

void display_handler()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    double elapsed_time = calc_elapsed_time();
    update_camera_position(&camera, elapsed_time);
    set_view_point(&camera);

    glPushMatrix();
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f( 1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);

    // Bottom face (y = -1.0f)
    glColor3f(1.0f, 0.5f, 0.0f);     // Orange
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Front face  (z = 1.0f)
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);

    // Back face (z = -1.0f)
    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    // Left face (x = -1.0f)
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    // Right face (x = 1.0f)
    glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube
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
    rotate_camera(&camera, a, b);
}

void init_gl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    
    init_window(640, 480, "Graphics assignment");
    init_input(callback);
    init_camera(&camera);
    init_gl();
    
    glutDisplayFunc(display_handler);

    glutMainLoop();

    return 0;
}
