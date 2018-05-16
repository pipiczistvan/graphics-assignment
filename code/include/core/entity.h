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

/**
 * Initialize the entity.
 */
void set_entity(struct Entity *entity, const char* model, const char* texture, struct Material *material);

/**
 * Move the entity to the given position.
 */
void move_entity(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z);

/**
 * Rotate the entity by the given angles.
 */
void rotate_entity(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z);

/**
 * Scale the entity.
 */
void scale_entity(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z);

#endif // ENTITY_H