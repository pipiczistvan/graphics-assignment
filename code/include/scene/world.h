#ifndef WORLD_H
#define WORLD_H

#include "core/entity.h"
#include "core/height_map.h"
#include "core/light.h"
#include "core/fog.h"
#include "scene/grasshopper.h"
#include "scene/bee.h"

#define TERRAIN_SCALE_X 100
#define TERRAIN_SCALE_Y 6
#define GRASS_COUNT 30
#define WALL_COUNT_PER_SIDE 10
#define GRASSHOPPER_COUNT 10
#define BEE_COUNT 5
#define FLOWER_COUNT 10

struct World
{
    struct Fog fog;
    struct Light light;
    struct HeightMap terrain;
    struct Entity skybox;
    struct Entity grasses[GRASS_COUNT];
    struct Entity walls[WALL_COUNT_PER_SIDE * 4];
    struct Grasshopper grasshoppers[GRASSHOPPER_COUNT];
    struct Bee bees[BEE_COUNT];
    struct Entity flowers[FLOWER_COUNT];
};

/**
 * Initialize world.
 */
void init_world(struct World *world);

/**
 * Update world.
 */
void update_world(struct World *world, double delta);

/**
 * Draw world.
 */
void draw_world(const struct World *world);

#endif // WORLD_H