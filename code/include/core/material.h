#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glut.h>

struct Material
{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess[1];
};

struct Material GOLD;
struct Material JADE;
struct Material DEFAULT;
struct Material RED_RUBBER;
struct Material BRONZE;
struct Material GREEN_RUBBER;
struct Material GREEN_PLASTIC;
struct Material OBSIDIAN;
struct Material SILVER;

/**
 * Load a material.
 */
void load_material(const struct Material *material);

/**
 * Set material ambient value.
 */
void set_material_ambient(struct Material *material, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w);

/**
 * Set material diffuse value.
 */
void set_material_diffuse(struct Material *material, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w);

/**
 * Set material specular value.
 */
void set_material_specular(struct Material *material, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w);

/**
 * Set material shininess value.
 */
void set_material_shininess(struct Material *material, const GLfloat x);

#endif // MATERIAL_H