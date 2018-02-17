#include "texture.h"

#include <GL/glut.h>
#include <SOIL/SOIL.h>

typedef GLubyte Pixel[3]; /*represents red green blue*/

void load_texture(char *file)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    int width;
    int height;

    unsigned char* image = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

	glEnable(GL_TEXTURE_2D);
}
