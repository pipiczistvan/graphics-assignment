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
struct Material RED_RUBBER =
{
    { 0.05, 0.0, 0.0, 1.0 },
    { 0.5, 0.4, 0.4, 1.0 },
    { 0.7, 0.04, 0.04, 1.0 },
    { 0.078125 }			
};
struct Material BRONZE =
{
    { 0.2125, 0.1275, 0.054, 1.0 },
    { 0.714, 0.4284, 0.18144, 1.0 },
    { 0.393548, 0.271906, 0.166721, 1.0 },
    { 0.2 }
};
struct Material GREEN_RUBBER =
{	
    { 0.0, 0.05, 0.0, 1.0 },
    { 0.4, 0.5, 0.4, 1.0 },
    { 0.04, 0.7, 0.04, 1.0 },
    { 0.078125 }
};
struct Material GREEN_PLASTIC =
{	
    { 0.0, 0.0, 0.0, 1.0 },
    { 0.1, 0.35, 0.1, 1.0 },
    { 0.45, 0.55, 0.45, 1.0 },
    { 0.25 }
};
struct Material OBSIDIAN =
{	
    { 0.05375, 0.05, 0.06625, 1.0 },
    { 0.18275, 0.17, 0.22525, 1.0 },
    { 0.332741, 0.328634, 0.346435, 1.0 },
    { 0.3 }
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
