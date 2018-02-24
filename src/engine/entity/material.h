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

void load_material(struct Material *material);

void set_material_ambient(struct Material *material, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

void set_material_diffuse(struct Material *material, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

void set_material_specular(struct Material *material, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

void set_material_shininess(struct Material *material, GLfloat x);

#endif // MATERIAL_H