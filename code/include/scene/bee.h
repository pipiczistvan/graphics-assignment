#ifndef BEE_H
#define BEE_H

#include "core/entity.h"
#include "core/height_map.h"

struct Bee
{
    struct Entity body;
    struct Entity left_wing;
    struct Entity right_wing;
    double flying_progression;
    double wing_progression;
};

void create_bees(struct Bee bees[], int count);

void update_bees(struct Bee bees[], int count, struct HeightMap *terrain, double delta);

void draw_bees(struct Bee bees[], int count);

#endif // BEE_H