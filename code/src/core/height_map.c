#include "core/height_map.h"
#include "core/draw.h"

#include <SOIL/SOIL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void set_height_map(struct HeightMap* height_map, const char* filename, const char* texture, double unit, struct Material *material)
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
    set_height_map_scale(height_map, 1.0, 1.0, 1.0);
    load_texture(texture, &(height_map->texture));
    height_map->material = *material;

    height_map->display_list = glGenLists(1);
    glNewList(height_map->display_list, GL_COMPILE);
    {
        draw_height_map(height_map);
    }
    glEndList();
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
    height_map->position.x = x;
    height_map->position.y = y;
    height_map->position.z = z;
}

void set_height_map_scale(struct HeightMap* height_map, GLfloat x, GLfloat y, GLfloat z)
{
    height_map->scale.x = x;
    height_map->scale.y = y;
    height_map->scale.z = z;
}

void get_height_map_normal_on_pos(const struct HeightMap* height_map, GLfloat x, GLfloat z, struct Vector3d* normal)
{
    double terrainX = x - height_map->position.x;
    double terrainZ = z - height_map->position.z;

    double tileSizeX = height_map->scale.x / height_map->n_rows;
    double tileSizeZ = height_map->scale.z / height_map->n_columns;

    int gridX = floor(terrainX / tileSizeX);
    int gridZ = floor(terrainZ / tileSizeZ);

    get_height_map_normal(height_map, gridX, gridZ, normal);
}

double get_terrain_height_on_pos(struct HeightMap* height_map, GLfloat x, GLfloat z)
{
    double terrainX = x - height_map->position.x;
    double terrainZ = z - height_map->position.z;

    double tileSizeX = height_map->scale.x / height_map->n_rows;
    double tileSizeZ = height_map->scale.z / height_map->n_columns;

    int gridX = floor(terrainX / tileSizeX);
    int gridZ = floor(terrainZ / tileSizeZ);

    if (gridX >= height_map->n_rows - 1 || gridZ >= height_map->n_columns - 1 || gridX < 0 || gridZ < 0) {
        return 0.0;
    }

    double xCoord = fmod(terrainX, tileSizeX);
    double zCoord = fmod(terrainZ, tileSizeZ);

    double terrainHeight;
    if (xCoord <= (1 - zCoord)) {
        terrainHeight = barry_centric(
                0.0, get_height_map_value(height_map, gridZ, gridX), 0.0,
                1.0, get_height_map_value(height_map, gridZ, gridX + 1), 0.0,
                0.0, get_height_map_value(height_map, gridZ + 1, gridX), 1.0,
                xCoord, zCoord);
    } else {
        terrainHeight = barry_centric(
                1.0, get_height_map_value(height_map, gridZ, gridX + 1), 0.0,
                1.0, get_height_map_value(height_map, gridZ + 1, gridX + 1), 1.0,
                0.0, get_height_map_value(height_map, gridZ + 1, gridX), 1.0,
                xCoord, zCoord);
    }

    return terrainHeight * height_map->scale.y + height_map->position.y;
}
