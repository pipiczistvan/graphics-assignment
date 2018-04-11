#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glut.h>
#include <obj/model.h>

#include "core/texture.h"
#include "core/material.h"
#include "core/utils.h"

struct Entity
{
    struct Vector3d position;
    struct Vector3d rotation;
    struct Vector3d scale;
    struct Model model;
    struct Texture texture;
    struct Material material;
};

void set_entity(struct Entity *entity, const char* model, const char* texture, struct Material *material);

void set_entity_position(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z);

void set_entity_rotation(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z);

void set_entity_scale(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z);

#endif // ENTITY_H