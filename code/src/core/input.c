#include "core/input.h"

#include "core/ASCII.h"

#include <GL/glut.h>

passive_motion_func_type passive_motion_func;

int mouse_released = FALSE;

void key_handler(unsigned char key, int x, int y)
{
	switch (key) 
    {
        case KEY_A:
            keyboard.A = PRESSED;
            break;
        case KEY_D:
            keyboard.D = PRESSED;
            break;
        case KEY_S:
            keyboard.S = PRESSED;
            break;
        case KEY_W:
            keyboard.W = PRESSED;
            break;
        case KEY_F:
            keyboard.F = PRESSED;
            break;
        case KEY_L:
            keyboard.L = PRESSED;
            break;
        case KEY_ESCAPE:
            keyboard.ESCAPE = PRESSED;
            break;
	}

	glutPostRedisplay();
}

void key_up_handler(unsigned char key, int x, int y)
{
	switch (key) 
    {
        case KEY_A:
            keyboard.A = RELEASED;
            break;
        case KEY_D:
            keyboard.D = RELEASED;
            break;
        case KEY_S:
            keyboard.S = RELEASED;
            break;
        case KEY_W:
            keyboard.W = RELEASED;
            break;
        case KEY_F:
            keyboard.F = RELEASED;
            break;
        case KEY_L:
            keyboard.L = RELEASED;
            break;
        case KEY_ESCAPE:
            keyboard.ESCAPE = RELEASED;
            break;
	}

	glutPostRedisplay();
}

void special_key_handler(int key, int x, int y)
{
    if (glutGetModifiers() & GLUT_ACTIVE_CTRL)
    {
        if (mouse_released == TRUE)
        {
            mouse_released = FALSE;
        } 
        else
        {
           mouse_released = TRUE;
        }
    }

	switch (key) 
    {
        case GLUT_KEY_F1:
            keyboard.F1 = PRESSED;
            break;
	}

	glutPostRedisplay();
}

void special_key_up_handler(int key, int x, int y)
{
	switch (key) 
    {
        case GLUT_KEY_F1:
            keyboard.F1 = RELEASED;
            break;
	}

	glutPostRedisplay();
}

void passive_motion_handler(int x, int y)
{
    if (mouse_released == FALSE)
    {
        int half_window_width = glutGet(GLUT_WINDOW_WIDTH) / 2;
        int half_window_height = glutGet(GLUT_WINDOW_HEIGHT) / 2;

        int d_x = x - half_window_width;
        int d_y = y - half_window_height;

        passive_motion_func(d_x, d_y);

        glutWarpPointer(half_window_width, half_window_height);
    }
}

void idle_handler()
{
    glutPostRedisplay();
}

void init_input(passive_motion_func_type f)
{
    glutKeyboardFunc(key_handler);
    glutKeyboardUpFunc(key_up_handler);
    glutSpecialFunc(special_key_handler);
    glutSpecialUpFunc(special_key_up_handler);
    glutPassiveMotionFunc(passive_motion_handler);
    glutIdleFunc(idle_handler);

    passive_motion_func = f;
}
