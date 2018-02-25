#ifndef HEIGHT_MAP_H
#define HEIGHT_MAP_H

#include <GL/glut.h>

#include "texture.h"
#include "../../core/utils.h"

struct HeightMap
{
    GLfloat position[3];
    GLfloat rotation[3];
    GLfloat scale[3];
    struct Texture texture;
    int n_rows;
    int n_columns;
    double* heights;
    struct Vector3d* normals;
};

/**
 * Load height map from image file.
 */
void set_height_map(struct HeightMap* height_map, const char* filename, const char* texture, double unit);

/**
 * Calculate the height values of the height map from image.
 */
void calc_height_map_heights(struct HeightMap* height_map, Pixel* image);

/**
 * Get the height of the map at the given point.
 */
double get_height_map_value(const struct HeightMap* height_map, int row, int column);

/**
 * Get the normal vector at the given point.
 */
void get_height_map_normal(
    const struct HeightMap* height_map,
    int row, int column,
    struct Vector3d* normal);

/**
 * Calculate height map surface normal vectors.
 */
void calc_height_map_normals(struct HeightMap* height_map, double unit);

/**
 * Free the allocated memory.
 */
void free_height_map(struct HeightMap* height_map);

void set_height_map_position(struct HeightMap* height_map, GLfloat x, GLfloat y, GLfloat z);

void set_height_map_rotation(struct HeightMap* height_map, GLfloat x, GLfloat y, GLfloat z);

void set_height_map_scale(struct HeightMap* height_map, GLfloat x, GLfloat y, GLfloat z);

#endif // HEIGHT_MAP_H
