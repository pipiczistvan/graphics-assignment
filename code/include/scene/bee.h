#ifndef BEE_H
#define BEE_H

#include "core/entity.h"
#include "core/height_map.h"

struct Bee
{
    struct Entity body;
    struct Entity left_wing;
    struct Entity right_wing;
    struct Vector3d target_position;
    struct Entity *target_flower;
    double floating_progression;
    double wing_progression;
    double eating_progression;
};

void create_bees(struct Bee bees[], int count);

void update_bees(struct Bee bees[], int bee_count, struct Entity flowers[], int flower_count, struct HeightMap *terrain, double delta);

void draw_bees(struct Bee bees[], int count);

#endif // BEE_H