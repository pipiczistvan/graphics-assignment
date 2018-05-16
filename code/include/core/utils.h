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

double calc_elapsed_time();

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
double degree_to_radian(const double degree);

/**
 * Generate random double value on [a, b) interval.
 */
double random_double(const double a, const double b);

/**
 * Calculates degree from radian.
 */
double radian_to_degree(const double radian);

/**
 * Calculates bary centric value.
 */
double bary_centric(const double p1_x, const double p1_y, const double p1_z,
                    const double p2_x, const double p2_y, const double p2_z,
                    const double p3_x, const double p3_y, const double p3_z,
                    const double pos_x, const double pos_y);

#endif /* UTILS_H */
