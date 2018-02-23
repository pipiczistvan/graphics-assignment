#include "light.h"

void load_light(struct Light *light, GLuint light_target)
{
    glLightfv(GL_LIGHT0, GL_POSITION, light->light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light->light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light->light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light->light_specular);

    glEnable(GL_LIGHTING);
    glEnable(light_target);
}

void set_light_attribute(GLfloat attribute[], GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    attribute[0] = x;
    attribute[1] = y;
    attribute[2] = z;
    attribute[3] = w;
}
