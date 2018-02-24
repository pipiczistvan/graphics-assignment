#include "light.h"

void load_light(struct Light *light, GLuint light_target)
{
    glLightfv(GL_LIGHT0, GL_POSITION, light->position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light->ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light->diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light->specular);

    glEnable(GL_LIGHTING);
    glEnable(light_target);
}

void set_light_attribute(GLfloat attribute[], GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    attribute[0] = x;
    attribute[1] = y;
    attribute[2] = z;
    attribute[3] = w;
}

void set_light_position(struct Light *light, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    set_light_attribute(light->position, x, y, z, w);
}

void set_light_ambient(struct Light *light, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    set_light_attribute(light->ambient, x, y, z, w);
}

void set_light_diffuse(struct Light *light, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    set_light_attribute(light->diffuse, x, y, z, w);
}

void set_light_specular(struct Light *light, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    set_light_attribute(light->specular, x, y, z, w);
}
