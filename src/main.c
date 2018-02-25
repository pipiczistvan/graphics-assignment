#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>

#include "core/display.h"
#include "core/input.h"
#include "core/time.h"

#include "engine/camera.h"
#include "engine/light.h"
#include "engine/draw.h"
#include "engine/entity/entity.h"
#include "engine/entity/height_map.h"

struct Entity tigerEntity;
struct Entity skyboxEntity;
struct Light light;
struct HeightMap terrain;

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
    //tigerEntity.rotation[1] += 10.0 * delta;
    //tigerEntity.rotation[2] += 10.0 * delta;

    skyboxEntity.rotation[1] += 1.0 * delta;

    draw_height_map(&terrain);
    draw_entity(&tigerEntity);
    draw_entity(&skyboxEntity);

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

    set_height_map(&terrain, "res/terrain.png", "res/grass.png", 96.0 / 256.0);
    set_height_map_scale(&terrain, 256.0, 96.0, 256.0);
    set_height_map_position(&terrain, -128.0, 0.0, -128.0);

    set_entity(&tigerEntity, "res/tiger.obj", "res/tiger.png", &GOLD);
    set_entity_scale(&tigerEntity, 0.001, 0.001, 0.001);
    set_entity_position(&tigerEntity, 10.0, 0.0, 0.0);

    set_entity(&skyboxEntity, "res/skybox.obj", "res/skybox.png", &DEFAULT);
    set_entity_scale(&skyboxEntity, 500.0, 500.0, 500.0);

    glutDisplayFunc(display_handler);

    glutMainLoop();

    return 0;
}
