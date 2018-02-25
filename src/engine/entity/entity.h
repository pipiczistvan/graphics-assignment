#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glut.h>

#include "model.h"
#include "texture.h"
#include "material.h"

struct Entity
{
    GLfloat position[3];
    GLfloat rotation[3];
    GLfloat scale[3];
    struct Model model;
    struct Texture texture;
    struct Material material;
};

void set_entity(struct Entity *entity, const char* model, const char* texture, struct Material *material);

void set_entity_position(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z);

void set_entity_rotation(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z);

void set_entity_scale(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z);

#endif // ENTITY_H