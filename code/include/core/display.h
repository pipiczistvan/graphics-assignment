#ifndef DISPLAY_H
#define DISPLAY_H

#define PERSPECTIVE 0
#define ORTHO 1

/**
 * Initialize display.
 */
void init_display(const int width, const int height, const char* title);

/**
 * Close the display, and free memory.
 */
void close_display();

/**
 * Set the display mode. (PERSPECTIVE, ORTHO)
 */
void set_display_mode(const int mode);

#endif // DISPLAY_H
