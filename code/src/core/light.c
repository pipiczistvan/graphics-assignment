#include "core/light.h"

void load_light(struct Light *light, const GLuint light_target)
{
    glEnable(GL_LIGHTING);
    glEnable(light_target);

    glLightfv(light_target, GL_POSITION, light->position);
    glLightfv(light_target, GL_AMBIENT, light->ambient);
    glLightfv(light_target, GL_DIFFUSE, light->diffuse);
    glLightfv(light_target, GL_SPECULAR, light->specular);
}

void set_light_attribute(GLfloat attribute[], const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w)
{
    attribute[0] = x;
    attribute[1] = y;
    attribute[2] = z;
    attribute[3] = w;
}

void set_light_position(struct Light *light, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w)
{
    set_light_attribute(light->position, x, y, z, w);
}

void set_light_ambient(struct Light *light, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w)
{
    set_light_attribute(light->ambient, x, y, z, w);
}

void set_light_diffuse(struct Light *light, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w)
{
    set_light_attribute(light->diffuse, x, y, z, w);
}

void set_light_specular(struct Light *light, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w)
{
    set_light_attribute(light->specular, x, y, z, w);
}
