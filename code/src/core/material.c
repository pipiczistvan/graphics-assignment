#include "core/material.h"

struct Material GOLD =
{
    { 0.24725, 0.1995, 0.0745, 1.0 },
    { 0.75164, 0.60648, 0.22648, 1.0 },
    { 0.628281, 0.555802, 0.366065, 1.0 },
    { 51.2 }
};
struct Material JADE =
{
    { 0.135, 0.2225, 0.1575, 0.95 },
    { 0.54,	0.89, 0.63, 0.95 },
    { 0.316228,	0.316228, 0.316228,	0.95 },
    { 12.8 }
};
struct Material DEFAULT =
{
    { 1.0, 1.0, 1.0, 1.0 },
    { 0.0, 0.0, 0.0, 1.0 },
    { 0.0, 0.0, 0.0, 1.0 },
    { 1.0 }
};

void load_material(struct Material *material)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material->shininess);
}

void set_material_attribute(GLfloat attribute[], GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    attribute[0] = x;
    attribute[1] = y;
    attribute[2] = z;
    attribute[3] = w;
}

void set_material_ambient(struct Material *material, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    set_material_attribute(material->ambient, x, y, z, w);
}

void set_material_diffuse(struct Material *material, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    set_material_attribute(material->diffuse, x, y, z, w);
}

void set_material_specular(struct Material *material, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    set_material_attribute(material->specular, x, y, z, w);
}

void set_material_shininess(struct Material *material, GLfloat x)
{
    material->shininess[0] = x;
}
