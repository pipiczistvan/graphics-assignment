#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glut.h>

struct Light
{
    GLfloat light_position[4];
    GLfloat light_ambient[4];
    GLfloat light_diffuse[4];
    GLfloat light_specular[4];
};

void load_light(struct Light *light, GLuint light_target);

void set_light_attribute(GLfloat attribute[], GLfloat x, GLfloat y, GLfloat z, GLfloat w);

#endif // LIGHT_H