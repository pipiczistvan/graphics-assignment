#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glut.h>

struct Light
{
    GLfloat position[4];
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
};

void load_light(struct Light *light, GLuint light_target);

void set_light_position(struct Light *light, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

void set_light_ambient(struct Light *light, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

void set_light_diffuse(struct Light *light, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

void set_light_specular(struct Light *light, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

#endif // LIGHT_H