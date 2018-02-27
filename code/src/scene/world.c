#include "scene/world.h"

#include "core/draw.h"
#include "core/entity.h"
#include "core/height_map.h"

#define GRASS_COUNT 500

struct Entity skyboxEntity;
struct Entity grassEntities[GRASS_COUNT];

void create_grasses()
{
    set_entity(&grassEntities[0], "res/grass.obj", "res/grass.png", &DEFAULT);

    int i;
    for (i = 0; i < GRASS_COUNT; i++)
    {
        grassEntities[i].model = grassEntities[0].model;
        grassEntities[i].texture = grassEntities[0].texture;
        grassEntities[i].material = grassEntities[0].material;

        int x = rand() % 128 + -64;
        int z = rand() % 128 + -64;
        set_entity_position(&grassEntities[i], x, get_terrain_height(&terrain, x, z), z);
        set_entity_scale(&grassEntities[i], 0.5, 0.5, 0.5);
    }
}

void init_world()
{
    set_height_map(&terrain, "res/heightmap2.png", "res/grassy_ground.png", 6.0 / 128.0);
    set_height_map_scale(&terrain, 128.0, 6.0, 128.0);
    set_height_map_position(&terrain, -64.0, 0.0, -64.0);

    set_entity(&skyboxEntity, "res/skybox.obj", "res/skybox.png", &DEFAULT);
    set_entity_scale(&skyboxEntity, 500.0, 500.0, 500.0);
    create_grasses();
}

void update_world(double delta)
{
    skyboxEntity.rotation.y += 1.0 * delta;
}

void draw_world()
{
    glDisable(GL_FOG);
    draw_entity(&skyboxEntity);
    glEnable(GL_FOG);

    draw_fog();
    draw_height_map(&terrain);
    
    int i;
    for (i = 0; i < GRASS_COUNT; i++)
    {
        draw_entity(&grassEntities[i]);
    }
}
