#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glut.h>

struct Texture
{
    GLuint id;
};

/**
 * Loads an image as texture.
 */
void load_texture(const char *file, struct Texture *texture);

#endif // TEXTURE_H