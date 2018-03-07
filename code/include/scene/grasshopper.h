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

void init_grasshoppers(struct Grasshopper grasshoppers[], int count);

void update_grasshoppers(struct Grasshopper grasshoppers[], int count, struct HeightMap *terrain, double delta);

void draw_grasshoppers(struct Grasshopper grasshoppers[], int count);

#endif // GRASSHOPPER_H