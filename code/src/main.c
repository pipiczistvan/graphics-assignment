#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "core/display.h"
#include "core/input.h"
#include "core/utils.h"
#include "core/camera.h"
#include "core/draw.h"
#include "core/entity.h"
#include "scene/world.h"

void display_handler()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    double delta = calc_elapsed_time();
    update_world(delta);
    update_camera(&terrain, delta);

    draw_world();

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
    srand(time(0));
    
    glutInit(&argc, argv);
    
    init_display(640, 480, "Graphics assignment");
    init_input(passive_motion_func_callback);
    init_camera();
    init_world();

    glutDisplayFunc(display_handler);

    glutMainLoop();

    return 0;
}
