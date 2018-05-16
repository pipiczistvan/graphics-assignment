#ifndef INPUT_H
#define INPUT_H

#define PRESSED 1
#define RELEASED 0

struct Keyboard
{
    int A;
    int D;
    int S;
    int W;
    int F;
    int L;
    int ESCAPE;
    int F1;
};

struct Mouse
{
    int x;
    int y;
};

struct Keyboard keyboard;
struct Mouse mouse;

typedef void (*passive_motion_func_type)(int, int);

/**
 * Set up the input.
 */
void init_input(passive_motion_func_type);

#endif // INPUT_H