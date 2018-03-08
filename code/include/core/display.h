#ifndef DISPLAY_H
#define DISPLAY_H

#define PERSPECTIVE 0
#define ORTHO 1

void init_display(int width, int height, char* title);

void close_display();

void set_display_mode(int mode);

#endif // DISPLAY_H
