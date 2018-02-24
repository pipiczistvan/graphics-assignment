#include "material.h"

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
