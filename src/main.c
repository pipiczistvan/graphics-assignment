#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>

#include "core/display.h"
#include "core/input.h"

#include "engine/model.h"
#include "engine/draw.h"
#include "engine/camera.h"
#include "engine/texture.h"

struct Model model;
int time;

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

    double delta = calc_elapsed_time();
    update_camera(delta);

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
        close_display();
    }
}

void passive_motion_func_callback(int a, int b)
{
    rotate_camera(a, b);
}

int main(int argc, char* argv[])
{
    load_model("res/lego.obj", &model);
    print_bounding_box(&model);

    glutInit(&argc, argv);
    
    init_display(640, 480, "Graphics assignment");
    init_input(passive_motion_func_callback);
    init_camera();
    load_texture("res/lego.png");
    
    glutDisplayFunc(display_handler);

    glutMainLoop();

    return 0;
}
