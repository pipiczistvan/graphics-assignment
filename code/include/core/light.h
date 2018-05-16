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

/**
 * Load a light.
 */
void load_light(struct Light *light, const GLuint light_target);

/**
 * Set light position.
 */
void set_light_position(struct Light *light, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w);

/**
 * Set light ambient value.
 */
void set_light_ambient(struct Light *light, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w);

/**
 * Set light diffuse value.
 */
void set_light_diffuse(struct Light *light, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w);

/**
 * Set light specular value.
 */
void set_light_specular(struct Light *light, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w);

#endif // LIGHT_H