#ifndef GRASSHOPPER_H
#define GRASSHOPPER_H

#include "core/entity.h"
#include "core/height_map.h"

struct Grasshopper
{
    struct Entity entity;
    double upward_speed;
    int in_air;
    int direction;
};

void create_grasshoppers(struct Grasshopper grasshoppers[], int grasshopper_count, struct Entity *grasses, int grass_count);

void update_grasshoppers(struct Grasshopper grasshoppers[], int count, struct HeightMap *terrain, double delta);

void draw_grasshoppers(struct Grasshopper grasshoppers[], int count);

#endif // GRASSHOPPER_H