#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>

#include "core/display.h"
#include "core/input.h"

#include "engine/model.h"
#include "engine/draw.h"
#include "engine/camera.h"
#include "engine/texture.h"
#include "engine/light.h"
#include "engine/material.h"

struct Model model;
struct Texture texture;
struct Material material;
struct Light light;
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

void set_lightings()
{
    set_light_position(&light, -3.0, 0.0, 3.0, 0.0);
    set_light_ambient(&light, 0.1, 0.1, 0.1, 0.0);
    set_light_diffuse(&light, 0.7, 0.7, 0.7, 0.0);
    set_light_specular(&light, 1.0, 1.0, 1.0, 0.0);

    load_light(&light, GL_LIGHT0);
}

void set_materials()
{
    set_material_ambient(&material, 0.24725, 0.1995, 0.0745, 1.0);
    set_material_diffuse(&material, 0.75164, 0.60648, 0.22648, 1.0);
    set_material_specular(&material, 0.628281, 0.555802, 0.366065, 1.0);
    set_material_shininess(&material, 51.2);
}

void display_handler()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    double delta = calc_elapsed_time();
    update_camera(delta);

    glPushMatrix();
    {
        load_material(&material);

        glTranslatef(5.0, 0.0, -0.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glRotatef(-90, 0.0, 1.0, 0.0);
        //glScalef(0.001, 0.001, 0.001);

        glBindTexture(GL_TEXTURE_2D, texture.id);
        draw_model(&model);
        //draw_normals(&model, 1.0);
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

    load_model("res/tiger.obj", &model);
    scale_model(&model, 0.001, 0.001, 0.001);
    print_model_info(&model);
    print_bounding_box(&model);
    load_texture("res/tiger.png", &texture);
    set_lightings();
    set_materials();
    
    glutDisplayFunc(display_handler);

    glutMainLoop();

    return 0;
}
