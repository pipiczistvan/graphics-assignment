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

void create_grasshoppers(struct Grasshopper grasshoppers[], const int grasshopper_count, const struct Entity *grasses, const int grass_count);

void update_grasshoppers(struct Grasshopper grasshoppers[], const int count, const struct HeightMap *terrain, const double delta);

void draw_grasshoppers(const struct Grasshopper grasshoppers[], const int count);

#endif // GRASSHOPPER_H