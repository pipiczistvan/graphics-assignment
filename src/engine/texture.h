#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glut.h>

struct Texture
{
    GLuint id;
};

void load_texture(char *file, struct Texture *texture);

#endif // TEXTURE_H