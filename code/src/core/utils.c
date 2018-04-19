#include "core/utils.h"

#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

int t;

double calc_elapsed_time()
{
    int current_time;
    double elapsed_time;
    
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - t) / 1000.0;
    t = current_time;

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

double radian_to_degree(double radian)
{
    return radian / M_PI * 180.0;
}

double random_double(double a, double b)
{
    return a + (double)(rand() / RAND_MAX) * (b - a);
}

double barry_centric(double p1_x, double p1_y,double p1_z,
                    double p2_x, double p2_y,double p2_z,
                    double p3_x, double p3_y,double p3_z,
                    double pos_x, double pos_y)
{
    double det = (p2_z - p3_z) * (p1_x - p3_x) + (p3_x - p2_x) * (p1_z - p3_z);
    double l1 = ((p2_z - p3_z) * (pos_x - p3_x) + (p3_x - p2_x) * (pos_y - p3_z)) / det;
    double l2 = ((p3_z - p1_z) * (pos_x - p3_x) + (p1_x - p3_x) * (pos_y - p3_z)) / det;
    double l3 = 1.0f - l1 - l2;
    return l1 * p1_y + l2 * p2_y + l3 * p3_y;
}