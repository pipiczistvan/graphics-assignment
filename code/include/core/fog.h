#ifndef FOG_H
#define FOG_H

#include <GL/glut.h>

struct Fog
{
    GLfloat color[4];
    GLfloat density;
};

#endif // MATERIAL_H