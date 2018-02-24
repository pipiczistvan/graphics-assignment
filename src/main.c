#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>

#include "core/display.h"
#include "core/input.h"
#include "core/time.h"

#include "engine/camera.h"
#include "engine/light.h"
#include "engine/entity.h"

struct Entity tigerEntity;
struct Light light;

void set_lightings()
{
    set_light_position(&light, -3.0, 0.0, 3.0, 0.0);
    set_light_ambient(&light, 0.1, 0.1, 0.1, 0.0);
    set_light_diffuse(&light, 0.7, 0.7, 0.7, 0.0);
    set_light_specular(&light, 1.0, 1.0, 1.0, 0.0);

    load_light(&light, GL_LIGHT0);
}

void display_handler()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    double delta = calc_elapsed_time();
    update_camera(delta);
    //tigerEntity.rotation[0] += 10.0 * delta;
    tigerEntity.rotation[1] += 10.0 * delta;
    //tigerEntity.rotation[2] += 10.0 * delta;

    glPushMatrix();
    {
        draw_entity(&tigerEntity);
    }
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
    glutInit(&argc, argv);
    
    init_display(640, 480, "Graphics assignment");
    init_input(passive_motion_func_callback);
    init_camera();

    set_lightings();
    set_entity(&tigerEntity, "res/tiger.obj", "res/tiger.png", &JADE);
    set_entity_scale(&tigerEntity, 0.001, 0.001, 0.001);

    glutDisplayFunc(display_handler);

    glutMainLoop();

    return 0;
}
