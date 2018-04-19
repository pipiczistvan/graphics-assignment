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
double degree_to_radian(double degree);

/**
 * Generate random double value on [a, b) interval.
 */
double random_double(double a, double b);

double radian_to_degree(double radian);

double barry_centric(double p1_x, double p1_y,double p1_z,
                    double p2_x, double p2_y,double p2_z,
                    double p3_x, double p3_y,double p3_z,
                    double pos_x, double pos_y);

#endif /* UTILS_H */
