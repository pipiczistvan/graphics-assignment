#include "height_map.h"

#include <SOIL/SOIL.h>

#include <stdio.h>
#include <stdlib.h>

void set_height_map_attribute(GLfloat attribute[], GLfloat x, GLfloat y, GLfloat z)
{
    attribute[0] = x;
    attribute[1] = y;
    attribute[2] = z;
}

void set_height_map(struct HeightMap* height_map, const char* filename, const char* texture, double unit)
{
    Pixel* image;
    int width;
    int height;

    image = (Pixel *)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
    if (image == NULL) {
        printf("ERROR: Unable to load the height map from \"%s\" image file!\n", filename);
        return;
    }

    height_map->n_rows = height;
    height_map->n_columns = width;

    calc_height_map_heights(height_map, image);
    calc_height_map_normals(height_map, unit);


    set_height_map_position(height_map, 0.0, 0.0, 0.0);
    set_height_map_rotation(height_map, 0.0, 0.0, 0.0);
    set_height_map_scale(height_map, 1.0, 1.0, 1.0);
    load_texture(texture, &(height_map->texture));
}

void calc_height_map_heights(struct HeightMap* height_map, Pixel* image)
{
    int i;
    int n_heights;

    n_heights = height_map->n_rows * height_map->n_columns;
    height_map->heights = (double*)malloc(n_heights * sizeof(double));

    for (i = 0; i < n_heights; ++i) {
        height_map->heights[i] = (double)image[i][0] / 255.0;
    }
}

double get_height_map_value(const struct HeightMap* height_map, int row, int column)
{
    int index;

    index = row * height_map->n_columns + column;
    
    return height_map->heights[index];
}

void calc_height_map_normals(struct HeightMap* height_map, double unit)
{
    int i, j, index;
    int n_normals;
    double h1, h2;

    n_normals = height_map->n_rows * height_map->n_columns;
    height_map->normals = (struct Vector3d *)malloc(n_normals * sizeof(struct Vector3d));

    index = 0;
    for (i = 0; i < height_map->n_rows; ++i) {
        for (j = 0; j < height_map->n_columns; ++j) {
            height_map->normals[index].x = 0.0;
            height_map->normals[index].y = 0.0;
            height_map->normals[index].z = 0.0;
            if (i >= 1 && i <= height_map->n_rows - 1) {
                h1 = get_height_map_value(height_map, i - 1, j); 
                h2 = get_height_map_value(height_map, i + 1, j); 
                height_map->normals[index].z += (h1 - h2) / (2.0 * unit);
                height_map->normals[index].y += 1.0;
            }
            if (j >= 1 && j <= height_map->n_rows - 1) {
                h1 = get_height_map_value(height_map, i, j - 1); 
                h2 = get_height_map_value(height_map, i, j + 1); 
                height_map->normals[index].x = (h1 - h2) / (2.0 * unit);
                height_map->normals[index].y += 1.0;
            }
            ++index;
        }
    }
}

void get_height_map_normal(
    const struct HeightMap* height_map,
    int row, int column,
    struct Vector3d* normal)
{
    int index;

    index = row * height_map->n_columns + column;
    
    normal->x = height_map->normals[index].x;
    normal->y = height_map->normals[index].y;
    normal->z = height_map->normals[index].z;
}

void free_height_map(struct HeightMap* height_map)
{
    // TODO: Free the allocated memory!
}

void set_height_map_position(struct HeightMap* height_map, GLfloat x, GLfloat y, GLfloat z)
{
    set_height_map_attribute(height_map->position, x, y, z);
}

void set_height_map_rotation(struct HeightMap* height_map, GLfloat x, GLfloat y, GLfloat z)
{
    set_height_map_attribute(height_map->rotation, x, y, z);
}

void set_height_map_scale(struct HeightMap* height_map, GLfloat x, GLfloat y, GLfloat z)
{
    set_height_map_attribute(height_map->scale, x, y, z);
}
