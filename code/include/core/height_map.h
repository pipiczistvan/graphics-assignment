#ifndef HEIGHT_MAP_H
#define HEIGHT_MAP_H

#include <GL/glut.h>

#include "core/material.h"
#include "core/texture.h"
#include "core/utils.h"

struct HeightMap
{
    struct Material material;
    struct Vector3d position;
    struct Vector3d scale;
    struct Texture texture;
    int n_rows;
    int n_columns;
    double* heights;
    struct Vector3d* normals;
    int display_list;
};

/**
 * Load height map from image file.
 */
void set_height_map(struct HeightMap* height_map, const char* filename, const char* texture, double unit, struct Material *material);

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

void set_height_map_scale(struct HeightMap* height_map, GLfloat x, GLfloat y, GLfloat z);

double get_terrain_height(struct HeightMap* height_map, GLfloat x, GLfloat z);

#endif // HEIGHT_MAP_H
