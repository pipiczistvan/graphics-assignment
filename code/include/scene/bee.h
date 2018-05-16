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

/**
 * Create bees.
 */
void create_bees(struct Bee bees[], const int count);

/**
 * Update bees.
 */
void update_bees(struct Bee bees[], int bee_count, struct Entity flowers[], const int flower_count, const struct HeightMap *terrain, const double delta);

/**
 * Draw bees.
 */
void draw_bees(const struct Bee bees[], const int count);

#endif // BEE_H