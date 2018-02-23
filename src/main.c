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

void set_lightings()
{
    GLfloat light_position[] = { -3.0, 0.0, 3.0, 0.0 };
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 0 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 0 };
    GLfloat light_specular[] = { 1, 1, 1, 0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void display_handler()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    double delta = calc_elapsed_time();
    update_camera(delta);

    glPushMatrix();
    {
        GLfloat material_ambient[] = { 0.24725, 0.1995, 0.0745, 1 };
        GLfloat material_diffuse[] = { 0.75164, 0.60648, 0.22648, 1 };
        GLfloat material_specular[] = { 0.628281, 0.555802, 0.366065, 1 };
        GLfloat material_shininess[] = { 51.2 };

        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

        glTranslatef(5.0, 0.0, -0.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glRotatef(-90, 0.0, 1.0, 0.0);
        //glScalef(0.001, 0.001, 0.001);

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
    load_texture("res/tiger.png");
    set_lightings();
    
    glutDisplayFunc(display_handler);

    glutMainLoop();

    return 0;
}
