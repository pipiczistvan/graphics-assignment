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
#include "scene/help.h"

int show_help = FALSE;
int help_pressed = FALSE;

void display_world()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    double delta = calc_elapsed_time();
    update_world(delta);
    update_camera(&terrain, delta);
    
    draw_world();

    glutSwapBuffers();
}

void display_help()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    draw_help();

    glutSwapBuffers();
}

void display_handler()
{
    if (show_help == TRUE)
    {
        display_help();
    } else {
        display_world();
    }

    if (keyboard.F1 == PRESSED)
    {
        if (help_pressed == FALSE)
        {
            help_pressed = TRUE;
            if (show_help == TRUE)
            {
                show_help = FALSE;
                set_display_mode(PERSPECTIVE);
            } else {
                show_help = TRUE;
                set_display_mode(ORTHO);
            }
        }
    } else {
        help_pressed = FALSE;
    }

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
    init_help();

    glutDisplayFunc(display_handler);

    glutMainLoop();

    return 0;
}
