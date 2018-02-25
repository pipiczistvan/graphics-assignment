#ifndef UTILS_H
#define UTILS_H

#define TRUE 1
#define FALSE 0

typedef unsigned char Pixel[3];

struct Vector3d
{
    double x;
    double y;
    double z;
};

/**
 * Calculate the length of the vector.
 */
double calc_vector_length(const struct Vector3d* vector);

/**
 * Normalize the vector.
 */
void normalize_vector(struct Vector3d* vector);

/**
 * Calculates radian from degree.
 */
double degree_to_radian(double degree);

/**
 * Generate random double value on [a, b) interval.
 */
double random_double(double a, double b);

#endif /* UTILS_H */
