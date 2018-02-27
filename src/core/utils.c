#include "utils.h"

#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

int time;

double calc_elapsed_time()
{
    int current_time;
    double elapsed_time;
    
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - time) / 1000.0;
    time = current_time;

    return elapsed_time;
}

double calc_vector_length(const struct Vector3d* vector)
{
    double s;
    double length;

    s = vector->x * vector->x + vector->y * vector->y + vector->z * vector->z;
    length = sqrt(s);

    return length;
}

void normalize_vector(struct Vector3d* vector)
{
    double length;

    length = calc_vector_length(vector);

    if (length != 0.0) {
        vector->x /= length;
        vector->y /= length;
        vector->z /= length;
    }
}

double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

double random_double(double a, double b)
{
    return a + (double)(rand() / RAND_MAX) * (b - a);
}
