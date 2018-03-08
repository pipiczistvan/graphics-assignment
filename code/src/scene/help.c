#include "scene/help.h"

#include "core/texture.h"

struct Texture help_texture;

void draw_help()
{
    glBindTexture(GL_TEXTURE_2D, help_texture.id);
    glPushMatrix();
    {
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);

        glTexCoord2f(1, 0);
        glVertex3f(1, 0, 0);

        glTexCoord2f(1, 1);
        glVertex3f(1, 1, 0);

        glTexCoord2f(0, 1);
        glVertex3f(0, 1, 0);
        glEnd();
    }
    glPopMatrix();
}

void init_help()
{
    load_texture("res/help.png", &help_texture);
}