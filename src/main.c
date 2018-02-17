#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>

#include "core/window.h"
#include "core/input.h"

#include "engine/model.h"
#include "engine/draw.h"
#include "engine/camera.h"

#define CAMERA_SPEED 1.0

struct Model model;
struct Camera camera;
int time;
typedef GLubyte Pixel[3]; /*represents red green blue*/

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

void initialize_texture(char* filename)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    int width;
    int height;

    unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
            (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

	glEnable(GL_TEXTURE_2D);
}

void display_handler()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    double elapsed_time = calc_elapsed_time();
    update_camera_position(&camera, elapsed_time);
    set_view_point(&camera);

    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.05);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(0.001, 0.001, 0.001);
    draw_model(&model);
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

    initialize_texture("res/lego.png");
}

int main(int argc, char* argv[])
{
    load_model("res/lego.obj", &model);
    print_bounding_box(&model);

    glutInit(&argc, argv);
    
    init_window(640, 480, "Graphics assignment");
    init_input(callback);
    init_camera(&camera);
    init_gl();
    
    glutDisplayFunc(display_handler);

    glutMainLoop();

    return 0;
}
